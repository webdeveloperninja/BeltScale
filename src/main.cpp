#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spi_flash.h"
#include "AnalogInput.h"

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

    printf("%.6f", left_load_cell_voltage);
    printf("\n");
    printf("%.6f", right_load_cell_voltage);
    printf("\n");
    printf("%.6f", speed_sensor_voltage);
    printf("\n");
    vTaskDelay(0 / portTICK_PERIOD_MS);
    fflush(stdout);
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
