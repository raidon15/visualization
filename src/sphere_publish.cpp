// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.hpp>
#include <rviz_visual_tools/remote_control.hpp>

// ROS
#include <rclcpp/rclcpp.hpp>

// C++
#include <string>
#include <vector>

// Msgs
#include <geometry_msgs/msg/vector3.hpp>

using namespace std::chrono_literals;

namespace rvt = rviz_visual_tools;

namespace rviz_visual_tools
{
class RvizVisualToolsDemo : public rclcpp::Node
{
private:
  // For visualizing things in rviz
  rvt::RvizVisualToolsPtr visual_tools_;

public:
  /**
   * \brief Constructor
   */
  explicit RvizVisualToolsDemo(const rclcpp::NodeOptions& options = rclcpp::NodeOptions())
    : Node("rviz_demo", options)
  {
    visual_tools_.reset(
        new rvt::RvizVisualTools("world", "/rviz_visual_tools", dynamic_cast<rclcpp::Node*>(this)));
    // create publisher before waiting
    visual_tools_->loadMarkerPub();
    bool has_sub = visual_tools_->waitForMarkerSub(10.0);
    if (!has_sub)
      RCLCPP_INFO(get_logger(), "/rviz_visual_tools does not have a subscriber after 10s. "
                                "Visualizations may be lost");

    // Clear messages
    visual_tools_->deleteAllMarkers();
    visual_tools_->enableBatchPublishing();
  }
};
}

int main(int argc, char** argv)
{
  rviz_visual_tools::RvizVisualToolsDemo demo = rviz_visual_tools::RvizVisualToolsDemo();

  return 0;
}

  