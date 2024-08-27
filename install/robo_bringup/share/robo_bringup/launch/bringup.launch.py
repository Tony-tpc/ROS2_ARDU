import os
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
# 导入启动另一个launch文件所需要的库
from launch.actions import IncludeLaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    ld = LaunchDescription()

    # 下位机
    ros2_arduino_bridge_share = get_package_share_directory('ros2_arduino_bridge')
    ros2_arduino_bridge_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(ros2_arduino_bridge_share, 'ros2_arduino.launch.py')),
    )

    # robo_description
    robo_description_share = get_package_share_directory('robo_description')
    robo_description_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(robo_description_share, 'launch', 'robo_description.launch.py')),
    )

    # radar
    radar_share = get_package_share_directory('ldlidar_sl_ros2')  
    radar_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(radar_share, 'launch', 'ld14.launch.py')),
    )

    # SLAM_TOOLBOX
    slam_toolbox_share = get_package_share_directory('slam_toolbox')  
    slam_toolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(slam_toolbox_share, 'launch', 'online_async_launch.py')),
    )
    
    

    ld.add_action(ros2_arduino_bridge_launch)
    ld.add_action(robo_description_launch)
    ld.add_action(radar_launch)
    ld.add_action(slam_toolbox_launch)
    return ld