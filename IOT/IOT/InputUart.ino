

void InputUart() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    Serial.println(input);
    ////////time setting//////
    if (input.startsWith("SETTIME ")) {
      String timeData = input.substring(8);  // حذف "SETTIME "
      setDateTimeFromSerial(timeData);
    } else {
      Serial.println("📩 پیام دریافت شد: " + input);
    }
    ///////manual cotrol///////
    if (input.startsWith("element1 on")) {
      element1 = 1;
      sendGpioMega();
    }
    if (input.startsWith("element1 off")) {
      element1 = 0;
      sendGpioMega();
    }
    if (input.startsWith("tank1 on")) {
      tank1 = 1;
      sendGpioMega();
    }
    if (input.startsWith("tank1 off")) {
      tank1 = 0;
      sendGpioMega();
    }
    if (input.startsWith("light1 on")) {
      light1 = 1;
      sendGpioMega();
    }
    if (input.startsWith("light1 off")) {
      light1 = 0;
      sendGpioMega();
    }


    ////////////////////////////////////////////////////
    if (input.equals("START")) {
      startDate = rtc.now();
      trackingStarted = true;
      preferences.putUInt("start_date", startDate.unixtime());  // ذخیره در EEPROM
      Serial.println("✅ شمارش روزها از امروز آغاز شد و در EEPROM ذخیره شد.");
    } else if (input.equals("DAYS")) {
      if (!trackingStarted) {
        Serial.println("⚠️ هنوز دستور 'START' داده نشده!");
      } else {
        DateTime now = rtc.now();
        int daysPassed = (now.unixtime() - startDate.unixtime()) / 86400;  // محاسبه روزهای سپری‌شده
        Serial.printf("📅 %d روز از تاریخ شروع گذشته است.\n", daysPassed);
      }
    } else {
      Serial.println("📩 پیام دریافت شد: " + input);
    }
  }
}