int adc_1;
int power_error_count;

void power_() {
  if (power_timer >= 2 && check_point == 0) {  //5
    power_timer = 0;
    adc_1 = 0;
    float average = 0;
    for (int i = 0; i < 5; i++) {
      //average += ACS2.mA_AC_sampling();
      average += analogRead(PA0);
    }
    float mA = average / 5;
    adc_1 = mA;
    // Serial2.print("input_power:");
    // Serial2.println(adc_1);


    if (adc_1 >= 1000 && power_count == 0) {
      //for over current
      power_check = 0;
      power_check_count = 0;
      power_check_timer = 0;
      //////////////////
      power_count = 1;
      Serial2.println("Input Power Connect");
      digitalWrite(led, 0);
      delay(50);
      digitalWrite(led, 1);
      delay(50);
      digitalWrite(led, 0);
      delay(50);
      digitalWrite(led, 1);
      delay(50);
      on_count = 0;
      if (security_state == "1") {

        if (number1 != "+981111111111") {
          input_number = number1;
          sms_text = "06280631064200200648063506440020064506CC0020062806270634062F";
          send_sms();
          sms_done_();
        }

        if (number2 != "+981111111111") {
          input_number = number2;
          sms_text = "06280631064200200648063506440020064506CC0020062806270634062F";
          send_sms();
          sms_done_();
        }

        //ring_alarm();
      }
    }

    if (adc_1 >= 1000) power_error_count = 0;

    if (adc_1 < 1000 && power_count == 1) {
      power_timer = 1;
      Serial2.println("---power trig---");
      ++power_error_count;
      if (power_error_count >= 3) {
        //////////////////////
        Serial2.println("pomp off");
        digitalWrite(rele, 0);
        pomp_state = 0;
        pomp_state_count = 0;
        time_over_current = 0;
        over_current_count = 0;

        //////////////////////
        start_power = 0;
        start_power_count = 0;
        power_count = 0;
        power_error_count = 0;
        pomp_count = 0;
        pomp_state_timer = 0;
        Serial2.println("Input Power DisConnect");
        if (security_state == "1") {
          on_count = 1;
          if (number1 != "+981111111111") {
            input_number = number1;
            sms_text = "06470634062F06270631000D000A062806310642002006420637063900200634062F";
            send_sms();
            sms_done_();
          }

          if (number2 != "+981111111111") {
            input_number = number2;
            sms_text = "06470634062F06270631000D000A062806310642002006420637063900200634062F";
            send_sms();
            sms_done_();
          }
          ring_alarm();
        }
      }
    }
  }
}


void powerState() {
  if (power_count == 1) {
    sms_text = "06280631064200200648063506440020064506CC0020062806270634062F";
    send_sms();
    sms_done_();
  }

  if (power_count == 0) {
    sms_text = "06280631064200200642063706390020064506CC0020062806270634062F";
    send_sms();
    sms_done_();
  }
}