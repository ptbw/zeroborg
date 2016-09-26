#ifdef __cplusplus
extern "C"{
#endif 

typedef int zeroborg;

#define PWM_MAX 		255
#define I2C_NORM_LEN 	4
#define I2C_LONG_LEN 	24

#define I2C_ID_ZEROBORG 0x40

#define COMMAND_SET_LED          1     // Set the LED status
#define COMMAND_GET_LED          2     // Get the LED status
#define COMMAND_SET_A_FWD        3     // Set motor 1 PWM rate in a forwards direction
#define COMMAND_SET_A_REV        4     // Set motor 1 PWM rate in a reverse direction
#define COMMAND_GET_A            5     // Get motor 1 direction and PWM rate
#define COMMAND_SET_B_FWD        6     // Set motor 2 PWM rate in a forwards direction
#define COMMAND_SET_B_REV        7     // Set motor 2 PWM rate in a reverse direction
#define COMMAND_GET_B            8     // Get motor 2 direction and PWM rate
#define COMMAND_SET_C_FWD        9     // Set motor 3 PWM rate in a forwards direction
#define COMMAND_SET_C_REV        10    // Set motor 3 PWM rate in a reverse direction
#define COMMAND_GET_C            11    // Get motor 3 direction and PWM rate
#define COMMAND_SET_D_FWD        12    // Set motor 4 PWM rate in a forwards direction
#define COMMAND_SET_D_REV        13    // Set motor 4 PWM rate in a reverse direction
#define COMMAND_GET_D            14    // Get motor 4 direction and PWM rate
#define COMMAND_ALL_OFF          15    // Switch everything off
#define COMMAND_SET_ALL_FWD      16    // Set all motors PWM rate in a forwards direction
#define COMMAND_SET_ALL_REV      17    // Set all motors PWM rate in a reverse direction
#define COMMAND_SET_FAILSAFE     18    // Set the failsafe flag, turns the motors off if communication is interrupted
#define COMMAND_GET_FAILSAFE     19    // Get the failsafe flag
#define COMMAND_RESET_EPO        20    // Resets the EPO flag, use after EPO has been tripped and switch is now clear
#define COMMAND_GET_EPO          21    // Get the EPO latched flag
#define COMMAND_SET_EPO_IGNORE   22    // Set the EPO ignored flag, allows the system to run without an EPO
#define COMMAND_GET_EPO_IGNORE   23    // Get the EPO ignored flag
#define COMMAND_GET_NEW_IR       24    // Get the new IR message received flag
#define COMMAND_GET_LAST_IR      25    // Get the last IR message received (long message, resets new IR flag)
#define COMMAND_SET_LED_IR       26    // Set the LED for indicating IR messages
#define COMMAND_GET_LED_IR       27    // Get if the LED is being used to indicate IR messages
#define COMMAND_GET_ANALOG_1     28    // Get the analog reading from port //1, pin 2
#define COMMAND_GET_ANALOG_2     29    // Get the analog reading from port //2, pin 4
#define COMMAND_GET_ID           0x99  // Get the board identifier
#define COMMAND_SET_I2C_ADD      0xAA  // Set a new I2C address

#define COMMAND_VALUE_FWD        1     // I2C value representing forward
#define COMMAND_VALUE_REV        2     // I2C value representing reverse

#define COMMAND_VALUE_ON         1     // I2C value representing on
#define COMMAND_VALUE_OFF        0     // I2C value representing off

#define COMMAND_ANALOG_MAX       0x3FF // Maximum value for analog readings

#define IR_MAX_BYTES             I2C_LONG_LEN - 2

int FlashLed( );

int ScanForZeroBorg(int device);

int SetMotor(int motor, float power);

int ZeroBorgInit(int device);

#ifdef __cplusplus
}
#endif
