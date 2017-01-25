/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 04. June 2015 09:56AM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
//#include "lliCtrlManager.h"
#include <pthread.h>

#include <boost/thread.hpp>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#define TEST_HEARTBEAT

ComponentMain::ComponentMain(int argc,char** argv)
: _inited(init(argc, argv))
{
  if (
        argc > 3 || //for roslaunch (min of argc is 3)
        (argc < 3 && argc > 1) // for rosrun (min of argc is 1)
      )
    {
        //if IP received from command line (as parameter), change the default (localhost - 127.0.0.1)
        IPADDR = argv[1];
    }
    else
    	IPADDR = "127.0.0.1";

    _sub_EffortsTh=ros::Subscriber(_nh.subscribe("/LLC/EFFORTS/Throttle", 10, &ComponentMain::handleEffortsTh,this));
    _sub_EffortsSt=ros::Subscriber(_nh.subscribe("/LLC/EFFORTS/Steering", 10, &ComponentMain::handleEffortsSt,this));
    _sub_EffortsJn=ros::Subscriber(_nh.subscribe("/LLC/EFFORTS/Joints", 10, &ComponentMain::handleEffortsJn,this));
	_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
	_pub_connected_to_platform=ros::Publisher(_nh.advertise<std_msgs::Bool>("/Sahar/link_with_platform",100));
	//_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));
	//Replace the thread group with a simple pthread because there is a SIGEV otherwise
    // and I didn't find the reason.
    // With pthread, it seems to work.
    _myHeartbeatThread = (pthread_t) NULL;

    //_maintains=NULL;
    _clli = (CLLI_Ctrl *) NULL;
    is_ready = false;
    SetState(State_Off);
    //ComponentMain::_this = this;

    _mythread = (pthread_t)NULL;
    //ros::Timer timer = nh.createTimer(ros::Duration(0.01), TimerCallback);
}

ComponentMain::~ComponentMain() {

	if(_clli) delete _clli;
	_clli=0;
	if (_mythread) {
		std::cout<< "destructor _mythread" << std::endl;
		pthread_cancel(_mythread);
		_mythread = (pthread_t)NULL;
	}
#ifdef TEST_HEARTBEAT
	if (_myHeartbeatThread) {
		pthread_cancel(_myHeartbeatThread);
		_myHeartbeatThread = (pthread_t)NULL;
	}
#endif
}
bool ComponentMain::init(int argc,char** argv){
	ros::init(argc,argv,"LLI_node");
	return true;
}

void ComponentMain::setNotReady(){
    _clli->DriveControlRelease();
    _clli->ManipulatorControlRelease();
        is_ready=false;
        SetState(State_Standby);
}

void ComponentMain::setReady() {
	//Add Semaphore here
	SetState(State_Standby);
	if (_clli->GetDriveCurrentState() == lli_State_Standby)
		_clli->DriveControlRequest();

	if (_clli->GetManipulatorCurrentState() == lli_State_Standby)
		_clli->ManipulatorControlRequest();

	if ((_clli->GetDriveCurrentState() == lli_State_Ready) &&
			(_clli->GetManipulatorCurrentState() == lli_State_Ready ))
				is_ready=true;
}


void ComponentMain::checkReady(){
	int count=0;

	if (is_ready == true){
		SetState(State_Ready);
		return;
	}
	else setReady();
}

void ComponentMain::SetState(CS_STATE inState){
	_state=inState;
}

bool ComponentMain::StateNotReady(){
	bool retval=true;
	if (_state==State_Ready){
		retval=false;
	}
	return retval;
}

bool ComponentMain::StateIsInit(){
	bool retval=false;
	if (_state==State_Init){
		retval=true;
	}
	return retval;
}

CS_STATE ComponentMain::GetComponentState()
{

	return _state;
}

bool ComponentMain::IsCLLIStillInInit()
{
	bool retval = false;
	if (_clli == (CLLI_Ctrl *)NULL) return true;
	if (_clli->GetDriveCurrentState() == lli_State_Init) retval=true;
	if (_clli->GetManipulatorCurrentState() == lli_State_Init) retval=true;

	return retval;
}

