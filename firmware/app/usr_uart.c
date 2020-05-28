#include "usr_uart.h"
#include "los_config.h"
#include "los_task.h"
#include "los_task.h"

static UINT32 uart_tskHandle_ld;
VOID uart_thread_proc(UINT32 uwArg){                  
    uwArg = uwArg;

    uint8_t temp;
    while(1){
        if(hal_uart_read(&temp,1,LOS_WAIT_FOREVER) > 0){
            printf("recv:%x!\n",temp);
        }    
    }
}

void usr_uart_initial(void){
	hal_uart_initial();

	TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 3;
    task_init_param.pcName = "uart";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)uart_thread_proc;
    task_init_param.uwStackSize = 0x800;
    LOS_TaskCreate(&uart_tskHandle_ld, &task_init_param);
}


