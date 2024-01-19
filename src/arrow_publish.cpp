#include "rclcpp/rclcpp.hpp"
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "std_msgs/msg/string.hpp"
#include <moveit/planning_interface/planning_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <cmath>
#include <geometry_msgs/msg/point.hpp>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("geometry_test");

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
  float ro = 0.3;
  float x = ro * cos(alfa) + x_prima;
  float y = ro * sin(alfa) + y_prima;
  float z1 = z;
  CoordenadasRectangulares rectangulares;
  rectangulares.x = x;
  rectangulares.y = y;
  rectangulares.z = z1;
  return rectangulares;
};

float CalculoFuerza(float x, float y, float z, float x_prima = 0, float y_prima = 0, float z_prima = 0, int direccion = 0)
{
  CoordenadasEsfericas esfericas = RectangulareEsfericas(x, y, z, x_prima, y_prima, z_prima);
  int direccion_ = direccion ;
  float alfa2 = esfericas.alfa * 57.2958 + direccion;
  esfericas.alfa = esfericas.alfa + direccion * 0.01744;
  RCLCPP_INFO(LOGGER, "alfa calculada: '%f'", alfa2);
  float a = 0.5;
  float fuerza = 0.0;

  if (alfa2 < 90 && alfa2 > -90)
  {
    fuerza = esfericas.ro * a * abs(sin(esfericas.alfa));
  }
  else
  {
    fuerza = 10;
  }
  fuerza = fuerza + a * abs((z - z_prima));
  return (fuerza);
}

void print_arrow(float x, float y, float z, float fuerza, moveit_visual_tools::MoveItVisualTools& vs, float x_prima = 0,
                 float y_prima = 0, float z_prima = 0)
{
  auto start_point = geometry_msgs::msg::Point();
  start_point.x = x;
  start_point.y = y;
  start_point.z = z;
  float norma = sqrt(pow(x - x_prima, 2) + pow(y - y_prima, 2) + pow(z - z_prima, 2));
  auto finish_point = geometry_msgs::msg::Point();
  finish_point.x = start_point.x + ((start_point.x - x_prima) * fuerza) / norma;
  finish_point.y = start_point.y + ((start_point.y - y_prima) * fuerza) / norma;
  finish_point.z = start_point.z + ((start_point.z - z_prima) * fuerza) / norma;
  vs.publishArrow(start_point, finish_point, rviz_visual_tools::RED);
}

int main(int argc, char** argv)
{
  //
  // initiate ROS2 communications
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  node_options.automatically_declare_parameters_from_overrides(true);
  auto node = rclcpp::Node::make_shared("publishing_arrow_rviz", node_options);
  auto moveit_visual_tools = moveit_visual_tools::MoveItVisualTools{ node, "/world", "/force_test" };
  /*
  rclcpp::executors::SingleThreadedExecutor executor;eo
  geometry_msgs::msg::PoseStamped ee_actual_pose =  move_group.getCurrentPose();
  float ee_x = ee_actual_pose.pose.position.x;
  printf("imprimir estado \n");
  printf("%lf\n", ee_x);*/

  // moveit_visual_tools.deleteAllMarkers();

  RCLCPP_INFO(LOGGER, "k loop");
  for (float alfa = -175; alfa <= 175; alfa = alfa + 10)
  {
    auto pose1 = geometry_msgs::msg::Pose();
    CoordenadasRectangulares posicion = EsfericasRectangulares(alfa, 0.0, 0.0, 0.0, 1.0);

    pose1.position.x = posicion.x;
    pose1.position.y = posicion.y;
    pose1.position.z = 0;
    pose1.orientation.x = 0;
    pose1.orientation.y = 0;
    pose1.orientation.z = 0;
    pose1.orientation.w = 0;
    float fuerza1 = CalculoFuerza(posicion.x, posicion.y, 0.0, 0, 0, 0);
    double fuerza1d = fuerza1;
    // RCLCPP_INFO(LOGGER, "x : '%f'", k);
    print_arrow(posicion.x, posicion.y, 0.0, fuerza1, moveit_visual_tools, 0.0, 0.0, 0.0);
    // moveit_visual_tools.publishXArrow(pose1, rviz_visual_tools::RED, rviz_visual_tools::LARGE, fuerza1d);
    // RCLCPP_INFO(LOGGER, "alfa: '%f'Fuerza: '%lf'", j, fuerza1d);
  }

  moveit_visual_tools.trigger();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}