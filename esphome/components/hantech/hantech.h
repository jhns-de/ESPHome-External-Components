#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace hantech {

// Temperature
const uint8_t HANTECH_TEMP_MIN = 16;          // Celsius
const uint8_t HANTECH_TEMP_MAX = 31;          // Celsius

// IR Transmission
const uint32_t HANTECH_IR_FREQUENCY = 38000;
const uint32_t HANTECH_HEADER_MARK = 9000;
const uint32_t HANTECH_HEADER_SPACE = 4500;
const uint32_t HANTECH_BIT_DURATION = 500;

const uint8_t HANTECH_INIT_1 = 0b11110101;
const uint8_t HANTECH_INIT_2 = 0b11101111;

const uint8_t HANTECH_MODE_FAN = 0b00110000;
const uint8_t HANTECH_MODE_AC = 0b01100000;
const uint8_t HANTECH_MODE_DRY = 0b01010000;

const uint8_t HANTECH_FAN_HIGH = 0b00011000;
const uint8_t HANTECH_FAN_MED  = 0b00101000;
const uint8_t HANTECH_FAN_LOW  = 0b00110000;


class HantechClimate : public climate_ir::ClimateIR {
  public:
    HantechClimate()
        : climate_ir::ClimateIR(HANTECH_TEMP_MIN, HANTECH_TEMP_MAX, 1.0f, true, true/*,
                              {climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
                              {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL},
                              {climate::CLIMATE_PRESET_NONE, climate::CLIMATE_PRESET_SLEEP}*/) {}
  protected:
    // Transmit via IR the state of this climate controller.
    void transmit_state() override;
    uint8_t * operation_mode_();
    // uint8_t fan_speed_();
    uint8_t * temperature_();
    // Handle received IR Buffer
    // bool on_receive(remote_base::RemoteReceiveData data) override;
    // bool parse_state_frame_(const uint8_t frame[]);
};

} // namespace hantech
} // namespace esphome
