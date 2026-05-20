//This is only for understanding, that there are another filters, which use another fields of points
// Don't change it

#include "blockage_diag.hpp"

namespace pointcloud_preprocessor
{

//BlockageDiag::BlockageDiag(const rclcpp::NodeOptions & options)
//: Filter("BlockageDiag", options)
//{
//  std::string node_namespace = std::string(this->get_namespace());
//  auto lidar_pos_name = node_namespace;
//  auto const pos = node_namespace.find_last_of('/');
//  if (pos != node_namespace.npos) {
//    lidar_pos_name = node_namespace.substr(pos + 1);
//  }
//  {
//    // initialize params:
//    debug_ = declare_parameter<bool>("debug", false);
//    horizontal_ring_id_ = declare_parameter<int>("horizontal_ring_id", 33);
//    blockage_ratio_threshold_ = declare_parameter<float>(lidar_pos_name + ".blockage_ratio_threshold", 0.2);
//    vertical_bins_ = declare_parameter<int>("vertical_bins", 32);
//    angle_range_deg_ = declare_parameter<std::vector<double>>(lidar_pos_name + ".angle_range", {0.0, 360.0});
//    is_channel_order_top2down_ = declare_parameter<bool>("is_channel_order_top2down", false);
//    blockage_count_threshold_ = declare_parameter<int>("blockage_count_threshold", 50);
//    blockage_buffering_frames_ = declare_parameter<int>("blockage_buffering_frames", 2);
//    blockage_buffering_interval_ = declare_parameter<int>("blockage_buffering_interval", 1);
//    max_distance_range_ = declare_parameter<double>("max_distance_range", 200.0);
//    horizontal_resolution_ = declare_parameter<double>("horizontal_resolution", 0.1);
//    blockage_kernel_ = declare_parameter<int>(lidar_pos_name + ".blockage_kernel", 10);
//    vehicle_blockage_angles_ = declare_parameter<std::vector<double>>(lidar_pos_name + ".vehicle_blockage_angles", std::vector<double>());
//    blockage_angle_delta_ = declare_parameter<double>("blockage_angle_delta", 0.5);
//    point_type_ = declare_parameter<std::string>("point_type", "PointXYZIRADRT");
//    std::vector<long int> default_rings_to_sorted(vertical_bins_);
//    for (long int i = 0; i < vertical_bins_; ++i) {default_rings_to_sorted[i] = i;}
//    rings_to_sorted_ = declare_parameter<std::vector<long int>>("rings_to_sorted", default_rings_to_sorted);
//  }
//
//  updater_.setHardwareID("blockage_diag");
//  updater_.add(
//    std::string(this->get_namespace()) + ": blockage_validation", this,
//    &BlockageDiagComponent::onBlockageChecker);
//  updater_.setPeriod(0.1);
//
//  if (debug_) {
//    lidar_depth_map_pub_ =
//      image_transport::create_publisher(this, "blockage_diag/debug/lidar_depth_map");
//    blockage_mask_pub_ =
//      image_transport::create_publisher(this, "blockage_diag/debug/blockage_mask_image");
//  }
//
//  using std::placeholders::_1;
//  set_param_res_ = this->add_on_set_parameters_callback(
//    std::bind(&BlockageDiagComponent::paramCallback, this, _1));
//}
//
//void BlockageDiagComponent::onBlockageChecker(DiagnosticStatusWrapper & stat)
//{
//  stat.add("ground_blockage_ratio", std::to_string(ground_blockage_ratio_));
//  stat.add("ground_blockage_count", std::to_string(ground_blockage_count_));
//  stat.add(
//    "ground_blockage_range_deg", "[" + std::to_string(ground_blockage_range_deg_[0]) + "," +
//                                   std::to_string(ground_blockage_range_deg_[1]) + "]");
//  stat.add("sky_blockage_ratio", std::to_string(sky_blockage_ratio_));
//  stat.add("sky_blockage_count", std::to_string(sky_blockage_count_));
//  stat.add(
//    "sky_blockage_range_deg", "[" + std::to_string(sky_blockage_range_deg_[0]) + "," +
//                                std::to_string(sky_blockage_range_deg_[1]) + "]");
//  stat.add("vertical_bins", std::to_string(vertical_bins_));
//  stat.add("horizontal_ring_id", std::to_string(horizontal_ring_id_));
//  // TODO(badai-nguyen): consider sky_blockage_ratio_ for DiagnosticsStatus." [todo]
//
//  auto level = DiagnosticStatus::OK;
//  std::string msg;
//  if (ground_blockage_ratio_ < 0) {
//    level = DiagnosticStatus::STALE;
//    msg = "STALE";
//  } else if (
//    (ground_blockage_ratio_ > blockage_ratio_threshold_) &&
//    (ground_blockage_count_ > blockage_count_threshold_)) {
//    level = DiagnosticStatus::ERROR;
//    msg = "ERROR";
//  } else if (ground_blockage_ratio_ > 0.0f) {
//    level = DiagnosticStatus::WARN;
//    msg = "WARN";
//  } else {
//    level = DiagnosticStatus::OK;
//    msg = "OK";
//  }
//
//  if ((ground_blockage_ratio_ > 0.0f) && (sky_blockage_ratio_ > 0.0f)) {
//    msg = msg + ": LIDAR both blockage";
//  } else if (ground_blockage_ratio_ > 0.0f) {
//    msg = msg + ": LIDAR ground blockage";
//  } else if (sky_blockage_ratio_ > 0.0f) {
//    msg = msg + ": LIDAR sky blockage";
//  }
//  stat.summary(level, msg);
//}
//
//bool BlockageDiagComponent::isBlockedByVehicle(const cv::Rect& blockage_boundary, std::vector<float>& angle_range_deg)
//{
//  double blockage_range_deg_start =
//    blockage_boundary.x * horizontal_resolution_ + angle_range_deg_[0];
//  double blockage_range_deg_finish =
//    (blockage_boundary.x + blockage_boundary.width) * horizontal_resolution_ +
//    angle_range_deg_[0];
//  if (vehicle_blockage_angles_.empty()) {
//    angle_range_deg[0] = blockage_range_deg_start;
//    angle_range_deg[1] = blockage_range_deg_finish;
//    return false;
//  } 
//  
//  if (blockage_range_deg_start >=  vehicle_blockage_angles_[0] - blockage_angle_delta_ &&
//    blockage_range_deg_finish <= vehicle_blockage_angles_[1] + blockage_angle_delta_) {
//    return true;
//  } 
//  
//  if (angle_range_deg[0] >= vehicle_blockage_angles_[0] - blockage_angle_delta_ &&
//    angle_range_deg[0] <= vehicle_blockage_angles_[1] + blockage_angle_delta_ &&
//    angle_range_deg[1] >= vehicle_blockage_angles_[1] + blockage_angle_delta_) {
//    angle_range_deg[0] = vehicle_blockage_angles_[1];
//    angle_range_deg[1] = blockage_range_deg_finish;
//  } else if (angle_range_deg[0] <= vehicle_blockage_angles_[0] - blockage_angle_delta_ &&
//    angle_range_deg[1] <= vehicle_blockage_angles_[1] + blockage_angle_delta_ &&
//    angle_range_deg[1] >= vehicle_blockage_angles_[0] - blockage_angle_delta_) {
//    angle_range_deg[0] = blockage_range_deg_start;
//    angle_range_deg[1] = vehicle_blockage_angles_[0];;
//  } else {
//    angle_range_deg[0] = blockage_range_deg_start;
//    angle_range_deg[1] = blockage_range_deg_finish;
//  }
//
//  return false;
//}
//
//int BlockageDiagComponent::getHorizontalIndex(double current_angle, double compensate_angle) {
//  current_angle = current_angle + compensate_angle - angle_range_deg_[0];
//  return static_cast<int>(current_angle / horizontal_resolution_) %
//    static_cast<int>(360.0 / horizontal_resolution_);
//}
//
//void BlockageDiagComponent::filter(
//  const PointCloud2ConstPtr & input, [[maybe_unused]] const IndicesPtr & indices, PointCloud2 & output)
//{
//  std::scoped_lock lock(mutex_);
//  int ideal_horizontal_bins;
//  int vertical_bins = vertical_bins_;
//  double compensate_angle = 0.0;
//  // Check the case when angle_range_deg_[1] exceed 360 and shifted the range to 0~360
//  if (angle_range_deg_[0] > angle_range_deg_[1]) {
//    compensate_angle = 360.0;
//  }
//  ideal_horizontal_bins = static_cast<int>(
//    (angle_range_deg_[1] + compensate_angle - angle_range_deg_[0]) / horizontal_resolution_);
//  auto pcl_getter = createPointcloudGetter(point_type_, input);
//  if (!pcl_getter) {
//    RCLCPP_ERROR(get_logger(), "Undefined pointcloud type");
//  }
//  cv::Mat full_size_depth_map(cv::Size(ideal_horizontal_bins, vertical_bins), CV_16UC1, cv::Scalar(0));
//  cv::Mat lidar_depth_map_8u(cv::Size(ideal_horizontal_bins, vertical_bins), CV_8UC1, cv::Scalar(0));
//  if (pcl_getter->empty()) {
//    ground_blockage_ratio_ = 1.0f;
//    sky_blockage_ratio_ = 1.0f;
//    if (ground_blockage_count_ <= 2 * blockage_count_threshold_) {
//      ground_blockage_count_ += 1;
//    }
//    if (sky_blockage_count_ <= 2 * blockage_count_threshold_) {
//      sky_blockage_count_ += 1;
//    }
//    ground_blockage_range_deg_[0] = angle_range_deg_[0];
//    ground_blockage_range_deg_[1] = angle_range_deg_[1];
//    sky_blockage_range_deg_[0] = angle_range_deg_[0];
//    sky_blockage_range_deg_[1] = angle_range_deg_[1];
//  } else {
//    while (pcl_getter->hasNextPoint()) {
//      double azimuth_deg = pcl_getter->getPointAzimuth();
//      if (
//        ((azimuth_deg > angle_range_deg_[0]) &&
//         (azimuth_deg <= angle_range_deg_[1] + compensate_angle)) ||
//        ((azimuth_deg + compensate_angle > angle_range_deg_[0]) &&
//         (azimuth_deg < angle_range_deg_[1]))) {
//        int horizontal_bin_index = getHorizontalIndex(azimuth_deg, compensate_angle);
//        uint16_t depth_intensity =
//          UINT16_MAX * (1.0 - std::min(pcl_getter->getPointDistance() / max_distance_range_, 1.0));
//        if (is_channel_order_top2down_) {
//          full_size_depth_map.at<uint16_t>(rings_to_sorted_[pcl_getter->getPointRing()], horizontal_bin_index) = depth_intensity;
//        } else {
//          full_size_depth_map.at<uint16_t>(vertical_bins - rings_to_sorted_[pcl_getter->getPointRing()] - 1, horizontal_bin_index) =
//            depth_intensity;
//        }
//      }
//      pcl_getter->getNextPoint();
//    }
//  }
//  full_size_depth_map.convertTo(lidar_depth_map_8u, CV_8UC1, 1.0 / 300);
//  cv::Mat no_return_mask(cv::Size(ideal_horizontal_bins, vertical_bins), CV_8UC1, cv::Scalar(0));
//  cv::inRange(lidar_depth_map_8u, 0, 1, no_return_mask);
//  cv::Mat erosion_dst;
//  cv::Mat blockage_element = cv::getStructuringElement(
//    cv::MORPH_RECT, cv::Size(2 * blockage_kernel_ + 1, 2 * blockage_kernel_ + 1),
//    cv::Point(blockage_kernel_, blockage_kernel_));
//  cv::erode(no_return_mask, erosion_dst, blockage_element);
//  cv::dilate(erosion_dst, no_return_mask, blockage_element);
//  cv::Mat time_series_blockage_result(
//    cv::Size(ideal_horizontal_bins, vertical_bins), CV_8UC1, cv::Scalar(0));
//  cv::Mat time_series_blockage_mask(
//    cv::Size(ideal_horizontal_bins, vertical_bins), CV_8UC1, cv::Scalar(0));
//  cv::Mat no_return_mask_binarized(
//    cv::Size(ideal_horizontal_bins, vertical_bins), CV_8UC1, cv::Scalar(0));
//
//  if (debug_) {
//    if (blockage_buffering_interval_ == 0) {
//      no_return_mask.copyTo(time_series_blockage_result);
//    } else {
//      no_return_mask_binarized = no_return_mask / 255;
//      if (blockage_frame_count_ >= blockage_buffering_interval_) {
//        no_return_mask_buffer.push_back(no_return_mask_binarized);
//        blockage_frame_count_ = 0;
//      } else {
//        blockage_frame_count_++;
//      }
//      for (const auto & binary_mask : no_return_mask_buffer) {
//        time_series_blockage_mask += binary_mask;
//      }
//      cv::inRange(
//        time_series_blockage_mask, no_return_mask_buffer.size() - 1, no_return_mask_buffer.size(),
//        time_series_blockage_result);
//    }
//  }
//
//  int start_vehicle_blockage_index = 0;
//  int end_vehicle_blockage_index = 0;
//  if (vehicle_blockage_angles_.size() == 2) {
//    start_vehicle_blockage_index = getHorizontalIndex(vehicle_blockage_angles_[0], compensate_angle);
//    end_vehicle_blockage_index = getHorizontalIndex(vehicle_blockage_angles_[1], compensate_angle);
//  }
//  int horizotal_blockage_bins = end_vehicle_blockage_index - start_vehicle_blockage_index;
//  cv::Mat ground_no_return_mask;
//  cv::Mat ground_vehicle_blockage_mask;
//  cv::Mat sky_no_return_mask;
//  cv::Mat sky_vehicle_blockage_mask;
//  no_return_mask(cv::Rect(0, 0, ideal_horizontal_bins, horizontal_ring_id_))
//    .copyTo(sky_no_return_mask);
//  no_return_mask(cv::Rect(start_vehicle_blockage_index, 0, end_vehicle_blockage_index - start_vehicle_blockage_index, horizontal_ring_id_))
//    .copyTo(sky_vehicle_blockage_mask);
//  no_return_mask(
//    cv::Rect(0, horizontal_ring_id_, ideal_horizontal_bins, vertical_bins - horizontal_ring_id_))
//    .copyTo(ground_no_return_mask);
//  no_return_mask(cv::Rect(start_vehicle_blockage_index, horizontal_ring_id_, end_vehicle_blockage_index - start_vehicle_blockage_index,  vertical_bins - horizontal_ring_id_))
//    .copyTo(ground_vehicle_blockage_mask);
//  ground_blockage_ratio_ =
//    static_cast<float>(cv::countNonZero(ground_no_return_mask) - cv::countNonZero(ground_vehicle_blockage_mask)) /
//    static_cast<float>((ideal_horizontal_bins - horizotal_blockage_bins) * (vertical_bins - horizontal_ring_id_));
//
//  if (horizontal_ring_id_ == 0) {
//    sky_blockage_ratio_ = 0.0f;
//  } else {
//    sky_blockage_ratio_ = static_cast<float>(cv::countNonZero(sky_no_return_mask) - cv::countNonZero(sky_vehicle_blockage_mask)) /
//                          static_cast<float>((ideal_horizontal_bins - horizotal_blockage_bins) * horizontal_ring_id_);
//  }
//
//  if (ground_blockage_ratio_ > blockage_ratio_threshold_) {
//    cv::Rect ground_blockage_bb = cv::boundingRect(ground_no_return_mask);
//    if (!isBlockedByVehicle(ground_blockage_bb, ground_blockage_range_deg_) &&
//      ground_blockage_count_ <= 2 * blockage_count_threshold_) {
//      ground_blockage_count_ += 1;
//    } else {
//      ground_blockage_ratio_ = 0.0;
//      ground_blockage_count_ = 0;
//    }
//  } else {
//    ground_blockage_count_ = 0;
//  }
//  if (sky_blockage_ratio_ > blockage_ratio_threshold_) {
//    cv::Rect sky_blockage_bx = cv::boundingRect(sky_no_return_mask);
//    if (!isBlockedByVehicle(sky_blockage_bx, sky_blockage_range_deg_) &&
//      sky_blockage_count_ <= 2 * blockage_count_threshold_) {
//      sky_blockage_count_ += 1;
//    } else {
//      sky_blockage_ratio_ = 0.0;
//      sky_blockage_count_ = 0;
//    }
//  } else {
//    sky_blockage_count_ = 0;
//  }
//
//  if (debug_) {
//    sensor_msgs::msg::Image::SharedPtr lidar_depth_map_msg =
//      cv_bridge::CvImage(std_msgs::msg::Header(), "mono16", full_size_depth_map).toImageMsg();
//    lidar_depth_map_msg->header = input->header;
//    lidar_depth_map_pub_.publish(lidar_depth_map_msg);
//
//    cv::Mat blockage_mask_colorized;
//    cv::applyColorMap(time_series_blockage_result, blockage_mask_colorized, cv::COLORMAP_JET);
//    sensor_msgs::msg::Image::SharedPtr blockage_mask_msg =
//      cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", blockage_mask_colorized).toImageMsg();
//    blockage_mask_msg->header = input->header;
//    blockage_mask_pub_.publish(blockage_mask_msg);
//  }
//  output.header = input->header;
//}
//rcl_interfaces::msg::SetParametersResult BlockageDiagComponent::paramCallback(
//  const std::vector<rclcpp::Parameter> & p)
//{
//  std::scoped_lock lock(mutex_);
//  if (get_param(p, "blockage_ratio_threshold", blockage_ratio_threshold_)) {
//    RCLCPP_DEBUG(
//      get_logger(), "Setting new blockage_ratio_threshold to: %f.", blockage_ratio_threshold_);
//  }
//  if (get_param(p, "horizontal_ring_id", horizontal_ring_id_)) {
//    RCLCPP_DEBUG(get_logger(), "Setting new horizontal_ring_id to: %d.", horizontal_ring_id_);
//  }
//  if (get_param(p, "vertical_bins", vertical_bins_)) {
//    RCLCPP_DEBUG(get_logger(), "Setting new vertical_bins to: %d.", vertical_bins_);
//  }
//  if (get_param(p, "blockage_count_threshold", blockage_count_threshold_)) {
//    RCLCPP_DEBUG(
//      get_logger(), "Setting new blockage_count_threshold to: %d.", blockage_count_threshold_);
//  }
//  if (get_param(p, "is_channel_order_top2down", is_channel_order_top2down_)) {
//    RCLCPP_DEBUG(get_logger(), "Setting new lidar model to: %d. ", is_channel_order_top2down_);
//  }
//  if (get_param(p, "angle_range", angle_range_deg_)) {
//    RCLCPP_DEBUG(
//      get_logger(), " Setting new angle_range to: [%f , %f].", angle_range_deg_[0],
//      angle_range_deg_[1]);
//  }
//  if (get_param(p, "blockage_buffering_frames", blockage_buffering_frames_)) {
//    RCLCPP_DEBUG(
//      get_logger(), "Setting new blockage_buffering_frames_ to: %d.", blockage_buffering_frames_);
//  }
//  if (get_param(p, "blockage_buffering_interval", blockage_buffering_interval_)) {
//    RCLCPP_DEBUG(
//      get_logger(), "Setting new blockage_buffering_interval_ to: %d.",
//      blockage_buffering_interval_);
//  }
//  rcl_interfaces::msg::SetParametersResult result;
//  result.successful = true;
//  result.reason = "success";
//  return result;
//}
}  // namespace pointcloud_preprocessor
