#include "zeroborg.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

__u8 buffer[I2C_NORM_LEN]; 

zeroborg handle=-1;

// Flashes the ZeroBorg LED 10 times
int FlashLed( )
{
	int i = 0;
	for( i = 0; i < 10; i++)
	{		
		i2c_smbus_write_byte_data(handle, COMMAND_SET_LED, COMMAND_VALUE_ON);
		usleep(50000);
		i2c_smbus_write_byte_data(handle, COMMAND_SET_LED, COMMAND_VALUE_OFF);
		usleep(50000);
	}
}
		
//ScanForZeroBorg([busNumber])
//Scans the I²C bus for a ZeroBorg boards and returns a list of all usable addresses
//The busNumber if supplied is which I²C bus to scan, 0 for Rev 1 boards, 1 for Rev 2 boards
int  ScanForZeroBorg(int busNumber)
{        
    printf("Init I²C bus #%d \n", busNumber);
	zeroborg zb = ZeroBorgInit( busNumber );
	if( zb < 0 )
	{
		printf("i2c open failed %d\n", zb );
		return 0;
	}

	printf("Scanning I²C bus with handle #%d \n", zb);
	
	__u8 command = COMMAND_SET_LED;
	__u8 level = COMMAND_VALUE_ON;	
	if( i2c_smbus_write_byte_data(handle, command, level) < 0 )
	{
		printf("i2c write byte failed\n");
	}
	
	command = COMMAND_GET_ID;	
    int recv = i2c_smbus_read_i2c_block_data(zb, command, I2C_NORM_LEN, buffer);
    printf("%d bytes returned from bus\n", recv);
    if( recv == I2C_NORM_LEN )
    {   
		printf("Buffer[1] = %x\n",buffer[1]);
		if( buffer[1] == I2C_ID_ZEROBORG )
		{
			printf("Found ZeroBorg\n");	
			FlashLed( );
			close(zb);
			return 1;
		}
	}
	
	close(zb);
	return 0;
}

//SetMotor(motor, power)
//Sets the drive level for motor 1, from +1 to -1.
//e.g.
//SetMotor(1, 0)     -> motor 1 is stopped
//SetMotor(1, 0.75)  -> motor 1 moving forward at 75% power
//SetMotor(1, -0.5)  -> motor 1 moving reverse at 50% power
//SetMotor(1, 1)     -> motor 1 moving forward at 100% power
int SetMotor(int motor, float power)
{
		if(handle < 0 )
		{
			printf("ZeroBorg not init\n");
			return(-1);
		}
		
		int pwm;
		__u8 command;
		
        if( power < 0 )
        {
            // Reverse
            switch (motor)
            {
            case 1:
				command = COMMAND_SET_A_REV;
				break;
			case 2:
				command = COMMAND_SET_B_REV;
				break;
			case 3:
				command = COMMAND_SET_C_REV;
				break;
			case 4:
				command = COMMAND_SET_D_REV;
				break;
			default:
				return 0;
			}
            pwm = (int)(-1 * PWM_MAX * power);
            if( pwm > PWM_MAX )
                pwm = PWM_MAX;
        }
        else
        {
            // Forward / stopped
            switch (motor)
            {
            case 1:
				command = COMMAND_SET_A_FWD;
				break;
			case 2:
				command = COMMAND_SET_B_FWD;
				break;
			case 3:
				command = COMMAND_SET_C_FWD;
				break;
			case 4:
				command = COMMAND_SET_D_FWD;
				break;
			default:
				return 0;
			}            
            pwm = (int)(PWM_MAX * power);
            if( pwm > PWM_MAX )
                pwm = PWM_MAX;
		}
       
        i2c_smbus_write_byte_data(handle, command, pwm);
}       

zeroborg ZeroBorgInit(int device)
{	
	char buf[15];
	snprintf(buf,15,"/dev/i2c-%d",device);
	if ((handle = open(buf, O_RDWR)) < 0) {
		return -2;
	}
	
	int addr = 0x40;
	if (ioctl(handle, I2C_SLAVE, addr) < 0) {
		close(handle);
		return -3;
	}
	
	//if( ioctl( handle, I2C_PEC, 0) < 0) {
		//fprintf(stderr, "Failed to disable PEC\n");
		//close(handle);
		//return -4; 
	//} 
		
	return handle;
}

