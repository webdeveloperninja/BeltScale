#include "AnalogInput.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define DEFAULT_VREF 1100 // Use adc2_vref_to_gpio() to obtain a better estimate

static esp_adc_cal_characteristics_t *adc_chars;

static void check_efuse(void)
{
#if CONFIG_IDF_TARGET_ESP32
  if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK)
  {
    printf("eFuse Two Point: Supported\n");
  }
  else
  {
    printf("eFuse Two Point: NOT supported\n");
  }
  // Check Vref is burned into eFuse
  if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK)
  {
    printf("eFuse Vref: Supported\n");
  }
  else
  {
    printf("eFuse Vref: NOT supported\n");
  }
#endif
}

AnalogInput::AnalogInput(adc_atten_t attenuation, adc1_channel_t adc1_channel)
{
  AnalogInput::attenuation = attenuation;
  AnalogInput::adc1_channel = adc1_channel;
}

uint32_t adc_reading = 0;

void AnalogInput::calibration_init()
{
  check_efuse();
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(AnalogInput::adc1_channel, AnalogInput::attenuation);

  adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, AnalogInput::attenuation, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
}

float AnalogInput::get_voltage()
{
  adc_reading += adc1_get_raw((adc1_channel_t)AnalogInput::adc1_channel);

  uint32_t mili_voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
  adc_reading = 0;

  return (float)mili_voltage * .001;
}
