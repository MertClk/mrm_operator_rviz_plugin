//
//  Copyright 2025 TIER IV, Inc. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef MRM_OPERATOR_RVIZ_PANEL_HPP_
#define MRM_OPERATOR_RVIZ_PANEL_HPP_

#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
// ROS 2 core
#include <rclcpp/rclcpp.hpp>
#include <rviz_common/panel.hpp>

#include <std_msgs/msg/u_int8.hpp>

#include <chrono>
#include <memory>
#include <utility>

namespace rviz_plugins
{
class MrmOperatorRvizPanel : public rviz_common::Panel
{
  Q_OBJECT

public:
  explicit MrmOperatorRvizPanel(QWidget * parent = nullptr);
  void onInitialize() override;

public Q_SLOTS:  // NOLINT for Qt
  void onClickEmergencyStop();
  void onClickComfortableStop();
  void onClickPullOver();
  void onClickClear();

private:
  void publishDebugData(const char * msg);

protected:
  // Layout
  QHBoxLayout * makeMRMModeGroup();

  rclcpp::Node::SharedPtr raw_node_;

  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr pub_emergency_status_;

  //// Vehicle Override Status
  QLabel * mrm_operator_status_label_ptr_{nullptr};

  QPushButton * emergency_stop_button_ptr_{nullptr};
  QPushButton * comfortable_stop_button_ptr_{nullptr};
  QPushButton * pull_over_button_ptr_{nullptr};
  QPushButton * clear_button_ptr_{nullptr};
};

}  // namespace rviz_plugins

#endif  // MRM_OPERATOR_RVIZ_PANEL_HPP_