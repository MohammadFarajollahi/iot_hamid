
void serial_setup_() {

  while (Serial2.available() > 0) {
    String ss = Serial2.readStringUntil('\n');
    ss.trim();

    sub1 = ss.substring(0, 7);  ///Sensors
    if (sub1 == "Sensors") {
      input_number = numberSend;
      sms_text = ss;
      send_sms2();
      sms_done_();
      delay(2000);
    }

    sub1 = ss.substring(0, 6);  ///OUTPUT_Heat1
    if (sub1 == "OUTPUT") {
      input_number = numberSend;
      sms_text = ss;
      send_sms2();
      sms_done_();
      delay(2000);
    }

    if (ss == "GSMcheck") {
      Serial2.println("gsm ok");
    }

    if (ss == "serial on") {
      Serial2.println("sim868 Serial show ok");
      serial_show = 1;
    }

    if (ss == "CheckSim800") {
      Serial2.println("Sim800 OK");
    }
    if (ss == "anten" || ss == "ANTEN") {
      Serial1.println("AT+CSQ");
    }

    if (ss == "INFO" || ss == "info" || ss == "information" || ss == "INFORMATION") {
      input_number = server_number1;
      information();
    }

    if (ss == "serial off") {
      Serial2.println("sim868 Serial show off");
      serial_show = 0;
    }

    if (ss == "p2p on") {
      Serial2.println("p2p mode on");
      p2p_mode = 1;
    }

    if (ss == "p2p off") {
      Serial2.println("p2p mode off");
      p2p_mode = 0;
    }

    if (ss == "VB" || ss == "vb") {
      Serial.print("car battery:");
      Serial2.println(car_batt);
    }

    if (ss == "reset gps" || ss == "RESET GPS") {
      Serial2.println("reset gps");
      Serial1.println("AT+CFUN=0");
      delay(1000);
      Serial1.println("AT+CFUN=1");
      delay(2000);
      digitalWrite(sim_power, HIGH);
      delay(2000);
      digitalWrite(sim_power, LOW);
      delay(3000);
      iwdg_init(IWDG_PRE_256, 1);
    }

    if (ss == "on" || ss == "ON") {
      Serial2.println("pomp on");
      digitalWrite(rele, 1);
    }

    if (ss == "off" || ss == "OFF") {
      Serial2.println("pomp off");
      digitalWrite(rele, 0);
    }

    if (ss == "reset" || ss == "RESET") {
      Serial2.println("reset");
      iwdg_init(IWDG_PRE_256, 1);
    }

    if (p2p_mode == 1) {
      Serial1.println(ss);
    }


    if (ss == "reset" || ss == "RESET") {
      Serial2.println("Reset ok");
      iwdg_init(IWDG_PRE_256, 1);
    }

    sim_data = ss;
    sub1 = sim_data.substring(0, 2);  ///ch
    if (sub1 == "cu" || sub1 == "Cu" || sub1 == "CU") {
      pomp_user_current();
    }

    //
  }

  //
}