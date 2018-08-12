################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APPS/fsme/fsme.c 

OBJS += \
./APPS/fsme/fsme.o 

C_DEPS += \
./APPS/fsme/fsme.d 


# Each subdirectory must supply rules for building sources it contributes
APPS/fsme/%.o: ../APPS/fsme/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -I"/home/sam/w/musavi/mus_proj/Inc" -I"/home/sam/w/musavi/mus_proj/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/sam/w/musavi/mus_proj/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/sam/w/musavi/mus_proj/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/sam/w/musavi/mus_proj/Drivers/CMSIS/Include" -I"/home/sam/w/musavi/mus_proj/APPS/fsme"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


