#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <filters/filter_chain.hpp>
#include <rclcpp/logger.hpp>
#include <geometry_msgs/msg/polygon_stamped.hpp>


class ObjectFilterNode : public rclcpp::Node {
public:
  ObjectFilterNode()
    : Node(
      "legit_filter",
      rclcpp::NodeOptions()
        .allow_undeclared_parameters(true)
        .automatically_declare_parameters_from_overrides(true) ),
    filter_chain_("sensor_msgs::msg::LaserScan")
  {
    auto qos = rclcpp::SensorDataQoS();

    sub_ = create_subscription<sensor_msgs::msg::LaserScan>(
      "scan", qos, std::bind(&ObjectFilterNode::cb, this, std::placeholders::_1));

    pub_ = create_publisher<sensor_msgs::msg::LaserScan>("scan_filtered", qos);




    //load yaml and initialize filter from parameter-namespace "filters"
    bool ok = filter_chain_.configure("filters",
      this->get_node_logging_interface(),
      this->get_node_parameters_interface());

    RCLCPP_INFO_ONCE(get_logger(), "FilterChain configured = %s", ok ? "true" : "false");

    if (!ok) {
      RCLCPP_WARN_ONCE(get_logger(), "No filters configured under namespace 'filters'.");
    } 
    else {
      RCLCPP_INFO_ONCE(get_logger(), "FilterChain configured.");
    }
  }

  
private:

  void cb(const sensor_msgs::msg::LaserScan::SharedPtr msg_in) {
    sensor_msgs::msg::LaserScan msg_out;

    bool applied = filter_chain_.update(*msg_in, msg_out);

    RCLCPP_DEBUG_THROTTLE(get_logger(), *get_clock(), 8000,
      "FilterChain.update() -> %s", applied ? "true" : "false");

    if (applied) {
      pub_->publish(msg_out);
    } else {
      pub_->publish(*msg_in);
    }
  }

  filters::FilterChain<sensor_msgs::msg::LaserScan> filter_chain_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_;
  rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr pub_;
  rclcpp::Subscription<geometry_msgs::msg::PolygonStamped>::SharedPtr rect_sub_;

  geometry_msgs::msg::PolygonStamped::SharedPtr latest_rectangle_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ObjectFilterNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}