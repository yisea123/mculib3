// #include <windows>
// const int NotUsed = system( "color 20" );
#define STM32F030x6
#define F_OSC   8000000UL
#define F_CPU   48000000UL
#include "periph_rcc.h"
#include "pin.h"
#include "timers.h"
#include "button_old.h"
#include "modbus_master.h"
// #include "example/example_adc.h"
// #include "example/example_modbus_master.h"
// #include "example_flash.h"
// #include "example_safe_flash.h"


/// эта функция вызываеться первой в startup файле
extern "C" void init_clock ()
{
   // FLASH::set (FLASH::Latency::_1);

    mcu::make_reference<mcu::Periph::RCC>()
        .set (mcu::RCC:: AHBprescaler::AHBnotdiv)
        .set (mcu::RCC:: APBprescaler::APBnotdiv)
        .set (mcu::RCC::  SystemClock::CS_PLL)
        .set (mcu::RCC::    PLLsource::HSIdiv2)
        .set (mcu::RCC::PLLmultiplier::_12)
        .on_PLL()
        .wait_PLL_ready();
}

using TX  = mcu::PA2;
using RX  = mcu::PA3;
using RTS = mcu::PA1;


int main()
{
    // mcu::example::safe_flash();
    // mcu::example::flash();

    // decltype(auto) counter = Counter::make<mcu::Periph::TIM1, mcu::PA9>(450);
    // uint16_t count{0};

    // decltype(auto) led = Pin::make<mcu::PB0, mcu::PinMode::Output>();
    // decltype(auto) led2 = Pin::make<mcu::PB1, mcu::PinMode::Output>();

    // decltype(auto) in = mcu::Button::make<mcu::PA9>();
    // decltype(auto) in2 = mcu::Button::make<mcu::PA7>();
    
    // decltype(auto) in = Pin::make<mcu::PA9, mcu::PinMode::Input>();
    // decltype(auto) in1 = Pin::make<mcu::PA7, mcu::PinMode::Input>();

    // Timer timer{100};
    // Timer timer_1{500};

    constexpr bool parity_enable {true};
    constexpr int  timeout       {100_ms};
    constexpr UART::Settings set {
          not parity_enable
        , UART::Parity::even
        , UART::DataBits::_8
        , UART::StopBits::_1
        , UART::Baudrate::BR9600
    };

    // constexpr auto uov_address {1};

    struct Modbus {
        Register<1, Modbus_function::read_03, 7>  uv_level;
    } modbus;

    decltype(auto) modbus_master =
        make_modbus_master <mcu::Periph::USART1, TX, RX, RTS> (
            timeout, set, modbus
    );

    while(1){
        modbus_master();
        // led ^= in;
        // led2 ^= in2;
        // count = counter;
    }

}
