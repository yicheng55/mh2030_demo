#include "dm9051_hal_at32f403a_spi1_priv.h"

const dm9051_hal_ops_t dm9051_at32f403a_polling_ops = {
    dm9051_at32f403a_polling_read_reg,
    dm9051_at32f403a_polling_write_reg,
    dm9051_at32f403a_polling_read_mem,
    dm9051_at32f403a_polling_write_mem,
    dm9051_at32f403a_polling_reset,
    dm9051_at32f403a_delay_ms,
    dm9051_at32f403a_delay_us,
    dm9051_at32f403a_irq_enable_if_enabled,
    dm9051_at32f403a_irq_disable_if_enabled,
    dm9051_at32f403a_enter_critical,
    dm9051_at32f403a_exit_critical
};

static dm9051_at32f403a_config_t dm9051_at32f403a_bound_config;

void dm9051_at32f403a_select(void)
{
    gpio_bits_reset(DM9051_AT32F403A_CS_PORT, DM9051_AT32F403A_CS_PIN);
}

void dm9051_at32f403a_deselect(void)
{
    gpio_bits_set(DM9051_AT32F403A_CS_PORT, DM9051_AT32F403A_CS_PIN);
}

int dm9051_at32f403a_wait_spi_idle(const dm9051_at32f403a_config_t *config)
{
    uint32_t timeout;

    if (config == 0) {
        return DM9051_HAL_ERR_PARAM;
    }

    timeout = config->spi_timeout;
    while (spi_i2s_flag_get(DM9051_AT32F403A_SPI, SPI_I2S_BF_FLAG) == SET) {
        if (timeout == 0u) {
            DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] SPI timeout: BSY\r\n");
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    return DM9051_HAL_OK;
}

int dm9051_at32f403a_transfer_byte(const dm9051_at32f403a_config_t *config,
                                   uint8_t tx,
                                   uint8_t *rx)
{
    uint32_t timeout;

    if ((config == 0) || (rx == 0)) {
        return DM9051_HAL_ERR_PARAM;
    }

    timeout = config->spi_timeout;
    while (spi_i2s_flag_get(DM9051_AT32F403A_SPI, SPI_I2S_TDBE_FLAG) == RESET) {
        if (timeout == 0u) {
            DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] SPI timeout: TXE tx=0x%02X\r\n", tx);
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }
    spi_i2s_data_transmit(DM9051_AT32F403A_SPI, tx);

    timeout = config->spi_timeout;
    while (spi_i2s_flag_get(DM9051_AT32F403A_SPI, SPI_I2S_RDBF_FLAG) == RESET) {
        if (timeout == 0u) {
            DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] SPI timeout: RXNE tx=0x%02X\r\n", tx);
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    *rx = (uint8_t)spi_i2s_data_receive(DM9051_AT32F403A_SPI);
    return DM9051_HAL_OK;
}

int dm9051_at32f403a_finish_transfer(const dm9051_at32f403a_config_t *config)
{
    uint32_t timeout;
    int status;

    if (config == 0) {
        return DM9051_HAL_ERR_PARAM;
    }

    status = dm9051_at32f403a_wait_spi_idle(config);

    timeout = config->spi_timeout;
    while (spi_i2s_flag_get(DM9051_AT32F403A_SPI, SPI_I2S_RDBF_FLAG) == SET) {
        if (timeout == 0u) {
            DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] SPI timeout: RXNE drain\r\n");
            return DM9051_HAL_ERR_TIMEOUT;
        }
        (void)spi_i2s_data_receive(DM9051_AT32F403A_SPI);
        --timeout;
    }

    return status;
}

void dm9051_at32f403a_spi1_bus_init_common(void)
{
    gpio_init_type gpio;

    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    gpio_pin_remap_config(SWJTAG_GMUX_010, TRUE);

    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_OUTPUT;
    gpio.gpio_pull = GPIO_PULL_NONE;
    gpio.gpio_pins = DM9051_AT32F403A_CS_PIN;
    gpio_init(DM9051_AT32F403A_CS_PORT, &gpio);
    dm9051_at32f403a_deselect();

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_OUTPUT;
    gpio.gpio_pull = GPIO_PULL_NONE;
    gpio.gpio_pins = DM9051_AT32F403A_RST_PIN;
    gpio_init(DM9051_AT32F403A_RST_PORT, &gpio);

    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE5, GPIO_MUX_0);
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_0);
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_0);

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_MUX;
    gpio.gpio_pull = GPIO_PULL_NONE;
    gpio.gpio_pins = DM9051_AT32F403A_SCK_PIN | DM9051_AT32F403A_MOSI_PIN;
    gpio_init(DM9051_AT32F403A_SCK_PORT, &gpio);

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_MUX;
    gpio.gpio_pull = GPIO_PULL_UP;
    gpio.gpio_pins = DM9051_AT32F403A_MISO_PIN;
    gpio_init(DM9051_AT32F403A_MISO_PORT, &gpio);

    spi_reset(DM9051_AT32F403A_SPI);
    {
        spi_init_type spi;
        spi_default_para_init(&spi);
        spi.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
        spi.master_slave_mode = SPI_MODE_MASTER;
        spi.mclk_freq_division = SPI_MCLK_DIV_4;
        spi.first_bit_transmission = SPI_FIRST_BIT_MSB;
        spi.frame_bit_num = SPI_FRAME_8BIT;
        spi.clock_polarity = SPI_CLOCK_POLARITY_LOW;
        spi.clock_phase = SPI_CLOCK_PHASE_1EDGE;
        spi_init(DM9051_AT32F403A_SPI, &spi);
    }
    spi_enable(DM9051_AT32F403A_SPI, TRUE);
}

