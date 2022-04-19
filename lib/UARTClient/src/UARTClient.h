#include "driver/uart.h"

#pragma once

class UARTClient
{
public:
  UARTClient(
      uart_config_t uart_configuration,
      int uart_port_num,
      int tx_io_num,
      int rx_io_num,
      int rts_io_num,
      int cts_io_num);

  void init();

  void transmit(char *payload);

private:
  uart_config_t uart_configuration;
  int uart_port_num;
  int tx_io_num;
  int rx_io_num;
  int rts_io_num;
  int cts_io_num;
};