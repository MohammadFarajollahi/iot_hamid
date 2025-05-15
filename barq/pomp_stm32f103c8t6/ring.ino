
String ring_number;
//SIM GPS : MCI
//+CLCC: 1,1,4,0,0,"+989114764806",145,""  // MCI RINGING
//+CLCC: 1,1,4,0,0,"09372425086",129,""    //IRANCEL RINGING

void ring() {  //+CLCC: 1,1,4,0,0,"+989372425086",145,""
  sub1 = sim_data.substring(18, 19);

  if (sub1 == "+") {
    ring_number = sim_data.substring(18, 31);
  }

  if (sub1 == "0") {
    sub1 = sim_data.substring(19, 29);
    sub1 = "+98" + sub1;
    ring_number = sub1;
  }


  Serial.print("Ring form:");
  Serial2.println(ring_number);


  if (ring_number == number1 || ring_number == number2 || ring_number == server_number1 || ring_number == server_number2) {
    Serial1.println("ATA");
  }

  if (ring_number != number1 && ring_number != number2 && ring_number != server_number1 && ring_number != server_number2) {
    Serial1.println("ATH");
  }



  //main
}

void ring_alarm() {
  Serial2.print("Ring to number1....");
  String S1 = "ATD" + number1 + ";";
  Serial1.println(S1);
  delay(1000);
}
