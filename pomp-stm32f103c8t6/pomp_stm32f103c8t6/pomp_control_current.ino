////////////////////////////////////auto current//////////////////////////
void auto_current_config() {
  Serial2.print("auto current");
  sms_text = "062A0646063806CC064500200627062A064806450627062A06CC06A90020067E0645067E000D000A06440637064106270020064806310648062F06CC0020062206280020063106270020064806350644002006A9064606CC062F00200648002006450646062A063806310020062806450627064606CC062F";
  send_sms();
  sms_done_();
  auto_current = 1;
  auto_current_count = 0;
  auto_current_timer = 0;
}

void auto_current_setting() {
  if (auto_current_count == 0 && auto_current_timer >= 10) {
    Serial2.println("pomp on");
    digitalWrite(rele, 1);
    auto_current_count = 1;
    auto_current_timer = 0;
    delay(100);
  }
  if (auto_current_count == 1 && auto_current_timer >= 20) {
    if (current >= .2) {
      auto_current = 0;
      auto_current_timer = 0;
      auto_current_count = 0;
      Serial2.println("auto tune end");
      Serial2.println("pomp off");
      digitalWrite(rele, 0);
      Serial2.print("Current:");
      Serial2.println(current);
      float cc;
      if (current >= .5) cc = current - .5;
      if (current < .5) cc = .1;
      user_current = String(cc);
      user_current1 = user_current.toFloat();
      Serial2.print("current_float:");
      Serial2.println(user_current);
      cc = current + 2.5;
      over_load1 = cc;
      over_load = String(cc);
      eeprom_save();
      sms_text = "062C063106CC062706460020064706480627002006A9063406CC002006480020062C063106CC0627064600200627063606270641064700200628062706310020067E0645067E00200630062E06CC0631064700200634062F";
      send_sms();
      sms_done_();
      delay(1000);
      sms_text = "Current: " + user_current;
      send_sms2();
      sms_done_();
      delay(1000);
      sms_text = "Over Load Current: " + over_load;
      send_sms2();
      sms_done_();
      digitalWrite(led, 1);
    }

    if (current < .2) {
      digitalWrite(rele, 0);
      Serial2.println("*Low current*");
      sms_text = "0645063406A906440020062F0631002006270646062F062706320647002006AF06CC063106CC000D000A067E0645067E002006480635064400200646064506CC0020062806270634062F";
      send_sms();
      sms_done_();
      auto_current = 0;
      auto_current_timer = 0;
      auto_current_count = 0;
    }
  }
}

//////////////////////////////////////////////time havakeshi////////////////////////////
void time_havakeshi_() {
  Serial2.println("setting time havashi");
  sub1 = sim_data.substring(5, 10);  ////time 15
  time_havakeshi = sub1;
  time_havakeshi1 = time_havakeshi.toFloat();
  Serial2.print("time_havakeshi:");
  Serial2.println(time_havakeshi);
  eeprom_save();
  sms_text = "062A0646063806CC06450627062A0020063206450627064600200630062E06CC0631064700200634062F";
  send_sms();
  sms_done_();
}

void current_send() {
  if (current < .09) current = 0;
  String cc = "Current:" + String(current) + "A";
  sms_text = cc;
  send_sms2();
  sms_done_();
}


//float average = 0;
void read_current() {
  if (current_count >= 3) {
    current_count = 0;
    currentRMS = measureCurrentRMS();
    current = currentRMS;
    Serial2.print("current:");
    Serial2.println(current);
  }
}


// محاسبه آفست سنسور (در حالت بدون جریان)
float calibrateOffset() {
  long sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += analogRead(SENSOR_PIN);
  }
  return (float)sum / SAMPLES * (5 / 4095.0);  // تبدیل مقدار ADC به ولتاژ
}

// اندازه‌گیری جریان RMS
float measureCurrentRMS() {
  long sumSquares = 0;
  for (int i = 0; i < SAMPLES; i++) {
    int sensorValue = analogRead(SENSOR_PIN);
    float voltage = sensorValue * (5 / 4095.0);                      // تبدیل مقدار ADC به ولتاژ
    float current = (voltage - offsetVoltage) / SENSOR_SENSITIVITY;  // محاسبه جریان
    sumSquares += current * current;                                 // مجذور جریان
  }
  float meanSquare = (float)sumSquares / SAMPLES;
  return sqrt(meanSquare);  // بازگشت مقدار RMS
}

