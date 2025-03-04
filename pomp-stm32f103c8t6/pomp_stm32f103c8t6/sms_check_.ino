




void sms_check_() {

  if (input_sms == 1 && sms_error_time >= 30) {
    Serial2.println("SMS CHECK ERROR");
    sms_error_time = 0;
    input_sms_count = 0;
    input_sms_timer = 0;
    input_sms = 0;
    number = 0;
    Serial1.println("AT+CMGD=1,4");
    delay(500);
    Serial1.println("AT+CMGD=1,4");
    delay(500);
    Serial1.println("AT+CMGF=1");
    delay(500);
    Serial1.println("AT+CSCS=\"GSM\"");
    delay(500);
    Serial1.println("AT+CSMP=17,167,0,0");
    delay(500);
  }

  if (input_sms == 1) {
    if (input_sms_timer >= 3) {
      Serial2.println("SMS CHECK TIMER*");
      ++input_sms_count;
      Serial1.println("AT+CMGR=1");
      input_sms_timer = 0;
    }

    if (input_sms_count >= 3) {
      input_sms_count = 0;
      input_sms_timer = 0;
      input_sms = 0;
      Serial2.println("SMS CHECK & DELETE ALL");
      Serial1.println("AT+CMGD=1,4");
    delay(500);
    }

    //sms input
  }


  //sms_check
}
