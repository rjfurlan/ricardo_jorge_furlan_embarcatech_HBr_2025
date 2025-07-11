#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// V:0.00 - 2025-04-16



// I2C_MAIN used by OLED
#define I2C_MAIN_GPIO_SCL      15
#define I2C_MAIN_GPIO_SDA      14
#define I2C_MAIN_BAUDRATE  400000
#define I2C_MAIN_BUS         i2c1

#define GPIO_BUTTON_A           5
#define GPIO_BUTTON_B           6
#define GPIO_BUZZER_A          21
#define GPIO_BUZZER_B          10   // WARNIG: Led G and Buzzer B share the same PWM slice
#define GPIO_LED_MATRIX         7
#define GPIO_LED_R             13
#define GPIO_LED_G             11   // WARNIG: Led G and Buzzer B share the same PWM slice
#define GPIO_LED_B             12
#define GPIO_JOYSTICK_BUTTON   22
#define GPIO_JOYSTICK_X        27
#define GPIO_JOYSTICK_Y        26
#define GPIO_MICROPHONE        28

#define AD_CHANNEL_JOYSTICK_X   1
#define AD_CHANNEL_JOYSTICK_Y   0
#define AD_CHANNEL_MICROPHONE   2
#define AD_CHANNEL_VSYS_1_3     3
#define AD_CHANNEL_CPU_TEMP     4


typedef enum {
    BUTTON_A        = GPIO_BUTTON_A,
    BUTTON_B        = GPIO_BUTTON_B,
    BUTTON_JOYSTICK = GPIO_JOYSTICK_BUTTON
} Button;

#endif
