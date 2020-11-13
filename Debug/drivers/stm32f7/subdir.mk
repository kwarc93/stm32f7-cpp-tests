################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../drivers/stm32f7/core.cpp \
../drivers/stm32f7/delay.cpp \
../drivers/stm32f7/gpio.cpp \
../drivers/stm32f7/one_wire.cpp \
../drivers/stm32f7/rcc.cpp \
../drivers/stm32f7/timer.cpp \
../drivers/stm32f7/usart.cpp 

OBJS += \
./drivers/stm32f7/core.o \
./drivers/stm32f7/delay.o \
./drivers/stm32f7/gpio.o \
./drivers/stm32f7/one_wire.o \
./drivers/stm32f7/rcc.o \
./drivers/stm32f7/timer.o \
./drivers/stm32f7/usart.o 

CPP_DEPS += \
./drivers/stm32f7/core.d \
./drivers/stm32f7/delay.d \
./drivers/stm32f7/gpio.d \
./drivers/stm32f7/one_wire.d \
./drivers/stm32f7/rcc.d \
./drivers/stm32f7/timer.d \
./drivers/stm32f7/usart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/stm32f7/%.o: ../drivers/stm32f7/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall  -g3 -D_LITE_EXIT -DSTM32F746xx -D__STACK_SIZE=0x00001000 -D__HEAP_SIZE=0x00020000 -I"C:\!projects\my\stm32f7-cpp-tests\drivers" -I"C:\!projects\my\stm32f7-cpp-tests" -std=gnu++17 -fno-exceptions -fno-rtti -Wno-register -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


