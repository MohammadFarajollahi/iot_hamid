
String inputData3;
void uart3() {
  while (Serial3.available() > 0) {
    inputData3 = Serial3.readStringUntil('\n');
    inputData3.trim();
    Serial.println(inputData3);

    if (inputData3 == "<<**Config quectel**>>") {
      GsmModem = 1;
      Serial.println("GSM MODEM OK");
    }

    if (inputData3 == "gsm ok") {
      GsmModem = 1;
      Serial2.println("gsm ok");
    }

    if (inputData3 == "sms soil sensor") {
      Serial2.println("sms soil sensor");
    }

    if (inputData3 == "sms out puts") {
      Serial2.println("sms out puts");
    }
  }
}