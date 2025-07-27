#include "hantech.h"
#include "esphome/core/log.h"
#include "esphome/components/remote_base/remote_base.h"
#include <string>

namespace esphome
{
  namespace hantech
  {

    static const char *const TAG = "hantech.climate";

    void HantechClimate::transmit_state()
    {
      uint8_t *remote_state;
      remote_state = this->operation_mode_();

      auto transmit = this->transmitter_->transmit();
      auto *data = transmit.get_data();
      data->set_carrier_frequency(HANTECH_IR_FREQUENCY);

      data->mark(HANTECH_HEADER_MARK);
      data->space(HANTECH_HEADER_SPACE);

      for (uint8_t x = 0; x < 10; x++)
      {
        uint8_t frame = remote_state[x];
        for (int8_t i = 7; i >= 0; i--) // doesnt work with unsigned!
        {
          bool bit = frame & (1 << i);

          if (bit == true)
          {
            data->mark(HANTECH_BIT_DURATION);
          }
          else
          {
            // ESP_LOGI(TAG, "ENCODE 0");
            data->space(HANTECH_BIT_DURATION);
          }
          // send space as every second signal
          data->space(HANTECH_BIT_DURATION);
        }
      }

      transmit.perform();
    }

    uint8_t *HantechClimate::operation_mode_()
    {
      static uint8_t dry[] = {0b11110101, 0b11101111, 0b11011111, 0b11110111, 0b10110111, 0b11111111, 0b11111111, 0b10101101, 0b11010000, 0b00000000};
      static uint8_t fan[] = {0b11110101, 0b11101111, 0b10111111, 0b11110111, 0b10110111, 0b11111111, 0b11111111, 0b10101110, 0b10101000, 0b00000000};
      // off 18
      static uint8_t off[] = {0b11110101, 0b11111111, 0b11011111, 0b11101111, 0b01110111, 0b11111111, 0b11111110, 0b10101101, 0b01110000, 0b00000000};
      switch (this->mode)
      {
      case climate::CLIMATE_MODE_HEAT_COOL:
      case climate::CLIMATE_MODE_COOL:
        return this->temperature_();
        break;
      case climate::CLIMATE_MODE_DRY:
        return dry;
        break;
      case climate::CLIMATE_MODE_FAN_ONLY:
        return fan;
        break;
      case climate::CLIMATE_MODE_OFF:
        return off;
        break;
      default:
        ESP_LOGW(TAG, "Mode not implemented!");
        return off;
        break;
      }
    }

    uint8_t *HantechClimate::temperature_()
    {
      static uint8_t deg16[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10111111, 0b11111111, 0b11111111, 0b01011010, 0b10110000, 0b00000000};
      static uint8_t deg17[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10111101, 0b11111111, 0b11111111, 0b10101101, 0b01101000, 0b00000000};
      static uint8_t deg18[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10111011, 0b11111111, 0b11111111, 0b10101101, 0b01110000, 0b00000000};
      static uint8_t deg19[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10111010, 0b11111111, 0b11111111, 0b11010110, 0b11010100, 0b00000000};
      static uint8_t deg20[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10110111, 0b11111111, 0b11111111, 0b10101101, 0b10110000, 0b00000000};
      static uint8_t deg21[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10110110, 0b11111111, 0b11111111, 0b11010110, 0b11101000, 0b00000000};
      static uint8_t deg22[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10110101, 0b11111111, 0b11111111, 0b11010110, 0b11110000, 0b00000000};
      static uint8_t deg23[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10110101, 0b01111111, 0b11111111, 0b11101011, 0b10101010, 0b00000000};
      static uint8_t deg24[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101111, 0b11111111, 0b11111111, 0b10101110, 0b10110000, 0b00000000};
      static uint8_t deg25[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101110, 0b11111111, 0b11111111, 0b11010111, 0b01101000, 0b00000000};
      static uint8_t deg26[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101101, 0b11111111, 0b11111111, 0b11010111, 0b01110000, 0b00000000};
      static uint8_t deg27[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101101, 0b01111111, 0b11111111, 0b11101011, 0b11010100, 0b00000000};
      static uint8_t deg28[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101011, 0b11111111, 0b11111111, 0b11010111, 0b10110000, 0b00000000};
      static uint8_t deg29[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101011, 0b01111111, 0b11111111, 0b11101011, 0b11101000, 0b00000000};
      static uint8_t deg30[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101010, 0b11111111, 0b11111111, 0b11101011, 0b11110000, 0b00000000};
      static uint8_t deg31[] = {0b11110101, 0b11101111, 0b11101111, 0b11110111, 0b10101010, 0b10111111, 0b11111111, 0b11110110, 0b10101010, 0b10000000};
      uint8_t temp = (uint8_t)roundf(clamp<float>(this->target_temperature, HANTECH_TEMP_MIN, HANTECH_TEMP_MAX));
      switch (temp)
      {
      case 16:
        return deg16;
        break;
      case 17:
        return deg17;
        break;
      case 18:
        return deg18;
        break;
      case 19:
        return deg19;
        break;
      case 20:
        return deg20;
        break;
      case 21:
        return deg21;
        break;
      case 22:
        return deg22;
        break;
      case 23:
        return deg23;
        break;
      case 24:
        return deg24;
        break;
      case 25:
        return deg25;
        break;
      case 26:
        return deg26;
        break;
      case 27:
        return deg27;
        break;
      case 28:
        return deg28;
        break;
      case 29:
        return deg29;
        break;
      case 30:
        return deg30;
        break;
      case 31:
        return deg31;
        break;
      default:
        ESP_LOGW(TAG, "Temperature out of range!");
      }
      return deg22;
    }

  } // namespace hantech
} // namespace esphome