#include <WiFi.h>
#include <Wire.h>
// #include <Stepper.h>
#include <AccelStepper.h>
#include <Adafruit_PWMServoDriver.h>
#include <LittleFS.h>

// ===== WiFi =====
const char* ssid = "LONE_ROBOT";
const char* password = "12345678";

WiFiServer server(80);

// ===== PCA9685 =====
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVO_FREQ 50

#define SERVO1_CH 0
#define SERVO2_CH 1
#define GRIPPER_CH 2

// Servo 1
#define SERVO1_STOP_US 1480
#define SERVO1_FWD_US  800
#define SERVO1_REV_US  2300

// Servo 2
#define SERVO2_STOP_US 1500
#define SERVO2_FWD_US  1850
#define SERVO2_REV_US  1300

// Gripper 180°
#define GRIPPER_OPEN_US   1600
#define GRIPPER_CLOSE_US  750

// ===== Stepper 28BYJ-48 + ULN2003 =====
const int IN1 = 16;
const int IN2 = 18;
const int IN3 = 17;
const int IN4 = 19;

//const int stepsPerRevolution = 2048;

const float BASE_SPEED = 512; // circa equivalente a 15 rpm con 2048 step/rev default 1024


// Ordine fasi trovato funzionante
//Stepper baseStepper(stepsPerRevolution, IN1, IN4, IN3, IN2);
// Ordine fasi trovato funzionante

AccelStepper baseStepper(AccelStepper::HALF4WIRE, IN1, IN4, IN3, IN2);

// int baseSpeedRpm = 15;

// Da calibrazione:
// 3500 step ≈ 90°
// quindi 1750 step ≈ 45°
#define BASE_45_STEPS 1750

// ===== Funzioni =====
int usToTicks(int us) {
  return (int)(us * 4096L / 20000L);
}

void writeServoUS(int ch, int us) {
  pwm.setPWM(ch, 0, usToTicks(us));
}

void releaseStepper() {
  baseStepper.setSpeed(0);

  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
}

