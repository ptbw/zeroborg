#include "zeroborg.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char buffer[I2C_NORM_LEN]; 

//ScanForZeroBorg([busNumber])
//Scans the I²C bus for a ZeroBorg boards and returns a list of all usable addresses
//The busNumber if supplied is which I²C bus to scan, 0 for Rev 1 boards, 1 for Rev 2 boards
int  ScanForZeroBorg(int busNumber)
{        
    printf("Init I²C bus #%d \n", busNumber);
	zeroborg handle = ZeroBorgInit( busNumber );
	if( handle < 0 )
		return handle;

	printf("Scanning I²C bus #%d \n", busNumber);
    int recv = i2c_smbus_read_block_data(handle, COMMAND_GET_ID, buffer);
    printf("%d bytes returned from bus\n", recv);
    if( recv == I2C_NORM_LEN )
		if( buffer[0] == I2C_ID_ZEROBORG )
		{
			printf("Found ZeroBorg\n");	
			close(handle);
			return 1;
		}
	
	close(handle);
	return 0;
}


zeroborg ZeroBorgInit(int device)
{
	zeroborg handle=-1;
	char buf[15];
	snprintf(buf,15,"/dev/i2c-%d",device);
	if ((handle = open(buf, O_RDWR)) < 0) {
		return -2;
	}
	
	int addr = 0x29;
	if (ioctl(handle, I2C_SLAVE, addr) < 0) {
		close(handle);
		return -3;
	}
	
	
	return handle;
}

