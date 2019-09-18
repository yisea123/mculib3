#pragma once

#include "timers.h"
#include "literals.h"
#include "function.h"
#include "periph_tim.h"
#include "periph_rcc.h"
#include "pin.h"

#if defined(USE_MOCK_TIM)
using TIM = mock::TIM;
#else
using TIM = mcu::TIM;
#endif

class Encoder : private TickSubscriber 
{
   int value{0};
   Callback<>    minus_callback;
   Callback<>    plus_callback;
   bool plus_executed {false};
   bool minus_executed{false};
   
   Pin& pin_a;
   Pin& pin_b;
   TIM& tim;
   Encoder(Pin& pin_a, Pin& pin_b, TIM& tim)
      : pin_a{pin_a}
      , pin_b{pin_b}
      , tim{tim}
   {tick_subscribe();}
public:
   template <mcu::Periph tim_, class Pin_a, class Pin_b, bool inverted = false>
   static auto& make ()
   {
      TIM::pin_static_assert<tim_, Pin_a>();
      TIM::pin_static_assert<tim_, Pin_b>();

      constexpr auto pin_mode_a = TIM::pin_mode<tim_, Pin_a>();
      constexpr auto pin_mode_b = TIM::pin_mode<tim_, Pin_b>();
      constexpr auto channel_a = TIM::channel<tim_, Pin_a>();
      constexpr auto channel_b = TIM::channel<tim_, Pin_b>();

      static Encoder encoder
      {
         Pin::make<Pin_a, pin_mode_a>(),
         Pin::make<Pin_b, pin_mode_b>(),
         mcu::make_reference<tim_>()
      };

      mcu::make_reference<mcu::Periph::RCC>().clock_enable<tim_>();

      encoder.tim.set(TIM::SlaveMode::Encoder3)
                 .template set<channel_a>(TIM::SelectionCompareMode::Input)
                 .template set<channel_b>(TIM::SelectionCompareMode::Input);
               //   .set_auto_reload(1);
      if (inverted)
         encoder.tim.template set<channel_a>(TIM::Polarity::falling);
      encoder.tim.clear_counter()
                 .counter_enable();


      return encoder;
   }

   uint16_t qty_click(){return tim.get_counter() / 2;}
   int16_t operator= (int16_t v){tim.set_counter(v); return *this;}
           operator  uint16_t()  {return tim.get_counter();}
   bool    operator> (int16_t v){return static_cast<int16_t> (tim.get_counter()) > v;}

   void set_minus_callback      (Callback<> v)   { minus_callback      = v; }
   void set_plus_callback       (Callback<> v)   { plus_callback       = v; }

   void notify() override {
      
      if (value < qty_click() and not plus_executed) {
         plus_executed = true;
         value = qty_click();
         plus_callback();
         return;
      }

      if (value > qty_click() and not minus_executed) {
         minus_executed = true;
         value = qty_click();
         minus_callback();
         return;
      }

      if (value == qty_click()){
         plus_executed = false;
         minus_executed = false;
         return;
      }
   }
};