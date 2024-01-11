
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

CoordenadasEsfericas RectangulareEsfericas(float x, float y, float z, float x_prima = 0, float y_prima = 0, float z_prima = 0)
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

CoordenadasRectangulares EsfericasRectangulares(float alfa, float z, float x_prima = 0, float y_prima = 0, float z_prima = 0)
{
    alfa = 0.0174533 * alfa;
    float ro = 1.0;
    float x = ro * cos(alfa) + x_prima;
    float y = ro * sin(alfa) + y_prima;
    float z1 = z;
    CoordenadasRectangulares rectangulares;
    rectangulares.x = x;
    rectangulares.y = y;
    rectangulares.z = z1;
    return rectangulares;
};

float CalculoFuerza(float x, float y, float z, float x_prima = 0, float y_prima = 0, float z_prima = 0)
{
    CoordenadasEsfericas esfericas = RectangulareEsfericas(x, y, z, x_prima, y_prima, z_prima);
    float alfa2 = esfericas.alfa * 57.2958;
    // RCLCPP_INFO(this->LOGGER, "alfa calculada: '%f'", alfa2);
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

void print_arrow(const std::shared_ptr<visualization::srv::ArrowPublish::Request> request,
                 std::shared_ptr<visualization::srv::ArrowPublish::Response> response)
{
    visual_tools_->deleteAllMarkers();
    auto start_point = request->current_point;
    auto force_origin = request->force_origin;
    float norma = sqrt(pow(request->current_point.x - request->force_origin.x, 2) + pow(request->current_point.y - request->force_origin.y, 2) + pow(request->current_point.z - request->force_origin.z, 2));
    auto finish_point = geometry_msgs::msg::Point();
    auto fuerza = CalculoFuerza(start_point.x, start_point.y, start_point.z, force_origin.x, force_origin.y, force_origin.z);
    finish_point.x = start_point.x + ((start_point.x - request->force_origin.x) * fuerza) / norma;
    finish_point.y = start_point.y + ((start_point.y - request->force_origin.y) * fuerza) / norma;
    finish_point.z = start_point.z + ((start_point.z - request->force_origin.z) * fuerza) / norma;
    visual_tools_->publishArrow(start_point, finish_point, rviz_visual_tools::RED, rviz_visual_tools::LARGE);
    visual_tools_->trigger();
}
CoordenadasRectangulares posicion_;

int main(int argc, char **argv)
{

    // initiate ROS2 communications
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    node_options.automatically_declare_parameters_from_overrides(true);
    auto node_ = rclcpp::Node::make_shared("publishing_arrow_rviz", node_options);
    auto service = node_->create_service<visualization::srv::ArrowPublish>("publish_arrow", &print_arrow);
    visual_tools_.reset(
        new rviz_visual_tools::RvizVisualTools("/world", "/force_arrow", node_));
    std::cout << "debug";
    

    // arrow.print_arrow(0.0,0.0,0.0,-0.84,0.059,1.17);
    rclcpp::spin(node_);
    rclcpp::shutdown();
    return 0;
}