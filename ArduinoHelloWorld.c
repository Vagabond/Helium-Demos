#include <SoftwareSerial.h>
#include <helium.h>

HeliumModem *modem;

void setup() {
  modem = new HeliumModem();
}

void loop()
{
  DataPack dp(1);
  dp.String((char *)"Hello World");
  modem->sendPack(&dp);
  delay(500);
}
