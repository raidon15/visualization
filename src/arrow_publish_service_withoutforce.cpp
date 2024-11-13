
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
#include "visualization/srv/arrow_publish.hpp"

// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.hpp>
#include <rviz_visual_tools/remote_control.hpp>

#include "rclcpp/rclcpp.hpp"

#include <memory>
#include <iostream>


rviz_visual_tools::RvizVisualToolsPtr visual_tools_;

void print_arrow(const std::shared_ptr<visualization::srv::ArrowPublish::Request> request,
                 std::shared_ptr<visualization::srv::ArrowPublish::Response> response)
{
    visual_tools_->deleteAllMarkers();
    auto start_point = request->current_point;
    auto force_origin = request->force_origin;
    auto force_direction = request->force_direction;
    float norma = sqrt(pow(request->current_point.x - request->force_origin.x, 2) + pow(request->current_point.y - request->force_origin.y, 2) + pow(request->current_point.z - request->force_origin.z, 2));
    auto finish_point = geometry_msgs::msg::Point();
    finish_point.x = start_point.x + ((start_point.x - request->force_origin.x) * request->force) / norma;
    finish_point.y = start_point.y + ((start_point.y - request->force_origin.y) * request->force) / norma;
    finish_point.z = start_point.z + ((start_point.z - request->force_origin.z) * request->force) / norma;
    visual_tools_->publishArrow(start_point, finish_point, rviz_visual_tools::RED, rviz_visual_tools::XSMALL);
    visual_tools_->trigger();
    response->force = request->force;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "force: %f", response->force);
}

int main(int argc, char **argv)
{

    // initiate ROS2 communications
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    node_options.automatically_declare_parameters_from_overrides(true);
    auto node_ = rclcpp::Node::make_shared("publishing_arrow_rviz", node_options);
    auto service = node_->create_service<visualization::srv::ArrowPublish>("publish_arrow_withoutforce", &print_arrow);
    visual_tools_.reset(
        new rviz_visual_tools::RvizVisualTools("/world", "/force_arrow", node_));
    std::cout << "debug";
    
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "publish in /force_arrow topic");

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to publish arrow ");
    // arrow.print_arrow(0.0,0.0,0.0,-0.84,0.059,1.17);
    rclcpp::spin(node_);
    rclcpp::shutdown();
    return 0;
}