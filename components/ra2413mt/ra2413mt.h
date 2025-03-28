#pragma once
#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif
#ifdef USE_BUTTON
#include "esphome/components/button/button.h"
#endif
#ifdef USE_SELECT
#include "esphome/components/select/select.h"
#endif
#ifdef USE_TEXT_SENSOR
#include "esphome/components/text_sensor/text_sensor.h"
#endif
#include "esphome/components/uart/uart.h"
#include "esphome/core/automation.h"
#include "esphome/core/helpers.h"

#include <map>

namespace esphome
{
  namespace ra2413mt
  {

    // 运动信息等级 00:无 01：静止02：活跃
    enum BodyMovementLevelStructure : uint8_t
    {
      BODY_MOVEMENT_LEVEL_NONE = 0x01,
      BODY_MOVEMENT_LEVEL_STATIC = 0x02,
      BODY_MOVEMENT_LEVEL_MOVE = 0x03,
      BODY_MOVEMENT_LEVEL_MOVEMENT = 0x04,
    };
    static const std::map<std::string, uint8_t> BODY_MOVEMENT_LEVEL_ENUM_TO_INT{{"none", BODY_MOVEMENT_LEVEL_NONE}, {"static", BODY_MOVEMENT_LEVEL_STATIC}, {"move", BODY_MOVEMENT_LEVEL_MOVE}, {"move", BODY_MOVEMENT_LEVEL_MOVEMENT}};
    static const std::map<uint8_t, std::string> BODY_MOVEMENT_LEVEL_INT_TO_ENUM{{BODY_MOVEMENT_LEVEL_NONE, "none"}, {BODY_MOVEMENT_LEVEL_STATIC, "static"}, {BODY_MOVEMENT_LEVEL_MOVE, "move"}, {BODY_MOVEMENT_LEVEL_MOVEMENT, "move"}};
    // 呼吸状态 01：正常 02：呼吸过高 03：呼吸过低 04：无
    enum BreatheMonitorLevelStructure : uint8_t
    {
      BREATHE_MONITOR_LEVEL_NORMAL = 0x01,
      BREATHE_MONITOR_LEVEL_HIGH = 0x02,
      BREATHE_MONITOR_LEVEL_LOW = 0x03,
      BREATHE_MONITOR_LEVEL_NONE = 0x04
    };
    static const std::map<std::string, uint8_t> BREATHE_MONITOR_LEVEL_ENUM_TO_INT{{"normal", BREATHE_MONITOR_LEVEL_NORMAL}, {"high", BREATHE_MONITOR_LEVEL_HIGH}, {"low", BREATHE_MONITOR_LEVEL_LOW}, {"none", BREATHE_MONITOR_LEVEL_NONE}};
    static const std::map<uint8_t, std::string> BREATHE_MONITOR_LEVEL_INT_TO_ENUM{{BREATHE_MONITOR_LEVEL_NORMAL, "normal"}, {BREATHE_MONITOR_LEVEL_HIGH, "high"}, {BREATHE_MONITOR_LEVEL_LOW, "low"}, {BREATHE_MONITOR_LEVEL_NONE, "none"}};
    // 入床\离床状态
    enum InOutBedStateStructure : uint8_t
    {
      IN_OUT_BED_STATE_OUT = 0x00,
      IN_OUT_BED_STATE_IN = 0x01,
      IN_OUT_BED_STATE_NONE = 0x02
    };
    static const std::map<std::string, uint8_t> IN_OUT_BED_STATE_ENUM_TO_INT{{"out", IN_OUT_BED_STATE_OUT}, {"in", IN_OUT_BED_STATE_IN}, {"none", IN_OUT_BED_STATE_NONE}};
    static const std::map<uint8_t, std::string> IN_OUT_BED_STATE_INT_TO_ENUM{{IN_OUT_BED_STATE_OUT, "out"}, {IN_OUT_BED_STATE_IN, "in"}, {IN_OUT_BED_STATE_NONE, "none"}};
    // 睡眠状态 00：深睡 01：浅睡 02：清醒 03：无
    enum SleepStateLevelStructure : uint8_t
    {
      SLEEP_STATE_LEVEL_DEEP = 0x00,
      SLEEP_STATE_LEVEL_SHALLOW = 0x01,
      SLEEP_STATE_LEVEL_WAKE = 0x02,
      SLEEP_STATE_LEVEL_NONE = 0x03
    };
    static const std::map<std::string, uint8_t> SLEEP_STATE_LEVEL_ENUM_TO_INT{{"deep", SLEEP_STATE_LEVEL_DEEP}, {"shallow", SLEEP_STATE_LEVEL_SHALLOW}, {"wake", SLEEP_STATE_LEVEL_WAKE}, {"none", SLEEP_STATE_LEVEL_NONE}};
    static const std::map<uint8_t, std::string> SLEEP_STATE_LEVEL_INT_TO_ENUM{{SLEEP_STATE_LEVEL_DEEP, "deep"}, {SLEEP_STATE_LEVEL_SHALLOW, "shallow"}, {SLEEP_STATE_LEVEL_WAKE, "wake"}, {SLEEP_STATE_LEVEL_NONE, "none"}};
    // 睡眠异常状态
    enum SleepUnusualStateStructure : uint8_t
    {
      SLEEP_UNUSUAL_STATE_SHORT = 0x00,
      SLEEP_UNUSUAL_STATE_LONG = 0x01,
      SLEEP_UNUSUAL_STATE_NOBODY = 0x02,
      SLEEP_UNUSUAL_STATE_NONE = 0x03,
    };
    static const std::map<std::string, uint8_t> SLEEP_UNUSUAL_STATE_ENUM_TO_INT{{"short", SLEEP_UNUSUAL_STATE_SHORT}, {"long", SLEEP_UNUSUAL_STATE_LONG}, {"nobody", SLEEP_UNUSUAL_STATE_NOBODY}, {"none", SLEEP_UNUSUAL_STATE_NONE}};
    static const std::map<uint8_t, std::string> SLEEP_UNUSUAL_STATE_INT_TO_ENUM{{SLEEP_UNUSUAL_STATE_SHORT, "short"}, {SLEEP_UNUSUAL_STATE_LONG, "long"}, {SLEEP_UNUSUAL_STATE_NOBODY, "nobody"}, {SLEEP_UNUSUAL_STATE_NONE, "none"}};
    // 上报模式
    enum ReportingModeStateStructure : uint8_t
    {
      REPORTING_MODE_STATE_ACTUAL_TIME = 0x00,
      REPORTING_MODE_STATE_SLEEP_TIME = 0x01,
    };
    static const std::map<std::string, uint8_t> REPORTING_MODE_STATE_ENUM_TO_INT{{"actual", REPORTING_MODE_STATE_ACTUAL_TIME}, {"sleep", REPORTING_MODE_STATE_SLEEP_TIME}};
    static const std::map<uint8_t, std::string> REPORTING_MODE_STATE_INT_TO_ENUM{{REPORTING_MODE_STATE_ACTUAL_TIME, "actual"}, {REPORTING_MODE_STATE_SLEEP_TIME, "sleep"}};
    // 睡眠质量
    enum SleepQualityStateStructure : uint8_t
    {
      SLEEP_QUALITY_STATE_NONE = 0x00,
      SLEEP_QUALITY_STATE_GOOD = 0x01,
      SLEEP_QUALITY_STATE_COMMONLY = 0x02,
      SLEEP_QUALITY_STATE_POOR = 0x03,
    };
    static const std::map<std::string, uint8_t> SLEEP_QUALITY_STATE_ENUM_TO_INT{{"none", SLEEP_QUALITY_STATE_NONE}, {"good", SLEEP_QUALITY_STATE_GOOD}, {"commonly", SLEEP_QUALITY_STATE_COMMONLY}, {"poor", SLEEP_QUALITY_STATE_POOR}};
    static const std::map<uint8_t, std::string> SLEEP_QUALITY_STATE_INT_TO_ENUM{{SLEEP_QUALITY_STATE_NONE, "none"}, {SLEEP_QUALITY_STATE_GOOD, "good"}, {SLEEP_QUALITY_STATE_COMMONLY, "commonly"}, {SLEEP_QUALITY_STATE_POOR, "poor"}};
    // 异常挣扎状态上报
    enum SleepUnusualMonitorStateStructure : uint8_t
    {
      SLEEP_UNUSUAL_MONITOR_STATE_NONE = 0x00,
      SLEEP_UNUSUAL_MONITOR_STATE_NORMAL = 0x01,
      SLEEP_UNUSUAL_MONITOR_STATE_ABNORMAL = 0x02,
    };
    static const std::map<std::string, uint8_t> SLEEP_UNUSUAL_MONITOR_STATE_ENUM_TO_INT{{"none", SLEEP_UNUSUAL_MONITOR_STATE_NONE}, {"normal", SLEEP_UNUSUAL_MONITOR_STATE_NORMAL}, {"abnormal", SLEEP_UNUSUAL_MONITOR_STATE_ABNORMAL}};
    static const std::map<uint8_t, std::string> SLEEP_UNUSUAL_MONITOR_STATE_INT_TO_ENUM{{SLEEP_UNUSUAL_MONITOR_STATE_NONE, "none"}, {SLEEP_UNUSUAL_MONITOR_STATE_NORMAL, "normal"}, {SLEEP_UNUSUAL_MONITOR_STATE_ABNORMAL, "abnormal"}};

