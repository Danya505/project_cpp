

#ifndef POINTCLOUD_PREPROCESSOR__CROP_BOX_FILTER_HPP_
#define POINTCLOUD_PREPROCESSOR__CROP_BOX_FILTER_HPP_

#include "../filter.hpp"

#include <vector>

namespace pointcloud_preprocessor
{
class CropBoxFilter : public pointcloud_preprocessor::Filter
{
private:
  struct CropBoxParam
  {
    double min_x{0.0};
    double max_x{0.0};
    double min_y{0.0};
    double max_y{0.0};
    double min_z{0.0};
    double max_z{0.0};
    bool negative{false};
  } param_;

public:
  CropBoxFilter();
  PointCloud* Apply(PointCloud* pc) override;
  void SetParams(const FilterParametr& param) override;
};
}  // namespace pointcloud_preprocessor

#endif  // POINTCLOUD_PREPROCESSOR__CROP_BOX_FILTER_HPP_
