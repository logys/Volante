# Cross compiling. "Generic" is used for embedded platforms
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Compilers
set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)

set(CMAKE_EXE_LINKER_FLAGS 
	"-Wl,--gc-sections -nostartfiles --static \
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map"
	CACHE INTERNAL "Linker options")

# Set STM32 SoC specific variables
set(STM32_DEFINES " \
    -DSTM32F1 \
    "
)

set(COMPILER_OPTIONS "-O2 -mcpu=cortex-m3")
SET(CMAKE_C_FLAGS "${COMPILER_OPTIONS} \
	-Werror -g -Wall -Wextra -fstack-protector -pipe" 
	CACHE INTERNAL "c compiler flags")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
