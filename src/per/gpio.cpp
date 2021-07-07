#include "stm32h7xx_hal.h"
#include "per/gpio.h"
#include "util/hal_map.h"

using namespace daisy;

void GPIO::Init(Config config)
{
    pin_ = config.pin;

    GPIO_InitTypeDef ginit;
    switch(config.mode)
    {
        case Config::Mode::INPUT: ginit.Mode = GPIO_MODE_INPUT; break;
        case Config::Mode::OUTPUT_PP: ginit.Mode = GPIO_MODE_OUTPUT_PP; break;
        case Config::Mode::OUTPUT_OD: ginit.Mode = GPIO_MODE_OUTPUT_OD; break;
        case Config::Mode::ANALOG: ginit.Mode = GPIO_MODE_ANALOG; break;
    }
    switch(config.pull)
    {
        case Config::Pull::NOPULL: ginit.Pull = GPIO_NOPULL; break;
        case Config::Pull::PULLUP: ginit.Pull = GPIO_PULLUP; break;
        case Config::Pull::PULLDOWN: ginit.Pull = GPIO_PULLDOWN; break;
    }
    switch(config.speed)
    {
        case Config::Speed::LOW: ginit.Speed = GPIO_SPEED_LOW; break;
        case Config::Speed::MEDIUM: ginit.Speed = GPIO_SPEED_MEDIUM; break;
        case Config::Speed::FAST: ginit.Speed = GPIO_SPEED_FAST; break;
        case Config::Speed::HIGH: ginit.Speed = GPIO_SPEED_HIGH; break;
    }

    ginit.Pin          = dsy_hal_map_get_pin(pin_);
    ginit.Alternate    = config.alternate;
    GPIO_TypeDef *port = dsy_hal_map_get_port(pin_);

    dsy_hal_map_gpio_clk_enable(pin_);

    HAL_GPIO_Init(port, &ginit);
}

void GPIO::DeInit()
{
    GPIO_TypeDef *port = dsy_hal_map_get_port(pin_);
    uint16_t      pin  = dsy_hal_map_get_pin(pin_);

    HAL_GPIO_DeInit(port, pin);
}

bool GPIO::Read()
{
    GPIO_TypeDef *port = dsy_hal_map_get_port(pin_);
    uint16_t      pin  = dsy_hal_map_get_pin(pin_);

    return HAL_GPIO_ReadPin(port, pin);
}

void GPIO::Write(bool state)
{
    GPIO_TypeDef *port = dsy_hal_map_get_port(pin_);
    uint16_t      pin  = dsy_hal_map_get_pin(pin_);

    return HAL_GPIO_WritePin(port, pin, (GPIO_PinState)state);
}

void GPIO::Toggle()
{
    GPIO_TypeDef *port = dsy_hal_map_get_port(pin_);
    uint16_t      pin  = dsy_hal_map_get_pin(pin_);

    HAL_GPIO_TogglePin(port, pin);
}