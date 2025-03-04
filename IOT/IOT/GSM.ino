

void gsmcheck_() {
  megaUart();
  if (gsmTimer >= 30 && gsmcheck == 0) {
    gsmTimer = 0;
    gsmcheck = 1;
    stm32_serial.println("GSMcheck");
  }

  if (gsmTimer >= 5 && gsmcheck == 1) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    LcdText = "GSM DisConnect";
    tft.setTextFont(3);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.fillRoundRect(290, 200, 180, 20, 1, TFT_BLACK);
    tft.setCursor(290, 200);
    tft.print(LcdText);
    gsmTimer = 0;
    gsmcheck = 0;
    stm32_serial.println("GSMcheck");
    ++gsmerror;
    if (gsmerror >= 3) {
      gsmerror = 0;
      stm32_serial.println("reset gsm");
    }
  }
}