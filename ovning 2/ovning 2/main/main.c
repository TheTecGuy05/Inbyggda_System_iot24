#include <stdio.h>
#include "help_components.h" // Ensure this file exists in the correct directory
#include "printer.h"
#include "esp_log.h"
#include "sdkconfig.h" // Add this line to include the configuration header
int func(void)
{
	int a = func();
	ESP_LOGI("MAIN", "got value %d", a);
	return a;
}
































