################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/syscalls.c \
../system/system_init.c 

S_UPPER_SRCS += \
../system/startup-cortex-m7.S 

OBJS += \
./system/startup-cortex-m7.o \
./system/syscalls.o \
./system/system_init.o 

S_UPPER_DEPS += \
./system/startup-cortex-m7.d 

C_DEPS += \
./system/syscalls.d \
./system/system_init.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall  -g3 -x assembler-with-cpp -D__STACK_SIZE=4096 -D__HEAP_SIZE=65536 -D_LITE_EXIT -DSTM32F746xx -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests/CMSIS" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/%.o: ../system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall  -g3 -D__STACK_SIZE=4096 -D__HEAP_SIZE=65536 -D_LITE_EXIT -DSTM32F746xx -I"/home/kwarc/eclipse/eclipse-workspaces/arm-cortex-m/stm32f7-cpp-tests/CMSIS" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