void ComponentMain::releaseDriverAndManipulator()
{
	_clli->DriveControlRelease();
	_clli->ManipulatorControlRelease();
}
void ComponentMain::workerFunc()
{

    SetState(State_Init);

    pthread_create(&_mythread, NULL, &callPThread, this);

#ifdef TEST_HEARTBEAT
	pthread_create(&_myHeartbeatThread, NULL, &callHeartbeat, this);
	//_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));
#endif


}

void ComponentMain::handleEffortsTh(const std_msgs::Float64& msg)
{
//	std::cout<< "LLI say:" << msg << std::endl;
	if (!is_ready){
		//Ignore Topic
		return;
	}
	short data;
	data = 100*msg.data;
	_clli->SetThrottelRequest(data);

}


void ComponentMain::handleEffortsSt(const std_msgs::Float64& msg)
{
//	std::cout<< "LLI say:" << msg << std::endl;
	if (!is_ready){
		//Ignore Topic
		return;
	}
	short data;
	data = 100*msg.data;
	_clli->SetSteeringRequest(data);
}


void ComponentMain::handleEffortsJn(const sensor_msgs::JointState& msg)
{
//	std::cout<< "LLI say:" << msg << std::endl;

	if (!is_ready){
		//Ignore Topic
		return;
	}
	short data1, data2;


		//= msg.position[i];
			data1 = msg.effort[1];
			data2 = msg.effort[2];
			_clli->SetJointRequest(data1, data2);

}


void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}

tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	tf::StampedTransform _tf;
		static tf::TransformListener listener;
		try {
		    listener.waitForTransform(distFrame, srcFrame, ros::Time(0), ros::Duration(10.0) );
		    listener.lookupTransform(distFrame, srcFrame, ros::Time(0), _tf);
		} catch (tf::TransformException& ex) {
		    ROS_ERROR("%s",ex.what());
		}
		return _tf;
}

void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
		msg.status.push_back(_report);
		_pub_diagnostic.publish(msg);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
		msg.header = header;
		msg.status.push_back(_report);
		_pub_diagnostic.publish(msg);
}
void ComponentMain::heartbeat(){
	using namespace boost::posix_time;
	ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
	double hz = HEARTBEAT_FREQUENCY;
	double cycle = (1/hz);
	ros::Duration oneSec(cycle);
//	ros::Duration oneSec(1.0);

	while(ros::ok()){
		//boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
		std_msgs::String msg;
		msg.data = "LLI";
		_pub.publish(msg);
		oneSec.sleep();
		//boost::this_thread::sleep(stop_time);
	}
}

void ComponentMain::publishConnectedToPlatform(std_msgs::Bool& msg){
	_pub_connected_to_platform.publish(msg);
}

void * ComponentMain::callHeartbeat(void * pParam)
{
	ComponentMain *myHandle = (ComponentMain *) (pParam);

	myHandle->heartbeat();

}

void * ComponentMain::callPThread(void * pParam)
{
	ComponentMain *myHandle = (ComponentMain *) (pParam);

	myHandle->lliCtrlLoop();

}

void ComponentMain::lliCtrlLoop()
{
	std::cout << "Welcome to lliCtrlLoop Thread " << std::endl;
	//Init QinetiQ IP
	    char ipAddr[16];
//	    string tmpStr = "192.168.101.3";
	    string tmpStr = IPADDR;
	    bool retval;

	    strcpy (ipAddr, tmpStr.c_str());

	   int lPort = 5355;
	   int rPort = 4660;

	   struct timeval start, end;
	   long mtime, seconds, useconds;
	   gettimeofday(&start, NULL);


	  // CLLI_Ctrl *clli = new CLLI_Ctrl ();
	   _clli = new CLLI_Ctrl ();
	   retval=_clli->Init(ipAddr, lPort, rPort);
	   if (retval == false){
		   //Failing to Init CLLI_Ctrl
		   return;
	   }

	   //QinitiQ has been properly initialized.
	ros::Rate r(100);
    std_msgs::Bool msg;
    //int count=0;
        while (ros::ok())
                {
                    r.sleep();
                    if (StateNotReady()){
                                                msg.data=false;
                                        }
                    else msg.data=true;
                    //if (count > 1000) msg.data=true;
                    //count++;
                        publishConnectedToPlatform(msg);
                        if (!_clli->PeriodicActivity())
                                                        break;


                }

}
