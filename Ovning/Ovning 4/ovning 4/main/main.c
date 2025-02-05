#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_task_wdt.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOSConfig.h"
#include "esp_mac.h"

#ifndef configTICK_RATE_HZ
#define configTICK_RATE_HZ 1000
#endif
#include <FreeRTOSConfig.h>

// Define portTICK_PERIOD_MS if not defined
#ifndef portTICK_PERIOD_MS
#ifdef CONFIG_FREERTOS_HZ
#define portTICK_PERIOD_MS (1000 / CONFIG_FREERTOS_HZ)
#else
#define portTICK_PERIOD_MS (1000 / configTICK_RATE_HZ)
#endif
#endif

// Button on GPIO 4 (example)
#define BUTTON_PIN GPIO_NUM_4

void app_main(void)
{
    // 1. Configure the button as input (with pullup)
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    if (gpio_config(&io_conf) != ESP_OK) {
        printf("Failed to configure GPIO\n");
        return;
    }

    // 2. Add the current task (app_main) to the watchdog
    //    NULL means "the task that calls the function" (app_main).
    if (esp_task_wdt_add(NULL) != ESP_OK) {
        printf("Failed to add task to WDT\n");
        return;
    }

    printf("Starting main loop. Press the button to 'feed' the WDT...\n");

    while (true) {
        int button_state = gpio_get_level(BUTTON_PIN);
        printf("Button state: %d\n", button_state); // Debugging information

        if (button_state == 0) {
            // Button pressed => feed (reset) the watchdog
            esp_task_wdt_reset();
            printf("Watchdog 'fed' via button press!\n");
        } else {
            printf("No button press - no feeding!\n");
        }

        // Wait one second before the next reading.
        // If we don't feed the WDT within 3 seconds => WDT triggers reset/panic
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}