// SPI Slave code
#include <SPI.h>

volatile uint8_t byteCount = 0;
volatile bool dataReady = false;

float data;
uint8_t *ptr = (uint8_t *)&data;

// SPI interrupt routine
ISR (SPI_STC_vect) {
  ptr[byteCount++] = SPDR;    //read one byte form SPI Data Regiser
  if (byteCount == 4) {
    dataReady = true;
  }
}

void setup (void) {
  Serial.begin(115200);
  Serial.println("\nSPI Slave");
  SPCR |= bit(SPE);        // enable SPI slave mode
  pinMode(MISO, OUTPUT);   // set MISO as OUTPUT
  SPI.attachInterrupt();
}

void loop (void) {
  if (dataReady) {
    Serial.println(data, 5);
    byteCount = 0;    // reset byteCount and dataReady flag
    dataReady = false;
  }
}
