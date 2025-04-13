################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_clock.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_debug.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_fifo.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_font.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_function.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

