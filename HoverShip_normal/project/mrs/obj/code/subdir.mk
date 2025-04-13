################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/Img_proc.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/Motor.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/PID.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/attitude_solution.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/barrier.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/circle.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/cross.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/garage.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/key.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/my_math.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/my_uart7.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/timer.c 

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
code/Img_proc.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/Img_proc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/Motor.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/Motor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/PID.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/attitude_solution.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/attitude_solution.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/barrier.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/barrier.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/circle.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/circle.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/cross.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/cross.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/garage.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/garage.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/key.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/key.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_math.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/my_math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_uart7.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/my_uart7.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/timer.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/code/timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

