# mrm_operator_rviz_plugin

This plugin publishes MRM messages so that mrm_handler can activate desired behavior. 

| **Behavior**          | **Output** |
|-----------------------|------------|
| Emergency Stop        | 0          |
| Comfortable Stop      | 1          |
| Pull Over             | 2          |
| MRM Clear             | 3          |

| **Output Topic**         | **Msg Type**               |
|--------------------------|----------------------------|
| `/system/selected_mrm`   | `std_msgs::msg::UInt8`     |

### Usage

* Start rviz and select panels/Add new panel.
* Select mrm_operator_rviz_plugin/MrmOperatorRvizPanel and press OK.

