
void sms_done_() {
  sms_error_time = 0;
  input_sms_count = 0;
  input_sms_timer = 0;
  input_sms = 0;
  number = 0;
  Serial1.flush();
  while (Serial1.available()) Serial1.read();
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.println("AT+CSCS=\"GSM\"");
  delay(500);
  Serial1.println("AT+CSMP=17,167,0,0");
  delay(500);
  Serial1.flush();
  Serial1.println("AT+CMGD=1,4");
  delay(500);
  Serial1.println("AT+CMGD=1,4");
  Serial1.flush();
  while (Serial1.available()) Serial1.read();
  Serial1.begin(9600);
  digitalWrite(led, 1);
}



void sms_done2_() {
  sms_error_time = 0;
  input_sms_count = 0;
  input_sms_timer = 0;
  input_sms = 0;
  number = 0;
  Serial1.flush();
  while (Serial1.available()) Serial1.read();
  // Serial1.println("AT+CMGDA=DEL ALL");
  // delay(500);
  // Serial1.println("AT+CMGDA=DEL ALL");
  delay(500);
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.println("AT+CSCS=\"IRA\"");
  delay(500);
  Serial1.println("AT+CSMP=17,167,0,0");
  delay(500);
  Serial1.flush();
  // Serial1.println("AT+CMGDA=DEL ALL");
  // delay(500);
  // Serial1.println("AT+CMGDA=DEL ALL");
  // Serial1.flush();
  while (Serial1.available()) Serial1.read();
  Serial1.begin(9600);
  digitalWrite(led, 1);
}