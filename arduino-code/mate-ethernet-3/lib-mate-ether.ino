#include <SPI.h>
#include <Ethernet.h>

IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

unsigned int localPort = 0000; // local port to listen on

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setupUDPConnection(unsigned int port, byte ipSegment) {
  // MAC address and IP address (in case DHCP fails)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, ipSegment };
  localPort = port;
  
  // start the Ethernet and UDP:
  IPAddress useIp(192, 168, 1, ipSegment);
  Ethernet.begin(mac, useIp, myDns, gateway, subnet);
  
//  Serial.print("IP address: ");
  IPAddress ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println("");
  
  Udp.begin(localPort);

  withIp = true;
  
  broadcastAlive();
}

void broadcastAlive() {
//  Serial.println(F("Broadcasting I exist..."));
  IPAddress remoteIp(255, 255, 255, 255);
  Udp.beginPacket(remoteIp, localPort);
  Udp.write("YEAH");
  Udp.endPacket();
}

void broadcastPerf(int frames) {
  IPAddress remoteIp(255, 255, 255, 255);
  Udp.beginPacket(remoteIp, localPort);
  Udp.write("PERF");
  String framesString = String(frames);
  char frameChar[5];
  framesString.toCharArray(frameChar, 5);
  Udp.write(frameChar);
  Udp.endPacket();

//  Serial.print(F("Broadcasting PERF "));
//  Serial.println(framesString);
}

bool checkForNewUDPMsg(char packetBuffer[]) {
  int packetSize = Udp.parsePacket();

  if(packetSize) {   
//    Serial.print("Received packet of size ");
//    Serial.println(packetSize);
//    Serial.print("From ");
//    IPAddress remote = Udp.remoteIP();
//    for (int i =0; i < 4; i++)
//    {
//      Serial.print(remote[i], DEC);
//      if (i < 3)
//      {
//        Serial.print(".");
//      }
//    }
//    Serial.print(", port ");
//    Serial.println(Udp.remotePort());
    
    Udp.read(packetBuffer, packetSize);
    return true;
  } else {
    return false;
  }
}
