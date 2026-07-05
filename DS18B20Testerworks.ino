// Read Temperature with DS18B20

// Include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// Data pin connected to the DS18B20
#define ONE_WIRE_BUS 2

// Create OneWire and DallasTemperature objects
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Variable to store the sensor address
DeviceAddress insideThermometer;

void setup() {

  // Start serial communication
  Serial.begin(9600);

  Serial.println("Dallas Temperature Sensor");

  // Start the temperature library
  sensors.begin();

  // Find connected sensors
  Serial.print("Devices found: ");
  Serial.println(sensors.getDeviceCount());

  // Get the first sensor on the bus
  if (!sensors.getAddress(insideThermometer, 0)) {
    Serial.println("Unable to find sensor.");
  }

  // Set sensor resolution (9–12 bits)
  sensors.setResolution(insideThermometer, 9);

  Serial.print("Sensor Address: ");
  printAddress(insideThermometer);
  Serial.println();
}

void loop() {

  // Request a temperature reading
  sensors.requestTemperatures();

  // Print the temperature
  printTemperature(insideThermometer);

  delay(1500);
}

// Print temperature in Celsius and Fahrenheit
void printTemperature(DeviceAddress deviceAddress) {

  float tempC = sensors.getTempC(deviceAddress);

  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Sensor disconnected");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" °C  ");

  Serial.print(DallasTemperature::toFahrenheit(tempC));
  Serial.println(" °F");
}

// Print the sensor's unique address
void printAddress(DeviceAddress deviceAddress) {

  for (uint8_t i = 0; i < 8; i++) {

    if (deviceAddress[i] < 16)
      Serial.print("0");

    Serial.print(deviceAddress[i], HEX);
  }
}