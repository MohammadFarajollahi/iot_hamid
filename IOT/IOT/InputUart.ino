

void InputUart() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    Serial.println(input);
    if (input.startsWith("SETTIME ")) {
      String timeData = input.substring(8);  // حذف "SETTIME "
      setDateTimeFromSerial(timeData);
    } else {
      Serial.println("📩 پیام دریافت شد: " + input);
    }
  }
}