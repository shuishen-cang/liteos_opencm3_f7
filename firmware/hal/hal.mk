HAL_INC += 	hal

HAL_SRC += 	hal/hal.c		\
			hal/hal_uart.c
		

ALL_INC 	+= $(HAL_INC)
ALL_SRC 	+= $(HAL_SRC)