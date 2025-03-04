

void uart2() {
  while (Serial2.available() > 0) {
    inputData = Serial2.readStringUntil('\n');
    inputData.trim();
    Serial.println(inputData);
    //***gsm check***
    if (inputData == "GSMcheck") {
      Serial3.println("GSMcheck");
    }

    if (inputData == "reset gsm") {
      Serial2.println("gsm reset ok");
      digitalWrite(gsm_reset, HIGH);
      delay(200);
      digitalWrite(gsm_reset, LOW);
    }

    if (inputData == "megaCheck") {
      Serial2.println("mega ok");
    }

    if (inputData == "megaResponse") {
      Serial2.println("Response ok");
    }

    sub1 = inputData.substring(0, 7);  ///Sensors
    if (sub1 == "Sensors") {
      Serial3.println(inputData);
    }

     sub1 = inputData.substring(0, 6);  ///OUTPUT_Heat1
    if (sub1 == "OUTPUT") {
      Serial3.println(inputData);
    }

    sub1 = inputData.substring(0, 1);  ///.c_str()
    if (sub1 == "{") {
      //char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
      //char json[] = inputData.c_str();
      deserializeJson(doc, inputData);

      //element1///
      if (doc["element1"] == "on") {
        Serial.println("element1 on");
        digitalWrite(element1, HIGH);
      }
      if (doc["element1"] == "off") {
        Serial.println("element1 off");
        digitalWrite(element1, LOW);
      }

      //element2///
      if (doc["element2"] == "on") {
        Serial.println("element2 on");
        digitalWrite(element2, HIGH);
      }
      if (doc["element2"] == "off") {
        Serial.println("element2 off");
        digitalWrite(element2, LOW);
      }

      //tank1///
      if (doc["tank1"] == "on") {
        Serial.println("tank1 on");
        digitalWrite(tank1, HIGH);
      }
      if (doc["tank1"] == "off") {
        Serial.println("tank1 off");
        digitalWrite(tank1, LOW);
      }

      //tank2///
      if (doc["tank2"] == "on") {
        Serial.println("tank2 on");
        digitalWrite(tank2, HIGH);
      }
      if (doc["tank2"] == "off") {
        Serial.println("tank2 off");
        digitalWrite(tank2, LOW);
      }

      //tank3///
      if (doc["tank3"] == "on") {
        Serial.println("tank3 on");
        digitalWrite(tank3, HIGH);
      }
      if (doc["tank3"] == "off") {
        Serial.println("tank3 off");
        digitalWrite(tank3, LOW);
      }

      //tank4///
      if (doc["tank4"] == "on") {
        Serial.println("tank4 on");
        digitalWrite(tank4, HIGH);
      }
      if (doc["tank4"] == "off") {
        Serial.println("tank4 off");
        digitalWrite(tank4, LOW);
      }

      //light1///
      if (doc["light1"] == "on") {
        Serial.println("light1 on");
        digitalWrite(light1, HIGH);
      }
      if (doc["light1"] == "off") {
        Serial.println("light1 off");
        digitalWrite(light1, LOW);
      }

      //light2///
      if (doc["light2"] == "on") {
        Serial.println("light2 on");
        digitalWrite(light2, HIGH);
      }
      if (doc["light2"] == "off") {
        Serial.println("light2 off");
        digitalWrite(light2, LOW);
      }

      //fan1///
      if (doc["fan1"] == "on") {
        Serial.println("fan1 on");
        digitalWrite(fan1, HIGH);
      }
      if (doc["fan1"] == "off") {
        Serial.println("fan1 off");
        digitalWrite(fan1, LOW);
      }

      //fan2///
      if (doc["fan2"] == "on") {
        Serial.println("fan2 on");
        digitalWrite(fan2, HIGH);
      }
      if (doc["fan2"] == "off") {
        Serial.println("fan2 off");
        digitalWrite(fan2, LOW);
      }
    }


    //
  }
}