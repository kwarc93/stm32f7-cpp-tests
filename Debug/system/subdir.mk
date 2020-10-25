################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../system/system_init.cpp 

S_UPPER_SRCS += \
../system/startup-cortex-m7.S 

OBJS += \
./system/startup-cortex-m7.o \
./system/system_init.o 

S_UPPER_DEPS += \
./system/startup-cortex-m7.d 

CPP_DEPS += \
./system/system_init.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall -x assembler-with-cpp -D_LITE_EXIT -DSTM32F746xx -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/%.o: ../system/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall -D_LITE_EXIT -DSTM32F746xx -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests/drivers" -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests" -std=c++17 -fno-exceptions -fno-rtti -Wno-register -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


