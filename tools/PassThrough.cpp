/*********************************************
*滤波器：直通滤波器
*  功能 ：快速去除不在规定区间范围内的点； 
*  时间 ：2019.5.19
*  明天5.20，还在整理代码，单身狗的悲哀；
*********************************************/
#include <iostream>
#include <pcl/filters/passthrough.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>

using namespace std;

int main(int argc, char** argv)
{
	//读取点云
	pcl::PCDReader reader;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_fz(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_fy(new pcl::PointCloud<pcl::PointXYZRGB>);
	reader.read("E:/code/date/coal_final.pcd", *cloud);

	//直通滤波
	pcl::PassThrough<pcl::PointXYZRGB> pass_z;//设置滤波器对象
	//参数设置
	pass_z.setInputCloud(cloud);
	pass_z.setFilterFieldName("z");
	//z轴区间设置
	pass_z.setFilterLimits(2.3,6);
	//设置为保留还是去除
	pass_z.setFilterLimitsNegative(true);
	pass_z.filter(*cloud_fz);

	//直通滤波
	pcl::PassThrough<pcl::PointXYZRGB> pass_y;//设置滤波器对象
	//参数设置
	pass_y.setInputCloud(cloud_fz);
	pass_y.setFilterFieldName("y");
	//y轴区间设置
	pass_y.setFilterLimits(-1.5, 0.9);
    //设置为保留还是去除
	//pass_y.setFilterLimitsNegative(false);
	pass_y.filter(*cloud_fy);

	pcl::PCDWriter writer;
	writer.write("E:/code/date/coal_520.pcd",*cloud_fy);

	//可视化
	pcl::visualization::PCLVisualizer viewer("cloud_viewer");
	viewer.setBackgroundColor(255, 255, 255);
	viewer.addPointCloud(cloud_fy);
	//添加坐标轴
	//viewer.addCoordinateSystem();
	while (!viewer.wasStopped())
	{
		viewer.spinOnce();
	}

	return(0);

}