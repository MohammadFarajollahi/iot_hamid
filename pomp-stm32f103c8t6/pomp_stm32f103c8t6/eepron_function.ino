

void read_eeprom_() {
  Serial2.println("Read EEPROM>>>");
  id = EEPROMread(0, 10);
  number1 = "+989372425086";
  number2 = "+989113185419";
  rele_state = EEPROMread(51, 60);
  security_state = EEPROMread(61, 70);
  user_current = EEPROMread(71, 80);
  time_havakeshi = EEPROMread(81, 90);
  over_load = EEPROMread(91, 100);

  Serial2.print("ID:");
  Serial2.println(id);
  if (id == "12345678") {
    pomp_khanegi = 0;
    Serial2.println("pomp dasht");
  }
  if (id == "87654321") {
    pomp_khanegi = 1;
    Serial2.println("pomp khanegi");
  }
  Serial2.print("Number1:");
  Serial2.println(number1);
  Serial2.print("Number2:");
  Serial2.println(number2);
  if (rele_state == "1") {
    digitalWrite(rele, 1);
    Serial2.println("POMP ON");
    pomp_state = 1;
  }
  if (rele_state == "0") {
    Serial2.println("POMP OFF");
    digitalWrite(rele, 0);
    pomp_state = 0;
  }
  if (security_state == "1") Serial2.println("Security on");
  if (security_state == "0") Serial2.println("Security off");
  user_current1 = user_current.toFloat();
  Serial2.print("User current:");
  Serial2.println(user_current);
  Serial2.print("Time havakeshi:");
  Serial2.println(time_havakeshi);
  over_load1 = over_load.toFloat();
  if (over_load1 > 0) {
    Serial2.print("Over load on:");
    Serial2.println(over_load);
  }
  if (over_load1 == 0) {
    Serial2.print("Over load off:");
    Serial2.println(over_load);
  }

  time_havakeshi1 = time_havakeshi.toInt();
  if (id.length() != 8 || number1.length() != 13 || number2.length() != 13) {
    input_number = "+989372425086";
    register_first = 1;
    config_();
  }
}


void eeprom_save() {
  Serial2.println("<***EEPROM***>");
  EEPROMwrite(0, id);
  delay(10);
  EEPROMwrite(11, number1);
  delay(10);
  EEPROMwrite(31, number2);
  delay(10);
  EEPROMwrite(51, rele_state);
  delay(10);
  EEPROMwrite(61, security_state);
  delay(10);
  EEPROMwrite(71, user_current);
  delay(10);
  EEPROMwrite(81, time_havakeshi);
  delay(10);
  EEPROMwrite(91, over_load);
  delay(10);
}


void information() {  //eeprom/12345678/+989372425086/+989114764806/+989379274959/0/0/0/1/11.111111,11.111111
  //id number1 number2 car_number gprs_state rele_state security_state auto_security_state loc_save
  Serial2.println("Server eeprom Sending...");
  sms_text = "eeprom/" + id + "/" + number1 + "/" + number2 + "/" + rele_state + "/" + security_state + "/" + user_current + "/" + time_havakeshi + "/" + over_load;
  Serial2.println(sms_text);
  send_sms2();
  sms_done_();
}


void server_eeprom() {  //eeprom/12345678/+989372425086/+989114764806/+989379274959/0/0/0/1/11.111111,11.111111
  Serial2.println("Server eeprom saving...");
  String data = sim_data;
  Serial2.println(sim_data);
  id = getValue(data, '/', 1);
  number1 = getValue(data, '/', 2);
  number2 = getValue(data, '/', 3);
  rele_state = getValue(data, '/', 4);
  security_state = getValue(data, '/', 5);
  user_current = getValue(data, '/', 6);
  time_havakeshi = getValue(data, '/', 7);
  over_load = getValue(data, '/', 8);
  Serial.print("ID:");
  Serial2.println(id);
  if (id == "12345678") {
    pomp_khanegi = 0;
    Serial2.println("pomp dasht");
  }
  if (id == "87654321") {
    pomp_khanegi = 1;
    Serial2.println("pomp khanegi");
  }
  Serial.print("Number1:");
  Serial2.println(number1);
  Serial.print("Number2:");
  Serial2.println(number2);
  if (rele_state == "1") Serial2.println("pomp on");
  if (rele_state == "0") Serial2.println("pomp off");
  if (security_state == "1") Serial2.println("Security on");
  if (security_state == "0") Serial2.println("Security off");
  user_current1 = user_current.toFloat();
  over_load1 = over_load.toFloat();
  Serial2.print("User current:");
  Serial2.println(user_current);
  Serial2.print("Time havakeshi:");
  Serial2.println(time_havakeshi);
  Serial2.print("over load:");
  Serial2.println(over_load);
  time_havakeshi1 = time_havakeshi.toInt();
  eeprom_save();
  sms_text = "062A0646063806CC06450627062A00200630062E06CC0631064700200634062F";
  send_sms();
  sms_done_();
}









String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}











String EEPROMread(int StartAddr, int StringLength) {
  char buf[StringLength + 1];
  eeprom_read_string(StartAddr, buf, StringLength + 1);
  String dataStr = buf;
  return dataStr;
}

void EEPROMwrite(int StartAddr, String DataString) {
  int val = DataString.length() + 1;
  char StringChar[val];
  char buff[val];

  DataString.toCharArray(StringChar, val);
  strcpy(buff, StringChar);
  eeprom_write_string(StartAddr, buff);
}

boolean eeprom_is_addr_ok(int addr) {
  return ((addr >= addressEEPROM_min) && (addr <= addressEEPROM_max));
}

boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
  int i;

  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) {
    return false;
  }

  for (i = 0; i < numBytes; i++) {
    EEPROM.write(startAddr + i, array[i]);
  }
  return true;
}

boolean eeprom_write_string(int addr, const char* string) {
  int numBytes;  // number of actual bytes to be written

  numBytes = strlen(string) + 1;  // Write string content plus byte terminator string (0x00)
  return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}

boolean eeprom_read_string(int addr, char* buffer, int bufSize) {
  byte ch;        // read bytes from eeprom
  int bytesRead;  // number of bytes read so far

  if (!eeprom_is_addr_ok(addr))  // check the starting address
  {
    return false;
  }

  if (bufSize == 0)  // how can we store bytes in an empty buffer?
  {
    return false;
  }

  if (bufSize == 1) {
    buffer[0] = 0;
    return true;
  }

  bytesRead = 0;                       // initialize a byte counter
  ch = EEPROM.read(addr + bytesRead);  // read the next byte from eeprom
  buffer[bytesRead] = ch;              // save it in the user's buffer
  bytesRead++;

  // if no stop conditions are met, read the next byte from the eeprom
  while ((ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= addressEEPROM_max)) {
    ch = EEPROM.read(addr + bytesRead);
    buffer[bytesRead] = ch;  // save it in the user's buffer
    bytesRead++;
  }

  if ((ch != 0x00) && (bytesRead >= 1))  // make sure the user buffer has the string terminator, (0x00) as the last byte
  {
    buffer[bytesRead - 1] = 0;
  }
  return true;
}