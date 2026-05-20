#include "PointCloud.h"
#include "crop_box_filter/crop_box_filter.hpp"

#include <iostream>
#include <string>
#include <memory>

std::ostream& operator<<(std::ostream& stream, const PointCloud& pc) {
	stream << "Point cloud (" << ToString(pc.pointcloud_type_) << "): " << std::endl;
	for (size_t i = 0; i < pc.size_; ++i) {
		for (size_t j = 0; j < pc.point_size_; ++j) {
			stream << pc.points_[i * pc.point_size_ + j] << " ";
		}
		stream << std::endl;
	}
	return stream;
}

int main() {
	try {
		PointCloud pc_xyzir, pc_xyzirdat;
		FillPointCloud(&pc_xyzir, 3, PointCloudType::XYZIR,
			{ 5.0, 1.2, 2.1, 0.5, 1.0,
			 -3.2, 0.2, 1.1, 0.7, 1.0,
			 2.2, 2.1, 7.0, 0.1, 2.0 });

		std::cout << "We have: " << pc_xyzir << std::endl;

		std::unique_ptr<pointcloud_preprocessor::Filter> cbf = std::make_unique<pointcloud_preprocessor::CropBoxFilter>();
		cbf->SetParams(pointcloud_preprocessor::FilterParametr({
			{"min_x", -4.0}, {"max_x", -2.0},
			{"min_y", 0.1}, {"max_y", 2.0},
			{"min_z", 0.5}, {"max_z", 3.0}
		}));
		auto out = std::unique_ptr<PointCloud>(cbf->Apply(&pc_xyzir));

		std::cout << "after CBF: " << *out << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
