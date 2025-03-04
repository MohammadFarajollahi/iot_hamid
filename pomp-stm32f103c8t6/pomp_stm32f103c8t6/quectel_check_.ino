


void quectel_check_() {

  if (sim_config == 1) {
    //digitalWrite(led, 1);
    if (count >= 60 && check_point_count == 0 && input_sms == 0) {
      //count = 0;
      check_point = 1;
      Serial1.println("AT");
      check_point_count = 1;
      check_point_timer = 0;
      error_ = 0;
    }


    if (check_point == 1 && input_sms == 0) {

      if (check_point_count == 1 && check_point_timer >= 3) {  //at check error
        Serial2.println("!!!Sim868 Error!!!");
        Serial1.println("AT");
        check_point_timer = 0;
        ++error_;
      }

      if (check_point_count == 2 && check_point_timer < 3) {  //check simcard
        Serial2.println("Sim868 ok");
        check_point_timer = 0;
        check_point_count = 3;
        error_ = 0;
        Serial1.println("AT+COPS?");
      }

      if (check_point_count == 3 && check_point_timer >= 3) {  //simcard check error
        Serial2.println("!!!Simcard Error!!!");
        Serial1.println("AT+COPS?");
        check_point_timer = 0;
        ++error_;
      }

      if (check_point_count == 4 && check_point_timer < 3) {  //network check
        Serial2.println("Sim card ok");
        check_point_timer = 0;
        check_point_count = 5;
        error_ = 0;
        Serial1.println("AT+CREG?");
      }

      if (check_point_count == 5 && check_point_timer >= 5) {  //network error
        Serial2.println("!!!network Error!!!");
        Serial1.println("AT+CREG?");
        check_point_timer = 0;
        ++error_;
      }

      if (check_point_count == 6 && check_point_timer < 3) {  //network ok
        Serial2.println("network ok");
        Serial2.println("Anten check");
        Serial1.println("AT+CSQ");
        check_point_timer = 0;
        check_point_count = 7;
        error_ = 0;
      }

      if (check_point_count == 7 && check_point_timer >= 3) {  //anten error
        Serial2.println("!!!anten Error!!!");
        Serial1.println("AT+CSQ");
        check_point_timer = 0;
        ++error_;
      }

      if (check_point_count == 8 && check_point_timer < 3) {  //anten ok
        Serial.print("Anten:");
        Serial2.println(anten);
        Serial2.println("Battery check");
        Serial1.println("AT+CBC");
        check_point_timer = 0;
        check_point_count = 9;
        error_ = 0;
      }

      if (check_point_count == 9 && check_point_timer >= 3) {  //battey error
        Serial2.println("!!!battery Error!!!");
        Serial1.println("AT+CBC");
        check_point_timer = 0;
        ++error_;
      }

      if (check_point_count == 10 && check_point_timer < 3) {  //battery ok _ check done
        Serial.print("Battery:");
        Serial2.println(battery1);
        Serial2.println("<***check done***>");
        check_point_timer = 0;
        check_point_count = 0;
        error_ = 0;
        count = 0;
        check_point = 0;
        Serial1.println("AT+CMGF=1");
        delay(500);
        Serial1.println("AT+CSCS=\"IRA\"");
        delay(500);
        Serial1.println("AT+CSMP=17,167,0,0");
        delay(500);
        Serial.print("Car battery:");
        Serial2.println(car_batt);
        reset_check = 0;  //baraye reset
        Serial1.flush();
        while (Serial1.available()) Serial1.read();
        if (id.length() != 8 || number1.length() != 13 || number2.length() != 13 || number1 == "+981111111111") {
          ++eeprom_chek;
          if (eeprom_chek >= 20) {
            eeprom_chek = 0;
            input_number = "+989372425086";
            register_first = 1;
            sim_data = "Config program 12345678";
            config_();
          }
        }
        // delay(500);
        // Serial1.println("AT+CMGR=1");
        // delay(500);
        // Serial1.println("AT+CMGR=1");
        // delay(500);
        Serial1.println("AT+CMGR=1");
      }


      if (error_ >= 4) {  // error and system reset
        Serial2.println("*<<<RESET SYSTEM>>>*");
        Serial1.println("AT+CFUN=0");
        delay(1000);
        Serial1.println("AT+CFUN=1");
        delay(2000);
        digitalWrite(sim_power, HIGH);
        delay(2000);
        digitalWrite(sim_power, LOW);
        delay(3000);

        //eeprom_save();
        iwdg_init(IWDG_PRE_256, 1);
      }

      if (input_sms == 1) {
        check_point_timer = 0;
        check_point_count = 0;
        error_ = 0;
        count = 0;
        check_point = 0;
      }

      //check_point
    }

    //
  }
  //
}


//***************************check_uart*************************
void check_uart() {

  if (check_point == 1) {
    if (check_point_count == 1) {  //check at
      if (sim_data == "OK") {
        check_point_count = 2;
      }
    }

    if (check_point_count == 3) {  //check model simcard

      sub1 = sim_data.substring(0, 5);
      if (sub1 == "+COPS") {
        sub1 = sim_data.substring(12, 24);  // +COPS: 0,0,"MTN Irancell"
        if (sub1 == "MTN Irancell") {       //simcard IRANCELL
          Serial2.println("Sim card Irancell");
          check_point_count = 4;
          simcard_model = 1;
        }
        sub1 = sim_data.substring(12, 15);  //+COPS: 0,0,"MCI"
        if (sub1 == "TCI") {                //simcard hamrah aval
          Serial2.println("Sim card IR-MCI");
          check_point_count = 4;
          simcard_model = 2;
        }
        sub1 = sim_data.substring(8, 15);  //+CSPN: "RighTel",0
        if (sub1 == "RighTel") {           //simcard hamrah aval
          Serial2.println("Sim card RighTel");
          simcard_model = 3;
          check_point_count = 4;
        }
      }
    }

    if (check_point_count == 5) {  //network check
      sub1 = sim_data.substring(0, 5);
      if (sub1 == "+CREG") {
        sub1 = sim_data.substring(9, 10);
        if (sub1 == "1") {
          Serial2.println("Connect to network");
          check_point_count = 6;
        }

        if (simcard_model == 3 && sub1 == "5") {
          Serial2.println("Connect to network");
          check_point_count = 6;
        }

        if (sub1 == "2") {
          Serial2.println("!!!!!network fail!!!!");
        }
      }
    }

    if (check_point_count == 7) {       //ANTEN check
      sub1 = sim_data.substring(0, 4);  //+CSQ: 27,0
      if (sub1 == "+CSQ") {
        sub1 = sim_data.substring(6, 8);
        anten = sub1;
        int Antenn = map(anten.toInt(), 0, 31, 0, 100);
        anten2 = String(Antenn);
        check_point_count = 8;
      }
    }


    if (check_point_count == 9) {       //battery check
      sub1 = sim_data.substring(0, 4);  //+CBC: 0,85,4081
      if (sub1 == "+CBC") {
        sub1 = sim_data.substring(8, 10);
        battery1 = sub1;
        battery = battery1.toInt();
        if (battery1 == "10") battery1 = "100";
        sub1 = sim_data.substring(11, 15);
        voltage1 = sub1;
        check_point_count = 10;
      }
    }

    //
  }

  //
}