void dm9051_at32f403a_spi1_polling_bus_init(void)
{
    dm9051_at32f403a_spi1_bus_init_common();
    printf("[AT32F403A] DM9051 SPI bus initialized (polling transfer)\r\n");
}

void dm9051_at32f403a_reset_gpio_sequence(void)
{
    gpio_bits_reset(DM9051_AT32F403A_RST_PORT, DM9051_AT32F403A_RST_PIN);
    Delay_Ms(2u);
    gpio_bits_set(DM9051_AT32F403A_RST_PORT, DM9051_AT32F403A_RST_PIN);
    Delay_Ms(10u);
}

void dm9051_at32f403a_polling_reset(void *ctx)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;

    dm9051_at32f403a_spi1_polling_bus_init();
    dm9051_at32f403a_irq_init_if_enabled(config);
    dm9051_at32f403a_reset_gpio_sequence();
}

void dm9051_at32f403a_delay_ms(uint32_t ms)
{
    while (ms > 0xffffu) {
        Delay_Ms(0xffffu);
        ms -= 0xffffu;
    }

    Delay_Ms((uint16_t)ms);
}

void dm9051_at32f403a_delay_us(uint32_t us)
{
    Delay_Us(us);
}

uint32_t dm9051_at32f403a_enter_critical(void *ctx)
{
    uint32_t primask;

    (void)ctx;
    primask = __get_PRIMASK();
    __disable_irq();
    return primask;
}

void dm9051_at32f403a_exit_critical(void *ctx, uint32_t state)
{
    (void)ctx;
    __set_PRIMASK(state);
}

int dm9051_at32f403a_polling_read_reg(void *ctx,
                                     uint8_t reg,
                                     uint8_t *val)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;
    uint8_t dummy = 0u;
    uint8_t cmd;
    int status;

    if ((config == 0) || (val == 0)) {
        return DM9051_HAL_ERR_PARAM;
    }

    cmd = (uint8_t)(reg | DM9051_OPC_REG_R);
    dm9051_at32f403a_select();
    status = dm9051_at32f403a_transfer_byte(config, cmd, &dummy);
    DM9051_AT32F403A_TRACE_PRINTF("[DM9051 HAL] read reg=0x%02X cmd=0x%02X cmd_status=%d dummy=0x%02X\r\n",
                                  reg,
                                  cmd,
                                  status,
                                  dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_transfer_byte(config, 0x00u, val);
        DM9051_AT32F403A_TRACE_PRINTF("[DM9051 HAL] read reg=0x%02X data_status=%d val=0x%02X\r\n",
                                      reg,
                                      status,
                                      *val);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_finish_transfer(config);
    } else {
        (void)dm9051_at32f403a_finish_transfer(config);
    }
    dm9051_at32f403a_deselect();

    return status;
}

