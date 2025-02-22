
void Clock() {
  if (ClockTimer >= 1) {
    ClockTimer = 0;

    DateTime now = rtc.now();

    int g_y = now.year();
    int g_m = now.month();
    int g_d = now.day();
    int g_h = now.hour();
    int g_min = now.minute();
    int g_sec = now.second();

    int j_y, j_m, j_d;
    JalaliConverter::toJalali(g_y, g_m, g_d, j_y, j_m, j_d);
    LcdText = "Clock=" + String(g_h) + ":" + String(g_min) + ":" + String(g_sec);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.fillRoundRect(1, 1, 120, 15, 1, TFT_BLACK);
    tft.setCursor(1, 1);
    tft.print(LcdText);
    LcdText = "Date=" + String(j_y) + "/" + String(j_m) + "/" + String(j_d);
    tft.fillRoundRect(1, 20, 120, 15, 1, TFT_BLACK);
    tft.setCursor(1, 20);
    tft.print(LcdText);


    // Serial.print("📅 تاریخ شمسی: ");
    // Serial.print(j_y);
    // Serial.print("/");
    // Serial.print(j_m);
    // Serial.print("/");
    // Serial.print(j_d);

    // Serial.print("  ⏰ زمان: ");
    // Serial.print(g_h);
    // Serial.print(":");
    // Serial.print(g_min);
    // Serial.print(":");
    // Serial.println(g_sec);
  }
}



void setDateTimeFromSerial(String input) {//SETTIME 2025,02,21,23,38,00
  int jalaliYear, jalaliMonth, jalaliDay, hour, minute, second;
  sscanf(input.c_str(), "%d,%d,%d,%d,%d,%d", &jalaliYear, &jalaliMonth, &jalaliDay, &hour, &minute, &second);

  //JalaliConverter jalali;
  //int miladiYear, miladiMonth, miladiDay;
  //jalali.toGregorian(jalaliYear, jalaliMonth, jalaliDay, miladiYear, miladiMonth, miladiDay);

  rtc.adjust(DateTime(jalaliYear, jalaliMonth, jalaliDay, hour, minute, second));
  Serial.println("✅ ساعت تنظیم شد!");
}

// // تابع تنظیم دستی ساعت و تاریخ
// void setDateTime(int year, int month, int day, int hour, int minute, int second) {
//   rtc.adjust(DateTime(year, month, day, hour, minute, second));
//   Serial.println("✅ زمان با موفقیت تنظیم شد!");
// }