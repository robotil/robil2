
/*
 * RosComm.h
 *
 *  Created on: Monday, 03. February 2014 03:30PM
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
#include <tf/tf.h>
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_VOOdometry;
	ros::Subscriber _sub_GPS;
	ros::Subscriber _sub_INS;
	ros::Subscriber _sub_PositionUpdate;
	ros::Subscriber _sub_LOCCommand;
	ros::Publisher  _pub_Odometry;
	ros::Publisher  _pub_LOCState;
	ros::Publisher  _pub_LOCComponentState;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void VOOdometryCallback(const config::LOC::sub::VOOdometry::ConstPtr &msg);
	void GPSCallback(const config::LOC::sub::GPS::ConstPtr &msg);
	void INSCallback(const config::LOC::sub::INS::ConstPtr &msg);
	void PositionUpdateCallback(const config::LOC::sub::PositionUpdate::ConstPtr &msg);
	void LOCCommandCallback(const config::LOC::sub::LOCCommand::ConstPtr &msg);
	void publishOdometry( config::LOC::pub::Odometry &msg);
	void publishLOCState( config::LOC::pub::LOCState &msg);
	void publishLOCComponentState( config::LOC::pub::LOCComponentState &msg);

  void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
  tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
};
#endif /* ROSCOMM_H_ */
