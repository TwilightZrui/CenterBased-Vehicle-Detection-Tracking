import rospy
import open3d as o3d
import numpy as np
import time
from sensor_msgs.msg import PointCloud2
from sensor_msgs import point_cloud2

global d
d = None

#回调获取点云话题数据
def callback_pcl(data):
    global d
    d=data

#转换点云格式
def Point_cloud():
    global d
    ss=point_cloud2.read_points(d, field_names=("x", "y", "z"), skip_nans=True)
    ss=list(ss)
    points=np.array(ss)
    return points
     
if __name__ == '__main__':
    rospy.init_node('points',anonymous=False)
    rospy.Subscriber('/lidar_center/velodyne_points', PointCloud2, callback_pcl)
    
    #创建可视化窗口
    vis = o3d.visualization.Visualizer()
    vis.create_window()
    #初始化o3d格式点云
    points3d = o3d.geometry.PointCloud()
    #设置点云大小，背景颜色
    render_option = vis.get_render_option()
    render_option.point_size = 1
    render_option.background_color = np.asarray([0, 0, 0])
    #加载点云到窗口里
    vis.add_geometry(points3d)
    
    to_reset = True
    
    rate = rospy.Rate(10)
    
    while not rospy.is_shutdown():
    #订阅的话题是否有数据
        if not d is None:
            points=Point_cloud()
            #获取points3d点云数据
            points3d.points = o3d.utility.Vector3dVector(points)
            #更新points3d
            vis.update_geometry(points3d)
            
            if to_reset:
                vis.reset_view_point(True)
                to_reset = False
            vis.poll_events()
            vis.update_renderer()
            
        else:
            print("not points_data")
            time.sleep(2)
        rate.sleep()

