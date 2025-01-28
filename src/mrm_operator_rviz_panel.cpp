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

#include "mrm_operator_rviz_panel.hpp"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QString>
#include <QVBoxLayout>
#include <rviz_common/display_context.hpp>

#include <chrono>
#include <memory>
#include <string>
#include <utility>

namespace rviz_plugins
{
MrmOperatorRvizPanel::MrmOperatorRvizPanel(QWidget * parent) : rviz_common::Panel(parent)
{
  // Create a new container widget
  QWidget * containerWidget = new QWidget(this);
  containerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto * containerLayout = new QVBoxLayout(containerWidget);
  // Set the alignment of the layout
  containerLayout->setAlignment(Qt::AlignCenter);
  containerLayout->setSpacing(1);

  // Layout
  auto * mrm_group = makeMRMModeGroup();

  containerLayout->addLayout(mrm_group);
}

void MrmOperatorRvizPanel::onInitialize()
{
  using std::placeholders::_1;

  raw_node_ = this->getDisplayContext()->getRosNodeAbstraction().lock()->get_raw_node();

  pub_emergency_status_ =
    raw_node_->create_publisher<std_msgs::msg::UInt8>("/system/selected_mrm", rclcpp::QoS{1});
}

QHBoxLayout * MrmOperatorRvizPanel::makeMRMModeGroup()
{
  emergency_stop_button_ptr_ = new QPushButton(tr("Emergency Stop"), this);
  connect(emergency_stop_button_ptr_, SIGNAL(clicked()), SLOT(onClickEmergencyStop()));

  comfortable_stop_button_ptr_ = new QPushButton(tr("Comfortable Stop"), this);
  connect(comfortable_stop_button_ptr_, SIGNAL(clicked()), SLOT(onClickComfortableStop()));

  pull_over_button_ptr_ = new QPushButton(tr("Pull Over"), this);
  connect(pull_over_button_ptr_, SIGNAL(clicked()), SLOT(onClickPullOver()));

  clear_button_ptr_ = new QPushButton(tr("Clear"), this);
  connect(clear_button_ptr_, SIGNAL(clicked()), SLOT(onClickClear()));

  QHBoxLayout * groupLayout = new QHBoxLayout;
  groupLayout->setAlignment(Qt::AlignCenter);
  // set these widgets to show up at the left and not stretch more than needed
  // groupLayout->addSpacing(5);
  groupLayout->addWidget(emergency_stop_button_ptr_);
  groupLayout->addWidget(comfortable_stop_button_ptr_);
  groupLayout->addWidget(pull_over_button_ptr_);
  groupLayout->addWidget(clear_button_ptr_);
  return groupLayout;
}
void MrmOperatorRvizPanel::publishDebugData(const char * msg)
{
  RCLCPP_DEBUG(raw_node_->get_logger(), msg);
}

void MrmOperatorRvizPanel::onClickEmergencyStop()
{
  publishDebugData("Clicked on Emergency Stop Button!");
  std_msgs::msg::UInt8 msg_mrm;
  msg_mrm.data = 0;
  pub_emergency_status_->publish(msg_mrm);
}

void MrmOperatorRvizPanel::onClickComfortableStop()
{
  publishDebugData("Clicked on Comfortable Stop Button!");
  std_msgs::msg::UInt8 msg_mrm;
  msg_mrm.data = 1;
  pub_emergency_status_->publish(msg_mrm);
}

void MrmOperatorRvizPanel::onClickPullOver()
{
  publishDebugData("Clicked on Pull Over Button!");
  std_msgs::msg::UInt8 msg_mrm;
  msg_mrm.data = 2;
  pub_emergency_status_->publish(msg_mrm);
}

void MrmOperatorRvizPanel::onClickClear()
{
  publishDebugData("Clicked on Clear Emergency Button!");
  std_msgs::msg::UInt8 msg_mrm;
  msg_mrm.data = 3;
  pub_emergency_status_->publish(msg_mrm);
}

}  // namespace rviz_plugins

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz_plugins::MrmOperatorRvizPanel, rviz_common::Panel)