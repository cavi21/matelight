bool connected = false;
bool withIp = false;

char ledsBuffer[3*3*150+2]; //buffer to hold incoming packet,

void setup() {
  // setup ethernet communication using DHCP 
  delay(1500);//<--important for W5100 module 
  
  Serial.begin(9600);
  Serial.println(F("Serial connected"));
  setupLeds(450); 

//   COM16 - 5555 5
//   COM17 - 6666 6
  
  setupUDPConnection(5555, 50);
}

unsigned long lastPerfStatus = millis();
unsigned long lastFrame = millis();
int frameCount = 0;
void loop() {
  if(withIp) {
    unsigned long nowMs = millis();
    if(nowMs - lastPerfStatus > 1000) {
      lastPerfStatus = nowMs;
      if(!connected) {      
        broadcastAlive();       
      } else {
        broadcastPerf(frameCount);
        frameCount = 0;        
      }
    }
  
    if(checkForNewUDPMsg(ledsBuffer)) {
      writeLedFrame(ledsBuffer, 1);
      connected = true;
      frameCount++;
      lastFrame = nowMs;
    } else {
      if(nowMs - lastFrame > 2000) {
        connected = false;
      }
    }
  }
}
