
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 04. June 2015 09:56AM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "../roscomm/RosComm.h"
//#include "lliCtrlManager.h"

#include <boost/thread.hpp>



ComponentMain::ComponentMain(int argc,char** argv)
{
	//sleep (3);
	_roscomm = new RosComm(this,argc, argv);


	//ComponentMain::_this = this;


   // _driver_thread = new boost::thread(&ComponentMain::lliCtrlLoop);

    _driver_thread = (boost::thread *) NULL;



//
	//ros::Timer timer = nh.createTimer(ros::Duration(0.01), TimerCallback);
}

ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm;
	_roscomm=0;

}

void ComponentMain::workerFunc()
{
#ifdef STAM
	char ipAddr[16];
    string tmpStr = "192.168.101.3";

    strcpy (ipAddr, tmpStr.c_str());

   int lPort = 5355;
   int rPort = 4660;

   struct timeval start, end;
   long mtime, seconds, useconds;
   gettimeofday(&start, NULL);


 //  CLLI_Ctrl *clli = new CLLI_Ctrl ();
  //  clli->Init(ipAddr, lPort, rPort);
#endif
  _driver_thread = new boost::thread(boost::bind(&ComponentMain::lliCtrlLoop, this));

  //  boost::thread some_thread(boost::bind(&ComponentMain::lliCtrlLoop,this));
}

void ComponentMain::handleEffortsTh(const config::LLI::sub::EffortsTh& msg)
{
//	std::cout<< "LLI say:" << msg << std::endl;

}
	

void ComponentMain::handleEffortsSt(const config::LLI::sub::EffortsSt& msg)
{
//	std::cout<< "LLI say:" << msg << std::endl;
}
	

void ComponentMain::handleEffortsJn(const config::LLI::sub::EffortsJn& msg)
{
//	std::cout<< "LLI say:" << msg << std::endl;
}
	

void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(_report);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(header, _report);
}

void ComponentMain::lliCtrlLoop()
{
	std::cout << "Welcome to lliCtrlLoop Thread " << std::endl;
	//Init QinetiQ IP
		char ipAddr[16];
	    string tmpStr = "192.168.101.3";

	    strcpy (ipAddr, tmpStr.c_str());

	   int lPort = 5355;
	   int rPort = 4660;

	   struct timeval start, end;
	   long mtime, seconds, useconds;
	   gettimeofday(&start, NULL);


	   CLLI_Ctrl *clli = new CLLI_Ctrl ();
	    clli->Init(ipAddr, lPort, rPort);

	for(;;)
		{
		    sleep(0.01);
			try
			{
				if (!clli->PeriodicActivity())
							break;
			}
			catch(boost::thread_interrupted&)
			{
				std::cout << "Thread has stopped. Problems with QinetiQ" << std::endl;
				return;
			}
		}
#ifdef STAM
	 boost::posix_time::seconds workTime(3);
	 while (1) {;}

	    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

	while(1){
		sleep(0.01);
		if (!clli->PeriodicActivity())
			break;
	}

	boost::this_thread::sleep(workTime);

#endif
}
