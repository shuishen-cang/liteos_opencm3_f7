ALL_SRC +=  																\
	${wildcard ./LiteOS/arch/arm/arm-m/src/*.c}			\
        ${wildcard ./LiteOS/kernel/*.c} 				\
        ${wildcard ./LiteOS/kernel/base/core/*.c} 		        \
        ${wildcard ./LiteOS/kernel/base/ipc/*.c} 			\
        ${wildcard ./LiteOS/kernel/base/mem/bestfit_little/*.c}         \
        ${wildcard ./LiteOS/kernel/base/mem/membox/*.c} 		\
        ${wildcard ./LiteOS/kernel/base/mem/common/*.c} 		\
        ${wildcard ./LiteOS/kernel/base/misc/*.c} 			\
        ${wildcard ./LiteOS/kernel/base/om/*.c} 			

ALL_SRCA +=  \
        LiteOS/arch/arm/los_dispatch_gcc.s

ALL_INC += 								\
        ./LiteOS/kernel/base/include  		                \
        ./LiteOS/kernel/extended/include  	                        \
        ./LiteOS/kernel/include				        \
	./LiteOS/arch/arm/arm-m/include 		                \
        ./LiteOS/OS_CONFIG
	                

