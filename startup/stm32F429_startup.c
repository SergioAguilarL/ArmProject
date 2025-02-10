/******************************************************************************
 * @file    stm32F3429_startup.c
 * @author  Sergio Aguilar Loera
 * @date    2025-02-03
 * @version 1.0
 * @brief   STM32F429 Bare-Metal Project
 *
 @details
 * The purpose of this file is to define the **Interrupt Service Routine (ISR) vector table** 
 * and setup the **initialization** for the STM32F429 microcontroller in a **bare-metal** 
 * environment (without an operating system or HAL libraries).
 *
 * ### Key Responsibilities:
 * 1. **ISR Vector Table**
 *    - Defines the **vector table** which contains pointers to **exception handlers** 
 *      and **interrupt service routines** (ISRs).
 *    - The **first entry** is the stack pointer (_estack), which is initialized to 
 *      the highest address of SRAM.
 *    - The **second entry** is the **Reset Handler**, which is the first function executed 
 *      after a reset.
 *
 * 2. **Reset Handler Implementation**
 *    - The **Reset_Handler** function is the first code that executes after power-up or reset.
 *    - Typically performs **low-level system initialization**, including:
 *        - Copying initialized **data sections** from **FLASH** to **SRAM**.
 *        - Clearing the **BSS section** (uninitialized global variables).
 *        - Setting up **stack pointer**.
 *        - Calling `SystemInit()` if needed.
 *        - Jumping to the `main()` function.
 *
 * 3. **Default Handlers for Exceptions and Interrupts**
 *    - Provides **weak definitions** of exception handlers.
 *    - Can be overridden in the user application.
 *    - Ensures unhandled interrupts don’t crash the system.
 *
 * ### Notes:
 * - This startup file is **specific to the STM32F429 microcontroller**.
 * - It does **not** use CMSIS or CubeIDE; it is designed for **bare-metal development**.
 * - Requires a **linker script (.ld)** to define memory layout.
 *
 * Copyright (c) <Year> <Your Name>. All rights reserved.
 *
 ******************************************************************************/
#include <stdint.h>

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (192 *1024) //192KB 
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))
#define STACK_START     SRAM_END


