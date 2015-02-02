#include <config.h>
#include <stdio.h>
#include <modbus.h>

void poll(void)
{
  modbus_t *mb;
  uint16_t tab_reg[32];
  printf("1");
  mb = modbus_new_rtu("/dev/ttyS0", 9600, 'n', 8, 1 );
  printf("2");
  modbus_connect(mb);
  printf("3");
  modbus_set_slave(mb, 1);
  printf("4");
  /* Read 5 registers from the address 0 */
  modbus_read_registers(mb, 0, 5, tab_reg);
  printf("6");
  modbus_close(mb);
  printf("7");
  modbus_free(mb);
  printf("8");
}

int main (void)
{
  int vermaj = libmodbus_version_major;
  int vermin = libmodbus_version_minor;
  int vermic = libmodbus_version_micro;


  puts ("2:Hello Modbus!");
  puts ("This is " PACKAGE_STRING ".");
  printf("Modbus library version: %i.%i.%i\n", vermaj, vermin, vermic);
  poll();
  return 0;
}


