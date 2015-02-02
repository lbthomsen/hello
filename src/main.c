#include <config.h>
#include <stdio.h>
#include <errno.h>
#include <modbus.h>

void poll(void)
{
  puts("0");
  modbus_t *mb;
  uint16_t tab_reg[32];
  puts("1");
  mb = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1 );
  puts("2");
  modbus_set_debug( mb, TRUE );
  puts("2.1");
  modbus_set_slave(mb, 1);
  puts("3");
  modbus_connect(mb);
  puts("4");
  /* Read 5 registers from the address 0 */
  int bytes_read  = modbus_read_registers(mb, 0, 5, tab_reg);
  if( bytes_read == -1 )
  {
    puts("5");
    printf("Error:%s\n", modbus_strerror(errno));
  }
  puts("6");
  modbus_close(mb);
  puts("7");
  modbus_free(mb);
  puts("8");
}

int main (void)
{
  int vermaj = libmodbus_version_major;
  int vermin = libmodbus_version_minor;
  int vermic = libmodbus_version_micro;

  puts ("11:Hello Modbus!");
  puts ("This is " PACKAGE_STRING ".");
  printf("Modbus library version: %i.%i.%i\n", vermaj, vermin, vermic);
  poll();
  return 0;
}


