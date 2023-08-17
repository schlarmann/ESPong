#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <esp8266channel3lib.h>

// Value of potentiometer in kOhms (e.g. 10.0 or 100.0)
#define POT_MAX_KOHM 1024.0f

#define POT_L_PIN 4
#define POT_R_PIN 5

#define POT_L_IDX 0
#define POT_R_IDX 1

#define ANALOG_SAMPLES 50
uint32_t currentPotLIdx = 0;
uint32_t currentPotRIdx = 0;
uint32_t currentPotIdx = POT_L_IDX;
float potValueL[ANALOG_SAMPLES] = {0};
float potValueR[ANALOG_SAMPLES] = {0};

void gatherPotValues(){
  int value = 0;
  if(currentPotIdx == POT_L_IDX){
    pinMode(POT_R_PIN, INPUT);
    pinMode(POT_L_PIN, OUTPUT);
    digitalWrite(POT_L_PIN, LOW);

    delay(1);

    value=analogRead(A0); // Left potentiometer is mounted in "reverse"
    potValueL[currentPotLIdx] = value;
    currentPotLIdx++;
    if(currentPotLIdx >= ANALOG_SAMPLES)
      currentPotLIdx=0;
    
  } else {
    pinMode(POT_L_PIN, INPUT);
    pinMode(POT_R_PIN, OUTPUT);
    digitalWrite(POT_R_PIN, LOW);
    
    delay(1);
    
    value=analogRead(A0);
    potValueR[currentPotRIdx] = value;
    currentPotRIdx++;
    if(currentPotRIdx >= ANALOG_SAMPLES)
      currentPotRIdx=0;

  }

  if(currentPotIdx == POT_L_IDX){
    currentPotIdx = POT_R_IDX;
  } else {
    currentPotIdx = POT_L_IDX;
  }
  
}

float getPotValue(int idx){
  float avg = 0.0f;
  if(idx == POT_L_IDX){
    for(int i=0; i<ANALOG_SAMPLES; i++){
      avg += potValueL[i];
    }
  } else {
    for(int i=0; i<ANALOG_SAMPLES; i++){
      avg += potValueR[i];
    }
  }

  avg /= ANALOG_SAMPLES;

  return avg;
}

// This callback gets called automatically every frame
void loadFrame(){
  CNFGPenX = 25;
  CNFGPenY = 25;
  CNFGColor( 17 );
  CNFGDrawText("Etch-a-Sketch", 3);
  // Calculate position of cursor
  int xPos = video_broadcast_framebuffer_width()*(getPotValue(POT_L_IDX)/POT_MAX_KOHM); // Left/Right
  int yPos = video_broadcast_framebuffer_height()*(getPotValue(POT_R_IDX)/POT_MAX_KOHM); // Up/Down

  // Place white pixel
  video_broadcast_tack_pixel(xPos, yPos, C3_COL_DD_WHITE);
}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
  Serial.begin(115200);
  Serial.println("Starting ESP-EtchASketch!");
  WiFi.softAP("EtchaSketchP", "EtchaSketchP");

  // Port defaults to 8266
  ArduinoOTA.setPort(8266);
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("EtchaSketchP");

  ArduinoOTA.onStart([]() {
    channel3Deinit();
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {   
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {    
    Serial.printf("Progress: %u%%\r\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  
  channel3Init(PAL, &loadFrame);
  Serial.printf("Update via %s:8266\n", WiFi.softAPIP().toString().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
  // Handle OTA requests
  ArduinoOTA.handle();
  gatherPotValues();
}
