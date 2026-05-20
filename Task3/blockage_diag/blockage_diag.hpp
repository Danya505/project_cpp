// Copyright 2022 TIER IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//This is only for understanding, that there are another filters, which use another fields of points
// Don't change it

#ifndef POINTCLOUD_PREPROCESSOR__BLOCKAGE_DIAG_HPP_
#define POINTCLOUD_PREPROCESSOR__BLOCKAGE_DIAG_HPP_

#include "../filter.hpp"


namespace pointcloud_preprocessor
{

//class BlockageDiag : public pointcloud_preprocessor::Filter
//{
//public:
//  virtual PointCloud* Apply(PointCloud* pc);
//	virtual void SetParams(const FilterParametr& param);
//
//private:
//  void onBlockageChecker(DiagnosticStatusWrapper & stat);
//  bool debug_ = false;
//  Updater updater_{this};
//  int vertical_bins_ = 32;
//  std::vector<double> angle_range_deg_ = {0, 360};
//  int horizontal_ring_id_ = 12;
//  float blockage_ratio_threshold_;
//  float ground_blockage_ratio_ = -1.0f;
//  float sky_blockage_ratio_ = -1.0f;
//  std::vector<float> ground_blockage_range_deg_ = {0.0f, 0.0f};
//  std::vector<float> sky_blockage_range_deg_ = {0.0f, 0.0f};
//  int blockage_kernel_ = 10;
//  int blockage_frame_count_ = 0;
//  int ground_blockage_count_ = 0;
//  int sky_blockage_count_ = 0;
//  int blockage_count_threshold_ = 50;
//  bool is_channel_order_top2down_ = true;
//  int blockage_buffering_frames_ = 2;
//  int blockage_buffering_interval_ = 1;
//  double max_distance_range_ = 200.0;
//  double horizontal_resolution_ = 0.4;
//  std::string point_type_ = "PointXYZIRADRT";
//  std::vector<double> vehicle_blockage_angles_ = {0, 0};
//  double blockage_angle_delta_ = 0.5;
//  std::vector<long int> rings_to_sorted_;
//
//public:
//  BlockageDiag();
//};
//
}  // namespace pointcloud_preprocessor

#endif  // POINTCLOUD_PREPROCESSOR__BLOCKAGE_DIAG_HPP_