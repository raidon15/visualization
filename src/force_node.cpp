#include "force_node.h"
#include <iostream>
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



CoordenadasEsfericas RectangulareEsfericas(float x, float y, float z, float x_prima , float y_prima,
                                           float z_prima )
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

CoordenadasRectangulares EsfericasRectangulares(float alfa, float z, float x_prima, float y_prima,float z_prima)
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

float CalculoFuerza(float x, float y, float z, float x_prima , float y_prima , float z_prima ,
                    float direccion )
{
  CoordenadasEsfericas esfericas = RectangulareEsfericas(x, y, z, x_prima, y_prima, z_prima);
  float alfa2 = multi_valor(esfericas.alfa * 57.2958);
  RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "alfa2 %s", alfa2);
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
      return (a + esfericas.ro * a);
    }
  }

  else
  {
    // RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "wrong ");
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "ok ");
    if (alfa2 >= min || alfa2 <= max)
    {
      return (a * abs(sin((alfa2 - direccion) * 0.01745)) + esfericas.ro * a);
    }
    else
    {
      return (a + esfericas.ro * a);
    }
  }
}