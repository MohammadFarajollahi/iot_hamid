

void quectel_uart(){

  while (Serial1.available() > 0) {
    sim_data = Serial1.readStringUntil('\n');
    sim_data.trim();
    Serial2.println(sim_data);
    check_();
    sim_data ="";
    input_data = 0;
  }
 

}