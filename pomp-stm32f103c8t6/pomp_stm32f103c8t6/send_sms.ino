

int check_s;
String sx;
String test;
String send_number_ucs2;

void ucs2_convert() {
  send_number_ucs2 = "";
  send_number_ucs2 = "0030";
  for (int i = 3; i < 13; i++) {
    test = input_number.substring(i, i + 1);
    int number_send = test.toInt();
    switch (number_send) {
      case 1:
        //strcat(send_number_ucs2, "0031");
        send_number_ucs2 += "0031";
        break;
      case 2:
        //strcat(send_number_ucs2, "0032");
        send_number_ucs2 += "0032";
        break;
      case 3:
        //strcat(send_number_ucs2, "0033");
        send_number_ucs2 += "0033";
        break;
      case 4:
        //strcat(send_number_ucs2, "0034");
        send_number_ucs2 += "0034";
        break;
      case 5:
        //strcat(send_number_ucs2, "0035");
        send_number_ucs2 += "0035";
        break;
      case 6:
        //strcat(send_number_ucs2, "0036");
        send_number_ucs2 += "0036";
        break;
      case 7:
        //strcat(send_number_ucs2, "0037");
        send_number_ucs2 += "0037";
        break;
      case 8:
        //strcat(send_number_ucs2, "0038");
        send_number_ucs2 += "0038";
        break;
      case 9:
        //strcat(send_number_ucs2, "0039");
        send_number_ucs2 += "0039";
        break;
      case 0:
        //strcat(send_number_ucs2, "0030");
        send_number_ucs2 += "0030";
        break;
    }
  }
}


void send_sms() {
  digitalWrite(led, 0);
  delay(100);
  digitalWrite(led, 1);
  delay(100);
  Serial1.println("AT+CSMP=17,167,0,8");
  delay(500);
  Serial1.println("AT+CSCS=\"UCS2\"");
  delay(500);
  ucs2_convert();
  String n = "AT+CMGS=\"" + send_number_ucs2 + "\"";
  Serial1.println(n);
  delay(300);
  Serial2.println(n);
  delay(500);
  Serial1.print(sms_text);
  delay(500);

  Serial1.write(26);
  delay(200);
  Serial1.write(26);
  delay(200);
  Serial1.write(26);
  delay(200);
  Serial2.println("sms send");

  delay(4000);
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




  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.println("AT+CSCS=\"GSM\"");
  delay(500);
  Serial1.println("AT+CSMP=17,167,0,0");
  delay(500);
  Serial1.flush();
  while (Serial1.available()) Serial1.read();
}
