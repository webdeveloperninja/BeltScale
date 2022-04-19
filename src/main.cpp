#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spi_flash.h"
#include "AnalogInput.h"
#include "esp_system.h"
#include "UARTClient.h"

u_int sensor_sample_rate_minutes = 1;

uart_config_t uart_config = {
    .baud_rate = 23,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
};

int uart_port_number = 34;
int tx_io_number = 34;
int rx_io_number = 3;
int rts_io_number = 43;
int cts_io_number = 23;

u_int ms_ticks_per_minutes(int minutes)
{
  return minutes * 60000;
}

void sample_sensors(void *pvParameter)
{
  UARTClient uart_client(
      uart_config,
      uart_port_number,
      tx_io_number,
      rx_io_number,
      rts_io_number,
      cts_io_number);

  AnalogInput left_load_cell(ADC_ATTEN_DB_11, ADC1_CHANNEL_0);  // DIO36
  AnalogInput right_load_cell(ADC_ATTEN_DB_11, ADC1_CHANNEL_3); // DIO39
  AnalogInput speed_sensor(ADC_ATTEN_DB_11, ADC1_CHANNEL_6);    // DIO34

  left_load_cell.calibration_init();
  right_load_cell.calibration_init();
  speed_sensor.calibration_init();

  for (;;)
  {
    float left_load_cell_voltage = left_load_cell.get_voltage();
    float right_load_cell_voltage = right_load_cell.get_voltage();
    float speed_sensor_voltage = speed_sensor.get_voltage();

    printf("%.6f", left_load_cell_voltage);
    printf("\n");
    printf("%.6f", right_load_cell_voltage);
    printf("\n");
    printf("%.6f", speed_sensor_voltage);
    printf("\n");
    vTaskDelay(pdMS_TO_TICKS(ms_ticks_per_minutes(sensor_sample_rate_minutes)));
  }
}

extern "C"
{
  void app_main(void)
  {
    xTaskCreate(&sample_sensors, "sample_sensors", 4096, NULL, 5, NULL);
    fflush(stdout);
  }
}
