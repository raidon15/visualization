

// ROS
#include <rclcpp/rclcpp.hpp>

// C++
#include <string>
#include <vector>
#include <eigen3/Eigen/Geometry>
// Msgs
#include <geometry_msgs/msg/vector3.hpp>

// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.hpp>
#include <rviz_visual_tools/remote_control.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node_ = rclcpp::Node("rviz_demo");
    // For visualizing things in rviz
    rviz_visual_tools::RvizVisualToolsPtr visual_tools_;
    visual_tools_.reset(
        new rviz_visual_tools::RvizVisualTools("world", "/rviz_visual_tools", &node_));

    // Create pose
    Eigen::Isometry3d pose;
    pose = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
    pose.translation() = Eigen::Vector3d(0.1, 0.1, 0.1);          // translate x,y,z

    // Publish arrow vector of pose
    visual_tools_->publishArrow(pose, rviz_visual_tools::RED, rviz_visual_tools::LARGE);

    // Don't forget to trigger the publisher!
    visual_tools_->trigger();
    return 0;
}