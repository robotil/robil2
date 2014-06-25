
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "../roscomm/RosComm.h"
#include "MoveBase.h"


ComponentMain::ComponentMain(int argc,char** argv)
{
	_events = 0;
	_roscomm = new RosComm(this,argc, argv);
	_move_base = new MoveBase(this);
}
ComponentMain::~ComponentMain() {
	if(_move_base) delete _move_base; _move_base=0;
	if(_roscomm) delete _roscomm; _roscomm=0;
}

void ComponentMain::handleGlobalPath(const config::PP::sub::GlobalPath& msg)
{
	_move_base -> on_path(msg);
}
	

void ComponentMain::handleBladePosition(const config::PP::sub::BladePosition& msg)
{
	//std::cout<< "PP say:" << msg << std::endl;
}
	

void ComponentMain::handleMap(const config::PP::sub::Map& msg)
{
	_move_base -> on_map(msg);
}
	

void ComponentMain::handleLocation(const config::PP::sub::Location& msg)
{
	_move_base -> on_position_update(msg);

}
	

void ComponentMain::publishLocalPath(config::PP::pub::LocalPath& msg)
{
	_roscomm->publishLocalPath(msg);
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

#include <decision_making/ROSTask.h>
void ComponentMain::set_events(decision_making::EventQueue* events){
	boost::mutex::scoped_lock l(_mt);
	_events = events;
}
void ComponentMain::rise_taskFinished(){
	boost::mutex::scoped_lock l(_mt);
	if(not _events) return;
	_events->raiseEvent("/CompleteTask");
}
void ComponentMain::rise_taskStarted(){
	boost::mutex::scoped_lock l(_mt);
	if(not _events) return;
	_events->raiseEvent("/TaskIsStarted");
}
void ComponentMain::rise_taskPaused(){
	boost::mutex::scoped_lock l(_mt);
	if(not _events) return;
	_events->raiseEvent("/TaskIsPaused");
}

void ComponentMain::cancel_navigation(){
	ROS_DEBUG("PP: cancel navigation");
	_move_base->deactivate(true);
}
void ComponentMain::pause_navigation(){
	ROS_DEBUG("PP: pause navigation");
	_move_base->deactivate();
}
void ComponentMain::resume_navigation(){
	_move_base -> activate();
}

