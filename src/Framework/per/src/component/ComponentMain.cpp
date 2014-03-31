
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "../roscomm/RosComm.h"
ComponentMain::ComponentMain(int argc,char** argv)
{
	_roscomm = new RosComm(this,argc, argv);
}
ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm; _roscomm=0;
}

void ComponentMain::handleLocation(const config::PER::sub::Location& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handlePerVelocity(const config::PER::sub::PerVelocity& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensorINS(const config::PER::sub::SensorINS& msg)
{
	_imuData = msg;
	//std::cout<< "PER say:" << msg << std::endl;
	config::PER::pub::INS msg2;
	msg2 = msg;
	publishINS(msg2);
	
}
	

void ComponentMain::handleSensorGPS(const config::PER::sub::SensorGPS& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
	_gpsData = msg;
	config::PER::pub::GPS msg2;
	msg2 = msg;
	publishGPS(msg2);	
}
	

void ComponentMain::handleSensorCamL(const config::PER::sub::SensorCamL& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensorCamR(const config::PER::sub::SensorCamR& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensorWire(const config::PER::sub::SensorWire& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensorSICK(const config::PER::sub::SensorSICK& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
	
}
	

void ComponentMain::handleSensorIBEO(const config::PER::sub::SensorIBEO& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
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
	_roscomm->publishGPS(msg);
}
	

void ComponentMain::publishINS(config::PER::pub::INS& msg)
{
	msg = _imuData;
	_roscomm->publishINS(msg);
}
	

void ComponentMain::publishBladePosition(config::PER::pub::BladePosition& msg)
{
	_roscomm->publishBladePosition(msg);
}
	

void ComponentMain::publishMap(config::PER::pub::Map& msg)
{
	_roscomm->publishMap(msg);
}
	

void ComponentMain::publishMiniMap(config::PER::pub::MiniMap& msg)
{
	_roscomm->publishMiniMap(msg);
}
	

void ComponentMain::publishVOOdometry(config::PER::pub::VOOdometry& msg)
{
	_roscomm->publishVOOdometry(msg);
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
