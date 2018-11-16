#pragma once
#include "interrupt.h"

#if define (STM32F103xB)

	// список прерываний, которые не описаны
	extern "C" void WWDG_IRQHandler            () { while(1) {} }
   extern "C" void PVD_IRQHandler             () { while(1) {} }
   extern "C" void TAMPER_IRQHandler          () { while(1) {} }
   extern "C" void RTC_IRQHandler             () { while(1) {} }
   extern "C" void FLASH_IRQHandler           () { while(1) {} }
   extern "C" void RCC_IRQHandler             () { while(1) {} }
   extern "C" void EXTI0_IRQHandler           () { while(1) {} }
   extern "C" void EXTI1_IRQHandler           () { while(1) {} }
   extern "C" void EXTI2_IRQHandler           () { while(1) {} }
   extern "C" void EXTI3_IRQHandler           () { while(1) {} }
   extern "C" void EXTI4_IRQHandler           () { while(1) {} }
   extern "C" void ADC1_2_IRQHandler          () { while(1) {} }
   extern "C" void USB_HP_CAN1_TX_IRQHandler  () { while(1) {} }
   extern "C" void USB_LP_CAN1_RX0_IRQHandler () { while(1) {} }
   extern "C" void CAN1_RX1_IRQHandler        () { while(1) {} }
   extern "C" void CAN1_SCE_IRQHandler        () { while(1) {} }
   extern "C" void EXTI9_5_IRQHandler         () { while(1) {} }
   extern "C" void TIM1_BRK_IRQHandler        () { while(1) {} }
   extern "C" void TIM1_UP_IRQHandler         () { while(1) {} }
   extern "C" void TIM1_TRG_COM_IRQHandler    () { while(1) {} }
   extern "C" void TIM1_CC_IRQHandler         () { while(1) {} }
   extern "C" void TIM2_IRQHandler            () { while(1) {} }
   extern "C" void TIM3_IRQHandler            () { while(1) {} }
   extern "C" void TIM4_IRQHandler            () { while(1) {} }
   extern "C" void I2C1_EV_IRQHandler         () { while(1) {} }
   extern "C" void I2C1_ER_IRQHandler         () { while(1) {} }
   extern "C" void I2C2_EV_IRQHandler         () { while(1) {} }
   extern "C" void I2C2_ER_IRQHandler         () { while(1) {} }
   extern "C" void SPI1_IRQHandler            () { while(1) {} }
   extern "C" void SPI2_IRQHandler            () { while(1) {} }
   extern "C" void EXTI15_10_IRQHandler       () { while(1) {} }
   extern "C" void RTC_Alarm_IRQHandler       () { while(1) {} }
   extern "C" void USBWakeUp_IRQHandler       () { while(1) {} }

	extern "C" void USART1_IRQHandler          () { interrupt_usart1.interrupt(); }
   extern "C" void USART2_IRQHandler          () { interrupt_usart2.interrupt(); }
   extern "C" void USART3_IRQHandler          () { interrupt_usart3.interrupt(); }

	extern "C" void DMA1_Channel1_IRQHandler   () { interrupt_DMA_channel1.interrupt(); }
   extern "C" void DMA1_Channel2_IRQHandler   () { interrupt_DMA_channel2.interrupt(); }
   extern "C" void DMA1_Channel3_IRQHandler   () { interrupt_DMA_channel3.interrupt(); }
   extern "C" void DMA1_Channel4_IRQHandler   () { interrupt_DMA_channel4.interrupt(); }
   extern "C" void DMA1_Channel5_IRQHandler   () { interrupt_DMA_channel5.interrupt(); }
   extern "C" void DMA1_Channel6_IRQHandler   () { interrupt_DMA_channel6.interrupt(); }
   extern "C" void DMA1_Channel7_IRQHandler   () { interrupt_DMA_channel7.interrupt(); }


#endif