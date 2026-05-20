#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

enum class PointCloudType {
    Undefined,
    XYZIR,
    XYZIRDAT
};

inline std::string ToString(PointCloudType type) {
    switch (type) {
        case PointCloudType::XYZIR:
            return "XYZIR";
        case PointCloudType::XYZIRDAT:
            return "XYZIRDAT";
        default:
            return "Undefined";
    }
}

class PointCloud;

class PointFieldAccessor {
public:
    virtual ~PointFieldAccessor() = default;
    virtual PointCloudType Type() const noexcept = 0;
    virtual size_t PointSize() const noexcept = 0;
    virtual double GetDistance(const PointCloud& pc, size_t index) const = 0;
    virtual double GetAzimuth(const PointCloud& pc, size_t index) const = 0;
};

inline const PointFieldAccessor& PointFieldAccessorByType(PointCloudType type);

class PointCloud {
public:
    void Init(PointCloudType pc_type, size_t points_count) {
        pointcloud_type_ = pc_type;
        point_field_accessor_ = &PointFieldAccessorByType(pc_type);
        size_ = points_count;
        point_size_ = point_field_accessor_->PointSize();
        points_.assign(size_ * point_size_, 0.0);
    }

    void AddPoint(const std::vector<double>& point, size_t ind) {
        if (point.size() != point_size_) {
            throw std::runtime_error("Point has unsupported size = " +
                                     std::to_string(point.size()) + " for type " + ToString(pointcloud_type_));
        }

        const auto offset = point_size_ * ind;
        std::copy(point.begin(), point.end(), points_.begin() + offset);
    }

    const PointFieldAccessor& GetPointFieldAccessor() const {
        if (point_field_accessor_ == nullptr) {
            throw std::runtime_error("pointcloud type is not initialized");
        }
        return *point_field_accessor_;
    }

    PointCloudType pointcloud_type_{PointCloudType::Undefined};
    size_t size_ = 0;
    size_t point_size_ = 0;
    std::vector<double> points_;

private:
    const PointFieldAccessor* point_field_accessor_{nullptr};
};

class XyzirPointFieldAccessor final : public PointFieldAccessor {
public:
    PointCloudType Type() const noexcept override {
        return PointCloudType::XYZIR;
    }

    size_t PointSize() const noexcept override {
        return 5;
    }

    double GetDistance(const PointCloud& pc, size_t index) const override {
        const auto offset = index * PointSize();
        return std::hypot(pc.points_[offset], pc.points_[offset + 1], pc.points_[offset + 2]);
    }

    double GetAzimuth(const PointCloud& pc, size_t index) const override {
        const auto offset = index * PointSize();
        return std::atan2(pc.points_[offset + 1], pc.points_[offset]);
    }
};

class XyzirdatPointFieldAccessor final : public PointFieldAccessor {
public:
    PointCloudType Type() const noexcept override {
        return PointCloudType::XYZIRDAT;
    }

    size_t PointSize() const noexcept override {
        return 8;
    }

    double GetDistance(const PointCloud& pc, size_t index) const override {
        const auto offset = index * PointSize();
        return pc.points_[offset + 5];
    }

    double GetAzimuth(const PointCloud& pc, size_t index) const override {
        const auto offset = index * PointSize();
        return pc.points_[offset + 6];
    }
};

inline const PointFieldAccessor& PointFieldAccessorByType(PointCloudType type) {
    static const XyzirPointFieldAccessor xyzir_accessor;
    static const XyzirdatPointFieldAccessor xyzirdat_accessor;

    switch (type) {
        case PointCloudType::XYZIR:
            return xyzir_accessor;
        case PointCloudType::XYZIRDAT:
            return xyzirdat_accessor;
        default:
            throw std::runtime_error("unknown pointcloud type");
    }
}

inline void FillPointCloud(PointCloud* pc, size_t points_count, PointCloudType point_type, const std::vector<double>& data) {
    const auto& point_field_accessor = PointFieldAccessorByType(point_type);
    const size_t point_size = point_field_accessor.PointSize();
    pc->Init(point_type, points_count);

    for (size_t ind = 0; ind < points_count; ++ind) {
        const auto first = ind * point_size;
        pc->AddPoint(std::vector<double>(data.begin() + first, data.begin() + first + point_size), ind);
    }
}

#endif //POINTCLOUD_H_
