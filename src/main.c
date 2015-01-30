#include <config.h>
#include <stdio.h>
#include <modbus.h>

void poll(void)
{
  modbus_t *mb;
  uint16_t tab_reg[32];

  mb = modbus_new_rtu("/dev/ttyS0", 9600, 'n', 8, 1 );

  modbus_connect(mb);

  /* Read 5 registers from the address 0 */
  modbus_read_registers(mb, 0, 5, tab_reg);

  modbus_close(mb);
  modbus_free(mb);
}

int main (void)
{
  int vermaj = libmodbus_version_major;
  int vermin = libmodbus_version_minor;
  int vermic = libmodbus_version_micro;


  puts ("Hello World!");
  puts ("This is " PACKAGE_STRING ".");
  printf("Modbus library version: %i.%i.%i\n", vermaj, vermin, vermic);
  poll();
  return 0;
}


