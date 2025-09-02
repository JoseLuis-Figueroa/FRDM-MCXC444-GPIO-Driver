# FRDM-MCXC444-GPIO-Driver
This repository contains the implementation of a reusable **General Purpose Input/Output (GPIO) driver** a **Hello World** code to the embedded systems for the **NXP FRDM-MCXC444 board** (ARM Cortex-M0+). The driver is written in **Embedded C (bare-metal)** and provides a portable, structured, and configurable interface to control MCU GPIO peripherals.

The project follows **layered driver design principles** (driver ↔ HAL ↔ application) and adheres to industry-standard practices such as **MISRA-C** for safety and reliability.

---

## Table of Contents
- [About the Project](#about-the-project)
  - [Key Features](#key-features)
  - [Technical Details](#technical-details)
- [Project Status](#project-status)
- [Getting Started](#getting-started)
  - [Dependencies](#dependencies)
  - [Getting the Source](#getting-the-source)
  - [Building](#building)
  - [Running](#running)
- [Usage](#usage)
- [Release Process](#release-process)
- [How to Get Help](#how-to-get-help)
- [Contributing](#contributing)
- [Further Reading](#further-reading)
- [License](#license)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)

---

## About the Project

The **GPIO Driver** allows initialization, configuration, and control of MCU I/O pins. It uses a **configuration table** (`gpio_cfg.c`) to define pin settings, enabling scalable and reusable hardware abstraction.  

This project serves as the foundation for **higher-level reusable drivers** and is designed for **bare-metal development** on the **FRDM-MCXC444** evaluation board.

### Key Features
- Configuration-driven initialization (`GPIO_init`).
- Safe access with **assertions** to prevent out-of-range settings.
- Support for:
  - Input and output modes.
  - Internal pull-up, pull-down, and no resistor.
  - Slew rate configuration.
- Pin operations:
  - `GPIO_pinRead`
  - `GPIO_pinWrite`
  - `GPIO_pinToggle`
- Direct register access (`GPIO_registerWrite`, `GPIO_registerRead`).
- Portable and reusable code structure.
- Doxygen-ready documentation.

### Technical Details
- **Microcontroller**: NXP MCXC444 (ARM Cortex-M0+).
- **Board**: FRDM-MCXC444.
- **Language**: Embedded C (bare-metal).
- **Coding Standard**: MISRA-C.
- **Tools:**
  - **IDE/Editor**: VS Code.
  - **Toolchain**: ARM GNU Toolchain (`arm-none-eabi-gcc`).
  - **Build System**: Makefile (auto-generated in `/Debug`).
  - **Documentation**: Doxygen (planned).

**[Back to top](#table-of-contents)**

---
