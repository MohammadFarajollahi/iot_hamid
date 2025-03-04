
void first_start() {
  if (sim_config == 0) {

    //***********state1************
    if (start_config_count == 0) {  //test sim
      Serial2.println("Check quectel");
      Serial1.println("AT");
      delay(500);
      Serial1.println("AT");
      delay(500);
      Serial1.println("ATE0");
      start_config_timer = 0;
      start_config_count = 1;
    }

    if (start_config_count == 2 && start_config_timer < 3) {  //sim on
      Serial2.println("quectel ok");
      start_config_timer = 0;
      start_config_count = 3;
      Serial2.println("Check sim card model!!!");
      Serial1.println("AT+COPS?");
    }

    if (start_config_count == 1 && start_config_timer >= 3) {  //quectel off
      Serial2.println("quectel Turning on...");
      digitalWrite(sim_power, HIGH);
      delay(2000);
      digitalWrite(sim_power, LOW);
      delay(1000);
      iwdg_init(IWDG_PRE_256, 1);
      start_config_timer = 0;
      start_config_count = 0;
    }

    if (start_config_count == 4 && start_config_timer < 3) {  //check simcard(simcard_ok)
      Serial2.println("***Simcard ok***");
      start_config_timer = 0;
      start_config_count = 5;
      simcard_count = 0;
      Serial2.println("Checking NETWORK>>>!");
      Serial1.println("AT+CREG?");
    }

    if (start_config_count == 3 && start_config_timer >= 10) {  //check simcard(sim_card fail)
      ++simcard_count;
      Serial2.println("!!!Simcard Error!!!");
      if (simcard_count < 3) {
        start_config_timer = 0;
        start_config_count = 3;
        Serial1.println("AT+COPS?");
      }

      if (simcard_count >= 5) {
        simcard_count = 0;
        Serial2.println("Reset quectel...");
        Serial1.println("AT+CFUN=0");
        delay(1000);
        Serial1.println("AT+CFUN=1");
        delay(2000);
        digitalWrite(sim_power, HIGH);
        delay(2000);
        digitalWrite(sim_power, LOW);
        delay(1000);
        iwdg_init(IWDG_PRE_256, 1);
        start_config_timer = 0;
        start_config_count = 0;
      }
    }

    if (start_config_count == 6 && start_config_timer < 5) {  // NETWORK Connect
      network_count = 0;
      Serial2.println("****Network Connected****");
      start_config_count = 7;
      start_config_timer = 0;
    }


    if (start_config_count == 5 && start_config_timer >= 5) {  // NETWORK not Connect
      ++network_count;
      Serial2.println("Network problem...check again...");
      if (network_count < 4) {
        Serial1.println("AT+CREG?");
        start_config_timer = 0;
      }
      if (network_count >= 4) {
        simcard_count = 0;
        network_count = 0;
        Serial2.println("Reset quectel...");
        Serial2.println("Can not Connect to network");
        Serial1.println("AT+CFUN=0");
        delay(1000);
        Serial1.println("AT+CFUN=1");
        delay(2000);
        digitalWrite(sim_power, HIGH);
        delay(2000);
        digitalWrite(sim_power, LOW);
        delay(100);
        iwdg_init(IWDG_PRE_256, 1);
        start_config_timer = 0;
        start_config_count = 0;
      }
    }

    if (start_config_count == 7) {  //****config quectel
      Serial2.println("<<**Config quectel**>>");
      Serial1.println("AT+CMGF=1");
      delay(100);
      Serial1.println("AT+CMGF=1");
      delay(200);
      Serial1.println("AT+CSCS=\"GSM\"");
      delay(100);
      Serial1.println("AT+CSCS=\"GSM\"");
      delay(200);
      Serial1.println("AT+CSMP=17,167,0,0");
      delay(100);
      Serial1.println("AT+CSMP=17,167,0,0");
      delay(200);
      Serial1.println("ATE0");
      delay(100);
      Serial1.println("ATE0");
      delay(200);
      Serial1.println("AT&W");
      delay(100);
      Serial1.println("AT&W");
      delay(200);
      sim_config = 1;
      start_config_timer = 0;
      start_config_count = 0;
      simcard_count = 0;
      network_count = 0;
      digitalWrite(led, 1);
      //***********************eeprom ***********************
      read_eeprom_();
      //if (start_sms_count == 1) start_sms();
      delay(1000);
      Serial1.println("AT+CMGL=\"ALL\"");
    }

    ///
  }

  ///
}


//**************************uart******************************
//**************************uart******************************
//**************************uart******************************
//**************************uart******************************
void first_config() {
  if (start_config_count == 1) {  //check sim868
    if (sim_data == "OK") {
      start_config_count = 2;
    }
  }

  if (start_config_count == 3) {  //check sim_card
    sub1 = sim_data.substring(0, 5);
    if (sub1 == "+COPS") {

      sub1 = sim_data.substring(12, 24);  // +COPS: 0,0,"MTN Irancell"
      if (sub1 == "MTN Irancell") {       //simcard IRANCELL
        Serial2.println("Sim card Irancell");
        simcard_model = 1;
        start_config_count = 4;
        Serial1.println("AT+CUSD=1,\"*555*4*3*2#\"");
      }

      sub1 = sim_data.substring(12, 15);  //+COPS: 0,0,"TCI"
      if (sub1 == "TCI") {                //simcard hamrah aval
        Serial2.println("Sim card IR-MCI");
        simcard_model = 2;
        start_config_count = 4;
      }

      sub1 = sim_data.substring(12, 19);  //+COPS: 0,0,"RighTel"
      if (sub1 == "RighTel") {            //simcard RighTel
        Serial2.println("Sim card RighTel");
        simcard_model = 3;
        start_config_count = 4;
        //simserial.println("AT+CUSD=1,\"720*7*1*3#\"");
      }
    }
  }

  if (start_config_count == 5) {  //network checking +CREG: 0,2
    sub1 = sim_data.substring(0, 5);
    if (sub1 == "+CREG") {
      sub1 = sim_data.substring(9, 10);
      if (sub1 == "1") {
        Serial2.println("Connect to network");
        start_config_count = 6;
      }

      if (simcard_model == 3 && sub1 == "5") {
        Serial2.println("Connect to network");
        start_config_count = 6;
      }

      if (sub1 == "2") {
        Serial2.println("!!!!!network fail!!!!");
      }
    }
  }



  //////
}