void setup() {
  Serial.begin(115200);
  // Montaggio del file system
  LittleFS.begin(true);
  // I2C ESP32
  Wire.begin(21, 22);

  // PCA9685
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  delay(500);

  writeServoUS(SERVO1_CH, SERVO1_STOP_US);
  writeServoUS(SERVO2_CH, SERVO2_STOP_US);
  writeServoUS(GRIPPER_CH, GRIPPER_OPEN_US);

  // Stepper
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);

  //baseStepper.setSpeed(baseSpeedRpm);
  //releaseStepper();

  baseStepper.setMaxSpeed(BASE_SPEED);
  baseStepper.setSpeed(0);

  

  // WiFi AP
  WiFi.softAP(ssid, password);

  Serial.println("WiFi creato");
  Serial.print("Connettiti a: ");
  Serial.println(ssid);
  Serial.print("Apri browser su: http://");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  baseStepper.runSpeed();
  
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  String path = req.substring(req.indexOf("GET ") + 4, req.indexOf(" HTTP"));

  if (path == "/BASE_P") {
    baseStepper.setSpeed(BASE_SPEED);
    sendText(client, "BASE +");
  }
  else if (path == "/BASE_M") {
    baseStepper.setSpeed(-BASE_SPEED);
    sendText(client, "BASE -");
  }
  else if (path == "/BASE_STOP") {
    releaseStepper();
    sendText(client, "BASE STOP");
  }
  else if (path == "/S1A") {
    writeServoUS(SERVO1_CH, SERVO1_FWD_US);
    sendText(client, "SERVO 1 AVANTI");
  }
  else if (path == "/S1S") {
    writeServoUS(SERVO1_CH, SERVO1_STOP_US);
    sendText(client, "SERVO 1 STOP");
  }
  else if (path == "/S1D") {
    writeServoUS(SERVO1_CH, SERVO1_REV_US);
    sendText(client, "SERVO 1 INDIETRO");
  }
  else if (path == "/S2A") {
    writeServoUS(SERVO2_CH, SERVO2_FWD_US);
    sendText(client, "SERVO 2 AVANTI");
  }
  else if (path == "/S2S") {
    writeServoUS(SERVO2_CH, SERVO2_STOP_US);
    sendText(client, "SERVO 2 STOP");
  }
  else if (path == "/S2D") {
    writeServoUS(SERVO2_CH, SERVO2_REV_US);
    sendText(client, "SERVO 2 INDIETRO");
  }
  else if (path == "/OPEN") {
    writeServoUS(GRIPPER_CH, GRIPPER_OPEN_US);
    sendText(client, "GRIPPER APERTO");
  }
  else if (path == "/CLOSE") {
    writeServoUS(GRIPPER_CH, GRIPPER_CLOSE_US);
    sendText(client, "GRIPPER CHIUSO");
  }
  else if (path == "/style.css") {
    serveFile(client, "/style.css", "text/css");
  }
  else if (path == "/script.js") {
    serveFile(client, "/script.js", "application/javascript");
  }
  else {
    serveFile(client, "/index.html", "text/html");
  }
  

  // ===== BASE =====
  //   if (req.indexOf("/BASE_P") != -1) {
  //   Serial.println("BASE ORARIO CONTINUO");
  //   baseStepper.setSpeed(BASE_SPEED);
  // }
  
  // if (req.indexOf("/BASE_M") != -1) {
  //   Serial.println("BASE ANTIORARIO CONTINUO");
  //   baseStepper.setSpeed(-BASE_SPEED);
  // }
  
  // if (req.indexOf("/BASE_STOP") != -1) {
  //   Serial.println("BASE STOP");
  //   releaseStepper();
  // }

  // // ===== SERVO 1 =====
  // if (req.indexOf("/S1A") != -1) {
  //   writeServoUS(SERVO1_CH, SERVO1_FWD_US);
  //   Serial.println("SERVO 1 AVANTI");
  // }

  // if (req.indexOf("/S1S") != -1) {
  //   writeServoUS(SERVO1_CH, SERVO1_STOP_US);
  //   Serial.println("SERVO 1 STOP");
  // }

  // if (req.indexOf("/S1D") != -1) {
  //   writeServoUS(SERVO1_CH, SERVO1_REV_US);
  //   Serial.println("SERVO 1 INDIETRO");
  // }

  // // ===== SERVO 2 =====
  // if (req.indexOf("/S2A") != -1) {
  //   writeServoUS(SERVO2_CH, SERVO2_FWD_US);
  //   Serial.println("SERVO 2 AVANTI");
  // }

  // if (req.indexOf("/S2S") != -1) {
  //   writeServoUS(SERVO2_CH, SERVO2_STOP_US);
  //   Serial.println("SERVO 2 STOP");
  // }

  // if (req.indexOf("/S2D") != -1) {
  //   writeServoUS(SERVO2_CH, SERVO2_REV_US);
  //   Serial.println("SERVO 2 INDIETRO");
  // }

  // // ===== GRIPPER =====
  // if (req.indexOf("/OPEN") != -1) {
  //   writeServoUS(GRIPPER_CH, GRIPPER_OPEN_US);
  //   Serial.println("GRIPPER APERTO");
  // }

  // if (req.indexOf("/CLOSE") != -1) {
  //   writeServoUS(GRIPPER_CH, GRIPPER_CLOSE_US);
  //   Serial.println("GRIPPER CHIUSO");
  // }

  // ===== PAGINA WEB =====
  // File f = LittleFS.open("/index.html", "r");

  // client.println("HTTP/1.1 200 OK");
  // client.println("Content-Type: text/html");
  // client.println();

  // while (f.available()) {
  //     client.write(f.read());
  // }

  // f.close();

  // client.println("HTTP/1.1 200 OK");
  // client.println("Content-type:text/html");
  // client.println();

  // client.println("<!DOCTYPE html><html>");
  // client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");

  // client.println("<style>");
  // client.println("body{font-family:Arial;text-align:center;margin-top:25px;}");
  // client.println(".container{display:flex;justify-content:center;gap:25px;flex-wrap:wrap;}");
  // client.println(".box{border:1px solid #999;border-radius:12px;padding:18px;width:260px;}");
  // client.println("button{font-size:24px;padding:18px;margin:8px;width:210px;}");
  // client.println("</style></head>");

  // client.println("<body>");
  // client.println("<h1>L-ONE Robot Test</h1>");

  // client.println("<div class='container'>");

  // client.println("<div class='box'>");
  // client.println("<h2>Base Z</h2>");
  // client.println("<p><a href='/BASE_P'><button>+</button></a></p>");
  // client.println("<p><a href='/BASE_STOP'><button>STOP</button></a></p>");
  // client.println("<p><a href='/BASE_M'><button>-</button></a></p>");
  // client.println("</div>");

  // client.println("<div class='box'>");
  // client.println("<h2>Servo 1</h2>");
  // client.println("<p><a href='/S1A'><button>AVANTI</button></a></p>");
  // client.println("<p><a href='/S1S'><button>STOP</button></a></p>");
  // client.println("<p><a href='/S1D'><button>INDIETRO</button></a></p>");
  // client.println("</div>");

  // client.println("<div class='box'>");
  // client.println("<h2>Servo 2</h2>");
  // client.println("<p><a href='/S2A'><button>AVANTI</button></a></p>");
  // client.println("<p><a href='/S2S'><button>STOP</button></a></p>");
  // client.println("<p><a href='/S2D'><button>INDIETRO</button></a></p>");
  // client.println("</div>");

  // client.println("<div class='box'>");
  // client.println("<h2>End Effector</h2>");
  // client.println("<p><a href='/OPEN'><button>APRI</button></a></p>");
  // client.println("<p><a href='/CLOSE'><button>CHIUDI</button></a></p>");
  // client.println("</div>");

  // client.println("</div>");
  // client.println("</body></html>");

  // client.println();
}

void sendText(WiFiClient &client, String msg) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println();
  client.println(msg);
  client.stop();
}

void serveFile(WiFiClient &client, const char* path, const char* type) {
  File f = LittleFS.open(path, "r");

  if (!f) {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain");
    client.println();
    client.println("File non trovato");
    client.stop();
    return;
  }

  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(type);
  client.println();

  while (f.available()) {
    client.write(f.read());
  }

  f.close();
  client.stop();
}
