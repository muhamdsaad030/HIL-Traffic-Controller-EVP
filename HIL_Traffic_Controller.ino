HIL_Traffic_Controller

/*
  Hardware-in-the-Loop (HIL) Traffic Signal Controller & EVP Simulator
  
  Hardware Setup:
  - Main Street: Green LED (Pin 2), Red LED (Pin 3)
  - Side Street: Green LED (Pin 4), Red LED (Pin 5)
  - Sensor 1 (Side Street Vehicle): Pushbutton (Pin 7)
  - Sensor 2 (Emergency Vehicle Preemption): Pushbutton (Pin 8)
  - Relays: Active-LOW configuration
*/

const int RELAY_MAIN_GREEN = 2;
const int RELAY_MAIN_RED   = 3;
const int RELAY_SIDE_GREEN = 4;
const int RELAY_SIDE_RED   = 5;

const int BTN_SIDE_VEHICLE = 7;
const int BTN_EVP          = 8;

void setup() {
  // Initialize UART Serial Telemetry
  Serial.begin(115200);
  Serial.println("================ SYSTEM INITIALIZATION ================");
  Serial.println("HIL Traffic Signal Controller online.");
  
  // Configure relay control pins as outputs
  pinMode(RELAY_MAIN_GREEN, OUTPUT);
  pinMode(RELAY_MAIN_RED, OUTPUT);
  pinMode(RELAY_SIDE_GREEN, OUTPUT);
  pinMode(RELAY_SIDE_RED, OUTPUT);

  // Configure button inputs with internal pull-up resistors
  pinMode(BTN_SIDE_VEHICLE, INPUT_PULLUP);
  pinMode(BTN_EVP, INPUT_PULLUP);

  // Set default state: Main Street GREEN, Side Street RED
  setIdleState();
}

void setIdleState() {
  // Active-LOW relays: LOW = Relay ON, HIGH = Relay OFF
  digitalWrite(RELAY_MAIN_GREEN, LOW);  // Green ON
  digitalWrite(RELAY_MAIN_RED, HIGH);   // Red OFF
  digitalWrite(RELAY_SIDE_GREEN, HIGH);  // Green OFF
  digitalWrite(RELAY_SIDE_RED, LOW);    // Red ON

  Serial.println("[STATE UPDATE] Main Street: GREEN | Side Street: RED");
}

void triggerEmergencyOverride() {
  Serial.println("-------------------------------------------------------");
  Serial.println("[INTERRUPT] Emergency Vehicle Preemption (EVP) Detected!");
  Serial.println("[ACTION] Executing instant state priority restoration...");
  Serial.println("-------------------------------------------------------");
  
  setIdleState();
  delay(1000); // Hold log state
}

void loop() {
  // Priority Check 1: Emergency Vehicle Preemption Button (Pin 8)
  if (digitalRead(BTN_EVP) == LOW) {
    triggerEmergencyOverride();
    return;
  }

  // Check 2: Side Street Vehicle Sensor Button (Pin 7)
  if (digitalRead(BTN_SIDE_VEHICLE) == LOW) {
    Serial.println("[INPUT] Vehicle detected on Side Street (Pin 7)");
    
    // Switch state: Main RED, Side GREEN
    digitalWrite(RELAY_MAIN_GREEN, HIGH);
    digitalWrite(RELAY_MAIN_RED, LOW);
    digitalWrite(RELAY_SIDE_GREEN, LOW);
    digitalWrite(RELAY_SIDE_RED, HIGH);
    
    Serial.println("[STATE UPDATE] Main Street: RED | Side Street: GREEN");

    // Hold Side Street green signal with non-blocking EVP polling loop
    for (int i = 0; i < 40; i++) { // 4 second total cycle (40 * 100ms)
      if (digitalRead(BTN_EVP) == LOW) {
        triggerEmergencyOverride();
        return;
      }
      delay(100);
    }

    // Return to default state after cycle completion
    setIdleState();
  }
} 