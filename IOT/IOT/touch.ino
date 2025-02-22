//************************input_touch**********************
//************************input_touch**********************
//************************input_touch**********************
void input_touch() {

  if (tft.getTouch(&x_t, &y_t)) {
    tft.fillRoundRect(1, 40, 100, 15, 5, TFT_BLACK);
    tft.setCursor(1, 40);
    String s1 = "x:" + String(x_t) + "  y:" + String(y_t);
    tft.setTextFont(3);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println(s1);

    ////////////////////////////////////mainTemp && mainHu////////////////////////////
    if (x_t >= 63400 && x_t <= 63700 && y_t >= 3600 && y_t <= 3800) {
      mainTempSettig -= .1;
      tft.setTextFont(3);
      tft.setTextSize(2);
      LcdText = "<< " + String(mainTempSettig, 1) + " >>";
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.fillRoundRect(310, 1, 60, 20, 1, TFT_BLACK);
      tft.setCursor(280, 1);
      tft.print(LcdText);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }

    if (x_t >= 62700 && x_t <= 63000 && y_t >= 3600 && y_t <= 3800) {
      mainTempSettig += .1;
      tft.setTextFont(3);
      tft.setTextSize(2);
      LcdText = "<< " + String(mainTempSettig, 1) + " >>";
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.fillRoundRect(310, 1, 60, 20, 1, TFT_BLACK);
      tft.setCursor(280, 1);
      tft.print(LcdText);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }
    //////////////////***hu***///////////////////////
    if (x_t >= 63400 && x_t <= 63700 && y_t >= 3300 && y_t <= 3500) {
      mainHuSetting -= .1;
      tft.setTextFont(3);
      tft.setTextSize(2);
      LcdText = "<< " + String(mainHuSetting, 1) + " >>";
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.fillRoundRect(310, 30, 60, 20, 1, TFT_BLACK);
      tft.setCursor(280, 30);
      tft.print(LcdText);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }

    if (x_t >= 62700 && x_t <= 63000 && y_t >= 3300 && y_t <= 3500) {
      mainHuSetting += .1;
      tft.setTextFont(3);
      tft.setTextSize(2);
      LcdText = "<< " + String(mainHuSetting, 1) + " >>";
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.fillRoundRect(310, 30, 60, 20, 1, TFT_BLACK);
      tft.setCursor(280, 30);
      tft.print(LcdText);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }
    ////////////save/////////
    if (x_t >= 62100 && x_t <= 62600 && y_t >= 3400 && y_t <= 3700) {
      preferences.begin("storage", false);
      delay(20);
      preferences.putFloat("mainTempSettig", mainTempSettig);
      preferences.putFloat("mainHuSetting", mainHuSetting);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      Serial.println("Save");
    }
  }
}
