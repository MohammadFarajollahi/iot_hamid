
void config_() {
  Serial2.println("<****Config device***>");
  sub1 = sim_data.substring(15, 23);  //Config program 12345678
  Serial.print("ID:");
  Serial2.println(sub1);
  id = sub1;
  if (register_first == 1) id = "12345678";
  number1 = "+981111111111";
  number2 = "+981111111111";
  rele_state = "0";
  security_state = "0";
  user_current = "0";
  over_load = "0";
  over_load1 = 0;
  time_havakeshi = "15";
  eeprom_save();
  delay(500);
  input_number = server_number1;
  sms_text = "CONFIG OK";
  send_sms2();
  sms_done_();

  if (id == "12345678") {
    input_number = server_number1;
    sms_text = "062D06270644062A0020067E0645067E0020063506460639062A06CC0020064106390627064400200634062F";
    send_sms();
    sms_done_();
    delay(1000);
  }

  if (id == "87654321") {
    input_number = server_number1;
    sms_text = "062D06270644062A0020067E0645067E0020062E0627064606AF06CC0020064106390627064400200634062F";
    send_sms();
    sms_done_();
    delay(1000);
  }
}