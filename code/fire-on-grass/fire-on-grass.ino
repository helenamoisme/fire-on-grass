#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

bool fire[135][240] = {};
int burned = 1;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_OLIVE);

  fire[50][5] = true;
  tft.fillCircle(5, 50, 4, TFT_ORANGE);
}

void loop() {
  for (int i = 0; i < 5000; i++) {
    int oldX = random(0, 240);
    int oldY = random(0, 135);

    if (fire[oldY][oldX]) {
      int fireX = oldX + random(1, 5);
      int fireY = oldY + random(-3, 4);

      // Keep both coordinates inside the display bounds.
      fireX = constrain(fireX, 0, 239);
      fireY = constrain(fireY, 0, 134);

      if (!fire[fireY][fireX]) {
        fire[fireY][fireX] = true;
        burned++;

        tft.fillCircle(fireX, fireY, 3, TFT_MAROON);

        tft.drawLine(
          oldX, oldY,
          fireX, fireY,
          TFT_ORANGE
        );

        tft.fillCircle(fireX, fireY, 2, TFT_RED);
        tft.drawPixel(fireX, fireY, TFT_YELLOW);
      }
    }
    if(burned >= 240*135*0.85){
      tft.fillScreen(TFT_OLIVE);
      memset(fire, 0, sizeof(fire));
      burned = 1;
      fire[50][5] = true;
      delay(1000);
      tft.fillCircle(5, 50, 4, TFT_ORANGE);
    }
  }

  delay(150);
}
