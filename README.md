# AVR MCU Families - MCAL and HAL Drivers

This repository provides a comprehensive collection of Microcontroller Abstraction Layer (MCAL) and Hardware Abstraction Layer (HAL) drivers for various AVR microcontroller families. Each driver is designed to facilitate the development and deployment of embedded applications using AVR MCUs.

## Repository Contents

### MCAL Drivers
The MCAL (Microcontroller Abstraction Layer) drivers provide low-level access to essential peripherals on AVR MCUs. The following drivers are included:

- **ICU (Input Capture Unit)**: For capturing input signals with precise timing.
- **ADC (Analog-to-Digital Converter)**: For reading analog signals from sensors and converting them to digital values.
- **GPIO (General Purpose Input/Output)**: For configuring and controlling digital input and output pins.
- **SPI (Serial Peripheral Interface)**: For high-speed, full-duplex communication with other devices.
- **UART (Universal Asynchronous Receiver/Transmitter)**: For serial communication with other devices.
- **Timers**: For time-based operations such as delays, event timing, and task scheduling.
- **PWM (Pulse Width Modulation)**: For generating PWM signals for motor control, LED dimming, and other applications.
- **I2C (TWI - Two-Wire Interface)**: A low-level driver for communicating with I2C-compatible devices. This driver enables the Atmega32 to act as a master or slave in an I2C communication setup, supporting multi-master and multi-slave configurations for data transfer between the MCU and other I2C-enabled peripherals like sensors, displays, and EEPROMs.


### HAL Drivers
The HAL (Hardware Abstraction Layer) drivers offer a higher-level interface for various peripherals, making it easier to develop applications without needing to handle low-level register configurations. The following drivers are included:

- **LCD**: Driver for interfacing with LCD displays.
- **Keypad**: Driver for interacting with matrix keypads.
- **Ultrasonic**: Driver for ultrasonic distance measurement sensors.
- **EEPROM**: A high-level driver for reading from and writing to external EEPROM devices using the I2C (TWI) protocol. This driver abstracts the I2C communication and provides easy-to-use functions for storing and retrieving data in external EEPROM chips, such as the 24Cxx series, allowing persistent storage of data across power cycles.


## Getting Started

To start using the drivers in this repository:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/al-sakka/AVR_Drivers
   ```
2. **Navigate to the desired driver**:
   Each driver is located in its respective directory within the repository, along with documentation on how to use it.
   
3. **Integrate the driver into your project**:
   - Include the necessary driver files in your project.
   - Initialize and configure the driver as per the documentation.

## Compatibility

These drivers are compatible with various AVR MCU families. Please refer to each driver's documentation for details on specific supported MCUs and configuration options.
