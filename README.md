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

Schematic diagram-

[Schematic_SENSOR-POD_Antony-Hybeen_fixed.pdf](https://github.com/user-attachments/files/34233550/Schematic_SENSOR-POD_Antony-Hybeen_fixed.pdf)

The pictures of the hardware are gven below:

<img width="4284" height="5<img width="4284" height="5712" alt="IMG_4518" src="https://github.com/user-attachments/assets/ca747690-347e-49af-84c0-7825929b82bb" />
712" alt="IMG_4516" src="https://github.com/user-attachments/assets/e039d547-6695-4da6-b4cf-6e3f0c06088c" />

<img width="4284" height="5712" alt="IMG_4523" src="https://github.com/user-attachments/assets/fdea4417-c1a9-4499-8762-211d842e246e" />
<img width="5712" height="4284" alt="IMG_4521" src="https://github.com/user-attachments/assets/9675270c-87e2-4221-b4dd-98b136a177f4" />
<img width="4284" height="5712" alt="IMG_4516" src="https://github.com/user-attachments/assets/2bf0c080-71c2-4052-8ef1-42b56d812ec9" />
<img width="865" height="676" alt="IMG_4522" src="https://github.com/user-attachments/assets/31b53b1f-5f88-4886-9370-569917f0b3b6" />






