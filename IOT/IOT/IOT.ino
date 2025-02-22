//*******sd_card********
#include "Arduino.h"
#include "SPI.h"
#include "FS.h"
#include "SD.h"
#define CS_PIN 7  // پایه CS برای ESP32-S3 (می‌تواند بسته به سیم‌کشی تغییر کند)
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <algorithm>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Touch_XPT2046 _touch_instance;
public:

  LGFX(void) {
    {
      auto cfg = _bus_instance.config();  // バス設定用の構造体を取得します。

      // SPIバスの設定
      cfg.spi_host = SPI2_HOST;  // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
      cfg.spi_mode = 0;                   // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 40000000;          // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read = 16000000;           // 受信時のSPIクロック
      cfg.spi_3wire = true;               // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock = true;                // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = SPI_DMA_CH_AUTO;  // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
      // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
      cfg.pin_sclk = 12;                       // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 11;                       // SPIのMOSIピン番号を設定
      cfg.pin_miso = 13;                       // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc = 6;                          // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);               // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);  // バスをパネルにセットします。
    }

    {  // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 4;     // CS
      cfg.pin_rst = -1;   // RST
      cfg.pin_busy = -1;  // BUSY
      cfg.panel_width = 320;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;  // 16bit
      cfg.bus_shared = true;   // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)
      cfg.memory_width = 320;
      cfg.memory_height = 480;
      _panel_instance.config(cfg);
    }

    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = 319;
      cfg.y_min = 0;
      cfg.y_max = 479;
      cfg.pin_int = -1;
      cfg.bus_shared = true;
      cfg.offset_rotation = 0;
      cfg.spi_host = SPI2_HOST;
      cfg.freq = 1000000;
      cfg.pin_sclk = 12;  // SCLK
      cfg.pin_mosi = 11;  // MOSI
      cfg.pin_miso = 13;  // MISO
      cfg.pin_cs = 5;     //   CS
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
    setPanel(&_panel_instance);
  }
};
LGFX tft;
unsigned long total = 0;
unsigned long tn = 0;
String LcdText;
//
//*****تاچ****
uint32_t count = ~0;
//#include <XPT2046_Touchscreen.h>

uint16_t x_t, y_t;  // touch
// #define CALIBRATION_FILE "/TouchCalData3"
// #define REPEAT_CAL false
// bool SwitchOn = false;
///////clock/////
#include <Wire.h>
#include <RTClib.h>
#include <TimeLib.h>
// تعریف کتابخانه تقویم شمسی
class JalaliConverter {
public:
  static void toJalali(int g_y, int g_m, int g_d, int &j_y, int &j_m, int &j_d) {
    int g_days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int j_days_in_month[] = { 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29 };
    int gy = g_y - 1600, gm = g_m - 1, gd = g_d - 1;
    long g_day_no = 365 * gy + (gy + 3) / 4 - (gy + 99) / 100 + (gy + 399) / 400;
    for (int i = 0; i < gm; ++i) g_day_no += g_days_in_month[i];
    if (gm > 1 && ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0))) g_day_no++;
    g_day_no += gd;
    int j_day_no = g_day_no - 79;
    int j_np = j_day_no / 12053;
    j_day_no %= 12053;
    int jy = 979 + 33 * j_np + 4 * (j_day_no / 1461);
    j_day_no %= 1461;
    if (j_day_no >= 366) {
      jy += (j_day_no - 1) / 365;
      j_day_no = (j_day_no - 1) % 365;
    }
    int i;
    for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i) j_day_no -= j_days_in_month[i];
    int jm = i + 1, jd = j_day_no + 1;
    j_y = jy;
    j_m = jm;
    j_d = jd;
  }
};
RTC_DS3231 rtc;
int ClockTimer;

///eeprom///
#include <Preferences.h>
Preferences preferences;

//sht20
#include <SHT2x.h>
SHT2x sht;

float mainTempSettig;
float mainHuSetting;

int shtTime = 5;
float MainHumidity;
float MainTemperature;

//****ds18b20****
float Temp1 = 25.5;
float Temp2 = 23.5;
float Temp3 = 21.5;
float Temp4 = 20.8;
float TempSetting1 = 22.3;
float hu1 = 65.5;
float hu2 = 76.4;
float hu3 = 63.5;
float hu4 = 73.4;
float HuSetting1 = 65.4;
int khak_count = 5;
//timer
hw_timer_t *timer = NULL;  // اشاره‌گر به تایمر
void IRAM_ATTR onTimer() {

  ++ClockTimer;
  ++shtTime;
  ++khak_count;
}


int buzzer = 21;

void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");
  //TIMER
  timer = timerBegin(0, 80, true);              // تایمر 0، تقسیم‌کننده 80 (1 میکروثانیه)
  timerAttachInterrupt(timer, &onTimer, true);  // اتصال وقفه
  timerAlarmWrite(timer, 1000000, true);        // وقفه هر 1,000,000 میکروثانیه (1 ثانیه)
  timerAlarmEnable(timer);
  //////////////clock/////
  Wire.begin(8, 9);  // برای ESP32-S3: SDA=GPIO21, SCL=GPIO22
  if (!rtc.begin()) {
    Serial.println("⛔ DS3231M شناسایی نشد!");
  }

  //setDateTime(2025, 2, 21, 22, 19, 30); // تنظیم ساعت روی 20 فوریه 2025، ساعت 14:30:00

  // if (rtc.lostPower()) {
  //   Serial.println("⚠ باتری ساعت از کار افتاده، تنظیم مجدد...");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }

  ////sdcard////
  if (!SD.begin(CS_PIN)) {
    Serial.println("Failed to initialize SD card.");
    return;
  }
  Serial.println("SD card initialized.");
  //////lcd//////
  Serial.println("Lovyan's LovyanGFX library Test!");
  tft.init();
  tft.setRotation(3);
  tft.startWrite();
  tft.fillScreen(TFT_BLACK);
  //tft.drawPngFile(SD, "/BACKGROUND.png", 0, 0);
  //sht20
  sht.begin();

  //eeprom///
  preferences.begin("storage", false);
  delay(20);
  mainTempSettig = preferences.getFloat("mainTempSettig", 0.0);
  delay(20);
  mainHuSetting = preferences.getFloat("mainHuSetting", 0.0);
  delay(20);
  if (mainTempSettig > 100) {
    mainTempSettig = 22.5;
    preferences.putFloat("mainTempSettig", mainTempSettig);
    delay(20);
  }

  if (mainHuSetting > 100) {
    mainHuSetting = 65.5;
    preferences.putFloat("mainHuSetting", mainHuSetting);
    delay(20);
  }
  preferences.end();
  ///////////////////////////////////////

  tft.drawLine(125, 55, 478, 55, TFT_WHITE);
  tft.drawLine(125, 0, 125, 55, TFT_WHITE);
  tft.drawLine(478, 0, 478, 55, TFT_WHITE);
  ///
  tft.drawLine(0, 185, 146, 185, TFT_WHITE);
  tft.drawLine(146, 55, 146, 305, TFT_WHITE);
  tft.drawLine(0, 305, 146, 305, TFT_WHITE);
}


void loop(void) {
  input_touch();
  Clock();
  Sht20();
  ds18b20();
  InputUart();
}