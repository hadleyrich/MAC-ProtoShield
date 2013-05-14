#include <Wire.h> // Required for I2C communication

#define I2C_ADDRESS 0x50 // Address of the EEPROM

byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // This will be replaced
char macstr[18]; // Just used to print the MAC address to serial

void setup() {
  Serial.begin(9600); // Start serial communication
  Wire.begin(); // Start I2C communication

  // Read the separate MAC address parts from the EEPROM
  mac[0] = read_register(0xFA);
  mac[1] = read_register(0xFB);
  mac[2] = read_register(0xFC);
  mac[3] = read_register(0xFD);
  mac[4] = read_register(0xFE);
  mac[5] = read_register(0xFF);

  // Format the mac address into a string for printing
  snprintf(macstr, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  // Print the address to the serial port
  Serial.print("MAC: ");
  Serial.println(macstr);
}

void loop() {
}

byte read_register(byte r) {
  /*
    Read a register address from an I2C slave
  */
  Wire.beginTransmission(I2C_ADDRESS); // Begin talking to EEPROM
  Wire.write(r); // The address of the register we want
  Wire.endTransmission(); // Send the data
  Wire.requestFrom(I2C_ADDRESS, 1); // Request one byte from the EEPROM
  while (!Wire.available()); // Wait for the response
  return Wire.read(); // Return the value
}

