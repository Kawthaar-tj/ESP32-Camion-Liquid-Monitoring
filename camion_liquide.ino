#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>

// ---- HW / IO ----
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int PIN_USE  = 34;
const int PIN_NEUF = 35;

// ---- WiFi / MQTT ----
const char* SSID = "Sedimat";
const char* PASS = "WelcomeSedimat38!!";

const char* MQTT_HOST = "192.168.3.51";
const int   MQTT_PORT = 1883;
const char* TOPIC     = "camion/donnees";
const char* DEV_ID    = "camion_X";

WiFiClient esp;
PubSubClient mqtt(esp);

// ---- Calibration tension -> % ----
const float V[] = {0.00,0.68,0.83,0.94,1.04,1.12,1.29,1.38,1.44,1.56,1.66,1.75};
const float P[] = {0.0,11.1,22.2,27.8,33.3,44.4,55.6,66.7,77.8,83.3,88.9,100.0};
const int N = sizeof(V)/sizeof(V[0]);

// ---- Cuve ----
const float V_TOT_L = 15.0;
const float RATIO   = 27.0 / 34.1;
const float OFFSET  = 0.55;

// ---- Timers ----
uint32_t tLCD = 0, tMQTT = 0;
const uint32_t LCD_MS  = 2000;
const uint32_t MQTT_MS = 1000;

// ---------------- helpers ----------------
static void wifiConnect() {
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(300);
}

static void mqttEnsure() {
  while (!mqtt.connected()) {
    mqtt.connect(DEV_ID);     // broker allow_anonymous
    if (!mqtt.connected()) delay(1000);
  }
}

static float adcV(int pin) {          // moyenne rapide
  uint32_t s = 0;
  for (int i = 0; i < 5; i++) { s += analogRead(pin); delay(1); }
  return (s / 5.0f) * (3.3f / 4095.0f);
}

static float vToPct(float v) {        // interpolation linéaire
  if (v <= V[0]) return 0;
  if (v >= V[N-1]) return 100;
  for (int i = 0; i < N-1; i++) {
    if (v >= V[i] && v <= V[i+1]) {
      float r = (v - V[i]) / (V[i+1] - V[i]);
      return P[i] + r * (P[i+1] - P[i]);
    }
  }
  return 0;
}

static float litresFromPin(int pin) {
  float pct = vToPct(adcV(pin)) * RATIO;
  pct = constrain(pct, 0.0f, 100.0f);
  float L = (pct / 100.0f) * V_TOT_L + OFFSET;
  return constrain(L, 0.0f, V_TOT_L);
}

static void isoTime(char* out, size_t n) {
  struct tm t;
  if (getLocalTime(&t)) strftime(out, n, "%Y-%m-%dT%H:%M:%SZ", &t);
  else snprintf(out, n, "unknown");
}

static void publishData(float useL, float neufL) {
  char ts[25]; isoTime(ts, sizeof(ts));
  char payload[200];
  // JSON minimal (pas ArduinoJson)
  snprintf(payload, sizeof(payload),
           "{\"device_id\":\"%s\",\"timestamp\":\"%s\",\"liquide_use\":%.2f,\"liquide_neuf\":%.2f}",
           DEV_ID, ts, useL, neufL);
  mqtt.publish(TOPIC, payload);
}

// ---------------- Arduino ----------------
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  lcd.init(); lcd.backlight();
  lcd.setCursor(0,0); lcd.print("Boot...");

  wifiConnect();

  configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // sync NTP (best effort)

  mqtt.setServer(MQTT_HOST, MQTT_PORT);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("WiFi OK");
  lcd.setCursor(0,1); lcd.print("MQTT...");
}

void loop() {
  mqttEnsure();
  mqtt.loop();

  uint32_t now = millis();
  float useL  = litresFromPin(PIN_USE);
  float neufL = litresFromPin(PIN_NEUF);

  if (now - tLCD >= LCD_MS) {
    lcd.setCursor(0,0); lcd.print("Use: ");  lcd.print(useL, 1);  lcd.print("L   ");
    lcd.setCursor(0,1); lcd.print("Neuf:");  lcd.print(neufL,1);  lcd.print("L   ");
    tLCD = now;
  }

  if (now - tMQTT >= MQTT_MS) {
    publishData(useL, neufL);
    tMQTT = now;
  }
}