################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../server/commanddata.o \
../server/filetestoperationcommand.o \
../server/getdatecommand.o \
../server/main.o \
../server/messagehandler.o \
../server/nextnprimecommand.o \
../server/nextprimecommand.o \
../server/testprimecommand.o 

CPP_SRCS += \
../server/commanddata.cpp \
../server/filetestoperationcommand.cpp \
../server/getdatecommand.cpp \
../server/main.cpp \
../server/messagehandler.cpp \
../server/nextnprimecommand.cpp \
../server/nextprimecommand.cpp \
../server/testprimecommand.cpp 

OBJS += \
./server/commanddata.o \
./server/filetestoperationcommand.o \
./server/getdatecommand.o \
./server/main.o \
./server/messagehandler.o \
./server/nextnprimecommand.o \
./server/nextprimecommand.o \
./server/testprimecommand.o 

CPP_DEPS += \
./server/commanddata.d \
./server/filetestoperationcommand.d \
./server/getdatecommand.d \
./server/main.d \
./server/messagehandler.d \
./server/nextnprimecommand.d \
./server/nextprimecommand.d \
./server/testprimecommand.d 


# Each subdirectory must supply rules for building sources it contributes
server/%.o: ../server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


