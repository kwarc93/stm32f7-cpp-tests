################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../system-setup/startup-cortex-m7.S 

OBJS += \
./system-setup/startup-cortex-m7.o 

S_UPPER_DEPS += \
./system-setup/startup-cortex-m7.d 


# Each subdirectory must supply rules for building sources it contributes
system-setup/%.o: ../system-setup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wunused -Wuninitialized -Wall  -g3 -x assembler-with-cpp -D__START=main -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


