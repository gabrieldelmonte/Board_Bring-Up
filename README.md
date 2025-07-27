# Board Bring-Up Project

A microcontroller-based embedded system project featuring real-time monitoring, alarm management, and multi-language support using the PIC18F4550 microcontroller.

## Project Overview

This project implements a comprehensive board bring-up system that combines multiple peripherals and sensors to create a monitoring and control system. The system features a state machine-based architecture with real-time clock functionality, analog sensor monitoring, alarm management, and a user-friendly LCD interface.

## Features

### Core Functionality
- **Real-Time Clock (RTC)**: DS1307-based timekeeping with hour, minute, and second setting
- **Analog Monitoring**: ADC-based sensor reading with configurable alarm thresholds
- **Alarm System**: Dual-level alarm monitoring (high/low thresholds) with visual indicators
- **Multi-Language Support**: Interface available in 6 different languages
- **State Machine Architecture**: Robust navigation system between different operational modes

### Hardware Peripherals
- **LCD Display**: 16-character display for system information and menus
- **LED Control**: Visual feedback and alarm indication system
- **Button Interface**: Navigation and parameter adjustment controls
- **I2C Communication**: For RTC and DAC communication
- **PWM Output**: Pulse width modulation for analog output control
- **Serial Communication**: UART interface for debugging and external communication
- **DAC Output**: MCP4725-based digital-to-analog conversion

### System States
- **Menu**: Main navigation interface
- **Alarm Configuration**: Set high and low alarm thresholds
- **Language Selection**: Choose from 6 available languages
- **Time Setting**: Configure hours, minutes, and seconds
- **Warning Mode**: Alert state when alarm conditions are triggered

## Hardware Requirements

### Microcontroller
- **PIC18F4550** microcontroller
- **20 MHz** crystal oscillator
- Power supply and basic support components

### Peripherals
- **DS1307** Real-Time Clock module
- **MCP4725** Digital-to-Analog Converter
- **16x2 LCD Display** with HD44780 controller
- **LEDs** for status indication
- **Push buttons** for user interface
- **Analog sensor** (connected to ADC channel 0)

### Development Tools
- MPLAB X IDE or compatible PIC development environment
- XC8 compiler for PIC18 family
- Programmer/debugger (PICkit, ICD, etc.)

## Project Structure

```
Board_Bring-Up/
├── src/
│   ├── main.c              # Main application entry point
│   └── code/
│       ├── ADC.c           # Analog-to-Digital Converter functions
│       ├── button.c        # Button handling and debouncing
│       ├── DAC_MCP4725.c   # MCP4725 DAC communication
│       ├── delay.c         # Timing and delay functions
│       ├── event.c         # Event handling and system events
│       ├── I2C.c           # I2C communication protocol
│       ├── LCD.c           # LCD display control functions
│       ├── LED.c           # LED control and patterns
│       ├── output.c        # Output formatting and display
│       ├── PWM.c           # Pulse Width Modulation control
│       ├── RTC_DS1307.c    # Real-Time Clock functions
│       ├── serial.c        # UART serial communication
│       ├── stateMachine.c  # Main state machine implementation
│       ├── variables.c     # Global variable management
│       └── headers/        # Header files for all modules
├── hardware/               # KiCad PCB design files
├── diagrams/               # System architecture diagrams
└── docs/                   # Project documentation
```

## Getting Started

### Prerequisites
1. MPLAB X IDE installed
2. XC8 compiler for PIC18 family
3. PIC programmer/debugger
4. Assembled hardware board or prototyping setup

### Building the Project
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/Board_Bring-Up.git
   cd Board_Bring-Up
   ```

2. Open the project in MPLAB X IDE

3. Configure the project settings:
   - Select PIC18F4550 as target device
   - Set XC8 as the compiler
   - Configure programmer/debugger

4. Build the project:
   - Click "Build" or use Ctrl+F11
   - Resolve any compilation errors

5. Program the microcontroller:
   - Connect your programmer
   - Click "Make and Program Device"

### Hardware Setup
1. Connect the LCD display to PORTD and control pins (RA2, RA3)
2. Wire the DS1307 RTC to the I2C bus (RC3/SCL, RC4/SDA)
3. Connect analog sensor to AN0 (RA0)
4. Wire push buttons for navigation
5. Connect LEDs for status indication
6. Ensure proper power supply (5V for PIC18F4550)

## Usage

### Navigation
- **Base Button**: Return to main menu from any state
- **Left/Right Buttons**: Navigate between menu options
- **Up/Down Buttons**: Adjust values in configuration modes

### Setting Alarms
1. Navigate to alarm configuration states
2. Use up/down buttons to adjust high and low thresholds
3. System will trigger warnings when sensor readings exceed limits

### Time Configuration
1. Access time setting modes through menu navigation
2. Adjust hours, minutes, and seconds individually
3. Changes are automatically saved to RTC

### Language Selection
- Navigate to language menu
- Choose from 6 available language options
- Interface will update to selected language

## Configuration

### System Parameters
Key configuration options in `defines.h`:
- `FREQ`: System frequency (20 MHz)
- `NUMBER_LANGUAGES`: Available languages (6)
- `MAX_ADC_VALUE`: Maximum ADC reading (1000)
- `MIN_ADC_VALUE`: Minimum ADC reading (0)

### Pin Assignments
- **LCD Data**: PORTD (RD0-RD7)
- **LCD Control**: RA2 (RS), RA3 (EN)
- **I2C**: RC3 (SCL), RC4 (SDA)
- **ADC Input**: RA0 (AN0)
- **LED Outputs**: Configurable in LED.c

## Additional Resources

- [PIC18F4550 Datasheet](https://www.microchip.com/en-us/product/PIC18F4550)
- [DS1307 RTC Datasheet](https://datasheets.maximintegrated.com/en/ds/DS1307.pdf)
- [MCP4725 DAC Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/22039d.pdf)
- PCB design files are available in the `hardware/` directory

## License

This project is licensed under the terms specified in the LICENSE file.
