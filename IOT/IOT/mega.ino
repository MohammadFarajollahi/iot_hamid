

void megaCheck() {
  if (megaState == 0) {
    if (megaCheckTimer >= 30 && megaChekCount == 0) {
      megaCheckTimer = 0;
      megaChekCount = 1;
      stm32_serial.println("megaCheck");
    }

    if (megaCheckTimer >= 2 && megaChekCount == 1) {

      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(megaReset, HIGH);
      delay(100);
      digitalWrite(megaReset, LOW);
      delay(2000);
      tft.setTextFont(3);
      tft.setTextSize(1);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.fillRoundRect(1, 310, 70, 20, 1, TFT_BLACK);
      tft.setCursor(1, 310);
      LcdText = "Mega Error";
      tft.print(LcdText);
      ++mega_error;
      megaCheckTimer = 25;
      megaCheckTimer = 0;
      megaChekCount = 1;
      Serial.println("mega Error!!!");
      stm32_serial.println("megaCheck");
      if (mega_error >= 2) {
        digitalWrite(megaReset, HIGH);
        delay(100);
        digitalWrite(megaReset, LOW);
        delay(1000);
        ESP.restart();  // ریست نرم‌افزاری ESP32
      }
    }

    megaUart();
  }
}




void megaGpio() {
  megaUart();

  if (MegaResponseCount == 1 && MegaresponseTimer >= 3) {
    stm32_serial.println("megaResponse");
    MegaresponseTimer = 0;
    megaResponse = 1;
  }

  if (megaResponse == 1 && MegaresponseTimer >= 2) {
    ++responseError;
    if (responseError == 3) {
      digitalWrite(megaReset, HIGH);
      delay(200);
      digitalWrite(megaReset, LOW);
      delay(2000);
    }
    if (responseError >= 5) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      Serial.println("response Error");
      digitalWrite(megaReset, HIGH);
      delay(100);
      digitalWrite(megaReset, LOW);
      delay(2000);
      ESP.restart();  // ریست نرم‌افزاری ESP32
    }
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    megaResponse = 0;
    MegaresponseTimer = 0;
    MegaResponseCount = 1;
    Serial.println("mega Error!!!");
    gpioTimer = 30;
  }

  if (megaState == 1) {
    if (gpioTimer >= 30) {
      MegaResponseCount = 1;
      MegaresponseTimer = 0;
      gpioTimer = 0;
      //element1//
      if (element1 == 1) {
        doc["element1"] = "on";
      }
      if (element1 == 0) {
        doc["element1"] = "off";
      }
      //element1//
      if (element2 == 1) {
        doc["element2"] = "on";
      }
      if (element2 == 0) {
        doc["element2"] = "off";
      }
      //tank1//
      if (tank1 == 1) {
        doc["tank1"] = "on";
      }
      if (tank1 == 0) {
        doc["tank1"] = "off";
      }
      //tank2//
      if (tank2 == 1) {
        doc["tank2"] = "on";
      }
      if (tank2 == 0) {
        doc["tank2"] = "off";
      }
      //tank3//
      if (tank3 == 1) {
        doc["tank3"] = "on";
      }
      if (tank3 == 0) {
        doc["tank3"] = "off";
      }
      //tank4//
      if (tank4 == 1) {
        doc["tank4"] = "on";
      }
      if (tank4 == 0) {
        doc["tank4"] = "off";
      }
      //light1//
      if (light1 == 1) {
        doc["light1"] = "on";
      }
      if (light1 == 0) {
        doc["light1"] = "off";
      }
      //light2//
      if (light2 == 1) {
        doc["light2"] = "on";
      }
      if (light2 == 0) {
        doc["light2"] = "off";
      }
      //fan1//
      if (fan1 == 1) {
        doc["fan1"] = "on";
      }
      if (fan1 == 0) {
        doc["fan1"] = "off";
      }
      //fan2//
      if (fan2 == 1) {
        doc["fan2"] = "on";
      }
      if (fan2 == 0) {
        doc["fan2"] = "off";
      }
      String SendText;
      serializeJson(doc, SendText);
      stm32_serial.println(SendText);
    }
  }
}