void Reset_Handler(void);
void NMI_Handler(void)                          __attribute__((weak,alias("Default_handler")));
void HardFault_Handler(void)                    __attribute__((weak,alias("Default_handler")));
void MemManage_Handler(void)                    __attribute__((weak,alias("Default_handler")));
void BusFault_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void UsageFault_Handler(void)                   __attribute__((weak,alias("Default_handler")));
void SVCall_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void DebugMonitor_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void PendSV_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void Systick_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void WWDG_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void PVD_Handler(void)                          __attribute__((weak,alias("Default_handler")));
void TAMP_STAMP_Handler(void)                   __attribute__((weak,alias("Default_handler")));
void RTC_WKUP_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void FLASH_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void RCC_Handler(void)                          __attribute__((weak,alias("Default_handler")));
void EXTI0_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void EXTI1_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void EXTI2_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void EXTI3_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void EXTI4_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void DMA1_Stream0_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA1_Stream1_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA1_Stream2_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA1_Stream3_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA1_Stream4_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA1_Stream5_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA1_Stream6_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void ADC_Handler(void)                          __attribute__((weak,alias("Default_handler")));
void CAN1_TX_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void CAN1_RX0_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void CAN1_RX1_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void CAN1_SCE_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void EXTI9_5_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void TIM1_BRK_TIM9_Handler(void)                __attribute__((weak,alias("Default_handler")));
void TIM1_UP_TIM10_Handler(void)                __attribute__((weak,alias("Default_handler")));
void TIM1_TRG_COM_TIM11_Handler(void)           __attribute__((weak,alias("Default_handler")));
void TIM1_CC_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void TIM2_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void TIM3_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void TIM4_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void I2C1_EV_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void I2C1_ER_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void I2C2_EV_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void I2C2_ER_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void SPI1_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void SPI2_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void USART1_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void USART2_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void USART3_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void EXTI15_10_Handler(void)                    __attribute__((weak,alias("Default_handler")));
void RTC_Alarm_Handler(void)                    __attribute__((weak,alias("Default_handler")));
void OTG_FS_WKUP_Handler(void)                  __attribute__((weak,alias("Default_handler")));
void TIM8_BRK_TIM12_Handler(void)               __attribute__((weak,alias("Default_handler")));
void TIM8_UP_TIM13_Handler(void)                __attribute__((weak,alias("Default_handler")));
void TIM8_TRG_COM_TIM14_Handler(void)           __attribute__((weak,alias("Default_handler")));
void TIM8_CC_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void DMA1_Stream7_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void FSMC_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void SDIO_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void TIM5_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void SPI3_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void UART4_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void UART5_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void TIM6_DAC_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void TIM7_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void DMA2_Stream0_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA2_Stream1_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA2_Stream2_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA2_Stream3_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA2_Stream4_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void ETH_Handler(void)                          __attribute__((weak,alias("Default_handler")));
void ETH_WKUP_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void CAN2_TX_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void CAN2_RX0_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void CAN2_RX1_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void CAN2_SCE_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void OTG_FS_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void DMA2_Stream5_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA2_Stream6_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void DMA2_Stream7_Handler(void)                 __attribute__((weak,alias("Default_handler")));
void USART6_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void I2C3_EV_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void I2C3_ER_Handler(void)                      __attribute__((weak,alias("Default_handler")));
void OTG_HS_EP1_OUT_Handler(void)               __attribute__((weak,alias("Default_handler")));
void OTG_HS_EP1_IN_Handler(void)                __attribute__((weak,alias("Default_handler")));
void OTG_HS_WKUP_Handler(void)                  __attribute__((weak,alias("Default_handler")));
void OTG_HS_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void DCMI_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void CRYP_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void HASH_RNG_Handler(void)                     __attribute__((weak,alias("Default_handler")));
void FPU_Handler(void)                          __attribute__((weak,alias("Default_handler")));
void UART7_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void UART8_Handler(void)                        __attribute__((weak,alias("Default_handler")));
void SPI4_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void SPI5_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void SPI6_Handler(void)                         __attribute__((weak,alias("Default_handler")));
void LCDTFT_Handler(void)                       __attribute__((weak,alias("Default_handler")));
void LCDTFTError_Handler(void)                  __attribute__((weak,alias("Default_handler")));
void DMA2D_Handler(void)                        __attribute__((weak,alias("Default_handler")));


uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)& SVCall_Handler,
    (uint32_t)& DebugMonitor_Handler,
    (uint32_t)& PendSV_Handler,        
    (uint32_t)& Systick_Handler,       
    (uint32_t)& WWDG_Handler,         
    (uint32_t)& PVD_Handler,          
    (uint32_t)& TAMP_STAMP_Handler,
    (uint32_t)& RTC_WKUP_Handler,      
    (uint32_t)& FLASH_Handler,        
    (uint32_t)& RCC_Handler,           
    (uint32_t)& EXTI0_Handler,         
    (uint32_t)& EXTI1_Handler, 
    (uint32_t)& EXTI2_Handler, 
    (uint32_t)& EXTI3_Handler, 
    (uint32_t)& EXTI4_Handler, 
    (uint32_t)& DMA1_Stream0_Handler,
    (uint32_t)& DMA1_Stream1_Handler,
    (uint32_t)& DMA1_Stream2_Handler,
    (uint32_t)& DMA1_Stream3_Handler,
    (uint32_t)& DMA1_Stream4_Handler,
    (uint32_t)& DMA1_Stream5_Handler,
    (uint32_t)& DMA1_Stream6_Handler,
    (uint32_t)& ADC_Handler,        
    (uint32_t)& CAN1_TX_Handler,    
    (uint32_t)& CAN1_RX0_Handler,
    (uint32_t)& CAN1_RX1_Handler,
    (uint32_t)& CAN1_SCE_Handler,
    (uint32_t)& EXTI9_5_Handler,
    (uint32_t)& TIM1_BRK_TIM9_Handler,
    (uint32_t)& TIM1_UP_TIM10_Handler,
    (uint32_t)& TIM1_TRG_COM_TIM11_Handler,
    (uint32_t)& TIM1_CC_Handler,
    (uint32_t)& TIM2_Handler,        
    (uint32_t)& TIM3_Handler,        
    (uint32_t)& TIM4_Handler,        
    (uint32_t)& I2C1_EV_Handler,
    (uint32_t)& I2C1_ER_Handler,
    (uint32_t)& I2C2_EV_Handler,
    (uint32_t)& I2C2_ER_Handler,
    (uint32_t)& SPI1_Handler,        
    (uint32_t)& SPI2_Handler,       
    (uint32_t)& USART1_Handler,      
    (uint32_t)& USART2_Handler,      
    (uint32_t)& USART3_Handler,      
    (uint32_t)& EXTI15_10_Handler,    
    (uint32_t)& RTC_Alarm_Handler,    
    (uint32_t)& OTG_FS_WKUP_Handler,
    (uint32_t)& TIM8_BRK_TIM12_Handler,
    (uint32_t)& TIM8_UP_TIM13_Handler, 
    (uint32_t)& TIM8_TRG_COM_TIM14_Handler,
    (uint32_t)& TIM8_CC_Handler,  
    (uint32_t)& DMA1_Stream7_Handler,  
    (uint32_t)& FSMC_Handler,       
    (uint32_t)& SDIO_Handler,       
    (uint32_t)& TIM5_Handler,       
    (uint32_t)& SPI3_Handler,       
    (uint32_t)& UART4_Handler,       
    (uint32_t)& UART5_Handler,       
    (uint32_t)& TIM7_Handler,
    (uint32_t)& DMA2_Stream0_Handler,
    (uint32_t)& DMA2_Stream1_Handler,
    (uint32_t)& DMA2_Stream2_Handler,
    (uint32_t)& DMA2_Stream3_Handler,
    (uint32_t)& DMA2_Stream4_Handler,
    (uint32_t)& ETH_Handler,
    (uint32_t)& ETH_WKUP_Handler,  
    (uint32_t)& CAN2_TX_Handler, 
    (uint32_t)& CAN2_RX0_Handler, 
    (uint32_t)& CAN2_RX1_Handler,
    (uint32_t)& CAN2_SCE_Handler, 
    (uint32_t)& OTG_FS_Handler,      
    (uint32_t)& DMA2_Stream5_Handler,
    (uint32_t)& DMA2_Stream6_Handler,
    (uint32_t)& DMA2_Stream7_Handler,
    (uint32_t)& USART6_Handler,      
    (uint32_t)& I2C3_EV_Handler,   
    (uint32_t)& I2C3_ER_Handler,   
    (uint32_t)& OTG_HS_EP1_OUT_Handler,
    (uint32_t)& OTG_HS_EP1_IN_Handler, 
    (uint32_t)& OTG_HS_WKUP_Handler,
    (uint32_t)& OTG_HS_Handler,        
    (uint32_t)& DCMI_Handler,          
    (uint32_t)& CRYP_Handler,          
    (uint32_t)& HASH_RNG_Handler,      
    (uint32_t)& FPU_Handler,           
    (uint32_t)& UART7_Handler,         
    (uint32_t)& UART8_Handler,         
    (uint32_t)& SPI4_Handler,         
    (uint32_t)& SPI5_Handler,          
    (uint32_t)& SPI6_Handler,          
    (uint32_t)& LCDTFT_Handler,        
    (uint32_t)& LCDTFTError_Handler,   
    (uint32_t)& DMA2D_Handler         

};

void Default_handler(void)
{

    while(1);
}

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main(void);

void Reset_Handler(void)
{
  // Copy .data from FLASH to SRAM
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t*) &_etext;
  uint8_t *sram_data = (uint8_t*) &_sdata;
  
  for (uint32_t i = 0; i < data_size; i++)
  {
    sram_data[i] = flash_data[i];
  }

  // Zero-fill .bss section in SRAM
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i < bss_size; i++)
  {
    bss[i] = 0;
  }
  
  main();
}