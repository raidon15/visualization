

// ROS
#include <rclcpp/rclcpp.hpp>

// C++
#include <string>
#include <vector>
#include <eigen3/Eigen/Geometry>
// Msgs
#include <geometry_msgs/msg/vector3.hpp>
// services
#include "std_srvs/srv/empty.hpp"
// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.hpp>
#include <rviz_visual_tools/remote_control.hpp>

#include "rclcpp/rclcpp.hpp"

#include <memory>

// For visualizing things in rviz
rviz_visual_tools::RvizVisualToolsPtr visual_tools_;

void sphere(const std::shared_ptr<std_srvs::srv::Empty::Request> request,
            std::shared_ptr<std_srvs::srv::Empty::Response> response)
{ // Create pose
  Eigen::Isometry3d pose;
  pose = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
  pose.translation() = Eigen::Vector3d(0.1, 0.1, 0.1);          // translate x,y,z

  // Publish arrow vector of pose
  visual_tools_->publishSphere(pose, rviz_visual_tools::RED, rviz_visual_tools::XXLARGE);
  // Don't forget to trigger the publisher!
  visual_tools_->trigger();
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  visual_tools_.reset(new rviz_visual_tools::RvizVisualTools("world", "/rviz_visual_tools", node));

  rclcpp::Service<std_srvs::srv::Empty>::SharedPtr service =
      node->create_service<std_srvs::srv::Empty>("publish_sphere", &sphere);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
