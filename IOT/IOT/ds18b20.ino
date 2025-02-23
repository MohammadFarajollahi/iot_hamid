

void ds18b20() {
  if (khak_count >= 5) {
    khak_count = 0;
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