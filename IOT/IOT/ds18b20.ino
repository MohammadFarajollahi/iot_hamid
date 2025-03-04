

void ds18b20() {
  if (khak_count >= 10) {
    khak_count = 0;

    //read soil temp
    sensors.requestTemperatures();  // درخواست خواندن دما
    for (int i = 0; i < numSensors; i++) {
      if (sensors.getAddress(sensorAddresses[i], i)) {
        float tempC = sensors.getTempC(sensorAddresses[i]);
        // Serial.print("دما سنسور ");
        // Serial.print(i + 1);
        // Serial.print(": ");
        // Serial.print(tempC);
        // Serial.println(" °C");
        if (i == 0) Temp1 = tempC;
        if (i == 1) Temp2 = tempC;
        if (i == 2) Temp3 = tempC;
        if (i == 3) Temp4 = tempC;
      } else {
        // Serial.print("سنسور ");
        // Serial.print(i + 1);
        // Serial.println(" متصل نیست!");
        if (i == 0) Temp1 = 0;
        if (i == 1) Temp2 = 0;
        if (i == 2) Temp3 = 0;
        if (i == 3) Temp4 = 0;
      }
    }

    //read soil hu
    hu1 = map(analogRead(huPin1), 3000, 0, 0, 100);
    hu2 = map(analogRead(huPin2), 3000, 0, 0, 100);
    hu3 = map(analogRead(huPin3), 3000, 0, 0, 100);
    hu4 = map(analogRead(huPin4), 3000, 0, 0, 100);
    if (hu1 > 99) hu1 = 100;
    if (hu2 > 99) hu2 = 100;
    if (hu3 > 99) hu3 = 100;
    if (hu4 > 99) hu4 = 100;
    // Serial.print("hu1:");
    // Serial.print(analogRead(huPin1));
    // Serial.print("/hu2:");
    // Serial.print(analogRead(huPin2));
    // Serial.print("/hu3:");
    // Serial.print(analogRead(huPin3));
    // Serial.print("/hu4:");
    // Serial.println(analogRead(huPin4));


    tft.setTextFont(3);
    tft.setTextSize(2);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    LcdText = "***Soil***";
    tft.setCursor(1, 55);
    tft.print(LcdText);
    //////////////////////
    tft.setTextFont(3);
    tft.setTextSize(2);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    //***tempSetting***
    LcdText = "<< " + String(TempSetting1, 1) + " >>";
    tft.fillRoundRect(30, 80, 60, 20, 1, TFT_BLACK);
    tft.setCursor(1, 80);
    tft.print(LcdText);
    //***Temp1***
    LcdText = "Temp1:" + String(Temp1, 1) + "C";
    tft.fillRoundRect(1, 100, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 100);
    tft.print(LcdText);
    //***Temp2***
    LcdText = "Temp2:" + String(Temp2, 1) + "C";
    tft.fillRoundRect(1, 120, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 120);
    tft.print(LcdText);
    //***Temp3***
    LcdText = "Temp3:" + String(Temp3, 1) + "C";
    tft.fillRoundRect(1, 140, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 140);
    tft.print(LcdText);
    //***Temp4***
    LcdText = "Temp4:" + String(Temp4, 1) + "C";
    tft.fillRoundRect(1, 160, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 160);
    tft.print(LcdText);

    ///////////////////////////////////////////////////////
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    //***HUSetting***
    LcdText = "<< " + String(HuSetting1, 1) + " >>";
    tft.fillRoundRect(30, 195, 60, 20, 1, TFT_BLACK);
    tft.setCursor(1, 195);
    tft.print(LcdText);
    //***hu1***
    LcdText = "HU1:" + String(hu1, 1) + "%";
    tft.fillRoundRect(1, 220, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 220);
    tft.print(LcdText);
    //***hu2***
    LcdText = "HU2:" + String(hu2, 1) + "%";
    tft.fillRoundRect(1, 240, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 240);
    tft.print(LcdText);
    //***hu3***
    LcdText = "HU3:" + String(hu3, 1) + "%";
    tft.fillRoundRect(1, 260, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 260);
    tft.print(LcdText);
    //***hu4***
    LcdText = "HU4:" + String(hu4, 1) + "%";
    tft.fillRoundRect(1, 280, 145, 20, 1, TFT_BLACK);
    tft.setCursor(1, 280);
    tft.print(LcdText);
  }
}



// تابع برای نمایش آدرس سنسورها
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
}