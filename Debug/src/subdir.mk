################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Server.cpp \
../src/helper.cpp \
../src/main.cpp \
../src/parser.cpp 

OBJS += \
./src/Server.o \
./src/helper.o \
./src/main.o \
./src/parser.o 

CPP_DEPS += \
./src/Server.d \
./src/helper.d \
./src/main.d \
./src/parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


