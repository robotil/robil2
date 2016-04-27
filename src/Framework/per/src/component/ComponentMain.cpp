
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "ComponentMain.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Bool.h>

#include "heightmap.h"
//#include "heightmap_projection.h"
#include "helpermath.h"
#include "mapper/mapper.h"
#include "rdbg.h"
#include "per/configConfig.h"
using namespace std; 
typedef string String;
typedef bool boolean;



ComponentMain::ComponentMain(int argc,char** argv)
: _inited(init(argc, argv))
{
_sub_Location=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Location","sub"), 10, &ComponentMain::handleLocation,this));
_sub_PerVelocity=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","PerVelocity","sub"), 10, &ComponentMain::handlePerVelocity,this));
_sub_SensorINS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorINS","sub"), 10, &ComponentMain::handleSensorINS,this));
_sub_SensorGPS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorGPS","sub"), 10, &ComponentMain::handleSensorGPS,this));
_sub_SensorCamL=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorCamL","sub"), 10, &ComponentMain::handleSensorCamL,this));
_sub_SensorCamR=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorCamR","sub"), 10, &ComponentMain::handleSensorCamR,this));
_sub_SensorWire=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorWire","sub"), 10, &ComponentMain::handleSensorWire,this));
_sub_SensorSICK1=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorSICK1","sub"), 10, &ComponentMain::handleSensorSICK1,this));
_sub_SensorSICK2=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorSICK2","sub"), 10, &ComponentMain::handleSensorSICK2,this));
_sub_SensorIBEO=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorIBEO","sub"), 10, &ComponentMain::handleSensorIBEO,this));
_sub_EffortsTh=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","EffortsTh","sub"), 10, &ComponentMain::handleEffortsTh,this));
_sub_EffortsSt=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","EffortsSt","sub"), 10, &ComponentMain::handleEffortsSt,this));
_sub_EffortsJn=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","EffortsJn","sub"), 10, &ComponentMain::handleEffortsJn,this));
_sub_GpsSpeed=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SensorGpsSpeed","sub"), 10, &ComponentMain::handleGpsSpeed,this));
_pub_GPS=ros::Publisher(_nh.advertise<config::PER::pub::GPS>(fetchParam(&_nh,"PER","GPS","pub"),10));
_pub_INS=ros::Publisher(_nh.advertise<config::PER::pub::INS>(fetchParam(&_nh,"PER","INS","pub"),10));
_pub_BladePosition=ros::Publisher(_nh.advertise<config::PER::pub::BladePosition>(fetchParam(&_nh,"PER","BladePosition","pub"),10));
_pub_Map=ros::Publisher(_nh.advertise<config::PER::pub::Map>(fetchParam(&_nh,"PER","Map","pub"),10));
_pub_MiniMap=ros::Publisher(_nh.advertise<config::PER::pub::MiniMap>(fetchParam(&_nh,"PER","MiniMap","pub"),10));
_pub_VOOdometry=ros::Publisher(_nh.advertise<config::PER::pub::VOOdometry>(fetchParam(&_nh,"PER","VOOdometry","pub"),10));
_pub_GpsSpeed=ros::Publisher(_nh.advertise<config::PER::pub::PerGpsSpeed>(fetchParam(&_nh,"PER","PerGpsSpeed","pub"),10));
_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));

	 Mapper::component = this;
     //Mapper::listener = new(tf::TransformListener);
     boost::thread mapper(Mapper::MainLoop, &this->_dyn_conf);
	 boost::this_thread::sleep(boost::posix_time::milliseconds(300));
	 boost::thread mapper2(Mapper::VisualizeLoop);
	 /// walrus func:
	  boost::this_thread::sleep(boost::posix_time::milliseconds(300));
	 //boost::thread mapper3(Mapper::StereoThread);
	 //boost::this_thread::sleep(boost::posix_time::milliseconds(300));
}
ComponentMain::~ComponentMain() {

    //delete Mapper::listener;
}
bool ComponentMain::init(int argc,char** argv){
	ros::init(argc,argv,"PER_node");
	return true;
}

void ComponentMain::handleLocation(const config::PER::sub::Location& msg)
{
  Mapper::handleLocation(msg);
}


