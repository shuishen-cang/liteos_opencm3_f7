USER_INC += board

USER_SRC += board/board.c
		

ALL_INC 	+= $(USER_INC)
ALL_SRC 	+= $(USER_SRC)
LDSCRIPT 	= board/board.ld