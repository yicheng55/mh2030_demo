#include "at32f403a_board.h"
#include "at32f403a_platform.h"

#include <stdarg.h>
#include <stdio.h>

static usart_type *uip_uart = USART1;

static void configure_debug_uart(uint32_t baudrate)
{
    gpio_init_type gpio;
    usart_init_type usart;

    crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_1);
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_1);

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_MUX;
    gpio.gpio_pull = GPIO_PULL_NONE;
    gpio.gpio_pins = GPIO_PINS_9;
    gpio_init(GPIOA, &gpio);

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_MUX;
    gpio.gpio_pull = GPIO_PULL_UP;
    gpio.gpio_pins = GPIO_PINS_10;
    gpio_init(GPIOA, &gpio);

    usart_default_para_init(&usart);
    usart.baudrate = baudrate;
    usart.word_length = USART_WORD_LEN_8B;
    usart.stop_bits = USART_STOP_1_BIT;
    usart.parity = USART_PARITY_NONE;
    usart.mode = USART_MODE_TX | USART_MODE_RX;
    usart_init(uip_uart, &usart);
    usart_enable(uip_uart, TRUE);
}

void at32f403a_uip_clock_init(void)
{
    crm_clocks_freq_type clocks;

    system_clock_config();

    crm_clocks_freq_get(&clocks);
    printf("\r\n[AT32F403A] board init\r\n");
    printf("[AT32F403A] SYSCLK=%lu HCLK=%lu PCLK1=%lu PCLK2=%lu\r\n",
           clocks.sclk_freq,
           clocks.ahb_freq,
           clocks.apb1_freq,
           clocks.apb2_freq);
}

void at32f403a_uip_board_init(uint32_t baudrate)
{
    at32f403a_uip_clock_init();
    Delay_Init();
    configure_debug_uart(baudrate);
}

int SER_PutChar(int ch)
{
    while (usart_flag_get(uip_uart, USART_TDBE_FLAG) == RESET) {
    }
    usart_data_transmit(uip_uart, (uint8_t)ch);
    return ch;
}

int fputc(int ch, FILE *f)
{
    (void)f;
    if (ch == '\n') {
        SER_PutChar('\r');
    }
    return SER_PutChar(ch);
}