int dm9051_at32f403a_polling_write_reg(void *ctx,
                                      uint8_t reg,
                                      uint8_t val)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;
    uint8_t dummy = 0u;
    uint8_t cmd;
    int status;

    if (config == 0) {
        return DM9051_HAL_ERR_PARAM;
    }

    cmd = (uint8_t)(reg | DM9051_OPC_REG_W);
    dm9051_at32f403a_select();
    status = dm9051_at32f403a_transfer_byte(config, cmd, &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_transfer_byte(config, val, &dummy);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_finish_transfer(config);
    } else {
        (void)dm9051_at32f403a_finish_transfer(config);
    }
    dm9051_at32f403a_deselect();

    return status;
}

int dm9051_at32f403a_polling_read_mem(void *ctx,
                                     uint8_t *buf,
                                     uint16_t len)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;
    uint8_t dummy;
    uint16_t i;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_at32f403a_select();
    status = dm9051_at32f403a_transfer_byte(config,
                                           (uint8_t)(DM9051_MRCMD | DM9051_OPC_REG_R),
                                           &dummy);
    for (i = 0u; (i < len) && (status == DM9051_HAL_OK); ++i) {
        status = dm9051_at32f403a_transfer_byte(config, 0x00u, &buf[i]);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_finish_transfer(config);
    } else {
        (void)dm9051_at32f403a_finish_transfer(config);
    }
    dm9051_at32f403a_deselect();

    DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] read mem len=%u status=%d\r\n",
                                 len,
                                 status);

    return status;
}

int dm9051_at32f403a_polling_write_mem(void *ctx,
                                      const uint8_t *buf,
                                      uint16_t len)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;
    uint8_t dummy;
    uint16_t i;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_at32f403a_select();
    status = dm9051_at32f403a_transfer_byte(config,
                                           (uint8_t)(DM9051_MWCMD | DM9051_OPC_REG_W),
                                           &dummy);
    for (i = 0u; (i < len) && (status == DM9051_HAL_OK); ++i) {
        status = dm9051_at32f403a_transfer_byte(config, buf[i], &dummy);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_finish_transfer(config);
    } else {
        (void)dm9051_at32f403a_finish_transfer(config);
    }
    dm9051_at32f403a_deselect();

    DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] write mem len=%u status=%d\r\n",
                                 len,
                                 status);

    return status;
}

void dm9051_at32f403a_default_config(dm9051_at32f403a_config_t *config)
{
    if (config == 0) {
        return;
    }

    config->transport = DM9051_AT32F403A_TRANSPORT_POLLING;
    config->irq_mode = DM9051_AT32F403A_IRQ_OFF;
    config->pins.cs_port = (uint32_t)DM9051_AT32F403A_CS_PORT;
    config->pins.cs_pin = DM9051_AT32F403A_CS_PIN;
    config->pins.sck_port = (uint32_t)DM9051_AT32F403A_SCK_PORT;
    config->pins.sck_pin = DM9051_AT32F403A_SCK_PIN;
    config->pins.miso_port = (uint32_t)DM9051_AT32F403A_MISO_PORT;
    config->pins.miso_pin = DM9051_AT32F403A_MISO_PIN;
    config->pins.mosi_port = (uint32_t)DM9051_AT32F403A_MOSI_PORT;
    config->pins.mosi_pin = DM9051_AT32F403A_MOSI_PIN;
    config->pins.rst_port = (uint32_t)DM9051_AT32F403A_RST_PORT;
    config->pins.rst_pin = DM9051_AT32F403A_RST_PIN;
    config->pins.int_port = (uint32_t)DM9051_AT32F403A_INT_PORT;
    config->pins.int_pin = DM9051_AT32F403A_INT_PIN;
    config->spi_timeout = DM9051_AT32F403A_DEFAULT_SPI_TIMEOUT;
}

