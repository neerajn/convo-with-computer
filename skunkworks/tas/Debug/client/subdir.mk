################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../client/main.o \
../client/messagehandler.o \
../client/simpleclient.o 

CPP_SRCS += \
../client/main.cpp \
../client/messagehandler.cpp 

OBJS += \
./client/main.o \
./client/messagehandler.o 

CPP_DEPS += \
./client/main.d \
./client/messagehandler.d 


# Each subdirectory must supply rules for building sources it contributes
client/%.o: ../client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


