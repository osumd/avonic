void setup() {
    Serial.begin(9600); // Initialize serial communication
}

void loop() {
    // Read analog voltage from the thermocouple amplifier
    int rawValue = analogRead(analogInputPin);

    // Convert the raw analog value to voltage (0 to 5V range)
    voltage = rawValue * (5.0 / 1023.0);

    // Convert voltage to temperature using the provided equation
    temperature = (voltage - 1.25) / 0.005;

    // Print the temperature value to the serial monitor
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V, Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    delay(1000); // Wait for 1 second before reading again
}