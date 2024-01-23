#include "rclcpp/rclcpp.hpp"
#include "visualization/srv/arrow_publish.hpp"                                       // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

 

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("publish_arrow_client");  // CHANGE
  rclcpp::Client<visualization::srv::ArrowPublish>::SharedPtr client =                // CHANGE
    node->create_client<visualization::srv::ArrowPublish>("/publish_grasp_point_arrow");          // CHANGE

  auto request = std::make_shared<visualization::srv::ArrowPublish::Request>();       // CHANGE
  request->current_point.x = 0;
  request->current_point.y = 0;
  request->current_point.z = 0;
  request->force_origin.x = 0.0;//-0.84;
  request->force_origin.y = 0.0;//0.059;
  request->force_origin.z = 0.0;//1.17;                                                            // CHANGE
  request->force_direction = -45;
  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Publishing sphere in x y z ");
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service publish marker");    // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}