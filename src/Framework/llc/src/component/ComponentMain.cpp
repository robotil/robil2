
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

void ComponentMain::handleWPDVelocity(const config::LLC::sub::WPDVelocity& msg)
{

	this->WPD_desired_speed.twist.linear.x = msg.twist.linear.x ;
	this->WPD_desired_speed.twist.angular.z = msg.twist.angular.z ;

	//std::cout<< "LLC say:" << this->WPD_desired_speed << std::endl;
}
	
void ComponentMain::handleWSMVelocity(const config::LLC::sub::WSMVelocity& msg)
{

	this->WSM_desired_speed.twist.linear.x = msg.twist.linear.x ;
	this->WSM_desired_speed.twist.angular.z = msg.twist.angular.z ;

	//std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handleBladePositionCommand(const config::LLC::sub::BladePositionCommand& msg)
{
	this->t_flag = 1 ;
	this->Blade_angle = msg ;
	//std::cout<< "Got blade command:" << msg << std::endl;
}
	

void ComponentMain::handleLocation(const config::LLC::sub::Location& msg)
{
	Per_pose = msg ;
	//std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handlePerVelocity(const config::LLC::sub::PerVelocity& msg)
{

	Per_measured_speed.twist.linear.x = msg.twist.linear.x ;
	Per_measured_speed.twist.angular.z = msg.twist.angular.z ;

//	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::publishEffortsTh(config::LLC::pub::EffortsTh& msg)
{
	_roscomm->publishEffortsTh(msg);
}
	

void ComponentMain::publishEffortsSt(config::LLC::pub::EffortsSt& msg)
{
	_roscomm->publishEffortsSt(msg);
}
	

void ComponentMain::publishEffortsJn(sensor_msgs::JointState& msg)
{
	_roscomm->publishEffortsJn(msg);
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