int dm9051_at32f403a_config_is_valid(const dm9051_at32f403a_config_t *config)
{
    if (config == 0) {
        return 0;
    }

    switch (config->transport) {
    case DM9051_AT32F403A_TRANSPORT_POLLING:
    case DM9051_AT32F403A_TRANSPORT_DMA:
        break;
    default:
        return 0;
    }

    switch (config->irq_mode) {
    case DM9051_AT32F403A_IRQ_OFF:
    case DM9051_AT32F403A_IRQ_EXTI:
        break;
    default:
        return 0;
    }

    if (config->spi_timeout == 0u) {
        return 0;
    }

    if ((config->pins.cs_port != (uint32_t)DM9051_AT32F403A_CS_PORT) ||
        (config->pins.cs_pin != DM9051_AT32F403A_CS_PIN) ||
        (config->pins.sck_port != (uint32_t)DM9051_AT32F403A_SCK_PORT) ||
        (config->pins.sck_pin != DM9051_AT32F403A_SCK_PIN) ||
        (config->pins.miso_port != (uint32_t)DM9051_AT32F403A_MISO_PORT) ||
        (config->pins.miso_pin != DM9051_AT32F403A_MISO_PIN) ||
        (config->pins.mosi_port != (uint32_t)DM9051_AT32F403A_MOSI_PORT) ||
        (config->pins.mosi_pin != DM9051_AT32F403A_MOSI_PIN) ||
        (config->pins.rst_port != (uint32_t)DM9051_AT32F403A_RST_PORT) ||
        (config->pins.rst_pin != DM9051_AT32F403A_RST_PIN) ||
        (config->pins.int_port != (uint32_t)DM9051_AT32F403A_INT_PORT) ||
        (config->pins.int_pin != DM9051_AT32F403A_INT_PIN)) {
        return 0;
    }

    return 1;
}

int dm9051_at32f403a_hal_bind(dm9051_hal_t *hal,
                              const dm9051_at32f403a_config_t *config)
{
    if ((hal == 0) || !dm9051_at32f403a_config_is_valid(config)) {
        return DM9051_HAL_ERR_PARAM;
    }

#if !DM9051_AT32F403A_ENABLE_DMA
    if (config->transport == DM9051_AT32F403A_TRANSPORT_DMA) {
        return DM9051_HAL_ERR_NOT_READY;
    }
#endif

#if !DM9051_AT32F403A_ENABLE_IRQ
    if (config->irq_mode == DM9051_AT32F403A_IRQ_EXTI) {
        return DM9051_HAL_ERR_NOT_READY;
    }
#endif

    dm9051_at32f403a_bound_config = *config;
    hal->ctx = &dm9051_at32f403a_bound_config;

    if (config->transport == DM9051_AT32F403A_TRANSPORT_POLLING) {
        hal->ops = &dm9051_at32f403a_polling_ops;
        return DM9051_HAL_OK;
    }

#if DM9051_AT32F403A_ENABLE_DMA
    hal->ops = &dm9051_at32f403a_dma_ops;
    return DM9051_HAL_OK;
#else
    return DM9051_HAL_ERR_NOT_READY;
#endif
}

const char *dm9051_at32f403a_transport_name(dm9051_at32f403a_transport_t transport)
{
    switch (transport) {
    case DM9051_AT32F403A_TRANSPORT_POLLING:
        return "polling";
    case DM9051_AT32F403A_TRANSPORT_DMA:
        return "dma";
    default:
        return "unknown";
    }
}

const char *dm9051_at32f403a_irq_name(dm9051_at32f403a_irq_mode_t irq_mode)
{
    switch (irq_mode) {
    case DM9051_AT32F403A_IRQ_OFF:
        return "off";
    case DM9051_AT32F403A_IRQ_EXTI:
        return "exti";
    default:
        return "unknown";
    }
}
