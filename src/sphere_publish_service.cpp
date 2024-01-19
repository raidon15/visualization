

// ROS
#include <rclcpp/rclcpp.hpp>

// C++
#include <string>
#include <vector>
#include <eigen3/Eigen/Geometry>
// Msgs
#include <geometry_msgs/msg/vector3.hpp>
#include "visualization/srv/marker_publish.hpp"
// services
#include "std_srvs/srv/empty.hpp"
// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.hpp>
#include <rviz_visual_tools/remote_control.hpp>

#include "rclcpp/rclcpp.hpp"

#include <memory>

// For visualizing things in rviz
rviz_visual_tools::RvizVisualToolsPtr visual_tools_;

void sphere(const std::shared_ptr<visualization::srv::MarkerPublish::Request> request,
            std::shared_ptr<visualization::srv::MarkerPublish::Response> response)
{  // Create pose
  visual_tools_->deleteMarker("next_goal",1);
  Eigen::Isometry3d pose;
  pose = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitY());  // rotate along X axis by 45 degrees
  pose.translation() =
      Eigen::Vector3d(request->pose.position.x, request->pose.position.y, request->pose.position.z);  // translate x,y,z

  rviz_visual_tools::Colors color;
  // Publish arrow vector of pose
  if (request->color_value == 1)
  {
    color = rviz_visual_tools::RED;
  }
  else if (request->color_value == 2)
  {
    color = rviz_visual_tools::GREEN;
  }
  else
  {
    color = rviz_visual_tools::BLUE;
  }
  visual_tools_->publishSphere(pose, color, rviz_visual_tools::XXLARGE,request->marker_ns,1);
  // Don't forget to trigger the publisher!
  visual_tools_->trigger();
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("publish_marker_server");

  visual_tools_.reset(new rviz_visual_tools::RvizVisualTools("world", "/rviz_visual_tools", node));

  rclcpp::Service<visualization::srv::MarkerPublish>::SharedPtr service =
      node->create_service<visualization::srv::MarkerPublish>("publish_sphere", &sphere);


  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "publish in /rviz_visual_tools topic");

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to publish sphere ");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
