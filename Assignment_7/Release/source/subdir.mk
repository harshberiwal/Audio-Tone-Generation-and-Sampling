################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/Analog_Converters.c \
../source/DAC.c \
../source/DMA.c \
../source/autocorrelate.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/test_sine.c \
../source/timers.c 

C_DEPS += \
./source/ADC.d \
./source/Analog_Converters.d \
./source/DAC.d \
./source/DMA.d \
./source/autocorrelate.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/test_sine.d \
./source/timers.d 

OBJS += \
./source/ADC.o \
./source/Analog_Converters.o \
./source/DAC.o \
./source/DMA.o \
./source/autocorrelate.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/test_sine.o \
./source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7\board" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7\source" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7\drivers" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7\CMSIS" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7\utilities" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Assignment_7\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ADC.d ./source/ADC.o ./source/Analog_Converters.d ./source/Analog_Converters.o ./source/DAC.d ./source/DAC.o ./source/DMA.d ./source/DMA.o ./source/autocorrelate.d ./source/autocorrelate.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/test_sine.d ./source/test_sine.o ./source/timers.d ./source/timers.o

.PHONY: clean-source

