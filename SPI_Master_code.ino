// SPI master code
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  Serial.println("\nSPI Master");
  SPI.begin();
}

void loop() {
  float pi = 3.14159;
  uint8_t *ptr = (uint8_t *)&pi;    //cast the address of a float into a pointer of byte
  
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(SS, LOW);  
  for (int i=0; i<sizeof(pi); i++) {
    SPI.transfer(*ptr);    // send the pi byte by byte
    Serial.print(*ptr);    // for debugging, print out each byte
    Serial.print(", ");
    *ptr++;
  }
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
  
  Serial.println();
  delay(5000);
}
