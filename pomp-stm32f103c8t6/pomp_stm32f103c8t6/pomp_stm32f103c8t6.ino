#include <EEPROM.h>
#include <libmaple/iwdg.h>

//****eeprom****
const int addressEEPROM_min = 0;  // Specify the address restrictions you want to use.
const int addressEEPROM_max = 300;

//*****timer****
void timer_(void);
#define LED_RATE 1000000


//adc curent
#include "ACS712.h"
#define SENSOR_PIN PA1            // پایه ADC که خروجی سنسور به آن متصل است
#define SAMPLES 3000              // تعداد نمونه‌گیری برای محاسبه RMS
#define SENSOR_SENSITIVITY 0.06  // حساسیت سنسور (ACS712-58A = 0.185V/A) (ACS712-30A = 0.06V/A)
float offsetVoltage = 0.0;        // مقدار ولتاژ آفست سنسور
float currentRMS = 0.0;           // جریان RMS

//************pin_config***********
int sim_power = PB11;
int rele = PC13;
int rele2 = PC14;
int led = PA7;
int sensor1 = PB14;
int sensor2 = PB15;
int ri_uart = PB12;
//**********program*************
String sim_data;
String sub1;
int input_data;
int start_config_count;
int start_config_timer;
int sim_config;
int simcard_model;
int simcard_count;
int network_count;
int watchdog_timer;
int hang;
int count;
int check_point;
int check_point_count;
int check_point_timer;
int error_;
int serial_show = 0;
int p2p_mode = 0;
int input_sms;
int input_sms_count;
int input_sms_timer;
String sms_time;
String server_number1 = "+989372425086";
String server_number2 = "+989114764806";
String number1;
String number2;
String input_number;
int number;
String sms_text;
int gps_timer;
String gps_signal;
String lat;
String lon;
String speed;
String sat_number;
String location;
String anten;
String battery1;
int battery;
String voltage1;
int loc_save_count;
int loc_save_timer;
int gps_signal1;
int gprs_time;
int gprs_count;
int gprs_timer;
int gprs_error;
int gprs_gps_test;
int first_time;
int turn_on_gprs;
int avcc_state;
int door_state;
int send_error;
int error_send;
int location_error;
int location_error_send;
String anten2;
int gprs_history_time = 300;
int gprs_history_count;
int gprs_his;
int gps_his_done;
int avcc_count;
int door_count;
int door_warning_timer;
int avcc_warning_timer;
int auto_security_timer;
int gprs_his_start;
int power_timer;
int adc;
int power_count;
int register_first;
int reset_;
int gprs_always;
int start_sms_count = 0;
int error_send_data;
int gprs;
int suc_gprs;
int error600_count;
float car_batt;
int gps_serial_count;
String number_charg;
int on_count;
int avcc_error_wait;
int avcc_alarm_count;
int door_error_wait;
int door_alarm_count;
int timer_reset;
int alarm_count1;
int alarm_count2;
int sms_error_time;
int reset_check;
int loc_car_batt;
int loc_car_batt_timer;
int batt_show;
String firsr_char_sms;
int wait_signal;
int wait_signal_count;
int check_number_count;
int current_count;
int start_adc;
int adc_samples;
float current;
int pomp_state;
int pomp_count;
int pomp_state_count;
int pomp_error_count;
int pomp_state_timer;
float user_current1;
String user_current;
int eeprom_chek;
int time_havakeshi1;
String time_havakeshi;
float over_load1;
String over_load;

int auto_current;
int auto_current_timer;
int auto_current_count;

int time_over_current;
int over_current_count;
int timer_pomp_on;
int power_off_count;
//****************eeprom******************
String id;
String rele_state;
String security_state;


int power_check;
int power_check_count;
int power_check_timer;
int over_check_error;

int pomp_khanegi;

String numberSend;
int timeReset;
//for first start to read correct current && calibrate
int start_power;
int start_power_count;

void setup() {
  Serial2.begin(9600);
  Serial1.begin(9600);
  Serial2.println("***Start program***");


  //****************pin_config***********

  pinMode(sim_power, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(sensor1, INPUT_PULLUP);
  //*****watchdog****
  iwdg_init(IWDG_PRE_256, 2000);


  //******timer*******
  Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
  Timer2.setPeriod(LED_RATE);
  Timer2.setCompare(TIMER_CH1, 1);
  Timer2.attachInterrupt(TIMER_CH1, timer_);

  //*******adc******
  offsetVoltage = calibrateOffset();  // محاسبه آفست اولیه سنسور
}


void loop() {

  quectel_uart();
  first_start();
  quectel_check_();
  serial_setup_();
  sms_check_();
  //sensor();
  power_();
  reset_micro();
}
