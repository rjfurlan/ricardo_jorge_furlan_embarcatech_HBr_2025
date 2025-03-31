#ifndef BITDOGLAB_DEFS
#define BITDOGLAB_DEFS

// V:0.00 - 2025-01-23
// V:0.01 - 2025-02-08
// V:0.02 - 2025-02-09


// WARNIGNG:   Led G e Buzzer B compartilham o mesmo PWM slice

#define BITDOGLAB_GPIO_OLED_I2C_SCL      15
#define BITDOGLAB_GPIO_OLED_I2C_SDA      14
#define BITDOGLAB_GPIO_BUTTON_A           5
#define BITDOGLAB_GPIO_BUTTON_B           6
#define BITDOGLAB_GPIO_BUZZER_A          21
#define BITDOGLAB_GPIO_BUZZER_B          10
#define BITDOGLAB_GPIO_LED_MATRIX         7
#define BITDOGLAB_GPIO_LED_R             13
#define BITDOGLAB_GPIO_LED_G             11
#define BITDOGLAB_GPIO_LED_B             12
#define BITDOGLAB_GPIO_JOYSTICK_BUTTON   22
#define BITDOGLAB_GPIO_JOYSTICK_X        27
#define BITDOGLAB_GPIO_JOYSTICK_Y        26
#define BITDOGLAB_GPIO_MICROPHONE        28

#define BITDOGLAB_AD_JOYSTICK_X      1
#define BITDOGLAB_AD_JOYSTICK_Y      0
#define BITDOGLAB_AD_MICROPHONE      2
#define BITDOGLAB_AD_VSYS_1_3        3
#define BITDOGLAB_AD_TEMP            4

#define BITDOGLAB_I2C_BUS               i2c1
#define BITDOGLAB_I2C_BUS_BAUDRATE      400000
#define BITDOGLAB_I2C_BUS_GPIO_SCL      15
#define BITDOGLAB_I2C_BUS_GPIO_SDA      14


#endif