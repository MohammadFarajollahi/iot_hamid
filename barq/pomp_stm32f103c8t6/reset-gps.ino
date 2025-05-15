

void reset_gps() {

  Serial2.println("reset gps");

  ///input_number = server_number1;
  sms_text = "Reset OK";
  send_sms2();
  sms_done_();
  reset_ = 1;
  Serial1.println("AT+CFUN=0");
  delay(1000);
  Serial1.println("AT+CFUN=1");
  delay(2000);
  digitalWrite(sim_power, HIGH);
  delay(2000);
  digitalWrite(sim_power, LOW);
  delay(3000);
 // eeprom_save();
  iwdg_init(IWDG_PRE_256, 1); 
}