void sendGpioMega() {

  MegaResponseCount = 1;
  MegaresponseTimer = 0;
  gpioTimer = 0;
  //element1//
  if (element1 == 1) {
    doc["element1"] = "on";
  }
  if (element1 == 0) {
    doc["element1"] = "off";
  }
  //element1//
  if (element2 == 1) {
    doc["element2"] = "on";
  }
  if (element2 == 0) {
    doc["element2"] = "off";
  }
  //tank1//
  if (tank1 == 1) {
    doc["tank1"] = "on";
  }
  if (tank1 == 0) {
    doc["tank1"] = "off";
  }
  //tank2//
  if (tank2 == 1) {
    doc["tank2"] = "on";
  }
  if (tank2 == 0) {
    doc["tank2"] = "off";
  }
  //tank3//
  if (tank3 == 1) {
    doc["tank3"] = "on";
  }
  if (tank3 == 0) {
    doc["tank3"] = "off";
  }
  //tank4//
  if (tank4 == 1) {
    doc["tank4"] = "on";
  }
  if (tank4 == 0) {
    doc["tank4"] = "off";
  }
  //light1//
  if (light1 == 1) {
    doc["light1"] = "on";
  }
  if (light1 == 0) {
    doc["light1"] = "off";
  }
  //light2//
  if (light2 == 1) {
    doc["light2"] = "on";
  }
  if (light2 == 0) {
    doc["light2"] = "off";
  }
  //fan1//
  if (fan1 == 1) {
    doc["fan1"] = "on";
  }
  if (fan1 == 0) {
    doc["fan1"] = "off";
  }
  //fan2//
  if (fan2 == 1) {
    doc["fan2"] = "on";
  }
  if (fan2 == 0) {
    doc["fan2"] = "off";
  }
  String SendText;
  serializeJson(doc, SendText);
  stm32_serial.println(SendText);
}


//********************************MegaUart*********************************
//********************************MegaUart*********************************
//********************************MegaUart*********************************
void megaUart() {
  while (stm32_serial.available() > 0) {
    stm32_string = stm32_serial.readStringUntil('\n');
    stm32_string.trim();
    Serial.println(stm32_string);

    if (stm32_string == "mega ok") {
      megaState = 1;
      megaCheckTimer = 0;
      megaChekCount = 0;
      mega_error = 0;
      gpioTimer = 30;
      LcdText = "Mega ok";
      tft.setTextFont(3);
      tft.setTextSize(1);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.fillRoundRect(1, 310, 50, 20, 1, TFT_BLACK);
      tft.setCursor(1, 310);
      tft.print(LcdText);
    }

    if (stm32_string == "Response ok") {
      megaResponse = 0;
      MegaresponseTimer = 0;
      MegaResponseCount = 0;
      lcdout();
    }

    if (stm32_string == "gsm ok") {
      gsmcheck = 0;
      gsmTimer = 0;
      LcdText = "GSM Connect";
      tft.setTextFont(3);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.fillRoundRect(290, 200, 180, 20, 1, TFT_BLACK);
      tft.setCursor(290, 200);
      tft.print(LcdText);
    }

    if (stm32_string == "gsm reset ok") {
      gsmcheck = 0;
      gsmTimer = 0;
      LcdText = "GSM Reset";
      tft.setTextFont(3);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.fillRoundRect(290, 200, 180, 20, 1, TFT_BLACK);
      tft.setCursor(290, 200);
      tft.print(LcdText);
    }

    if (stm32_string == "sms out puts") {
      LcdText = "GSM SMS";
      tft.setTextFont(3);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.fillRoundRect(290, 230, 180, 20, 1, TFT_BLACK);
      tft.setCursor(290, 230);
      tft.print(LcdText);

      String sendSms;
      if (element1 == 0) sendSms += "OUTPUT_Heat1 OFF";
      if (element1 == 1) sendSms += "OUTPUT_Heat1 ON";
      if (element2 == 0) sendSms += "/Heat2 OFF";
      if (element2 == 1) sendSms += "/Heat2 ON";
      if (tank1 == 0) sendSms += "/Tank1 OFF";
      if (tank1 == 1) sendSms += "/Tank1 ON";
      if (tank2 == 0) sendSms += "/Tank2 OFF";
      if (tank2 == 1) sendSms += "/Tank2 ON";
      if (tank3 == 0) sendSms += "/Tank3 OFF";
      if (tank3 == 1) sendSms += "/Tank3 ON";
      if (tank4 == 0) sendSms += "/Tank4 OFF";
      if (tank4 == 1) sendSms += "/Tank4 ON";
      if (tank5 == 0) sendSms += "/Tank5 OFF";
      if (tank5 == 1) sendSms += "/Tank5 ON";
      if (light1 == 0) sendSms += "/Light1 OFF";
      if (light1 == 1) sendSms += "/Light1 ON";
      if (light2 == 0) sendSms += "/Light2 OFF";
      if (light2 == 1) sendSms += "/Light2 ON";
      if (fan1 == 0) sendSms += "/fan1 OFF";
      if (fan1 == 1) sendSms += "/fan1 ON";
      if (fan2 == 0) sendSms += "/fan2 OFF";
      if (fan2 == 1) sendSms += "/fan2 ON";
      stm32_serial.println(sendSms);
    }

    if (stm32_string == "sms soil sensor") {
      LcdText = "GSM SMS";
      tft.setTextFont(3);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.fillRoundRect(290, 230, 180, 20, 1, TFT_BLACK);
      tft.setCursor(290, 230);
      tft.print(LcdText);

      String sendSms = "Sensors_Temp:" + String(MainTemperature, 1) + "/HU:" + String(MainHumidity, 1) + "/T1:" + String(Temp1, 1) + "/T2:" + String(Temp2, 1) + "/T3:" + String(Temp3, 1) + "/T4:" + String(Temp4, 1) + "/HU1:" + String(hu1, 1) + "/HU2:" + String(hu2, 1) + "/HU3:" + String(hu3, 1) + "/HU4:" + String(hu4, 1);
      stm32_serial.println(sendSms);
    }

    if (stm32_string == "sms out puts") {
      LcdText = "GSM SMS";
      tft.setTextFont(3);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.fillRoundRect(290, 230, 180, 20, 1, TFT_BLACK);
      tft.setCursor(290, 230);
      tft.print(LcdText);
    }
  }
}