void ComponentMain::setVisualize(char flags)
{
  Mapper::setVisualize((unsigned char)flags);
}

void ComponentMain::handlePerVelocity(const config::PER::sub::PerVelocity& msg)
{
}
	

void ComponentMain::handleSensorINS(const config::PER::sub::SensorINS& msg)
{
	_imuData = msg;
	config::PER::pub::INS msg2;
	msg2 = msg;
	publishINS(msg2);	
}
	

void ComponentMain::handleSensorGPS(const config::PER::sub::SensorGPS& msg)
{
	_gpsData = msg;
	config::PER::pub::GPS msg2;
	msg2 = msg;
	publishGPS(msg2);
}
	

void ComponentMain::handleSensorCamL(const config::PER::sub::SensorCamL& msg)
{
  Mapper::handleCamL(msg);
}
	

void ComponentMain::handleSensorCamR(const config::PER::sub::SensorCamR& msg)
{
  Mapper::handleCamR(msg);
}
	

void ComponentMain::handleSensorWire(const config::PER::sub::SensorWire& msg)
{
  //rdbg("wire");
}
	

void ComponentMain::handleSensorSICK1(const config::PER::sub::SensorSICK1& msg)
{
  Mapper::handleSickR(msg);
}
void ComponentMain::handleSensorSICK2(const config::PER::sub::SensorSICK2& msg)
{
  
  Mapper::handleSickL(msg);
}
	

void ComponentMain::handleSensorIBEO(const config::PER::sub::SensorIBEO& msg)
{
  int check=0; 
  ros::param::param("/LOC/Ready",check,0);
  if(!check) return;
  Mapper::handleIBEO(msg);
}
	


void ComponentMain::handleEffortsTh(const config::PER::sub::EffortsTh& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleEffortsSt(const config::PER::sub::EffortsSt& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleEffortsJn(const config::PER::sub::EffortsJn& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::publishGPS(config::PER::pub::GPS& msg)
{
	msg = _gpsData;
	//std::cout << "publishing: " << msg << std::endl;
	_pub_GPS.publish(msg);
}
	

void ComponentMain::publishINS(config::PER::pub::INS& msg)
{
	msg = _imuData;
	_pub_INS.publish(msg);
}
	

void ComponentMain::publishBladePosition(config::PER::pub::BladePosition& msg)
{
	_pub_BladePosition.publish(msg);
}
	

void ComponentMain::publishMap(config::PER::pub::Map& msg)
{
  _pub_Map.publish(msg);
}
	

void ComponentMain::publishMiniMap(config::PER::pub::MiniMap& msg)
{
   _pub_MiniMap.publish(msg);
}
	

void ComponentMain::publishVOOdometry(config::PER::pub::VOOdometry& msg)
{
	_pub_VOOdometry.publish(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform ComponentMain::getLastTransform(std::string srcFrame, std::string distFrame){
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

void ComponentMain::handleGpsSpeed(const config::PER::sub::SensorGpsSpeed& msg)
{
	config::PER::pub::PerGpsSpeed msg2;
	msg2 = msg;
	publishGpsSpeed(msg2);
}

void ComponentMain::publishGpsSpeed(config::PER::pub::PerGpsSpeed& msg)
{
	_pub_GpsSpeed.publish(msg);
}

/**
 * Walrus Changes:
 */
void ComponentMain::setLanes(Mat m)
{
  Mapper::setLanes(m);
}

void ComponentMain::configCallback(per::configConfig &config, uint32_t level)
{
  // Set class variables to new values. They should match what is input at the dynamic reconfigure GUI.
    _dyn_conf = config;
    char flags = 0;
    if (config.heightMap)
        flags += 1;
    if (config.typeMap)
        flags += 8;
    Mapper::setVisualize((unsigned char)flags);
}
void ComponentMain::heartbeat(){
	using namespace boost::posix_time;
	ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
	double hz = HEARTBEAT_FREQUANCY;
	while(ros::ok()){
		boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
		std_msgs::String msg;
		msg.data = "PER";
		_pub.publish(msg);
	    boost::this_thread::sleep(stop_time);
	}
}
