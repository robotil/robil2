
/*
 * RosComm.cpp
 *
 *  Created on: Monday, 03. February 2014 03:30PM
 *      Author: autogenerated
 */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "RosComm.h"
#include "../component/ComponentMain.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
	: _inited(init(argc, argv)), _comp(comp)
{
	_sub_Odometry=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WSM","Odometry","sub"), 10, &RosComm::OdometryCallback,this));
	_sub_BladPosition=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WSM","BladPosition","sub"), 10, &RosComm::BladPositionCallback,this));
	_sub_WSMCommand=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WSM","WSMCommand","sub"), 10, &RosComm::WSMCommandCallback,this));
	_sub_WSMData=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WSM","WSMData","sub"), 10, &RosComm::WSMDataCallback,this));
	_pub_BladePositionCommand=ros::Publisher(_nh.advertise<config::WSM::pub::BladePositionCommand>(fetchParam(&_nh,"WSM","BladePositionCommand","pub"),10));
	_pub_WSMSpeed=ros::Publisher(_nh.advertise<config::WSM::pub::WSMSpeed>(fetchParam(&_nh,"WSM","WSMSpeed","pub"),10));
	_pub_WSMExecutionState=ros::Publisher(_nh.advertise<config::WSM::pub::WSMExecutionState>(fetchParam(&_nh,"WSM","WSMExecutionState","pub"),10));
	_pub_WSMComponentState=ros::Publisher(_nh.advertise<config::WSM::pub::WSMComponentState>(fetchParam(&_nh,"WSM","WSMComponentState","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"WSM_node");
	return true;
}


void RosComm::OdometryCallback(const config::WSM::sub::Odometry::ConstPtr &msg)
{
	_comp->handleOdometry(*msg);
}
	

void RosComm::BladPositionCallback(const config::WSM::sub::BladPosition::ConstPtr &msg)
{
	_comp->handleBladPosition(*msg);
}
	

void RosComm::WSMCommandCallback(const config::WSM::sub::WSMCommand::ConstPtr &msg)
{
	_comp->handleWSMCommand(*msg);
}
	

void RosComm::WSMDataCallback(const config::WSM::sub::WSMData::ConstPtr &msg)
{
	_comp->handleWSMData(*msg);
}
	

void RosComm::publishBladePositionCommand( config::WSM::pub::BladePositionCommand &msg)
{
	_pub_BladePositionCommand.publish(msg);
}
	

void RosComm::publishWSMSpeed( config::WSM::pub::WSMSpeed &msg)
{
	_pub_WSMSpeed.publish(msg);
}
	

void RosComm::publishWSMExecutionState( config::WSM::pub::WSMExecutionState &msg)
{
	_pub_WSMExecutionState.publish(msg);
}
	

void RosComm::publishWSMComponentState( config::WSM::pub::WSMComponentState &msg)
{
	_pub_WSMComponentState.publish(msg);
}
	
void RosComm::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform RosComm::getLastTrasform(std::string srcFrame, std::string distFrame){
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
