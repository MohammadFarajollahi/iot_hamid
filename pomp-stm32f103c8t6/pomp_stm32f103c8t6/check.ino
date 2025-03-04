

void check_() {

  //*****first time config*****
  if (sim_config == 0) first_config();

  if (sim_config == 1) {
    if (check_point == 1 && input_sms == 0) check_uart();

    sub1 = sim_data.substring(0, 8);  ///+CUSD: 0
    if (sub1 == "+CUSD: 0") {
      mojodi_charg_send();
    }
    //***input sms***+CMTI
    sub1 = sim_data.substring(0, 5);
    if (sub1 == "+CMTI") {
      digitalWrite(led, 0);
      delay(50);
      digitalWrite(led, 1);
      delay(50);
      Serial2.println("SMS recive *CMTI*");
      input_sms = 1;
      Serial1.println("AT+CMGR=1");
      delay(100);
      Serial1.println("AT+CMGR=1");
      input_sms_timer = 0;
    }



    sub1 = sim_data.substring(0, 5);  // Read Number +CMGR
    if (sub1 == "+CMGR") {
      number_read();
      Serial2.println("SMS recive *+CMGR*");
    }

    sub1 = sim_data.substring(0, 5);  //+CMGL
    if (sub1 == "+CMGL") {
      digitalWrite(led, 0);
      delay(50);
      digitalWrite(led, 1);
      delay(50);
      Serial2.println("SMS recive *+CMGL*");
      input_sms = 1;
      Serial1.println("AT+CMGR=1");
      delay(100);
      //Serial.flush();
      delay(100);
      Serial1.println("AT+CMGR=1");
      input_sms_timer = 0;
    }

    if (sim_data == "RING") {
      Serial1.println("AT+CLCC");
    }

    sub1 = sim_data.substring(0, 5);
    if (sub1 == "+CLCC") {
      ring();
    }


    if (number != 0) {

      if (sim_data == "reset" || sim_data == "reset gps" || sim_data == "Reset gps" || sim_data == "Reset") {
        reset_gps();
      }

      if (sim_data != "RING") {
        sub1 = sim_data.substring(0, 1);  //// change pass R 1111 1111 12345678 +989372425086
        if (sub1 == "R") {
          new_user();
        }
      }

      sub1 = sim_data.substring(0, 14);  //Config program 87654321
      if (sub1 == "Config program") {
        config_();
      }
    }
    //********************************************user send sms****************************************
    if (number > 0 && number < 5) {
      sub1 = sim_data.substring(2, 6);  //// add member A 1111 2 +989372425086
      if (sub1 == "1111") {
        sub1 = sim_data.substring(0, 1);
        if (sub1 == "a" || sub1 == "A") {
          add_member();
        }
      }

      if (sim_data == "soil sensor" || sim_data == "Soil sensor") {
        sms_text = "soil Request receive\r\nPlease wait...";
        numberSend = input_number;
        send_sms2();
        sms_done_();
        delay(2000);
        Serial2.println("sms soil sensor");
      }

      if (sim_data == "out puts" || sim_data == "Out puts") {
        sms_text = "Out put Request receive\r\nPlease wait...";
        numberSend = input_number;
        send_sms2();
        sms_done_();
        delay(2000);
        Serial2.println("sms out puts");
      }

      sub1 = sim_data.substring(0, 1);  //// add member A 1111 2 +989372425086
      if (sub1 == "l" || sub1 == "L") {
        send_location();
      }


      sub1 = sim_data.substring(0, 2);  //s1
      if (sub1 == "s1" || sub1 == "S1") {
        security_on();
      }

      sub1 = sim_data.substring(0, 2);  //s2
      if (sub1 == "s2" || sub1 == "S2") {
        security_off();
      }

      ///////////////////on/////////////////
      if (sim_data == "0631064806340646" || sim_data == "067E0645067E00200631064806340646") {
        if (number == 3 || number == 4 || number == 1 || number == 2) pomp_on();
      }
      sub1 = sim_data.substring(0, 3);  // car on
      if (sub1 == "On1" || sub1 == "ON1") {
        if (number == 3 || number == 4 || number == 1 || number == 2) pomp_on();
      }
      ///////////////////off/////////////////
      if (sim_data == "062E0627064506480634" || sim_data == "067E0645067E0020062E0627064506480634") {
        if (number == 3 || number == 4 || number == 1 || number == 2) pomp_off();
      }
      sub1 = sim_data.substring(0, 2);  // car off
      if (sub1 == "of" || sub1 == "OF" || sub1 == "Of") {
        if (number == 3 || number == 4 || number == 1 || number == 2) pomp_off();
      }

      sub1 = sim_data.substring(0, 2);  // anten
      if (sub1 == "bt" || sub1 == "BT" || sub1 == "Bt") sms_anten();



      sub1 = sim_data.substring(0, 11);  ////information
      if (sub1 == "information" || sub1 == "Information") {
        if (number == 3 || number == 4) information();
      }

      sub1 = sim_data.substring(0, 6);  ////eeprom/12345678/+989372425086/+989114764806/+989379274959/0/0/0/1/11.111111,11.111111
      if (sub1 == "eeprom" || sub1 == "Eeprom") {
        if (number == 3 || number == 4) server_eeprom();
      }

      sub1 = sim_data.substring(0, 2);  ///ch
      if (sub1 == "ch" || sub1 == "Ch" || sub1 == "CH") {
        mojodi_charg();
      }

      sub1 = sim_data.substring(0, 7);  ///ch
      if (sub1 == "current" || sub1 == "Current") {
        pomp_user_current();
      }

      sub1 = sim_data.substring(0, 2);  ///ch
      if (sub1 == "uc" || sub1 == "Uc" || sub1 == "UC") {
        current_send();
      }

      sub1 = sim_data.substring(0, 4);  ///time 15
      if (sub1 == "time" || sub1 == "Time" || sub1 == "TIME") {
        time_havakeshi_();
      }

      sub1 = sim_data.substring(0, 12);  ///over current
      if (sub1 == "over current" || sub1 == "Over current") {
        over_current_setting();
      }

      sub1 = sim_data.substring(0, 12);  ///auto current
      if (sub1 == "Auto current" || sub1 == "auto current" || sub1 == "auto current" || sim_data == "062A0646063806CC064500200627062A064806450627062A06CC06A9" || sim_data == "0627062A064806450627062A06CC06A9" || sim_data == "062A0646063806CC0645") {
        auto_current_config();
      }
    }
  }
  //CHECK_
}


