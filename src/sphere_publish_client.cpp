#include "rclcpp/rclcpp.hpp"
#include "visualization/srv/marker_publish.hpp"                                       // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 4) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_three_ints_client X Y Z");      // CHANGE
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("publish_marker_client");  // CHANGE
  rclcpp::Client<visualization::srv::MarkerPublish>::SharedPtr client =                // CHANGE
    node->create_client<visualization::srv::MarkerPublish>("/publish_sphere");          // CHANGE

  auto request = std::make_shared<visualization::srv::MarkerPublish::Request>();       // CHANGE
  request->pose.position.x = atoll(argv[1]);
  request->pose.position.y = atoll(argv[2]);
  request->pose.position.z = atoll(argv[3]);                                                              // CHANGE

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