    // Command Header & Footer
    static const uint8_t CMD_FRAME_HEADER[4] = {0xFD, 0xFC, 0xFB, 0xFA};
    static const uint8_t CMD_FRAME_END[4] = {0x04, 0x03, 0x02, 0x01};

    static const uint8_t ENABLE_CMD_VALUE[1] = {0x01};
    static const uint8_t DISABLE_CMD_VALUE[1] = {0x00};

    // 使能配置
    static const uint8_t CMD_START[14] = {0xFD, 0xFC, 0xFB, 0xFA, 0x04, 0x00, 0xFF, 0x00, 0x01, 0x00, 0x04, 0x03, 0x02, 0x01};
    // 结束使能配置
    static const uint8_t CMD_END[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x02, 0x00, 0xFE, 0x00, 0x04, 0x03, 0x02, 0x01};
    // 获取配置
    static const uint8_t CMD_CONF[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x02, 0x00, 0x61, 0x00, 0x04, 0x03, 0x02, 0x01};

    static const uint8_t CMD_TEST[30] = {0xFD, 0xFC, 0xFB, 0xFA, 0x14, 0x00, 0x60, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x03, 0x02, 0x01};
    // 默认距离配置
    static const uint8_t CMD_DEFAUT_DISTANCE[30] = {0xFD, 0xFC, 0xFB, 0xFA, 0x14, 0x00, 0x60, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x03, 0x02, 0x01};
    // 默认灵敏度配置
    static const uint8_t CMD_DEFAUT_SENSITIVITY[30] = {0xFD, 0xFC, 0xFB, 0xFA, 0x14, 0x00, 0x64, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x00, 0x63, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x04, 0x03, 0x02, 0x01};
    //

