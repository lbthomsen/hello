#include <config.h>
#include <stdio.h>
#include <errno.h>
#include <modbus.h>
#include <iostream.h>
#include <fcntl.h>
#include <stropts.h>
#include <termios.h>

void flip(void)
{
    int fd;
    cout << "CP210x Serial Test\n";
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        cout << "Error opening port /dev/ttyUSB0\n";
        return -1;
    }

    unsigned long gpio;

    ioctl(fd, 0x8000, &gpio);
    cout << "original gpio = ";
    cout << hex << gpio << endl;
    gpio = ~gpio;
    gpio = gpio << 8;
    gpio |= 0x00FF;
    cout << "gpio = ";
    cout << hex << gpio << endl;
    ioctl(fd, 0x8001, &gpio);
    ioctl(fd, 0x8000, &gpio);
    cout << "new gpio = ";
    cout << hex << gpio << endl;

    close(fd);

    return 0;
}

void poll(void)
{
  puts("0");
  modbus_t *mb;
  uint16_t tab_reg[32];
  puts("1");
  mb = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1 );
  if( mb == NULL )
  {
      puts( "Unable to open port." );
      return;
  }
  puts("2");
  modbus_set_debug( mb, TRUE );
  puts("2.1");
  modbus_set_slave(mb, 1);
  
  modbus_rtu_set_serial_mode( mb, MODBUS_RTU_RS485 );
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
  flip();
  poll();
  return 0;
}