void sms_anten() {
  int Anten = map(anten.toInt(), 0, 31, 0, 100);

  if (Anten > 0) {
    sms_text = "Anten: " + String(Anten) + "%" + "\n" + "Battery: " + battery1 + "%";
    send_sms2();
    sms_done_();
  }

  if (Anten == 0) {
    sms_text = "06440637064106270020062F0642062706CC064206CC0020062F06CC06AF06310020062A064406270634002006A9064606CC062F";
    send_sms();
    sms_done_();
  }
}

void mojodi_charg() {
  Serial2.println("mojodi charj");
  if (simcard_model == 1) {
    number_charg = input_number;
    sms_text = "062F0631062E064806270633062A00200634064506270020062A062706CC06CC062F00200634062F000D000A0644063706410627002006A9064506CC0020063506280631002006A9064606CC062F";
    send_sms();
    sms_done_();
    Serial1.println("AT+CUSD=1,\"*141*1#\",15");
  }
  if (simcard_model > 1) {
    Serial2.println("simcard tokhmie");
    number_charg = input_number;
    sms_text = "06280631062706CC002006270633062A0639064406270645002006340627063106980020063306CC0645002006A906270631062A060C002006410642063700200627067E06310627062A064806310020062706CC063106270646063306440020067E0634062A06CC06280627064606CC0020064506CC002006340648062F";
    send_sms();
    sms_done_();
  }
}


void mojodi_charg_send() {
  Serial2.println("send mojodi charj");
  sub1 = sim_data.substring(11, 30);  ///+CUSD: 0, "Etebar 324283 Rial Shegeftangiz 0 Rial,ta 9378/10/1
  input_number = number_charg;
  sms_text = sub1;
  send_sms2();
  sms_done_();
  number_charg = "";
}


void number_read() {
  sub1 = sim_data.substring(19, 20);
  if (sub1 == "+") {
    check_number_count = 0;
    sub1 = sim_data.substring(19, 32);  //+CMGR: "REC READ","+989372425086","","23/09/15,20:43:28+14"
    Serial2.print("input number:");
    Serial2.println(sub1);
    input_number = sub1;
    if (sub1 == server_number1) {
      Serial2.println("Server1 Send sms");
      number = 3;
    } else if (sub1 == server_number2) {
      Serial2.println("Server2 Send sms");
      number = 4;
    } else if (sub1 == number1) {
      Serial2.println("number1 Send sms");
      number = 1;
    } else if (sub1 == number2) {
      Serial2.println("number2 Send sms");
      number = 2;
    } else {
      Serial2.println("Unknown");
      number = 5;
    }

    //***sms time****
    if (number >= 1 && number <= 4) {
      sub1 = sim_data.substring(38, 55);  //+CMGR: "REC READ","+989372425086","","23/09/15,20:43:28+14"
      sms_time = sub1;
      Serial2.print("SmS time:");
      Serial2.println(sms_time);
    }
  } else {
    ++check_number_count;
    Serial1.println("AT+CMGR=1");
    input_sms_timer = 0;
    if (check_number_count >= 3) {
      check_number_count = 0;
      Serial1.println("AT+CMGDA=DEL ALL");
      delay(500);
      Serial1.println("AT+CMGDA=DEL ALL");
      Serial1.flush();
    }
  }

  //
}