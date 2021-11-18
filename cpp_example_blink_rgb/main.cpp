#include "pico/stdlib.h"
#include "pico/binary_info.h"

// const uint BLUE_LED_PIN = 18;
// const uint GREEN_LED_PIN = 19;
// const uint RED_LED_PIN = 20;

int main() {
    uint32_t LED_STATE = 0;

    gpio_init_mask(0b111<<17); // 111<<17 it is 1 for pins 18,19,20 and other 0
    gpio_set_dir_out_masked(0b111<<17);

    while (true) {
        gpio_put_masked(111<<17, LED_STATE<<18);
        LED_STATE++;
        LED_STATE = LED_STATE>7 ? 0 : LED_STATE;
        sleep_ms(500);
    }
    return 0;
}
