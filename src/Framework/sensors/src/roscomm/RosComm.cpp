
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

	_pub_Sensor_SICK_1=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_SICK_1>(fetchParam(&_nh,"SENSORS","Sensor_SICK_1","pub"),10));
	_pub_Sensor_SICK_2=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_SICK_2>(fetchParam(&_nh,"SENSORS","Sensor_SICK_2","pub"),10));
	_pub_Sensor_IBEO_1=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_IBEO_1>(fetchParam(&_nh,"SENSORS","Sensor_IBEO_1","pub"),10));
	_pub_Sensor_IBEO_2=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_IBEO_2>(fetchParam(&_nh,"SENSORS","Sensor_IBEO_2","pub"),10));
	_pub_Sensor_IBEO_3=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_IBEO_3>(fetchParam(&_nh,"SENSORS","Sensor_IBEO_3","pub"),10));
	_pub_Sensor_IBEO_4=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_IBEO_4>(fetchParam(&_nh,"SENSORS","Sensor_IBEO_4","pub"),10));
	_pub_Sensor_CAM_R=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_CAM_R>(fetchParam(&_nh,"SENSORS","Sensor_CAM_R","pub"),10));
	_pub_Sensor_CAM_L=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_CAM_L>(fetchParam(&_nh,"SENSORS","Sensor_CAM_L","pub"),10));
	_pub_Sensor_WIRE=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_WIRE>(fetchParam(&_nh,"SENSORS","Sensor_WIRE","pub"),10));
	_pub_Sensor_GPS=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_GPS>(fetchParam(&_nh,"SENSORS","Sensor_GPS","pub"),10));
	_pub_Sensor_INS=ros::Publisher(_nh.advertise<config::SENSORS::pub::Sensor_INS>(fetchParam(&_nh,"SENSORS","Sensor_INS","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"SENSORS_node");
	return true;
}



void RosComm::publishSensor_SICK_1( config::SENSORS::pub::Sensor_SICK_1 &msg)
{
	_pub_Sensor_SICK_1.publish(msg);
}
	

void RosComm::publishSensor_SICK_2( config::SENSORS::pub::Sensor_SICK_2 &msg)
{
	_pub_Sensor_SICK_2.publish(msg);
}
	

void RosComm::publishSensor_IBEO_1( config::SENSORS::pub::Sensor_IBEO_1 &msg)
{
	_pub_Sensor_IBEO_1.publish(msg);
}
	

void RosComm::publishSensor_IBEO_2( config::SENSORS::pub::Sensor_IBEO_2 &msg)
{
	_pub_Sensor_IBEO_2.publish(msg);
}
	

void RosComm::publishSensor_IBEO_3( config::SENSORS::pub::Sensor_IBEO_3 &msg)
{
	_pub_Sensor_IBEO_3.publish(msg);
}
	

void RosComm::publishSensor_IBEO_4( config::SENSORS::pub::Sensor_IBEO_4 &msg)
{
	_pub_Sensor_IBEO_4.publish(msg);
}
	

void RosComm::publishSensor_CAM_R( config::SENSORS::pub::Sensor_CAM_R &msg)
{
	_pub_Sensor_CAM_R.publish(msg);
}
	

void RosComm::publishSensor_CAM_L( config::SENSORS::pub::Sensor_CAM_L &msg)
{
	_pub_Sensor_CAM_L.publish(msg);
}
	

void RosComm::publishSensor_WIRE( config::SENSORS::pub::Sensor_WIRE &msg)
{
	_pub_Sensor_WIRE.publish(msg);
}
	

void RosComm::publishSensor_GPS( config::SENSORS::pub::Sensor_GPS &msg)
{
	_pub_Sensor_GPS.publish(msg);
}
	

void RosComm::publishSensor_INS( config::SENSORS::pub::Sensor_INS &msg)
{
	_pub_Sensor_INS.publish(msg);
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