    enum AckDataStructure : uint8_t
    {
      CONTROL = 2,
      COMMAND = 3,
      COMMAND_STATUS = 6
    };

    class RA2413MTComponent : public Component, public uart::UARTDevice
    {
#ifdef USE_SENSOR
      SUB_SENSOR(move_distance)
      SUB_SENSOR(move_energy)
      SUB_SENSOR(static_distance)
      SUB_SENSOR(static_energy)
#endif
#ifdef USE_TEXT_SENSOR
      SUB_TEXT_SENSOR(status)
#endif
#ifdef USE_NUMBER
      SUB_NUMBER(max_move_distance)
      SUB_NUMBER(max_static_distance)
      SUB_NUMBER(unattended_duration)
      SUB_NUMBER(move_sensitivity)
      SUB_NUMBER(static_sensitivity)
#endif
#ifdef USE_BUTTON
      SUB_BUTTON(query_conf)
      SUB_BUTTON(reset_mmw)
#endif
    public:
      RA2413MTComponent();
      void dump_config() override;
      void setup() override;
      void read_all_info();
      void loop() override;
      void set_throttle(uint16_t value) { this->throttle_ = value; };
      void set_max_distances_timeout();
      void max_move_distance();
      void max_static_distance();
      void unattended_duration();
      void set_sensitivity();
      void move_sensitivity();
      void static_sensitivity();
      void get_config();
      void reset_mmw();

    protected:
      void readline_(int readch, uint8_t *buffer, int len);
      void handle_periodic_data_(uint8_t *buffer, int len);
      bool handle_ack_data_(uint8_t *buffer, int len);
      void send_control_command_();

      uint16_t throttle_;
      int32_t last_periodic_millis_ = millis();
    };

  }
}