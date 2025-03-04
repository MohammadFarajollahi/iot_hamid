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

    ////program start /////////////
    if (x_t >= 63000 && x_t <= 63600 && y_t >= 2300 && y_t <= 2700 && lock == 0) {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      StartPrgram = 1;
      if (StartPrgram == 1) LcdText = "Program Start";
      if (StartPrgram == 0) LcdText = "Prgram Stop";
      tft.setTextFont(3);
      tft.setTextSize(1);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.fillRoundRect(150, 310, 100, 20, 1, TFT_BLACK);
      tft.setCursor(150, 310);
      tft.print(LcdText);
    }

    ////program start /////////////
    if (x_t >= 62200 && x_t <= 62800 && y_t >= 2300 && y_t <= 2700 && lock == 0) {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      StartPrgram = 0;
      if (StartPrgram == 1) LcdText = "Program Start";
      if (StartPrgram == 0) LcdText = "Prgram Stop";
      tft.setTextFont(3);
      tft.setTextSize(1);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.fillRoundRect(150, 310, 100, 20, 1, TFT_BLACK);
      tft.setCursor(150, 310);
      tft.print(LcdText);
    }

    ////////////////////////////////////mainTemp && mainHu////////////////////////////
    if (x_t >= 63400 && x_t <= 63700 && y_t >= 3600 && y_t <= 3800 && lock == 0) {
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

    if (x_t >= 62700 && x_t <= 63000 && y_t >= 3600 && y_t <= 3800 && lock == 0) {
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
    if (x_t >= 63400 && x_t <= 63700 && y_t >= 3300 && y_t <= 3500 && lock == 0) {
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

    if (x_t >= 62700 && x_t <= 63000 && y_t >= 3300 && y_t <= 3500 && lock == 0) {
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
    if (x_t >= 62100 && x_t <= 62600 && y_t >= 3400 && y_t <= 3700 && lock == 0) {
      preferences.begin("storage", false);
      delay(20);
      preferences.putFloat("mainTempSettig", mainTempSettig);
      preferences.putFloat("mainHuSetting", mainHuSetting);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      Serial.println("Save");
    }

    //lock//
    if (x_t >= 62200 && x_t <= 62800 && y_t >= 300 && y_t <= 500) {
      if (lock == 0) {
        lock = 1;
        esp_task_wdt_reset();  // ریست کردن تایمر واچ‌داگ
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        tft.setTextFont(3);
        tft.setTextSize(2);
        tft.fillRoundRect(370, 300, 110, 20, 1, TFT_BLACK);
        tft.setTextColor(TFT_WHITE, TFT_RED);
        LcdText = " LOCK ";
        tft.setCursor(380, 300);
        tft.print(LcdText);
      }
      if (lock == 1) {
        ++lock_count;
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
      }
    }

    if (x_t >= 63700 && x_t <= 64600 && y_t >= 3000 && y_t <= 3300) {
      if (lock_count >= 2) {
        lock_count = 0;
        lock = 0;
        esp_task_wdt_reset();  // ریست کردن تایمر واچ‌داگ
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        tft.setTextFont(3);
        tft.setTextSize(2);
        tft.fillRoundRect(370, 300, 110, 20, 1, TFT_BLACK);
        tft.setTextColor(TFT_GREEN, TFT_WHITE);
        LcdText = " UNLOCK ";
        tft.setCursor(380, 300);
        tft.print(LcdText);
      }
    }
  }
}
