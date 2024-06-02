# MSP430-DMA-Keyboard-State-Manager-Lab-3

Welcome to this GitHub repository showcasing a sophisticated embedded system project for MSP430x2xx microcontrollers, programmed in C to leverage a finite state machine (FSM) for managing peripherals with an emphasis on Direct Memory Access (DMA) and keyboard interactions. This project is ideally structured for intricate hardware control and is perfect for educational purposes and advanced embedded development.

# Features

Modular Design: Code is organized into Application (APP), Board Support Package (BSP), Hardware Abstraction Layer (HAL), and Application Programming Interface (API) layers, enhancing both maintainability and scalability.

Finite State Machine (FSM): Manages system states and transitions for effective control of operational modes, ensuring a robust and responsive system.

Peripheral Management with DMA: Utilizes DMA for efficient data transfer in peripheral management, significantly reducing CPU load and enhancing performance.

Keyboard-Driven Interactions: Implements a keyboard interface for user inputs, driving state transitions and system configurations directly through hardware interactions.

Low Power Management: Implements various low-power modes to optimize power consumption, vital for battery-operated and energy-efficient applications.

# FSM States and Operations

The FSM in this project manages different aspects of system functionality through these states:

state0 (Idle State): Awaits user interaction or external triggers, with low power consumption.

state1 (Input Reading): Handles keypad inputs, enabling interrupts and preparing the system for user interaction.

state2 (Display Management): Manages the LCD display, adjusting content based on user inputs via the keypad.

state3 (System Adjustment): Adjusts system settings based on user commands and system status.

state4 (Error Handling): Manages system errors with indicators through LEDs and messages on the LCD.

# Peripheral Utilization

Key Peripherals:

GPIOs

LEDs

LCD

Keypad

Interrupts

# Project Structure

api.h & api.c: Define and implement interactions with peripherals.

app.h: Declares FSM states, modes, and global variables.

bsp.h & bsp.c: Include hardware-specific configurations and initializations.

halGPIO.h & halGPIO.c: Provide lower-level hardware management functions.

main.c: Initializes the system and manages the operational loop.

# Getting Started

To start using this project on your MSP430 device:

1. Set up your development environment using Code Composer Studio or MSPGCC.
2. Clone this repository to your machine.
3. Open the project in your IDE, navigating to the main directory.
4. Compile the code with an MSP430-compatible compiler.
5. Flash the binary to your microcontroller.
6. Reset the microcontroller to boot into the default state.
