# Arduino Voltage Monitoring System

## Overview

This project utilizes an Arduino board to measure and report voltage levels from an analog sensor. It reads voltage through an analog pin, applies voltage correction calculations, and sends the processed data via a Software Serial interface. The system also implements averaging to smooth out readings over time.

## Features

- **Voltage Measurement**: Reads voltage from an analog input.
- **Voltage Correction**: Accounts for the Arduino's reference voltage to provide accurate readings.
- **Running Average**: Smooths readings by averaging multiple samples.
- **Serial Communication**: Sends formatted voltage data over a Software Serial interface for external monitoring or control.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Nano)
- Voltage sensor (e.g., a voltage divider circuit)
- Jumper wires for connections

## Wiring Diagram

- Connect the voltage sensor output to analog pin A0 on the Arduino.
- Connect the ground of the sensor to the Arduino ground.
- Connect the supply voltage to the sensor as required.

## Installation

1. **Set Up the Hardware**:
   - Connect the Arduino to your computer.
   - Wire the voltage sensor to the appropriate pins on the Arduino.

2. **Install Required Libraries**:
   - This project does not require any external libraries beyond the standard Arduino IDE libraries.

3. **Upload the Code**:
   - Open the Arduino IDE, load the provided code, and upload it to your Arduino board.

## Code Explanation

### Key Functions

- `setup()`: Initializes the analog input and serial communication.
- `loop()`: Main loop that triggers voltage reading every 2 seconds.
- `readCorrectVoltage()`: Reads the analog value and calculates the corrected voltage based on the reference voltage.
- `readAvg()`: Computes the average voltage from multiple readings for smoothing.
- `sendData(float volt)`: Formats the voltage data and sends it via Software Serial.

### Voltage Calculation

The voltage measurement is based on the following formula:

Where:
- `R1` and `R2` are the resistances used in the voltage divider circuit.

## Usage

1. Once the Arduino is powered and the code is uploaded, it will start measuring the voltage from the connected sensor.
2. The voltage readings are printed to the Serial Monitor every 2 seconds.
3. If using the Software Serial interface, connect to the appropriate RX and TX pins for communication.

## Notes

- Ensure that the voltage levels from the sensor do not exceed the Arduino's maximum input voltage (typically 5V).
- Modify the resistor values (`R1` and `R2`) in the code as per your voltage divider configuration to achieve accurate readings.

## Troubleshooting

- If you do not see readings in the Serial Monitor, ensure that the baud rate matches the one set in the code (9600).
- Check connections to ensure the voltage sensor is wired correctly to the analog input.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests for improvements or bug fixes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### vin = vout / (R2 / (R1 + R2))
