#include "usr_blink.h"
#include "los_config.h"
#include "los_task.h"

static UINT32 blink_tskHandle_ld;
VOID blink_thread_proc(UINT32 uwArg){                  
    uwArg = uwArg;

    while(1){
        set_LD1();
        LOS_Msleep(100);
        set_LD2();
        LOS_Msleep(100);
        set_LD3();
        LOS_Msleep(400);
        clr_LD1();
        LOS_Msleep(100);
        clr_LD2();
        LOS_Msleep(100);
        clr_LD3();
        LOS_Msleep(400);
    }
}

void usr_blink_initial(void){
    TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 2;
    task_init_param.pcName = "blinky";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)blink_thread_proc;
    task_init_param.uwStackSize = 0x400;
    LOS_TaskCreate(&blink_tskHandle_ld, &task_init_param);
}