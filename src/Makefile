PROJECT_NAME     := uwb
TARGETS          := dwm_nrf52832
OUTPUT_DIRECTORY := bin

SDK_ROOT := ../nRF5_SDK_17.1.0_ddde560/
PROJ_DIR := .
GNU_INSTALL_ROOT := /usr/bin/

$(OUTPUT_DIRECTORY)/dwm_nrf52832.out: \
  LINKER_SCRIPT  := uwb_nrf52.ld

# Source files common to all targets
SRC_FILES += $(wildcard $(PROJ_DIR/deca_driver/*.c))
SRC_FILES += $(wildcard $(PROJ_DIR)/*.c)
SRC_FILES += $(SDK_ROOT)/modules/nrfx/mdk/system_nrf52.c
SRC_FILES += $(SDK_ROOT)/modules/nrfx/mdk/gcc_startup_nrf52.S
SRC_FILES += $(SDK_ROOT)/components/libraries/util/app_error.c
SRC_FILES += $(SDK_ROOT)/components/libraries/util/app_error_weak.c
SRC_FILES += $(SDK_ROOT)/components/libraries/fifo/app_fifo.c
SRC_FILES += $(SDK_ROOT)/components/libraries/uart/app_uart_fifo.c
SRC_FILES += $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_uarte.c
SRC_FILES += $(SDK_ROOT)/integration/nrfx/legacy/nrf_drv_uart.c
SRC_FILES += $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_uart.c
SRC_FILES += $(SDK_ROOT)/modules/nrfx/drivers/src/prs/nrfx_prs.c
SRC_FILES += $(SDK_ROOT)/components/libraries/util/app_util_platform.c
SRC_FILES += $(SDK_ROOT)/integration/nrfx/legacy/nrf_drv_spi.c
SRC_FILES += $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_spi.c

# Include folders common to all targets
INC_FOLDERS += $(PROJ_DIR)/deca_driver
INC_FOLDERS += $(PROJ_DIR)
INC_FOLDERS += ./config
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/hal
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx
INC_FOLDERS += $(SDK_ROOT)/integration/nrfx
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/mdk
INC_FOLDERS += $(SDK_ROOT)/components/toolchain/cmsis/include
INC_FOLDERS += $(SDK_ROOT)/components/libraries/util
INC_FOLDERS += $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd
INC_FOLDERS += $(SDK_ROOT)/components/libraries/delay
INC_FOLDERS += $(SDK_ROOT)/components/libraries/uart
INC_FOLDERS += $(SDK_ROOT)/components/libraries/log
INC_FOLDERS += $(SDK_ROOT)/components/libraries/experimental_section_vars
INC_FOLDERS += $(SDK_ROOT)/components/libraries/log/src
INC_FOLDERS += $(SDK_ROOT)/components/libraries/strerror
INC_FOLDERS += $(SDK_ROOT)/integration/nrfx/legacy
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/hal
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/drivers/include
INC_FOLDERS += $(SDK_ROOT)/components/libraries/fifo


# Libraries common to all targets
LIB_FILES += \

# Optimization flags
OPT = -O3 -g3
# Uncomment the line below to enable link time optimization
#OPT += -flto

# C flags common to all targets
CFLAGS += $(OPT)
CFLAGS += -DAPP_TIMER_V2
CFLAGS += -DAPP_TIMER_V2_RTC1_ENABLED
CFLAGS += -DBOARD_PCA10040
CFLAGS += -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DFLOAT_ABI_HARD
CFLAGS += -DNRF52
CFLAGS += -DNRF52832_XXAA
CFLAGS += -DNRF52_PAN_74
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS += -Wall -Werror
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# keep every function in a separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin -fshort-enums

# C++ flags common to all targets
CXXFLAGS += $(OPT)
# Assembler flags common to all targets
ASMFLAGS += -g3
ASMFLAGS += -mcpu=cortex-m4
ASMFLAGS += -mthumb -mabi=aapcs
ASMFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
ASMFLAGS += -DAPP_TIMER_V2
ASMFLAGS += -DAPP_TIMER_V2_RTC1_ENABLED
ASMFLAGS += -DBOARD_PCA10040
ASMFLAGS += -DCONFIG_GPIO_AS_PINRESET
ASMFLAGS += -DFLOAT_ABI_HARD
ASMFLAGS += -DNRF52
ASMFLAGS += -DNRF52832_XXAA
ASMFLAGS += -DNRF52_PAN_74

# Linker flags
LDFLAGS += $(OPT)
LDFLAGS += -mthumb -mabi=aapcs -L$(SDK_ROOT)/modules/nrfx/mdk -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m4
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# let linker dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs

dwm_nrf52832: CFLAGS += -D__HEAP_SIZE=8192
dwm_nrf52832: CFLAGS += -D__STACK_SIZE=8192
dwm_nrf52832: ASMFLAGS += -D__HEAP_SIZE=8192
dwm_nrf52832: ASMFLAGS += -D__STACK_SIZE=8192

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIB_FILES += -lc -lnosys -lm


.PHONY: default help

# Default target - first one defined
default: dwm_nrf52832

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo		nrf52832_xxa/a
	@echo		sdk_config - starting external tool for editing sdk_config.h
	@echo		flash      - flashing binary

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc


include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

.PHONY: flash erase

# Flash the program
flash: default
#	@echo Flashing: $(OUTPUT_DIRECTORY)/dwm_nrf52832.hex
#	nrfjprog -f nrf52 --program $(OUTPUT_DIRECTORY)/dwm_nrf52832.hex --sectorerase
#	nrfjprog -f nrf52 --reset
#
	../code/src/openocd -s ../code/tcl \
		-f interface/stlink.cfg \
		-f target/nrf52.cfg \
		-c "init; \
			halt; \
			nrf5 mass_erase; \
			program bin/dwm_nrf52832.hex verify reset; \
			exit"

erase:
#	nrfjprog -f nrf52 --eraseall
	../code/src/openocd -s ../code/tcl \
		-f interface/stlink.cfg \
		-f target/nrf52.cfg \
		-c "init; \
			halt; \
			nrf5 mass_erase; \
			exit"

SDK_CONFIG_FILE := ./config/sdk_config.h
CMSIS_CONFIG_TOOL := $(SDK_ROOT)/external_tools/cmsisconfig/CMSIS_Configuration_Wizard.jar
sdk_config:
	java -jar $(CMSIS_CONFIG_TOOL) $(SDK_CONFIG_FILE)
