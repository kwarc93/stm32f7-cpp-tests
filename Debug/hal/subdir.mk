################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../hal/hal_delay.cpp \
../hal/hal_led.cpp \
../hal/hal_system.cpp \
../hal/hal_temperature_sensor.cpp \
../hal/hal_usart.cpp 

OBJS += \
./hal/hal_delay.o \
./hal/hal_led.o \
./hal/hal_system.o \
./hal/hal_temperature_sensor.o \
./hal/hal_usart.o 

CPP_DEPS += \
./hal/hal_delay.d \
./hal/hal_led.d \
./hal/hal_system.d \
./hal/hal_temperature_sensor.d \
./hal/hal_usart.d 


# Each subdirectory must supply rules for building sources it contributes
hal/%.o: ../hal/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall  -g3 -D_LITE_EXIT -DSTM32F746xx -D__STACK_SIZE=0x00001000 -D__HEAP_SIZE=0x00020000 -I"C:\!projects\my\stm32f7-cpp-tests\drivers" -I"C:\!projects\my\stm32f7-cpp-tests" -std=c++17 -fno-exceptions -fno-rtti -Wno-register -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


