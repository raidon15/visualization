
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
struct CoordenadasEsfericas
{
  float alfa;
  float beta;
  float ro;
};

struct CoordenadasRectangulares
{
  float x;
  float y;
  float z;
};

CoordenadasEsfericas RectangulareEsfericas(float x, float y, float z, float x_prima = 0, float y_prima = 0,
                                           float z_prima = 0)
{
  float ro = sqrt(pow(x - x_prima, 2) + pow(y - y_prima, 2) + pow(z - z_prima, 2));
  float alfa = atan2(y - y_prima, x - x_prima);
  float alfa2 = alfa * 57.2958;
  // RCLCPP_INFO(LOGGER, "alfa calculada: '%f'", alfa2);
  float beta = acos(z / (sqrt(pow(x - x_prima, 2) + pow(y - y_prima, 2) + pow(z - z_prima, 2))));
  CoordenadasEsfericas esfericas;
  esfericas.alfa = alfa;
  esfericas.beta = beta;
  esfericas.ro = ro;
  return esfericas;
};

CoordenadasRectangulares EsfericasRectangulares(float alfa, float z, float x_prima = 0, float y_prima = 0,
                                                float z_prima = 0)
{
  alfa = 0.0174533 * alfa;
  float ro = 0.15;
  float x = ro * cos(alfa) + x_prima;
  float y = ro * sin(alfa) + y_prima;
  float z1 = z;
  CoordenadasRectangulares rectangulares;
  rectangulares.x = x;
  rectangulares.y = y;
  rectangulares.z = z1;
  return rectangulares;
};
float multi_valor(float angulo)
{
  if (angulo > 360)
  {
    return (angulo - 360);
  }
  else if (angulo < 0)
  {
    return (angulo + 360);
  }
  else
  {
    return angulo;
  }
}
float CalculoFuerza(float x, float y, float z, float x_prima = 0, float y_prima = 0, float z_prima = 0,
                    float direccion = 0)
{
  CoordenadasEsfericas esfericas = RectangulareEsfericas(x, y, z, x_prima, y_prima, z_prima);
  float alfa2 = multi_valor(esfericas.alfa * 57.2958);

  direccion = multi_valor(direccion);

  RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "alfa calculada: '%f' direccion: '%lf'", alfa2, direccion);
  float a = 0.5;
  float fuerza = 0.0;
  float min = multi_valor(direccion - 90);
  float max = multi_valor(direccion + 90);
  RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "min: '%f' max: '%lf'", min, max);
  if (direccion > 90 && direccion < 270)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "wrong ");
    // RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "ok ");
    if (alfa2 >= min && alfa2 <= max)
    {
      return (a * abs(sin((alfa2 - direccion) * 0.01745)) + esfericas.ro * a);
    }
    else
    {
      return (a +  esfericas.ro * a);
    }
  }

  else
  {
    // RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "wrong ");
    RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "ok ");
    if (alfa2 >= min || alfa2 <= max)
    {
      return (a * abs(sin((alfa2 - direccion) * 0.01745)) + esfericas.ro * a);
    }
    else
    {
      return (a +  esfericas.ro * a);
    }
  }
}

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
    CoordenadasRectangulares posicion =
        EsfericasRectangulares(angle, force_origin.z, force_origin.x, force_origin.y, force_origin.z);
    start_point.x = posicion.x;
    start_point.y = posicion.y;
    start_point.z = force_origin.z;
    auto fuerza = CalculoFuerza(start_point.x, start_point.y, start_point.z, force_origin.x, force_origin.y,
                                force_origin.z, force_direction);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "alfa: '%f'Fuerza: '%lf'", angle, fuerza);
    float norma = sqrt(pow(start_point.x - force_origin.x, 2) + pow(start_point.y - force_origin.y, 2) +
                       pow(start_point.z - force_origin.z, 2));
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