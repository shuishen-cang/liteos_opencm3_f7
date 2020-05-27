#include "hal.h"
#include "los_config.h"
#include "los_task.h"
#include "board.h"

VOID myled_thread_proc(UINT32 uwArg){                           //因为有FIFO存在，该任务的优先级可以很低
    uwArg = uwArg;

    while(1){
      toggle_LD1();
      toggle_LD2();
      printf("cang!\n");
      LOS_Msleep(500);
    }
}

static UINT32 myled_tskHandle_ld2;
volatile uint16_t systick_flag = 0;
int main(void)
{
	hal_initial();
	usr_uart_initial();

	UINT32 uwRet = LOS_KernelInit();
	
    TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 2;
    task_init_param.pcName = "myled_ld2";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)myled_thread_proc;
    task_init_param.uwStackSize = 0x400;
    LOS_TaskCreate(&myled_tskHandle_ld2, &task_init_param);

	LOS_Start();
	while(1){

	}
}
