


void send_location() {

  Serial2.println("Send location");
  sms_text = "good signal";
  send_sms2();
  sms_done_();
  //main
}
