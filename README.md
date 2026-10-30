# Arduino-Based-Water-Quality-Detection-Apparatus

## Project Overview

This project involves the independent design, fabrication, and programming of an Arduino-based water-quality monitoring apparatus designed to measure the pH and Total Dissolved Solids (TDS) levels of freshwater environments. The apparatus also incorporates an air-temperature and humidity sensor to collect additional environmental measurements.

Using an Arduino Uno R3 microcontroller, I integrated a pH probe, TDS probe, DHT11 temperature and humidity sensor, Real-Time Clock (RTC) module, and SD card module into a custom-fabricated Styrofoam housing.

The program, developed using the Arduino IDE, facilitates the simultaneous operation of the sensors, processes their measurements, and automatically records the resulting data. Measurements are timestamped using the RTC module and stored on an SD card in CSV format, allowing the collected data to be transferred to and analyzed using spreadsheet software.

## Hardware Components

- Arduino Uno R3 Microcontroller
- pH Sensor and Probe (Analog Input A0)
- Gravity TDS Sensor and Probe (Analog Input A1)
- DHT11 Temperature and Humidity Sensor (Digital Pin 2)
- DS1307 Real-Time Clock (RTC) Module
- SD Card Module (Chip Select: Digital Pin 10)
- Custom-Fabricated Styrofoam Housing

## Software and Libraries
EEPROM.h

SPI.h

SD.h

GravityTDS.h

DHT11.h

Wire.h

RTClib.h

**Development Environment:** Arduino IDE

**Programming Language:** Arduino C/C++

**Libraries Used:**
- EEPROM.h – Supports EEPROM memory functionality.
- SPI.h – Provides SPI communication for the SD card module.
- SD.h – Facilitates data storage and retrieval on the SD card.
- GravityTDS.h – Controls the Gravity TDS sensor and calculates TDS measurements.
- DHT11.h – Facilitates temperature and humidity measurements.
- Wire.h – Provides I2C communication for the RTC module.
- RTClib.h – Interfaces with the DS1307 RTC module and retrieves date and time information.

## Program Functionality

The program performs the following operations:

1. **Sensor Initialization:** Initializes the TDS sensor, DHT11 sensor, RTC module, and SD card.
2. **Environmental Measurements:** Collects air-temperature and humidity readings using the DHT11 sensor.
3. **TDS Measurements:** Calculates TDS concentrations in parts per million (ppm), incorporating temperature compensation using the measured air temperature.
4. **pH Measurements:** Collects ten analog readings from the pH sensor, sorts the readings, and averages the middle six values to reduce measurement variability before calculating the resulting pH value.
5. **Timekeeping:** Retrieves the current date and time from the DS1307 RTC module to timestamp each measurement.
6. **Data Storage:** Records the timestamp, temperature, humidity, TDS concentration, and pH measurement onto the SD card in CSV format.
7. **Continuous Monitoring:** Repeats the measurement and recording process approximately once per second.

## Data Organization

The program automatically creates and writes measurements to a CSV file named `tds.csv`.

The recorded data is organized into five columns:

| Column | Measurement |
|---|---|
| 1 | Date and Time |
| 2 | Air Temperature (°C) |
| 3 | Relative Humidity (%) |
| 4 | Total Dissolved Solids (ppm) |
| 5 | pH |

Each measurement is separated by a comma, allowing the CSV file to be opened and analyzed using spreadsheet software.

## Calibration

The Gravity TDS sensor supports calibration through serial communication. The program's original calibration instructions specify entering calibration mode, supplying a known TDS concentration measured at 25°C, and saving the calibration parameters.

The pH sensor also uses a voltage-to-pH calculation with an adjustable calibration offset.

## Project Application

I utilized the completed apparatus to collect pH and TDS measurements from a local freshwater pond to investigate potential water-quality concerns, including possible runoff pollution. I subsequently shared my findings with a municipal environmental protection agency and the Connecticut Department of Energy and Environmental Protection (CT DEEP).

## Acknowledgments

I independently designed and fabricated the apparatus and developed its programming, incorporating guidance from my high-school physics teacher and publicly available programming resources. Manufacturer-provided sensor code and external Arduino libraries were used as starting points where applicable.
