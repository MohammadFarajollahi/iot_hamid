
void timer_(void) {
  ++reset_check;
  if (reset_check >= 250) iwdg_init(IWDG_PRE_256, 1);



  //********start quectel***********
  if (sim_config == 0) {
    ++start_config_timer;
    digitalWrite(led, !digitalRead(led));
  }


  //***********main timers**********
  if (sim_config == 1) {
    //digitalWrite(led, 1);
    if (input_sms == 0) ++count;
    //******check sim868*****
    if (check_point == 1) {
      ++check_point_timer;
    }
    //****input_sms*****
    if (input_sms == 1) {
      ++input_sms_timer;
      ++sms_error_time;
    }
    ++power_timer;
    ++current_count;
    if (pomp_state_count == 1) ++pomp_state_timer;
    //if (battery < 10) digitalWrite(led, !digitalRead(led));
    ++timer_reset;

    if (door_count == 1) ++door_warning_timer;
    if (door_warning_timer >= 60) door_count = 0;

    if (auto_current == 1) {
      ++auto_current_timer;
      digitalWrite(led, !digitalRead(led));
    }

    if (over_current_count == 1) ++time_over_current;

    if (power_check_count == 0) {
      ++power_check_timer;
      if (power_check_timer >= 60) {
        power_check_count = 1;
        power_check_timer = 0;
        power_check = 1;
      }
    }

    if (power_check == 1 && over_check_error == 1) {
      ++power_check_timer;
      if (power_check_timer >= 60) {
        reset_ = 1;
        iwdg_init(IWDG_PRE_256, 1);
      }
    }
    //
  }

  if (sim_config == 0) {
    timeReset++;
    if (timeReset >= 40) iwdg_init(IWDG_PRE_256, 1);
  }

  //*****WATCHDOG*****
  if (reset_ == 0) {
    iwdg_feed();
  }
  ++watchdog_timer;
  if (watchdog_timer >= 60) iwdg_init(IWDG_PRE_256, 1);
}
