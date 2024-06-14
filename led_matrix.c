/*
    Project name : LED Matrix Display
    Modified Date: 14-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-mega-led-matrix-display
*/

#include <LedControl.h>

// Create a new LedControl instance
// Parameters: DIN pin, CLK pin, CS pin, number of devices
LedControl lc = LedControl(51, 52, 53, 1);

// 8x8 font data (example for characters, use a full font set for more characters)
const byte font8x8[96][8] PROGMEM = {
  // Add character patterns here (each character is 8 bytes representing 8 rows)
  // Example for 'H' (character code 72):
  { B01100110, B01100110, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110 },
  // Add more characters as needed...
};

void setup() {
  // Wake up the MAX7219 from power-saving mode
  lc.shutdown(0, false);
  // Set brightness level (0 is min, 15 is max)
  lc.setIntensity(0, 8);
  // Clear display register
  lc.clearDisplay(0);
}

void loop() {
  scrollText("HELLO ");
  delay(1000);
}

void scrollText(const char *text) {
  while (*text) {
    for (int i = 0; i < 8; i++) {
      lc.clearDisplay(0);
      for (int row = 0; row < 8; row++) {
        lc.setRow(0, row, pgm_read_byte(&font8x8[*text - 32][row]) >> i);
      }
      delay(100);
    }
    text++;
  }
}
