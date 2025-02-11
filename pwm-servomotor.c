#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_SERVO 22 // Pin to control the servo motor
// #define PWM_SERVO 12 // Pin to control the led

const float PWM_FREQUENCY = 50.0; // 50Hz frequency (20ms period)
const uint16_t WRAP_PERIOD = 40000; // 50Hz max value to counter
const float PWM_DIVISER = 64.0; // adjust PWM clock 

// duty cycle values for 0, 90 and 180 degrees
uint16_t DUTY_180 = 2400; // 2400µs -> 180 degrees
uint16_t DUTY_90 = 1470;  // 1470µs -> 90 degrees
uint16_t DUTY_0 = 500;    // 500µs -> 0 degrees

void pwm_setup(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice, PWM_DIVISER); 
    pwm_set_wrap(slice, WRAP_PERIOD);
    pwm_set_enabled(slice, true);
}

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
