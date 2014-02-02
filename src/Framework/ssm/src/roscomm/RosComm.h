
/*
 * RosComm.h
 *
 *  Created on: Sunday, 02. February 2014 10:15AM
 *      Author: autogenerated
 */
#ifndef ROSCOMM_H_
#define ROSCOMM_H_
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <ParameterTypes.h>
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_MissionStatus;
	ros::Publisher  _pub_StatusData;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void MissionStatusCallback(const config::SSM::sub::MissionStatus::ConstPtr &msg);
	void publishStatusData( config::SSM::pub::StatusData &msg);

};
#endif /* ROSCOMM_H_ */