#include "crop_box_filter.hpp"

#include <cmath>
#include <cstring>
#include <utility>
#include <vector>

namespace pointcloud_preprocessor
{
CropBoxFilter::CropBoxFilter()
: Filter("CropBoxFilter")
{
}

PointCloud* CropBoxFilter::Apply(PointCloud* pc)
{
  const auto point_size = pc->point_size_;
  const auto total_size = pc->size_ * point_size;
  std::vector<double> output;
  output.reserve(total_size);

  for (size_t global_offset = 0; global_offset + point_size <= total_size;
       global_offset += point_size) {
    const double x = pc->points_[global_offset];
    const double y = pc->points_[global_offset + 1];
    const double z = pc->points_[global_offset + 2];

    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
      logger_.log("Ignoring point containing NaN values");
      continue;
    }

    const bool point_is_inside =
      x > param_.min_x && x < param_.max_x &&
      y > param_.min_y && y < param_.max_y &&
      z > param_.min_z && z < param_.max_z;

    if ((!param_.negative && point_is_inside) || (param_.negative && !point_is_inside)) {
      output.insert(
        output.end(),
        pc->points_.begin() + global_offset,
        pc->points_.begin() + global_offset + point_size);
    }
  }

  auto output_pc = new PointCloud;
  output_pc->Init(pc->pointcloud_type_, 0);
  output_pc->points_ = std::move(output);
  output_pc->point_size_ = point_size;
  output_pc->size_ = output_pc->points_.empty() ? 0 : output_pc->points_.size() / point_size;
  return output_pc;
}

void CropBoxFilter::SetParams(const FilterParametr& param)
{
  CropBoxParam new_param{};
  new_param.min_x = param.GetParam("min_x", param_.min_x);
  new_param.max_x = param.GetParam("max_x", param_.max_x);
  new_param.min_y = param.GetParam("min_y", param_.min_y);
  new_param.max_y = param.GetParam("max_y", param_.max_y);
  new_param.min_z = param.GetParam("min_z", param_.min_z);
  new_param.max_z = param.GetParam("max_z", param_.max_z);
  new_param.negative = static_cast<bool>(param.GetParam("negative", param_.negative ? 1.0 : 0.0));

  if (new_param.min_x < new_param.max_x &&
      new_param.min_y < new_param.max_y &&
      new_param.min_z < new_param.max_z) {
    if (param_.min_x != new_param.min_x || param_.max_x != new_param.max_x ||
        param_.min_y != new_param.min_y || param_.max_y != new_param.max_y ||
        param_.min_z != new_param.min_z || param_.max_z != new_param.max_z ||
        param_.negative != new_param.negative) {
      logger_.log("[paramCallback] Setting the minimum point to: " +
        std::to_string(new_param.min_x) + " " + std::to_string(new_param.min_y) + " " + std::to_string(new_param.min_z));
      logger_.log("[paramCallback] Setting the maximum point to: " +
        std::to_string(new_param.max_x) + " " + std::to_string(new_param.max_y) + " " + std::to_string(new_param.max_z));
      logger_.log(std::string("[paramCallback] Setting the filter negative flag to: ") +
        (new_param.negative ? "true" : "false"));
      param_ = new_param;
    }
  }

  Filter::SetParams(param);
}

}  // namespace pointcloud_preprocessor
