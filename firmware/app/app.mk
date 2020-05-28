APP_INC 	+= 	app				

APP_SRC 	+= 	app/board.c		\
				app/usr_uart.c	\
				app/usr_blink.c

LDSCRIPT 	= 	app/board.ld
		

ALL_INC 	+= $(APP_INC)
ALL_SRC 	+= $(APP_SRC)