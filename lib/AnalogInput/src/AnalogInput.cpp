#include "AnalogInput.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

AnalogInput::AnalogInput(adc_atten_t attenuation, adc1_channel_t adc1_channel)
{
  AnalogInput::attenuation = attenuation;
  AnalogInput::adc1_channel = adc1_channel;
}

void AnalogInput::calibration_init()
{
}

float AnalogInput::get_voltage()
{
}
