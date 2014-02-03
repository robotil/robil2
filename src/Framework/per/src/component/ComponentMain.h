
/*
 * ComponentMain.h
 *
 *  Created on: Monday, 03. February 2014 03:30PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleSensor_SICK_1(const config::PER::sub::Sensor_SICK_1& msg);
	void handleSensor_SICK_2(const config::PER::sub::Sensor_SICK_2& msg);
	void handleSensor_IBEO_1(const config::PER::sub::Sensor_IBEO_1& msg);
	void handleSensor_IBEO_2(const config::PER::sub::Sensor_IBEO_2& msg);
	void handleSensor_IBEO_3(const config::PER::sub::Sensor_IBEO_3& msg);
	void handleSensor_IBEO_4(const config::PER::sub::Sensor_IBEO_4& msg);
	void handleSensor_CAM_R(const config::PER::sub::Sensor_CAM_R& msg);
	void handleSensor_CAM_L(const config::PER::sub::Sensor_CAM_L& msg);
	void handleSensor_WIRE(const config::PER::sub::Sensor_WIRE& msg);
	void handleSensor_INS(const config::PER::sub::Sensor_INS& msg);
	void handleSensor_GPS(const config::PER::sub::Sensor_GPS& msg);
	void handleOdometry(const config::PER::sub::Odometry& msg);
	void handleTrottleEffort(const config::PER::sub::TrottleEffort& msg);
	void handleSteeringEffort(const config::PER::sub::SteeringEffort& msg);
	void handleJointsEffort(const config::PER::sub::JointsEffort& msg);
	void handlePERCommand(const config::PER::sub::PERCommand& msg);
	void publishMiniMap(config::PER::pub::MiniMap& msg);
	void publishMap(config::PER::pub::Map& msg);
	void publishINS(config::PER::pub::INS& msg);
	void publishGPS(config::PER::pub::GPS& msg);
	void publishBladPosition(config::PER::pub::BladPosition& msg);
	void publishVOOdometry(config::PER::pub::VOOdometry& msg);
	void publishSensorsCommand(config::PER::pub::SensorsCommand& msg);
	void publishPERSensorsState(config::PER::pub::PERSensorsState& msg);
	void publishPERComponentState(config::PER::pub::PERComponentState& msg);
  void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
  tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
};
#endif /* COMPONENTMAIN_H_ */
