################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APPS/glcd/ST7565R.c \
../APPS/glcd/glcd.c \
../APPS/glcd/glcd_graphics.c \
../APPS/glcd/glcd_graphs.c \
../APPS/glcd/glcd_text.c \
../APPS/glcd/unit_tests.c 

OBJS += \
./APPS/glcd/ST7565R.o \
./APPS/glcd/glcd.o \
./APPS/glcd/glcd_graphics.o \
./APPS/glcd/glcd_graphs.o \
./APPS/glcd/glcd_text.o \
./APPS/glcd/unit_tests.o 

C_DEPS += \
./APPS/glcd/ST7565R.d \
./APPS/glcd/glcd.d \
./APPS/glcd/glcd_graphics.d \
./APPS/glcd/glcd_graphs.d \
./APPS/glcd/glcd_text.d \
./APPS/glcd/unit_tests.d 


# Each subdirectory must supply rules for building sources it contributes
APPS/glcd/%.o: ../APPS/glcd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -I"/home/sam/w/musavi/mus_proj/Inc" -I"/home/sam/w/musavi/mus_proj/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/sam/w/musavi/mus_proj/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/sam/w/musavi/mus_proj/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/sam/w/musavi/mus_proj/Drivers/CMSIS/Include" -I"/home/sam/w/musavi/mus_proj/APPS/glcd" -I"/home/sam/w/musavi/mus_proj/APPS/glcd/fonts"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


