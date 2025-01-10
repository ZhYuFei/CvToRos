#include "cv_to_ros/img_projector.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

namespace cv_to_ros
{
projector::projector(const rclcpp::NodeOptions & options)
: Node("projector", options), count_(0)
{
  RCLCPP_INFO(this->get_logger(), "Projector is start");
  
  pub_debug_src = create_publisher<sensor_msgs::msg::Image>("/projector/picture", 1);
  
  cap = cv::VideoCapture("example/test.mp4");

  timer_ = create_wall_timer(20ms, std::bind(&projector::on_timer, this));

  if (!cap.isOpened()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to open vedio");
    rclcpp::shutdown();
  }
}

void projector::on_timer()
{
  cv::Mat src;
  cap.read(src);

  if (src.empty()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to capture frame");
    rclcpp::shutdown();
  }

  msg_debug_src.header.stamp = this->now();

  auto msg_img = cv_bridge::CvImage(msg_debug_src.header, "bgr8", src).toImageMsg();
  
  pub_debug_src->publish(*msg_img);

  RCLCPP_INFO(this->get_logger(), "Data send");
}

}  // namespace cv_to_ros

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(cv_to_ros::projector)
