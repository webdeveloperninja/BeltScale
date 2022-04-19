#pragma once
#include "driver/adc.h"
#define ADC1_EXAMPLE_CHAN0 ADC1_CHANNEL_6

class AnalogInput
{
public:
  AnalogInput(adc_atten_t attenuation, adc1_channel_t adc1_channel);

  void init();

  float get_voltage();

private:
  adc_atten_t attenuation;
  adc1_channel_t adc1_channel;
};