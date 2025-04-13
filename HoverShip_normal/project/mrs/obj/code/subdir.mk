################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/Img_proc.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/Motor.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/PID.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/attitude_solution.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/barrier.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/circle.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/cross.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/garage.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/key.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/my_math.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/my_uart7.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/timer.c 

OBJS += \
./code/Img_proc.o \
./code/Motor.o \
./code/PID.o \
./code/attitude_solution.o \
./code/barrier.o \
./code/circle.o \
./code/cross.o \
./code/garage.o \
./code/key.o \
./code/my_math.o \
./code/my_uart7.o \
./code/timer.o 

C_DEPS += \
./code/Img_proc.d \
./code/Motor.d \
./code/PID.d \
./code/attitude_solution.d \
./code/barrier.d \
./code/circle.d \
./code/cross.d \
./code/garage.d \
./code/key.d \
./code/my_math.d \
./code/my_uart7.d \
./code/timer.d 


# Each subdirectory must supply rules for building sources it contributes
code/Img_proc.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/Img_proc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/Motor.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/Motor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/PID.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/attitude_solution.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/attitude_solution.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/barrier.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/barrier.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/circle.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/circle.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/cross.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/cross.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/garage.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/garage.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/key.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/key.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_math.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/my_math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_uart7.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/my_uart7.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/timer.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/code/timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

