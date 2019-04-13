


CUBE_DIR=~/Downloads/STM32Cube_FW_F0_V1.9.0
DST_DIR=./
CMSIS_DIR=$DST_DIR/CMSIS

# Start up assembler
cp $CUBE_DIR/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x6.s $DST_DIR/startup.s

# Linker script
cp $CUBE_DIR/Projects/STM32F0308-Discovery/Applications/FreeRTOS/FreeRTOS_ThreadCreation/SW4STM32/STM32F0308-Discovery/STM32F030R8Tx_FLASH.ld $DST_DIR/link.ld

# CMSIS headers
cp $CUBE_DIR/Drivers/CMSIS/Device/ST/STM32F0xx/Include/stm32f030x6.h $CMSIS_DIR/
cp $CUBE_DIR/Drivers/CMSIS/Include/core_cm0.h $CMSIS_DIR/
cp $CUBE_DIR/Drivers/CMSIS/Device/ST/STM32F0xx/Include/system_stm32f0xx.h $CMSIS_DIR/
cp $CUBE_DIR/Drivers/CMSIS/Include/core_cmInstr.h $CMSIS_DIR/
cp $CUBE_DIR/Drivers/CMSIS/Include/core_cmFunc.h $CMSIS_DIR/
cp $CUBE_DIR/Drivers/CMSIS/Include/cmsis_gcc.h $CMSIS_DIR/

# Note:
# In Drivers/CMSIS/Device/ST/STM32F0xx/Include/stm32f0xx.h it says:
# "#define STM32F030x6 */  /*!< STM32F030x4, STM32F030x6 Devices (STM32F030xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)"

# Finding the linker script
# $> find -iname "*.ld" | grep -i "stm32f030" | rev | cut -d "/" -f 1 | rev | uniq
