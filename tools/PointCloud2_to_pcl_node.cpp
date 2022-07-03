#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include <iostream>
#include <sensor_msgs/PointCloud.h>
#include <pcl/point_types.h>                 //pcl点云格式头文件
#include <pcl_conversions/pcl_conversions.h> //转换
#include <pcl/point_cloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
using namespace std;

//将ros::PointCloud2格式的数据解析为pcl点云数据格式

void Callback(const sensor_msgs::PointCloud2& msg){
	//cout<<"height:"<<msg->height<<"    width:"<<msg->width<<endl;
	//解析data数据
	//sensor_msgs::PointCloud convertCloud;
	//sensor_msgs::convertPointCloud2ToPointCloud(msg,convertCloud);
	//for(int i=0;i<convertCloud.points.size();i++)
	//{
	//	cout<<convertCloud.points[i]<<endl;
	//}
	//cout<<"--------------------------------------------------"<<endl;
	pcl::PointCloud<pcl::PointXYZI> cloud_pcl_xyzi;
	pcl::fromROSMsg(msg, cloud_pcl_xyzi);
	for(int i=0;i<cloud_pcl_xyzi.points.size();i++)
	{
		cout<<cloud_pcl_xyzi.points[i]<<endl;
	}
}

int main(int argc,char ** argv){
	ros::init(argc,argv,"read_lidar_snow");
	ros::NodeHandle node;
	ros::Subscriber sub=node.subscribe("/wanji_point",100,Callback);
	ros::spin();
	return 0;
}