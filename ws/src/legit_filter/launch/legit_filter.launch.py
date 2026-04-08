from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pkg = get_package_share_directory('legit_filter')
    params_file = os.path.join(pkg, 'config', 'params.yaml')

    return LaunchDescription([
        Node(
            package='legit_filter',
            executable='legit_filter',
            name='legit_filter',
            output='screen',
            parameters=[params_file],
            arguments=['--ros-args','--log-level','info'] #For plugin logs
        ),

    ])