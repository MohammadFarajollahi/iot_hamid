
void wifi() {
  if (CheckCount >= 5) {  // check for wifi....
    CheckCount = 0;
    if (connect == 0 && wifiReset == 0) {
      if (WiFi.status() == WL_CONNECTED) {
        connect = 1;
        connectError = 0;
        Serial.println("Connected to WiFi");
        LcdText = "WIFI Connect";
        tft.setTextFont(3);
        tft.setTextSize(1);
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.fillRoundRect(250, 310, 120, 20, 1, TFT_BLACK);
        tft.setCursor(250, 310);
        tft.print(LcdText);
      }
    }

    if (connect == 1 && WiFi.status() != WL_CONNECTED) {
      LcdText = "WIFI Disconnect";
      tft.setTextFont(3);
      tft.setTextSize(1);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.fillRoundRect(250, 310, 120, 20, 1, TFT_BLACK);
      tft.setCursor(250, 310);
      tft.print(LcdText);
      Serial.println("WiFi Disconnected");
      WiFi.disconnect();
      delay(3000);
      WiFi.begin(ssid, password);
      connect = 0;
    }
  }
}
