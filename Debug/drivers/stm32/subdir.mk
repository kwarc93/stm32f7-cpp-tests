################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../drivers/stm32/gpio.cpp 

OBJS += \
./drivers/stm32/gpio.o 

CPP_DEPS += \
./drivers/stm32/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/stm32/%.o: ../drivers/stm32/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall  -g3 -D__STACK_SIZE=4096 -D__HEAP_SIZE=65536 -D_LITE_EXIT -DSTM32F746xx -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests/drivers" -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests" -std=c++11 -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


