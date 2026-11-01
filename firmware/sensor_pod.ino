#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MLX90614.h>
#include <QMC5883LCompass.h> 

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SEA_LEVEL_PRESSURE_HPA 1013.25

#define SERVICE_UUID        "76d0d6cf-90e1-40a8-9c01-5b86ebb30c6e"
#define CHARACTERISTIC_UUID "24c62ff5-3951-4448-a4a3-324e6a54abd2"
Adafruit_BME280 bme;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
QMC5883LCompass compass; 

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        pServer->getAdvertising()->start();
    }
};

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (!mlx.begin()) {
        Serial.println("Could not find mlx sensor");
        while (1);
    }
    if (!bme.begin(0x77)) {
        Serial.println("Could not find bme sensor");
        while (1);
    }
    compass.init();
    Serial.println("compass initialised");
    BLEDevice::init("test_weather_xiao");

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY
    );

    pCharacteristic->addDescriptor(new BLE2902());
    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();
}
String getCompassDirection(float degrees) {
    if (degrees >= 337.5 || degrees < 22.5)   return "North";
    if (degrees >= 22.5  && degrees < 67.5)   return "North East";
    if (degrees >= 67.5  && degrees < 112.5)  return "East";
    if (degrees >= 112.5 && degrees < 157.5)  return "South East";
    if (degrees >= 157.5 && degrees < 202.5)  return "South";
    if (degrees >= 202.5 && degrees < 247.5)  return "South West";
    if (degrees >= 247.5 && degrees < 292.5)  return "West";
    if (degrees >= 292.5 && degrees < 337.5)  return "North West";
    return "Unknown";
}

void loop() {
//bme
    float raw_temp = bme.readTemperature();
    float temp = raw_temp - 0.5;//aligned with environment temperature obtained from web to match
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() * 0.000009869233;  
    float altitude = bme.readAltitude(SEA_LEVEL_PRESSURE_HPA);

//mlx
    float ambientTemp = mlx.readAmbientTempC();
    float object_raw_Temp = mlx.readObjectTempC();
    float objectTemp = object_raw_Temp+3.0;//as typically core body temperature is 2-3 degrees higher than the frehead temperature, aligned after checking with thermometer

//compass
    compass.read(); 
    int magX = compass.getX();
    int magY = compass.getY();
    int magZ = compass.getZ();
    float uTX = (float)magX * 0.033333;
    float uTY = (float)magY * 0.033333;
    float uTZ = (float)magZ * 0.033333;
    float totalMagneticField = sqrt(uTX*uTX + uTY*uTY + uTZ*uTZ);
    float heading = atan2((float)magY, (float)magX);
    float declinationAngle = 0.039;  
    heading += declinationAngle;
    
    if (heading < 0)        heading += 2 * PI;
    if (heading > 2 * PI)   heading -= 2 * PI;

    float headingDegrees = heading * 180 / PI;
    String compassDir = getCompassDirection(headingDegrees);

//for test
    Serial.println("--------------------------------");
    Serial.print("BME Temperature : "); Serial.print(temp); Serial.println(" °C");
    Serial.print("Humidity        : "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Pressure        : "); Serial.print(pressure, 4); Serial.println(" atm");
    Serial.print("Altitude        : "); Serial.print(altitude); Serial.println(" m");
    Serial.print("Ambient Temp    : "); Serial.print(ambientTemp); Serial.println(" °C");
    Serial.print("Object Temp     : "); Serial.print(objectTemp); Serial.println(" °C");
    
    Serial.print("Mag Field Strength: "); Serial.print(totalMagneticField, 2); Serial.println(" uT");
    Serial.print("Heading         : "); Serial.print(headingDegrees, 1); Serial.print("° ("); Serial.print(compassDir); Serial.println(")");

//bluetooth
    if (deviceConnected) {

        String dataPackage =
            String(temp, 2) + "," +              
            String(humidity, 2) + "," +          
            String(pressure, 4) + "," +          
            String(altitude, 2) + "," +          
            String(ambientTemp, 2) + "," +       
            String(objectTemp, 2) + "," +        
            String(object_raw_Temp, 2) + "," +    
            String(headingDegrees, 1) + "," +     
            String(totalMagneticField, 1) + "," + 
            compassDir;                          

        pCharacteristic->setValue(dataPackage.c_str());
        pCharacteristic->notify();

        Serial.print("BLE Packet Sent: ");
        Serial.println(dataPackage);
    }

    delay(2000);
}
