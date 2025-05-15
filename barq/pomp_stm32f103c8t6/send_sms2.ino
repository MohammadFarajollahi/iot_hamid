
void send_sms2() {
  digitalWrite(led, 0);
  delay(100);
  digitalWrite(led, 1);
  Serial1.println("AT+CSMP=17,167,0,0");
  delay(500);
  String n = "AT+CMGS=\"" + input_number + "\"";
  Serial1.println(n);
  delay(300);
  Serial2.println(n);
  delay(500);
  Serial1.print(sms_text);
  delay(100);

  Serial1.write(26);
  delay(200);
  Serial1.write(26);
  delay(200);
  Serial1.write(26);
  delay(200);
  Serial2.println("send sms");

  delay(3000);
  chek_send_();
  if (check_s == 1) Serial2.println("SMS DELIVERED");
  if (check_s == 0) {
    Serial1.write(26);
    Serial2.println("SMS NOT DELIVERED");
    delay(2000);

    chek_send_();
    if (check_s == 1) Serial2.println("SMS DELIVERED");
    if (check_s == 0) {
      Serial1.write(26);
      Serial2.println("SMS NOT DELIVERED");
      delay(3000);
      chek_send_();
      if (check_s == 1) Serial2.println("SMS DELIVERED");
      if (check_s == 0) {
        Serial1.write(26);
        Serial2.println("SMS NOT DELIVERED");
        delay(5000);
      }
    }
  }
  check_s = 0;
}

void chek_send_() {

  while (Serial1.available() > 0) {
    sx = Serial1.readStringUntil('\n');
    sx.trim();
    Serial2.println(sx);
    if (sx == "OK") check_s = 1;
    sx = "";
  }
}