


void sensor() {
  if (security_state == "1") {
    if (digitalRead(sensor1) == 0 && door_count == 0) {
      Serial2.println("--sensor1 trig--");
      delay(50);
      if (digitalRead(sensor1) == 0) ++door_alarm_count;
      if (door_alarm_count >= 3) {
        Serial2.println("***Sensor Alarm***");
        if (number1 != "+981111111111") {
          input_number = number1;
          Serial.println("Door input warning");
          sms_text = "06470634062F06270631002006440631063206340020067E0645067E";
          send_sms();
          sms_done2_();
        }

        if (number2 != "+981111111111") {
          input_number = number2;
          Serial.println("Door input warning");
          sms_text = "06470634062F06270631002006440631063206340020067E0645067E";
          send_sms();
          sms_done2_();
        }
        ring_alarm();
        door_count = 1;
        door_alarm_count = 0;
      }
    }
  }
}

/////















void security_on() {
  Serial2.println("Security mode enabled");
  security_state = "1";
  door_count = 0;
  door_warning_timer = 0;
  avcc_count = 0;
  avcc_warning_timer = 0;
  eeprom_save();
  sms_text = "062F0632062F06AF06CC06310020064106390627064400200634062F";
  send_sms();
  sms_done_();
  auto_security_timer = 0;
}


void security_off() {
  Serial2.println("Security mode disabled");
  security_state = "0";
  door_count = 0;
  door_warning_timer = 0;
  avcc_count = 0;
  avcc_warning_timer = 0;
  eeprom_save();
  sms_text = "062F0632062F06AF06CC06310020063A06CC06310020064106390627064400200634062F";
  send_sms();
  sms_done_();
  auto_security_timer = 0;
}