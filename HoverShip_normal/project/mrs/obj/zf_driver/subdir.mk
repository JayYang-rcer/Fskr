################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_adc.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_delay.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_dvp.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_encoder.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_exti.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_flash.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_gpio.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_iic.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_pit.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_pwm.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_soft_iic.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_soft_spi.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_spi.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_timer.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_uart.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_usb_cdc.c 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_iic.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_soft_spi.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_iic.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_soft_spi.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_iic.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_spi.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_soft_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

