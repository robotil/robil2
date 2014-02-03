
/*
 * ComponentMain.cpp
 *
 *  Created on: Monday, 03. February 2014 03:30PM
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

void ComponentMain::handleOdometry(const config::OCU::sub::Odometry& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleBladPosition(const config::OCU::sub::BladPosition& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleMap(const config::OCU::sub::Map& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleWPDDecisions(const config::OCU::sub::WPDDecisions& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleLocalPath(const config::OCU::sub::LocalPath& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleIEDDetectionEvent(const config::OCU::sub::IEDDetectionEvent& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handlePlatformState(const config::OCU::sub::PlatformState& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleSoftwareState(const config::OCU::sub::SoftwareState& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleSensorsState(const config::OCU::sub::SensorsState& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleSMMEMissionState(const config::OCU::sub::SMMEMissionState& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::handleMissionAcceptance(const config::OCU::sub::MissionAcceptance& msg)
{
	std::cout<< "OCU say:" << msg << std::endl;
}
	

void ComponentMain::publishPositionUpdate(config::OCU::pub::PositionUpdate& msg)
{
	_roscomm->publishPositionUpdate(msg);
}
	

void ComponentMain::publishSMMECommand(config::OCU::pub::SMMECommand& msg)
{
	_roscomm->publishSMMECommand(msg);
}
	

void ComponentMain::publishSMMEControlMode(config::OCU::pub::SMMEControlMode& msg)
{
	_roscomm->publishSMMEControlMode(msg);
}
	

void ComponentMain::publishNavigationTask(config::OCU::pub::NavigationTask& msg)
{
	_roscomm->publishNavigationTask(msg);
}
	

void ComponentMain::publishManipulationTask(config::OCU::pub::ManipulationTask& msg)
{
	_roscomm->publishManipulationTask(msg);
}
	

void ComponentMain::publishMissionTask(config::OCU::pub::MissionTask& msg)
{
	_roscomm->publishMissionTask(msg);
}
	

void ComponentMain::publishCustomPath(config::OCU::pub::CustomPath& msg)
{
	_roscomm->publishCustomPath(msg);
}
	

void ComponentMain::publishTeleoperationControlMode(config::OCU::pub::TeleoperationControlMode& msg)
{
	_roscomm->publishTeleoperationControlMode(msg);
}
	

void ComponentMain::publishTeleoperationThrottle(config::OCU::pub::TeleoperationThrottle& msg)
{
	_roscomm->publishTeleoperationThrottle(msg);
}
	

void ComponentMain::publishTeleoperationSteering(config::OCU::pub::TeleoperationSteering& msg)
{
	_roscomm->publishTeleoperationSteering(msg);
}
	

void ComponentMain::publishTeleoperationJoints(config::OCU::pub::TeleoperationJoints& msg)
{
	_roscomm->publishTeleoperationJoints(msg);
}
	

void ComponentMain::publishIEDDetectionEvent(config::OCU::pub::IEDDetectionEvent& msg)
{
	_roscomm->publishIEDDetectionEvent(msg);
}
	

void ComponentMain::publishIEDLocation(config::OCU::pub::IEDLocation& msg)
{
	_roscomm->publishIEDLocation(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);;
}
