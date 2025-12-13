
#include <Arduino.h>

#define SIMULATION_MODE 

// Pin Definitions
const int antSwitchPin = 14; 
const int statusLed = 13;
const int rssiPin = A0; 

const int rssiThreshold = -85; // dBm
const int hysteresis = 3;      // dB
const int perPenalty = 2;      // Weight for packet errors
unsigned long lastCheck = 0;
unsigned long checkInterval = 20; // 50Hz polling
bool activeAntenna = HIGH; // HIGH: Ant A, LOW: Ant B

int getLinkQuality();
void toggleAntenna(bool state);
void setup() {
  Serial.begin(115200);
  
  pinMode(antSwitchPin, OUTPUT);
  pinMode(statusLed, OUTPUT);
  
  // Start with primary antenna
  toggleAntenna(HIGH);

  #ifdef SIMULATION_MODE
    while(!Serial && millis() < 2000); // Wait briefly for monitor
    Serial.println("[System] Diversity Logic Started (Simulation)");
  #endif
}

void loop() {
  if (millis() - lastCheck >= checkInterval) {
    lastCheck = millis();

    int currentScore = getLinkQuality();

    if (currentScore > -60) {
      checkInterval = 100;
    } else {
      checkInterval = 20; 
    }

    #ifdef SIMULATION_MODE
      Serial.print("Ant:"); Serial.print(activeAntenna ? "A" : "B");
      Serial.print(" Score:"); Serial.print(currentScore);
    #endif
    if (currentScore < rssiThreshold) {
      
      int candidateScore;

      #ifdef SIMULATION_MODE
        candidateScore = currentScore + random(5, 15);
      #else
        candidateScore = analogRead(rssiPin); 
      #endif
      if (candidateScore > (currentScore + hysteresis)) {
        #ifdef SIMULATION_MODE
          Serial.print(" >> Switching >>");
        #endif
        
        toggleAntenna(!activeAntenna);
      }
    }
    
    #ifdef SIMULATION_MODE
      Serial.println();
    #endif
  }
}
int getLinkQuality() {
  int rssi, per;

  #ifdef SIMULATION_MODE
    float t = millis() / 1000.0;
    rssi = -75 + (sin(t) * 20) + random(-2, 2); 
    per = (rssi < -85) ? random(0, 8) : 0; 
  #else
    int rawVal = analogRead(rssiPin);
    rssi = map(rawVal, 0, 1023, -100, -40);
    per = 0; 
  #endif
  return rssi - (per * perPenalty);
}

void toggleAntenna(bool state) {
  activeAntenna = state;
  digitalWrite(antSwitchPin, activeAntenna);
  digitalWrite(statusLed, activeAntenna);
}