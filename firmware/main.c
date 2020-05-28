#include "hal.h"
#include "los_config.h"
#include "los_task.h"
#include "usr_blink.h"

int main(void)
{
	hal_initial();
	LOS_KernelInit();
    usr_uart_initial();
	usr_blink_initial();
	LOS_Start();
	while(1);
}