

void Sht20() {
  if (shtTime >= 10) {
    shtTime = 0;
    MainTemperature = sht.getTemperature();
    MainHumidity = sht.getHumidity();
    //***Temp***
    LcdText = "Temp:" + String(MainTemperature, 1) + "C";
    tft.setTextFont(3);
    tft.setTextSize(2);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.fillRoundRect(130, 1, 140, 20, 1, TFT_BLACK);
    tft.setCursor(130, 1);
    tft.print(LcdText);
    //***hu***
    LcdText = "HU:" + String(MainHumidity, 1) + "%";
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.fillRoundRect(130, 30, 140, 20, 1, TFT_BLACK);
    tft.setCursor(130, 30);
    tft.print(LcdText);
    //////////////////////////////////////////////////////////////
    LcdText = "<< " + String(mainTempSettig, 1) + " >>";
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.fillRoundRect(310, 1, 60, 20, 1, TFT_BLACK);
    tft.setCursor(280, 1);
    tft.print(LcdText);

    LcdText = "<< " + String(mainHuSetting, 1) + " >>";
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.fillRoundRect(310, 30, 60, 20, 1, TFT_BLACK);
    tft.setCursor(280, 30);
    tft.print(LcdText);

   


    // Serial.print("  🌡 دما: ");
    // Serial.print(temperature, 1);
    // Serial.print("°C");

    // Serial.print("  💧 رطوبت: ");
    // Serial.print(humidity, 1);
    // Serial.println("%");
  }
}