import launch
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    """Generate launch description with multiple components."""
    container = ComposableNodeContainer(
            name='cv_to_ros',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=[
                ComposableNode(
                    package='cv_to_ros',
                    plugin='cv_to_ros::projector',
                    name='projector')
            ],
            output='screen',
    )

    return launch.LaunchDescription([container])
