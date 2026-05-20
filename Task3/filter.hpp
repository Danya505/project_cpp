#ifndef POINTCLOUD_PREPROCESSOR__FILTER_HPP_
#define POINTCLOUD_PREPROCESSOR__FILTER_HPP_

#include "Logger.h"
#include "PointCloud.h"

#include <string>
#include <unordered_map>
#include <utility>

namespace pointcloud_preprocessor
{

class FilterParametr {
public:
    FilterParametr() = default;
    explicit FilterParametr(std::unordered_map<std::string, double> params) : params_(std::move(params)) {}

    void ChangeParam(const std::string& param_name, double param_val) {
        params_[param_name] = param_val;
    }

    double GetParam(const std::string& param_name) const {
        return params_.at(param_name);
    }

    double GetParam(const std::string& param_name, double default_val) const noexcept {
        auto it = params_.find(param_name);
        if (it == params_.end()) {
            return default_val;
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, double> params_;
};

class Filter
{
public:
  explicit Filter(const std::string& filter_name = "pointcloud_preprocessor_filter")
  : filter_name_(filter_name), logger_(filter_name_) {}

  virtual ~Filter() = default;
  
  const std::string& GetFilterName() const {
      return filter_name_;
  }
  
  double GetDistance(const PointCloud* pc, size_t index) const {
      return pc->GetPointFieldAccessor().GetDistance(*pc, index);
  }
  
  double GetAzimuth(const PointCloud* pc, size_t index) const {
      return pc->GetPointFieldAccessor().GetAzimuth(*pc, index);
  }

  virtual PointCloud* Apply(PointCloud* pc) = 0;
  
  virtual void SetParams(const FilterParametr& param) {
      params_ = param;
  }

  const FilterParametr& GetFilterParam() const noexcept {
      return params_;
  }

protected:
    std::string filter_name_;
    Logger logger_;
    FilterParametr params_;
};

}  // namespace pointcloud_preprocessor

#endif  // POINTCLOUD_PREPROCESSOR__FILTER_HPP_
