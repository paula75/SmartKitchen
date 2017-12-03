APPLICATION = sensor_node
include ../Makefile.tests_common

FEATURES_REQUIRED = periph_i2c periph_gpio

USEMODULE += xtimer
USEMODULE += pn532
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules
USEMODULE += gnrc_ipv6_default
USEMODULE += gcoap
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo

# Required by gcoap example
USEMODULE += od
USEMODULE += fmt

# set default device parameters in case they are undefined
TEST_PN532_I2C ?= I2C_DEV\(0\)
TEST_PN532_RESET ?= GPIO_PIN\(1,22\)
TEST_PN532_IRQ ?= GPIO_PIN\(1,23\)

# alternative SPI configuration
TEST_PN532_SPI ?= SPI_DEV\(0\)
TEST_PN532_NSS ?= GPIO_PIN\(0,2\)

# export parameters
CFLAGS += -DTEST_PN532_I2C=$(TEST_PN532_I2C)
CFLAGS += -DTEST_PN532_RESET=$(TEST_PN532_RESET)
CFLAGS += -DTEST_PN532_IRQ=$(TEST_PN532_IRQ)
CFLAGS += -DTEST_PN532_SPI=$(TEST_PN532_SPI)
CFLAGS += -DTEST_PN532_NSS=$(TEST_PN532_NSS)

# select if you want to build the SPI or the I2C version of the driver:
# set PN532_MODE to `i2c` or to `spi`
PN532_MODE ?= i2c
ifeq ($(PN532_MODE),i2c)
  CFLAGS += -DPN532_SUPPORT_I2C
endif
ifeq ($(PN532_MODE),spi)
  CFLAGS += -DPN532_SUPPORT_SPI
endif

CFLAGS += -I$(CURDIR)

include $(RIOTBASE)/Makefile.include
