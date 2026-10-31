# IoT-Project-SensorPod
ESP-32 based multi sensor hardware project integrating BME280, MLX90614 and QMC5883L sensors.Along with swift based application to display outputs.

Overview:

This project integrates proximal environment data like temperature, humidity,atmospheric pressure,magnetic, directional data like device orientation and magnetic strength as well as infrared temperature sensing to sense body temperature.
The device acquires these data using their respective sensors and processes it using an esp-32 based microcontroller called Xiao Seeed c3. The processed data is then transmitted wirelessly using BLE.

Required Hardware Components:

- Xiao Seeed C3

  Main esp-32 based microcontroller

- BME-280

  Temperature,humidity,atmospheric pressure and altitude sensor.

- MLX90614

  Non-contact Infrared temperature sensor

- QMC5883L

  3-Axis magnetic field sensing and heading sensor.

- Protoboard

  For circuit assembling

- Soldering Components

  To solder and combining electrical components

- Connecting Wires

  To establish connection between components

Features:

- Temperature, humidity and atmospheric pressure reading using BME-280 sensor module and calculated value of altitude with the    help of atmospheric pressure
- Non contact temperature sensing using infrared light  based sensor module to accurately measure temperature of hot objects as   well as body temperature(functions as a thermometer).
- 3-axis magnetic sensor to accurately measure the surrounding magnetic field and device orientation calculation by given         angle. Helpful in determining whether high magnetic field object relative to normal magnetic field is present near the device.
- Wireless transmission of all these data via BLE to the connected device and hence display the values in a custom Swift-UI       based application. The data is updated approximately once in 2 seconds.


Communication:

The device transmits data by transferring sensor values as data packets via Bluetooth Low Energy(BLE), using custom GATT service and characteristic. The device identifies itself as “test_weather_xiao” that allows the nearby devices to connect to it. The data transmission occurs approximately within a radius of 7 metres.

Software and Libraries used:

- Arduino Framework
- Wire.h
- Adafruit_Sensor.h
- Adafruit_BME280.h
- Adafruit_MLX90614.h
- QMC5883LCompass.h
- BLE-libraries

Current Limitations:

- Sensor calibration requires further validation
- Current transmission heavily relies on BLE transmission compromising in range

Future Improvements:

- Improve sensor calibration and measurement reliability.
- Implement more robust data handling and communication.

Project Status:
- Prototype / Ongoing Development