void pomp_control() {

  if (auto_current == 1) auto_current_setting();

  if (pomp_state == 1 && power_count == 1 && current < .7 && auto_current == 0) {
    pomp_state_count = 0;
    pomp_count = 0;
    pomp_state_timer = 0;
  }

  if (pomp_state == 1 && power_count == 1 && current >= .7 && auto_current == 0) {
    if (current < user_current1 && pomp_count == 0) {
      pomp_state_count = 1;
      pomp_count = 1;
      pomp_state_timer = 0;
      Serial2.print("LOW Current WARNING...");
      Serial2.println("Timer Start");
    }

    if (pomp_state_count == 1 && pomp_state_timer >= time_havakeshi1) {
      pomp_state_timer = 0;
      pomp_state_count = 0;
      pomp_count = 0;
      pomp_state = 0;
      Serial2.println("***Hava keshi***");
      digitalWrite(rele, 0);
      delay(1000);
      input_number = number1;
      sms_text = "002000200020002A002A002A002A06470634062F06270631002A002A002A002A000D000A0645063406A906440020064706480627002006A9063406CC0020067E0645067E";
      send_sms();
      sms_done_();
      delay(2000);

      input_number = number1;
      sms_text = "current:" + String(current);
      send_sms2();
      sms_done_();

      ring_alarm();
      rele_state = "0";
      eeprom_save();
    }


    if (current >= user_current1) {
      if (pomp_state_count == 1) {
        Serial2.print("LOW Current ok");
        Serial2.println("Timer off");
      }
      pomp_state_count = 0;
      pomp_count = 0;
      pomp_state_timer = 0;
    }

    if (over_load1 > 0) {


      if (current >= over_load1 && over_current_count == 0) {
        time_over_current = 0;
        over_current_count = 1;
        Serial2.print("HIGH Current WARNING...");
        Serial2.println("Timer Start");
      }

      if (current < over_load1) {
        if (over_current_count == 1) {
          Serial2.print("HIGH Current ok");
          Serial2.println("Timer off");
        }
        time_over_current = 0;
        over_current_count = 0;
      }

      if (time_over_current >= 10 && over_current_count == 1) {
        if (power_check == 0) {
          over_check_error = 1;
          over_current_count = 0;
          time_over_current = 0;
          // input_number = number1;
          // sms_text = "06470634062F06270631000D000A067E0645067E0020062A062D062A00200641063406270631";
          // send_sms();
          // sms_done_();
          //delay(2000);
        }
        if (power_check == 1) {
          pomp_state = 0;
          time_over_current = 0;
          over_current_count = 0;
          Serial2.println("***Over load***");
          digitalWrite(rele, 0);
          delay(1000);
          input_number = number1;
          sms_text = "06470634062F062706310020062706360627064106470020062C063106CC06270646000D000A067E0645067E0020062A062D062A002006410634062706310020064506CC0020062806270634062F";
          send_sms();
          sms_done_();
          delay(2000);
          ring_alarm();
          rele_state = "0";
          eeprom_save();
        }
      }
    }


    ////
  }
}

void over_current_setting() {
  Serial2.println("Over current setting");
  sub1 = sim_data.substring(13, 19);  ////over current 1.2
  over_load = sub1;
  over_load1 = over_load.toFloat();
  Serial2.print("current_float:");
  Serial2.println(over_load);
  eeprom_save();
  sms_text = "062A0646063806CC06450627062A00200627063606270641064700200628062706310020062C063106CC0627064600200630062E06CC0631064700200634062F";
  send_sms();
  sms_done_();
  time_over_current = 0;
  over_current_count = 0;
}

void pomp_user_current() {

  Serial2.println("pomp user current");
  sub1 = sim_data.substring(8, 15);  ////current 1.75 cu 1.75
  user_current = sub1;
  user_current1 = user_current.toFloat();
  Serial2.print("current_float:");
  Serial2.println(user_current);
  eeprom_save();
  sms_text = "062C063106CC062706460020067E0645067E00200630062E06CC0631064700200634062F";
  send_sms();
  sms_done_();
  pomp_state_count = 0;
}

void pomp_on() {
  Serial2.println("pomp on");
  digitalWrite(rele, 1);
  delay(1000);
  rele_state = "1";
  eeprom_save();
  sms_text = "067E0645067E0020063106480634064600200634062F";
  send_sms();
  sms_done_();
  pomp_state = 1;
  pomp_state_count = 0;
  time_over_current = 0;
  over_current_count = 0;
}



void pomp_off() {
  Serial2.println("pomp off");
  digitalWrite(rele, 0);
  delay(1000);
  rele_state = "0";
  eeprom_save();
  sms_text = "067E0645067E0020062E062706450648063400200634062F";
  send_sms();
  sms_done_();
  pomp_state = 0;
  pomp_state_count = 0;
  time_over_current = 0;
  over_current_count = 0;
}