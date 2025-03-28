#include "ra2413mt.h"

#include <utility>
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif

#define highbyte(val) (uint8_t)((val) >> 8)
#define lowbyte(val) (uint8_t)((val) & 0xff)

namespace esphome
{
  namespace ra2413mt
  {

    static const char *const TAG = "ra2413mt";
    uint8_t conf8[2];
    uint16_t conf16;

    uint8_t data8[2];
    uint16_t data16;

    // long millis = 0L;
    int refresh_millisecond = 500;

    RA2413MTComponent::RA2413MTComponent() {}

    void RA2413MTComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "RA2413MT:");
#ifdef USE_SENSOR
      LOG_SENSOR("  ", "运动距离MoveDistanceSensor", this->move_distance_sensor_);
      LOG_SENSOR("  ", "运动能量值MoveEnergySensor", this->move_energy_sensor_);
      LOG_SENSOR("  ", "静止距离StaticDistanceSensor", this->static_distance_sensor_);
      LOG_SENSOR("  ", "静止能量值StaticEnergySensor", this->static_energy_sensor_);
#endif
#ifdef USE_TEXT_SENSOR
      LOG_TEXT_SENSOR("  ", "检测状态StatusTextSensor", this->status_text_sensor_);
#endif
#ifdef USE_NUMBER
      LOG_NUMBER("  ", "最大移动距离MaxMoveDistanceNumber", this->max_move_distance_number_);
      LOG_NUMBER("  ", "最大静止距离MaxStaticDistanceNumber", this->max_static_distance_number_);
      LOG_NUMBER("  ", "移动灵敏度MoveSensitivityNumber", this->move_sensitivity_number_);
      LOG_NUMBER("  ", "静止灵敏度StaticSensitivityNumber", this->static_sensitivity_number_);
      LOG_NUMBER("  ", "无人持续时间UnattendedDurationNumber", this->unattended_duration_number_);
#endif
#ifdef USE_BUTTON
      LOG_BUTTON("  ", "QueryConfButton", this->query_conf_button_);
      LOG_BUTTON("  ", "ResetMmwButton", this->reset_mmw_button_);
#endif
      this->read_all_info();
    }

    void RA2413MTComponent::setup()
    {
      this->read_all_info();
    }

    void RA2413MTComponent::read_all_info()
    {
      this->get_config();
    }

    void RA2413MTComponent::loop()
    {
      const int max_line_length = 80;
      static uint8_t buffer[max_line_length];

      while (available())
      {
        this->readline_(read(), buffer, max_line_length);
      }
    }

    void RA2413MTComponent::readline_(int readch, uint8_t *buffer, int len)
    {

      static int pos = 0;
      if (readch >= 0)
      {
        if (pos < len - 1)
        {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
        else
        {
          pos = 0;
        }

        if (pos >= 4)
        {
          if (buffer[pos - 4] == 0x04 && buffer[pos - 3] == 0x03 && buffer[pos - 2] == 0x02 && buffer[pos - 1] == 0x01)
          {
            if (this->handle_ack_data_(buffer, pos))
            {
              pos = 0; // Reset position index ready for next time
            }
            else
            {
              ESP_LOGV(TAG, "ACK Data incomplete");
            }
          }

          if (buffer[pos - 4] == 0xf8 && buffer[pos - 3] == 0xf7 && buffer[pos - 2] == 0xf6 && buffer[pos - 1] == 0xf5)
          {
            if (buffer[0] == 0xF4 && buffer[1] == 0xF3 && buffer[2] == 0xF2 && buffer[3] == 0xF1)
            {
              /* 处理周期数据 */
              this->handle_periodic_data_(buffer, pos);
            }
            pos = 0;
          }
        }
      }
    }
    void RA2413MTComponent::handle_periodic_data_(uint8_t *buffer, int len)
    {
      if (len < 11)
      {
        ESP_LOGE(TAG, "Error with last command : incorrect length");
        return;
      }

      int32_t current_millis = millis();
      if (current_millis - last_periodic_millis_ < this->throttle_)
        return;
      last_periodic_millis_ = current_millis;

      if (len == 21)
      {
#ifdef USE_TEXT_SENSOR
        if (this->status_text_sensor_ != nullptr)
        {
          std::string movement_level = BODY_MOVEMENT_LEVEL_INT_TO_ENUM.at(buffer[8]);
          if (this->status_text_sensor_->get_state() != movement_level)
            this->status_text_sensor_->publish_state(movement_level);
        }
#endif
#ifdef USE_SENSOR
        data8[0] = buffer[9];
        data8[1] = buffer[10];
        data16 = *(uint16_t *)(data8);
        if (this->move_distance_sensor_ != nullptr)
        {
          int new_move_distance_sensor = (data16 & 0xFF);

          if (this->move_distance_sensor_->get_state() != new_move_distance_sensor)
            this->move_distance_sensor_->publish_state(new_move_distance_sensor);
        }

        if (this->move_energy_sensor_ != nullptr)
        {
          int new_move_distance_sensor = (buffer[11] & 0xFF);
          if (this->move_energy_sensor_->get_state() != new_move_distance_sensor)
            this->move_energy_sensor_->publish_state(new_move_distance_sensor);
        }
        data8[0] = buffer[12];
        data8[1] = buffer[13];
        data16 = *(uint16_t *)(data8);
        if (this->static_distance_sensor_ != nullptr)
        {
          int new_static_distance_sensor = (data16 & 0xFF);
          if (this->static_distance_sensor_->get_state() != new_static_distance_sensor)
            this->static_distance_sensor_->publish_state(new_static_distance_sensor);
        }
        if (this->static_energy_sensor_ != nullptr)
        {
          int new_static_energy_sensor = (buffer[14] & 0xFF);
          if (this->static_energy_sensor_->get_state() != new_static_energy_sensor)
            this->static_energy_sensor_->publish_state(new_static_energy_sensor);
        }
#endif
      }
    }
    bool RA2413MTComponent::handle_ack_data_(uint8_t *buffer, int len)
    {
      if (len < 23)
      {
        // ESP_LOGE(TAG, "Error with last command : incorrect length");
        return true;
      }
      if (buffer[0] != 0xFD || buffer[1] != 0xFC || buffer[2] != 0xFB || buffer[3] != 0xFA)
      { // check 4 frame start bytes
        ESP_LOGE(TAG, "Error with last command : incorrect Header");
        return true;
      }
      if (len == 34)
      {
#ifdef USE_NUMBER
        if (this->max_move_distance_number_ != nullptr)
        {
          // ESP_LOGW(TAG, " Buffer 12 content: %02X bytes", buffer[12]);
          this->max_move_distance_number_->publish_state(buffer[12]);
        }
#endif
#ifdef USE_NUMBER
        if (this->max_static_distance_number_ != nullptr)
        {
          // ESP_LOGW(TAG, " Buffer 13 content: %02X bytes", buffer[13]);
          this->max_static_distance_number_->publish_state(buffer[13]);
        }
#endif
#ifdef USE_NUMBER
        if (this->move_sensitivity_number_ != nullptr)
        {
          // ESP_LOGW(TAG, " Buffer 14 content: %02X bytes", buffer[14]);
          this->move_sensitivity_number_->publish_state(buffer[14]);
        }
#endif
#ifdef USE_NUMBER
        if (this->static_sensitivity_number_ != nullptr)
        {
          // ESP_LOGW(TAG, " Buffer 23 content: %02X bytes", buffer[23]);
          this->static_sensitivity_number_->publish_state(buffer[23]);
        }
#endif
#ifdef USE_NUMBER
        if (this->unattended_duration_number_ != nullptr)
        {
          conf8[0] = buffer[28];
          conf8[1] = buffer[29];
          conf16 = *(uint16_t *)(conf8);
          this->unattended_duration_number_->publish_state(conf16);
        }
#endif
      }

      return true;
    }

    // 获取配置
    void RA2413MTComponent::get_config()
    {
      // 使能配置命令
      this->write_array(CMD_START, 14);

      delay(15); // NOLINT
      this->write_array(CMD_CONF, 12);
      delay(15); // NOLINT
      // 结束配置命令
      this->write_array(CMD_END, 12);
    }
    // 发送控制命令
    void RA2413MTComponent::send_control_command_()
    {
      // 使能配置命令
      this->write_array(CMD_START, 14);

      delay(15); // NOLINT

      // 结束配置命令
      this->write_array(CMD_END, 12);
    }
    /** 恢复默认配置 */
    void RA2413MTComponent::reset_mmw()
    {
      // 使能配置命令
      this->write_array(CMD_START, 14);

      delay(15); // NOLINT
      this->write_array(CMD_DEFAUT_DISTANCE, 30);
      delay(15); // NOLINT
      this->write_array(CMD_DEFAUT_SENSITIVITY, 30);
      delay(15); // NOLINT
      this->write_array(CMD_CONF, 12);
      delay(15); // NOLINT
      // 结束配置命令
      this->write_array(CMD_END, 12);
      // 配置完成后查询一下配置
    }

    /** 设置检测距离 无人时间 */
    void RA2413MTComponent::set_max_distances_timeout()
    {
      int max_move_distance = static_cast<int>(this->max_move_distance_number_->state);
      int max_static_distance = static_cast<int>(this->max_static_distance_number_->state);
      int unattended_duration = static_cast<int>(this->unattended_duration_number_->state);
      uint8_t value[30] = {
          0xFD, 0xFC, 0xFB, 0xFA,
          0x14, 0x00, 0x60, 0x00,
          0x00, 0x00, lowbyte(max_move_distance), 0x00,
          0x00, 0x00, 0x01, 0x00,
          lowbyte(max_static_distance), 0x00, 0x00, 0x00,
          0x02, 0x00, lowbyte(unattended_duration), highbyte(unattended_duration),
          0x00, 0x00, 0x04, 0x03,
          0x02, 0x01};
      // ESP_LOGV(TAG, "配置最大移动检测距离 %02X", lowbyte(time));
      // 使能配置命令
      this->write_array(CMD_START, 14);

      delay(15); // NOLINT
      this->write_array(value, 30);
      delay(15); // NOLINT
      this->write_array(CMD_CONF, 12);
      delay(15); // NOLINT
      // // 结束配置命令
      this->write_array(CMD_END, 12);
    }

    /** 配置最大移动检测距离 */
    void RA2413MTComponent::max_move_distance()
    {
      this->set_max_distances_timeout();
    }
    void RA2413MTComponent::max_static_distance()
    {
      this->set_max_distances_timeout();
    }
    void RA2413MTComponent::unattended_duration()
    {
      this->set_max_distances_timeout();
    }
    /** 设置能量触发值 */
    void RA2413MTComponent::set_sensitivity()
    {
      int move_sensitivity = static_cast<int>(this->move_sensitivity_number_->state);
      int static_sensitivity = static_cast<int>(this->static_sensitivity_number_->state);
      uint8_t value[30] = {
          0xFD, 0xFC, 0xFB, 0xFA,
          0x14, 0x00, 0x64, 0x00,
          0x00, 0x00, 0xFF, 0xFF,
          0x00, 0x00, 0x01, 0x00,
          lowbyte(move_sensitivity), 0x00, 0x00, 0x00,
          0x02, 0x00, lowbyte(static_sensitivity), 0x00,
          0x00, 0x00, 0x04, 0x03,
          0x02, 0x01};
      // ESP_LOGV(TAG, "配置最大移动检测距离 %02X", lowbyte(time));
      // 使能配置命令
      this->write_array(CMD_START, 14);

      delay(15); // NOLINT
      this->write_array(value, 30);
      delay(15); // NOLINT
      this->write_array(CMD_CONF, 12);
      delay(15); // NOLINT
      // // 结束配置命令
      this->write_array(CMD_END, 12);
    }
    void RA2413MTComponent::move_sensitivity() { this->set_sensitivity(); }
    void RA2413MTComponent::static_sensitivity() { this->set_sensitivity(); }
  }
}