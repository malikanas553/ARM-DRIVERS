# ARM Cortex-M4 SysTick & NVIC Drivers (TM4C)

This repository contains a **bare-metal driver implementation** for the **SysTick Timer** and the **Nested Vectored Interrupt Controller (NVIC)** targeting **ARM Cortex-M4** microcontrollers (**TM4C series**).

This project was developed as the **Final Project for the ARM Cortex-M Course (Advanced Embedded Diploma)** and focuses on **system timers** and **interrupt management**, with the system configured to run at a **16 MHz clock speed**. :contentReference[oaicite:0]{index=0}

---

## 📌 Overview

In this project, two essential drivers are implemented:

- **SysTick Timer Driver**
  - Initialize the SysTick timer
  - Start/Stop timer
  - SysTick interrupt handler
  - Generate interrupts at specific time intervals

- **NVIC Driver**
  - Enable/disable interrupts for specific IRQ numbers
  - Set priority for specific IRQ numbers
  - Enable/disable ARM system/fault exceptions
  - Set priority for ARM system/fault exceptions :contentReference[oaicite:1]{index=1}

---

## 🧩 Implemented APIs 

### SysTick APIs
```c
void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);
```
### NVIC APIs
```c
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);

void NVIC_EnableException(NVIC_ExceptionType Exception_Num);
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num,
                               NVIC_ExceptionPriorityType Exception_Priority);
```
# 🚀 Quick Start Guide (SysTick + NVIC Drivers)

This quick start guide shows you how to **integrate and use** the SysTick and NVIC drivers in your embedded project (ARM Cortex-M4 / TM4C @ 16 MHz). :contentReference[oaicite:0]{index=0}

---

## 1) ✅ Add Driver Files to Your Project

Make sure your project contains the following driver files:

### Header files (Include folder)
- `std_types.h`
- `common_macros.h`
- `systick.h`
- `nvic.h`

### Source files (Source folder)
- `systick.c`
- `nvic.c`

Recommended structure:
```text
Project/
│
├── Inc/
│   ├── std_types.h
│   ├── common_macros.h
│   ├── systick.h
│   └── nvic.h
│
├── Src/
│   ├── systick.c
│   └── nvic.c
│
└── main.c
```
## 2) Include Headers

To use the SysTick and NVIC drivers correctly, include the following headers in your application file (e.g., `main.c`):

```c
#include "std_types.h"
#include "common_macros.h"
#include "systick.h"
#include "nvic.h"
```
--- 
## Notes:
- Drivers are intended for register-level programming (no HAL dependency).

- Can be extended easily to support more Cortex-M peripherals.


