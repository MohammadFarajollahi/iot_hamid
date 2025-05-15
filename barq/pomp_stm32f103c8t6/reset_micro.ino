
void reset_micro() {



  if (hang == 0) watchdog_timer = 0;

  if (timer_reset >= 29000 && gprs == 0) {

    Serial1.println("AT+CFUN=0");
    delay(1000);
    Serial1.println("AT+CFUN=1");
    delay(2000);
    digitalWrite(sim_power, HIGH);
    delay(2000);
    digitalWrite(sim_power, LOW);
    delay(3000);

    reset_ = 1;
    iwdg_init(IWDG_PRE_256, 1);
  }
}