# STM32F4xx Project with CMSIS, HAL, and BSP Components

🚀 **A structured project template for STM32F4xx development using CMSIS, HAL, and BSP components.**

This project is designed for **bare-metal** and **low-level firmware development** using the **STM32Cube architecture**, integrating:
- **CMSIS** – ARM Cortex Microcontroller Software Interface Standard
- **HAL** – Hardware Abstraction Layer for STM32F4xx
- **BSP Components** – Board Support Package for peripherals

## 🛠 Prerequisites

### Required Tools

Before cloning and using the project, ensure the following tools are installed:

| Tool                | Description                                   | Download Link                                                                 |
|---------------------|-----------------------------------------------|--------------------------------------------------------------------------------|
| **CMake**           | Build system generator                        | [CMake](https://cmake.org/download/)                                           |
| **ARM Toolchain**   | GCC for ARM Cortex-M (`arm-none-eabi`)        | [GNU ARM](https://developer.arm.com/downloads/-/gnu-rm)                        |
| **OpenOCD**         | Debugging and flashing tool                   | [OpenOCD](http://openocd.org/)                                                 |
| **ST-Link Utility** | GUI tool for flashing STM32 (Optional)        | [ST-Link Utility](https://www.st.com/en/development-tools/stsw-link004.html)    |

## 📥 Cloning the Repository

Clone the project **with submodules** to include CMSIS, HAL, and BSP components:

```sh
git clone --recurse-submodules https://github.com/SergioAguilarL/ArmProject.git
cd ArmProject
```

## 💡 If you forgot to clone with submodules, initialize them with:

```sh
git submodule update --init --recursive

```
## ⚙️ Building the Project
This project uses CMake for building. However I already created an .bat file to run for clean and incremental build you can find in the root folder of this repo

## 🔌 Flashing the Firmware
Flash the generated .bin file using OpenOCD uisng the .bat file I placed in the in the root folde, just run the file after a successful build and see you board workig!!!

## 📜 License
This project is licensed under the MIT License. See the LICENSE file for details.

## 💬 Questions & Contributions
Feel free to open an issue or contribute to this project.
📩 Contact: Sergio Aguilar Loera @ sergioaguilarloera@gmail.com




