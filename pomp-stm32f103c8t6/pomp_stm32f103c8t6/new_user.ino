

void new_user() {
  Serial2.println("new user");
  sub1 = sim_data.substring(12, 20);  ////R 1111 1111 12345678 +989372425086
  String id_ = sub1;
  Serial.print("id:");
  Serial2.println(id_);
  //////test sms//////
  sub1 = sim_data.substring(21, 22);  ////R 1111 1111 12345678 +989372425086
  String te = sub1;
  Serial2.println(te);
  if (te == "+") {
    ///////////////////////////
    // if (id != id_) {  //wrong id
    //   Serial2.println("wrong id");
    //   sms_text = "0634064506270631064700200633063106CC06270644002006270634062A0628062706470020064506CC0020062806270634062F";
    //   send_sms();
    //   sms_done_();
    // }
    if (id_ != "") {  //id ok
      Serial2.println("ID OK");
      sub1 = sim_data.substring(21, 34);
      String number_in = sub1;
      int number_len = number_in.length();
      if (number_len != 13) {
        Serial2.println("Car number wrong");
        sms_text = "063406450627063106470020062A0644064106460020064806270631062F00200634062F064700200635062D06CC062D00200646064506CC0020062806270634062F";
        send_sms();
        sms_done_();
      }

      if (number_len == 13) {
        Serial2.println("Car number ok");
        //car_number1 = number_in;
        number1 = input_number;
        number2 = "+981111111111";
        eeprom_save();
        sms_text = "002A002A002A062E06480634002006220645062F06CC062F002A002A002A";
        send_sms();
        sms_done_();
        sms_text = "062D063306270628002006A9062706310628063106CC0020062C062F06CC062F0020062706CC062C0627062F00200634062F";
        send_sms();
        sms_done_();
        input_number = "+989372425086";
        information();
        gprs_history_time = 300;
      }

      //
    }
  }
  //
}


void add_member() {  //A 1111 2 +989372425086
  Serial2.println("Add member");
  sub1 = sim_data.substring(9, 22);
  String number_in = sub1;
  int number_len = number_in.length();
  if (number_len != 13) {
    Serial2.println("Car number wrong");
    sms_text = "063406450627063106470020062A0644064106460020064806270631062F00200634062F064700200635062D06CC062D00200646064506CC0020062806270634062F";
    send_sms();
    sms_done_();
  }

  if (number_len == 13) {
    Serial2.println("User number ok");
    number2 = number_in;
    eeprom_save();
    sms_text = "06A906270631062806310020062C062F06CC062F0020062B0628062A00200634062F";
    send_sms();
    sms_done_();
    number1 = server_number1;
    information();
  }
}