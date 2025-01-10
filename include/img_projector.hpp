#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <sensor_msgs/msg/image.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

namespace cv_to_ros
{

class projector : public rclcpp::Node
{
public:
  explicit projector(const rclcpp::NodeOptions & options);
  cv::VideoCapture cap;
protected:
  void on_timer();

private:
  size_t count_;
  sensor_msgs::msg::Image msg_debug_src;///< 发送图
  rclcpp::Publisher<decltype(msg_debug_src)>::SharedPtr pub_debug_src;
  
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace composition

