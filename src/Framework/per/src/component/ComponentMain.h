
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <tf/tf.h>

// #include <per/lane.h>
// #include <per/roadLanes.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <dynamic_reconfigure/server.h>
#include <per/configConfig.h>

#include <ros/ros.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <boost/thread.hpp>























#include <std_msgs/String.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/tf.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/NavSatStatus.h>
//#include <gps_common/GPSFix.h>
//#include <gps_common/GPSStatus.h>
#include <sensor_msgs/JointState.h>
#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <robil_msgs/Path.h>
#include <robil_msgs/IEDLocation.h>
#include <robil_msgs/Map.h>
#include <robil_msgs/AssignManipulatorTask.h>
#include <robil_msgs/AssignMission.h>
#include <robil_msgs/AssignNavTask.h>
#include <robil_msgs/MissionAcceptance.h>
#include <sensor_msgs/JointState.h>
#include <robil_msgs/MultiLaserScan.h>
#include <robil_msgs/GpsSpeed.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>






using namespace std;
// using namespace per;
using namespace cv;


class HeightMap;

class ComponentMain {
	bool _inited;
	  ros::NodeHandle _nh;
	  ros::Publisher _pub_diagnostic;
	  boost::thread_group _maintains;
		ros::Subscriber _sub_Location;
		ros::Subscriber _sub_PerVelocity;
		ros::Subscriber _sub_SensorINS;
		ros::Subscriber _sub_SensorGPS;
		ros::Subscriber _sub_SensorCamL;
		ros::Subscriber _sub_SensorCamR;
		ros::Subscriber _sub_SensorWire;
		ros::Subscriber _sub_SensorSICK1;
		ros::Subscriber _sub_SensorSICK2;
		ros::Subscriber _sub_SensorIBEO;
		ros::Subscriber _sub_EffortsTh;
		ros::Subscriber _sub_EffortsSt;
		ros::Subscriber _sub_EffortsJn;
		ros::Subscriber _sub_GpsSpeed;
		ros::Publisher  _pub_GPS;
		ros::Publisher  _pub_INS;
		ros::Publisher  _pub_BladePosition;
		ros::Publisher  _pub_Map;
		ros::Publisher  _pub_MiniMap;
		ros::Publisher  _pub_VOOdometry;
		ros::Publisher  _pub_GpsSpeed;
        ros::Publisher  _pub_PC;
        ros::Publisher  _pub_PC_world;
        ros::Publisher _pub_hMap;
        ros::Publisher _pub_tMap;

	  bool init(int argc,char** argv);
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
    void handleLocation(const nav_msgs::Odometry& msg);
	void handlePerVelocity(const geometry_msgs::TwistStamped& msg);
	void handleSensorINS(const sensor_msgs::Imu& msg);
	void handleSensorGPS(const sensor_msgs::NavSatFix& msg);
	void handleSensorCamL(const sensor_msgs::Image& msg);
	void handleSensorCamR(const sensor_msgs::Image& msg);
	void handleSensorWire(const std_msgs::Float64& msg);
	void handleSensorSICK1(const sensor_msgs::LaserScan& msg);
	void handleSensorSICK2(const sensor_msgs::LaserScan& msg);
	void handleSensorIBEO(const robil_msgs::MultiLaserScan& msg);
	void handleEffortsTh(const std_msgs::Float64& msg);
	void handleEffortsSt(const std_msgs::Float64& msg);
	void handleEffortsJn(const sensor_msgs::JointState& msg);
	void publishGPS(sensor_msgs::NavSatFix& msg);
	void publishINS(sensor_msgs::Imu& msg);
	void publishBladePosition(sensor_msgs::JointState& msg);
	void publishMap(robil_msgs::Map& msg);
	void publishMiniMap(robil_msgs::Map& msg);
	void publishDebug(sensor_msgs::ImagePtr hmsg, sensor_msgs::ImagePtr tmsg);
	void publishVOOdometry(nav_msgs::Odometry& msg);
	void publishGpsSpeed(robil_msgs::GpsSpeed& msg);
	void handleGpsSpeed(const robil_msgs::GpsSpeed& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTransform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void configCallback(per::configConfig &config, uint32_t level);
	void handleSensorIBEOandINS(const sensor_msgs::ImuConstPtr& msgINS, const robil_msgs::MultiLaserScanConstPtr& msgIBEO);
	void setVisualize(char);
	void heartbeat();

	/**
	 * Walrus Changes:
	 */
	void setLanes(Mat m);
    per::configConfig _dyn_conf;
private:
      sensor_msgs::Imu _imuData;
      sensor_msgs::NavSatFix _gpsData;
      HeightMap* height_map;
      bool _should_pub;
      std_msgs::Header _should_pub_timeout;
      tf::TransformListener listener;

      
      
  
};
#endif /* COMPONENTMAIN_H_ */
