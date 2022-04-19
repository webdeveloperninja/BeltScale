#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "UARTClient.h"

#define BUF_SIZE (1024)

UARTClient::UARTClient(
    uart_config_t uart_configuration,
    int uart_port_num,
    int tx_io_num,
    int rx_io_num,
    int rts_io_num,
    int cts_io_num)
{
  UARTClient::uart_configuration = uart_configuration;
  UARTClient::uart_port_num = uart_port_num;
  UARTClient::tx_io_num = tx_io_num;
  UARTClient::rx_io_num = rx_io_num;
  UARTClient::rts_io_num = rts_io_num;
  UARTClient::cts_io_num = cts_io_num;
}

void UARTClient::init()
{
  uart_config_t uart_config = {
      .baud_rate = UARTClient::uart_configuration.baud_rate,
      .data_bits = UARTClient::uart_configuration.data_bits,
      .parity = UARTClient::uart_configuration.parity,
      .stop_bits = UARTClient::uart_configuration.stop_bits,
      .flow_ctrl = UARTClient::uart_configuration.flow_ctrl,
      .source_clk = UARTClient::uart_configuration.source_clk,
  };

  int intr_alloc_flags = 0;

  ESP_ERROR_CHECK(
      uart_driver_install(
          UARTClient::uart_port_num,
          BUF_SIZE * 2,
          0,
          0,
          NULL,
          intr_alloc_flags));

  ESP_ERROR_CHECK(
      uart_param_config(
          UARTClient::uart_port_num,
          &uart_config));

  ESP_ERROR_CHECK(
      uart_set_pin(
          UARTClient::uart_port_num,
          UARTClient::tx_io_num,
          UARTClient::rx_io_num,
          UARTClient::rts_io_num,
          UARTClient::cts_io_num));
}

void UARTClient::transmit(const char *payload)
{
  uart_write_bytes(UARTClient::uart_port_num, payload, sizeof payload);
}