void lcdout() {
  tft.setTextFont(3);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.fillRoundRect(160, 80, 120, 20, 1, TFT_BLACK);
  if (element1 == 0) LcdText = "Heat1 OFF";
  if (element1 == 1) LcdText = "Heat1 ON";
  tft.setCursor(160, 80);
  tft.print(LcdText);
  tft.fillRoundRect(160, 100, 120, 20, 1, TFT_BLACK);
  if (element2 == 0) LcdText = "Heat2 OFF";
  if (element2 == 1) LcdText = "Heat2 ON";
  tft.setCursor(160, 100);
  tft.print(LcdText);
  tft.fillRoundRect(160, 120, 120, 20, 1, TFT_BLACK);
  if (tank1 == 0) LcdText = "Tank1 OFF";
  if (tank1 == 1) LcdText = "Tank1 ON";
  tft.setCursor(160, 120);
  tft.print(LcdText);
  tft.fillRoundRect(160, 140, 120, 20, 1, TFT_BLACK);
  if (tank2 == 0) LcdText = "Tank2 OFF";
  if (tank2 == 1) LcdText = "Tank2 ON";
  tft.setCursor(160, 140);
  tft.print(LcdText);
  tft.fillRoundRect(160, 160, 120, 20, 1, TFT_BLACK);
  if (tank3 == 0) LcdText = "Tank3 OFF";
  if (tank3 == 1) LcdText = "Tank3 ON";
  tft.setCursor(160, 160);
  tft.print(LcdText);
  tft.fillRoundRect(160, 180, 120, 20, 1, TFT_BLACK);
  if (tank4 == 0) LcdText = "Tank4 OFF";
  if (tank4 == 1) LcdText = "Tank4 ON";
  tft.setCursor(160, 180);
  tft.print(LcdText);
  if (tank5 == 0) LcdText = "Tank5 OFF";
  if (tank5 == 1) LcdText = "Tank5 ON";
  tft.fillRoundRect(160, 200, 120, 20, 1, TFT_BLACK);
  tft.setCursor(160, 200);
  tft.print(LcdText);
  tft.fillRoundRect(160, 220, 130, 20, 1, TFT_BLACK);
  if (light1 == 0) LcdText = "Light1 OFF";
  if (light1 == 1) LcdText = "Light1 ON";
  tft.setCursor(160, 220);
  tft.print(LcdText);
  tft.fillRoundRect(160, 240, 130, 20, 1, TFT_BLACK);
  if (light2 == 0) LcdText = "Light2 OFF";
  if (light2 == 1) LcdText = "Light2 ON";
  tft.setCursor(160, 240);
  tft.print(LcdText);
  tft.fillRoundRect(160, 260, 120, 20, 1, TFT_BLACK);
  if (fan1 == 0) LcdText = "Fan1 OFF";
  if (fan1 == 1) LcdText = "Fan1 ON";
  tft.setCursor(160, 260);
  tft.print(LcdText);
  tft.fillRoundRect(160, 280, 120, 20, 1, TFT_BLACK);
  if (fan2 == 0) LcdText = "Fan2 OFF";
  if (fan2 == 1) LcdText = "Fan2 ON";
  tft.setCursor(160, 280);
  tft.print(LcdText);
}
