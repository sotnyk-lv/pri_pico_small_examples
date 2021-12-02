#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define RED 0
#define GREEN 1
#define BLUE 2

const uint RED_LED_PIN = 18;
const uint GREEN_LED_PIN = 19;
const uint BLUE_LED_PIN = 20;

void set_up_pwm(const uint8_t PIN, const uint16_t wrap, const uint16_t level=0) {
    gpio_set_function(PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PIN);
    pwm_set_wrap(slice_num, wrap);
    if (PIN % 2) {
        pwm_set_chan_level(slice_num, PWM_CHAN_B, level);
    }
    else {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, level);
    }
    pwm_set_enabled(slice_num, true);
}

int main() {
    const uint16_t wrap = 120;

    stdio_init_all();

    uint16_t states[] = {0, wrap*2/3, wrap/3};
    int8_t change[] = {1, 1, -1};
    uint8_t PINS[] = {RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN};

    set_up_pwm(RED_LED_PIN, wrap, states[RED]);
    set_up_pwm(GREEN_LED_PIN, wrap, states[GREEN]);
    set_up_pwm(BLUE_LED_PIN, wrap, states[BLUE]);

    while (true) {
        for (int i=0; i < 3; ++i) {
            pwm_set_gpio_level(PINS[i], states[i]);
            states[i] += change[i];
            if (states[i] >= wrap) change[i] = -1;
            if (states[i] <= 0)    change[i] = 1;
        }

        sleep_ms(20);

        printf("red: %d; green: %d; blue: %d.\n", states[RED], states[GREEN], states[BLUE]);
    }
    return 0;
}
