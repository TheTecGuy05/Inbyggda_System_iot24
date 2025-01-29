#include <stdio.h>
#include "esp_log.h"

#define NEW_LINE "\n"

#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_MAGENTA "\033[0;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RESET "\033[0m"





#define PRINTF_COLOR(color, format_string, ...) \
     printf("%s" format_string "%s", color , ##__VA_ARGS__, ANSI_RESET)

#define PRINTF_COLOR_WITH_LINE(color, format_string, ...) \
     PRINTF_COLOR(ANSI_MAGENTA, "[%s:%d] ", __FILE__, __LINE__); \
        PRINTF_COLOR(color, format_string, ##__VA_ARGS__)
const static char *const TAG = "MAIN";

void app_main() {
    PRINTF_COLOR(ANSI_BLUE, "GROUP 1 ");
    PRINTF_COLOR(ANSI_BLUE, "GROUP 1\n");
    int NEW_WORLD_COUNT = 1;
    const char *test_string = "t""e""s""t";
    ESP_LOGI (TAG, "Hello World for my %d time: %s", 1, test_string);

    PRINTF_COLOR(ANSI_RED, "%s" NEW_LINE, test_string);
   
    PRINTF_COLOR_WITH_LINE(ANSI_YELLOW, "Hello World %d" NEW_LINE, NEW_WORLD_COUNT);

    printf("Hello World 1\n");
}
