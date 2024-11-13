// src/force_service_client.cpp
#include "rclcpp/rclcpp.hpp"
#include "visualization/srv/arrow_publish.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <chrono>


using namespace std::chrono_literals;
class ForceServiceClient : public rclcpp::Node {
public:
    ForceServiceClient() : Node("force_service_client") {
        client_ = this->create_client<visualization::srv::ArrowPublish>("publish_grasp_point_arrow");

        // Wait for the service to be available
        while (!client_->wait_for_service(1s)){
            RCLCPP_INFO(this->get_logger(), "Waiting for the service to be available...");
        }

        // Create and send the request
        auto request = std::make_shared<visualization::srv::ArrowPublish::Request>();
        request->current_point.x = 1.0;
        request->current_point.y = 2.0;
        request->current_point.z = 3.0;
        request->force_origin.x = 0.0;
        request->force_origin.y = 0.0;
        request->force_origin.z = 0.0;
        request->color_value = 1;
        request->force_direction = 0;
        request->marker_ns = "gripp_point";
        request->force = 5.0;

        auto future = client_->async_send_request(request);

        // Wait for the response and print it
        try {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "Received response with force: %.2f", response->force);
        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
        }
    }

private:
    rclcpp::Client<visualization::srv::ArrowPublish>::SharedPtr client_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ForceServiceClient>());
    rclcpp::shutdown();
    return 0;
}
