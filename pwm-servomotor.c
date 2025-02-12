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

void set_servo_position(uint gpio, uint16_t duty_cycle_us) {
    uint slice = pwm_gpio_to_slice_num(gpio);

    //Convert pulse time (µs) to PWM level (0 to WRAP_PERIOD)
    uint16_t level = (duty_cycle_us * WRAP_PERIOD) / 20000; // 20ms = 20000µs

    pwm_set_gpio_level(gpio, level);

}

int main()
{
    stdio_init_all();
    pwm_setup(PWM_SERVO);

    // Initial movements to 180°, 90°, and 0° respectively
    set_servo_position(PWM_SERVO, DUTY_180);
    sleep_ms(5000);

    set_servo_position(PWM_SERVO, DUTY_90);
    sleep_ms(5000);

    set_servo_position(PWM_SERVO, DUTY_0);
    sleep_ms(5000);

    // Smooth movement between 0° and 180° continuously
    uint16_t pos = DUTY_0;
    int direction = 2; // Positive increment initially

    while (true) {
        pos += direction;
        set_servo_position(PWM_SERVO, pos);
        sleep_ms(10);

        pos += direction;

        if (pos >= DUTY_180) {
            pos = DUTY_180;
            direction = -2; // Negative increment
        } 
        else if (pos <= DUTY_0) {
            pos = DUTY_0;
            direction = 2;  // Positive increment
        }

    }
}
