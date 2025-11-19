#include <SoftwareSerial.h>

// --- Configuration ---
const int GAS_SENSOR_PIN = A0;  // Connect MQ-2/MQ-6 Analog output here
const int BUZZER_PIN = 8;       // Connect Buzzer Positive pin here
const int GSM_RX_PIN = 9;       // Connect to GSM Module TX
const int GSM_TX_PIN = 10;      // Connect to GSM Module RX

// GSM Module Object
SoftwareSerial gsmSerial(GSM_RX_PIN, GSM_TX_PIN); 

// --- Calibration ---
// Gas presence usually spikes above 400-500. 
// ADJUST THIS VALUE based on your specific sensor testing.
const int GAS_THRESHOLD = 400; 

// --- Mobile Number ---
// REPLACE THIS with your actual mobile number including country code
const String MOBILE_NUMBER = "+919999999999"; 
const String ROOM_NAME = "Kitchen - Main Valve";

boolean isGasDetected = false; // Prevents spamming SMS loops

void setup() {
  // Initialize Serial Monitor for debugging on PC
  Serial.begin(9600);
  Serial.println("System Initializing...");

  // Initialize GSM Serial communication
  gsmSerial.begin(9600); 
  
  // Pin Setup
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is off initially

  Serial.println("Waiting for sensor warm-up (20 seconds)...");
  delay(20000); // Give MQ sensor time to heat up and stabilize
  Serial.println("System Armed and Ready.");
}

void loop() {
  // 1. Read Gas Level
  int gasLevel = analogRead(GAS_SENSOR_PIN);
  
  // Debugging: Print level to Serial Monitor so you can calibrate
  Serial.print("Current Gas Level: ");
  Serial.println(gasLevel);

  // 2. Check against Threshold
  if (gasLevel > GAS_THRESHOLD) {
    
    // Activate Alarm
    digitalWrite(BUZZER_PIN, HIGH);
    
    // Check if we have already sent the SMS for this specific leak event
    if (isGasDetected == false) {
      Serial.println("Gas Detected! Sending SMS...");
      sendSMS(gasLevel);
      isGasDetected = true; // Set flag so we don't send 100 SMS messages in a row
    }
    
  } else {
    // Gas levels are normal
    digitalWrite(BUZZER_PIN, LOW);
    
    // Reset the flag. This allows the system to send a NEW SMS 
    // if gas is cleared and then leaks again later.
    isGasDetected = false; 
  }

  delay(1000); // Wait 1 second before next reading
}

void sendSMS(int level) {
  // Set GSM module to Text Mode
  gsmSerial.println("AT+CMGF=1"); 
  delay(1000);

  // Specify the destination number
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(MOBILE_NUMBER);
  gsmSerial.println("\""); 
  delay(1000);

  // The Content of the SMS
  gsmSerial.print("ALERT: Gas Leakage Detected!");
  gsmSerial.print("\nLocation: ");
  gsmSerial.print(ROOM_NAME);
  gsmSerial.print("\nSensor Level: ");
  gsmSerial.print(level);
  gsmSerial.print("\nPlease take immediate action.");

  // End command with CTRL+Z (ASCII code 26) to send
  delay(100);
  gsmSerial.println((char)26); 
  
  delay(5000); // Wait for message to send
  Serial.println("SMS Sent.");
}