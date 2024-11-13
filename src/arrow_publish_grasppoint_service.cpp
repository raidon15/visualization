
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
#include "force_node.h"

rviz_visual_tools::RvizVisualToolsPtr visual_tools_;


void print_arrow(const std::shared_ptr<visualization::srv::ArrowPublish::Request> request,
                 std::shared_ptr<visualization::srv::ArrowPublish::Response> response)
{
  visual_tools_->deleteAllMarkers();
  auto start_point = request->current_point;
  auto force_origin = request->force_origin;
  auto force_direction = request->force_direction;

  auto finish_point = geometry_msgs::msg::Point();

  for (float angle = 0; angle <= 360; angle = angle + 10)
  {
    CoordenadasRectangulares posicion = EsfericasRectangulares(angle, -force_origin.x, force_origin.z, force_origin.y, -force_origin.x);


    start_point.x = -posicion.z;
    start_point.y = posicion.y;
    start_point.z = posicion.x;


    auto fuerza = CalculoFuerza( start_point.z, start_point.y, -start_point.x,
                                 force_origin.z, force_origin.y,-force_origin.x,
                                force_direction);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "alfa: '%f'Fuerza: '%lf'", angle, fuerza);

    float norma = sqrt(pow(start_point.x - force_origin.x, 2) 
                      + pow(start_point.y - force_origin.y, 2) 
                      + pow(start_point.z - force_origin.z, 2));

                      
    finish_point.x = start_point.x + ((start_point.x - force_origin.x) * fuerza) / norma;
    finish_point.y = start_point.y + ((start_point.y - force_origin.y) * fuerza) / norma;
    finish_point.z = start_point.z + ((start_point.z - force_origin.z) * fuerza) / norma;
    visual_tools_->publishArrow(start_point, finish_point, rviz_visual_tools::RED, rviz_visual_tools::XSMALL);
    visual_tools_->trigger();
    // moveit_visual_tools.publishXArrow(pose1, rviz_visual_tools::RED, rviz_visual_tools::LARGE, fuerza1d);
    // RCLCPP_INFO(LOGGER, "alfa: '%f'Fuerza: '%lf'", j, fuerza1d);
    response->force = fuerza;
  }
}
CoordenadasRectangulares posicion_;

int main(int argc, char** argv)
{
  // initiate ROS2 communications
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  node_options.automatically_declare_parameters_from_overrides(true);
  auto node_ = rclcpp::Node::make_shared("grasp_point_arrow", node_options);
  auto service = node_->create_service<visualization::srv::ArrowPublish>("publish_grasp_point_arrow", &print_arrow);

 

  visual_tools_.reset(new rviz_visual_tools::RvizVisualTools("/world", "/force_arrow_grasp_point", node_));
  std::cout << "debug";

  // arrow.print_arrow(0.0,0.0,0.0,-0.84,0.059,1.17);
  rclcpp::spin(node_);
  rclcpp::shutdown();
  return 0;
}