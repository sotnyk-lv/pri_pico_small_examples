#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint BLUE_LED_PIN = 18;
const uint GREEN_LED_PIN = 19;
const uint RED_LED_PIN = 20;

int main() {
    uint32_t LED_STATE = 0;

//    gpio_init_mask(0b111<<17); // 111<<17 it is 1 for pins 18,19,20 and other 0
    stdio_init_all();

    gpio_set_function(BLUE_LED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(GREEN_LED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RED_LED_PIN, GPIO_FUNC_PWM);

    uint blue_slice_num = pwm_gpio_to_slice_num(BLUE_LED_PIN);
    uint green_slice_num = pwm_gpio_to_slice_num(GREEN_LED_PIN);
    uint red_slice_num = pwm_gpio_to_slice_num(RED_LED_PIN);

    pwm_set_wrap(blue_slice_num, 99);
    pwm_set_wrap(green_slice_num, 99);
    pwm_set_wrap(red_slice_num, 99);

    pwm_set_chan_level(blue_slice_num, PWM_CHAN_A, 99);
    pwm_set_chan_level(green_slice_num, PWM_CHAN_B, 99);
    pwm_set_chan_level(red_slice_num, PWM_CHAN_A, 99);

    pwm_set_enabled(blue_slice_num, true);
    pwm_set_enabled(green_slice_num, true);
    pwm_set_enabled(red_slice_num, true);

    int8_t RED_STATE = 0;
    int8_t GREEN_STATE = 66;
    int8_t BLUE_STATE = 33;

    int8_t red_change = 1;
    int8_t green_change = 1;
    int8_t blue_change = -1;

    while (true) {

        pwm_set_chan_level(red_slice_num, PWM_CHAN_A, RED_STATE);
        pwm_set_chan_level(green_slice_num, PWM_CHAN_B, GREEN_STATE);
        pwm_set_chan_level(blue_slice_num, PWM_CHAN_A, BLUE_STATE);

        sleep_ms(20);

        RED_STATE += red_change;
        GREEN_STATE += green_change;
        BLUE_STATE += blue_change;

        if (RED_STATE >= 99) red_change=-1;
        if (RED_STATE <= 0) red_change=1;
        if (GREEN_STATE >= 99) green_change=-1;
        if (GREEN_STATE <= 0) green_change=1;
        if (BLUE_STATE >= 99) blue_change=-1;
        if (BLUE_STATE <= 0) blue_change=1;

        printf("red: %d; green: %d; blue: %d.\n", RED_STATE, GREEN_STATE, BLUE_STATE);

    }
    return 0;
}
