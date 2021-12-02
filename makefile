######################################
# target
######################################
TARGET = main

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources

CORE_SOURCES := $(wildcard ./STM32L151C6Tx/Core/Src/*.c)

# HAL_SOURCES := $(shell find ./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src -name "*.c")
HAL_SOURCES = \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pcd.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pcd_ex.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.c \
./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_ll_usb.c \
./STM32L151C6Tx/USB_DEVICE/App/usb_device.c \
./STM32L151C6Tx/USB_DEVICE/App/usbd_desc.c \
./STM32L151C6Tx/USB_DEVICE/Target/usbd_conf.c \
./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c

C_SOURCES := $(CORE_SOURCES) $(HAL_SOURCES)

# ASM sources
ASM_SOURCES = \
./STM32L151C6Tx/Core/Startup/startup_stm32l151c6tx.s

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

PROGAMMER = C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi

# mcu
MCU = $(CPU) -mthumb

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS = \
-D USE_HAL_DRIVER \
-D STM32L151xB


# AS includes
AS_INCLUDES = \
-I ./STM32L151C6Tx/Core\Inc

# C includes
C_INCLUDES =  \
-I ./STM32L151C6Tx/Core/Inc \
-I ./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Inc \
-I ./STM32L151C6Tx/Drivers/STM32L1xx_HAL_Driver/Inc/Legacy \
-I ./STM32L151C6Tx/Drivers/CMSIS/Device/ST/STM32L1xx/Include \
-I ./STM32L151C6Tx/Drivers/CMSIS/Include \
-I ./STM32L151C6Tx/USB_DEVICE/App \
-I ./STM32L151C6Tx/USB_DEVICE/Target \
-I ./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
-I ./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc \
-T ./STM32L151C6Tx/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Core/Inc

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = ./STM32L151C6Tx/STM32L151C6Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T $(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	@echo ""

$(BUILD_DIR)/%.o: %.s makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
	@echo ""

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo ""
	$(SZ) $@
	@echo ""

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@
	@echo ""

#######################################
# clean up
#######################################
clean:
	rm -rf $(BUILD_DIR)

flash:
	@#$(PROGAMMER) -c port=SWD -w $(BUILD_DIR)/$(TARGET).bin 0x08000000 -hardRst
	@#$(PROGAMMER) -c port=SWD --start 0x08000000
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000

gdb:
	openocd -f interface/stlink.cfg -f target/stm32l1.cfg -c "init"

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
