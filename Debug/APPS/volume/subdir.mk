################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APPS/volume/volume.c \
../APPS/volume/volume_pwm.c 

OBJS += \
./APPS/volume/volume.o \
./APPS/volume/volume_pwm.o 

C_DEPS += \
./APPS/volume/volume.d \
./APPS/volume/volume_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
APPS/volume/%.o: ../APPS/volume/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -I"/home/sam/w/musavi/mus_proj/Inc" -I"/home/sam/w/musavi/mus_proj/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/sam/w/musavi/mus_proj/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/sam/w/musavi/mus_proj/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/sam/w/musavi/mus_proj/Drivers/CMSIS/Include" -I"/home/sam/w/musavi/mus_proj/APPS/encoder" -I"/home/sam/w/musavi/mus_proj/APPS/event" -I"/home/sam/w/musavi/mus_proj/APPS/push-btn" -I"/home/sam/w/musavi/mus_proj/APPS/volume" -I"/home/sam/w/musavi/mus_proj/APPS/link_list" -I"/home/sam/w/musavi/mus_proj/APPS/glcd" -I"/home/sam/w/musavi/mus_proj/APPS/glcd/fonts" -I"/home/sam/w/musavi/mus_proj/APPS/glcd" -I"/home/sam/w/musavi/mus_proj/APPS/glcd/fonts" -I"/home/sam/w/musavi/mus_proj/APPS/fv1" -I"/home/sam/w/musavi/mus_proj/APPS/glcd" -I"/home/sam/w/musavi/mus_proj/APPS/glcd/fonts" -I"/home/sam/w/musavi/mus_proj/APPS/effect" -I"/home/sam/w/musavi/mus_proj/APPS/link_list"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


