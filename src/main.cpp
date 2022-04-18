#include "AnalogInput.h"
#include "UART.h"
#include <stdio.h>

extern "C"
{
  void app_main(void)
  {
    AnalogInput left_load_cell(ADC_ATTEN_DB_11, ADC1_CHANNEL_0);  // DIO36
    AnalogInput right_load_cell(ADC_ATTEN_DB_11, ADC1_CHANNEL_3); // DIO39
    AnalogInput speed_sensor(ADC_ATTEN_DB_11, ADC1_CHANNEL_6);    // DIO34

    float left_load_cell_voltage = left_load_cell.get_voltage();
    float right_load_cell_voltage = right_load_cell.get_voltage();
    float speed_sensor_voltage = speed_sensor.get_voltage();

    printf("%6.4lf", left_load_cell_voltage);
    printf("%6.4lf", right_load_cell_voltage);
    printf("%6.4lf", speed_sensor_voltage);
  }
}

/*

1) Read 3 analog inputs
    -- Left load cell
    -- Right load cell
    -- Speed sensor

2) On an interval send senor data to Comm module
    -- Default interval n minutes eg: 10 min
    -- On change interval n minutes. Left load cell changes by x percent eg 2 min
*/
