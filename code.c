// Basic demo for accelerometer readings from Adafruit MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN_l    6
#define LED_PIN_r    7
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  4

// Declare our NeoPixel strip object:
Adafruit_NeoPixel stripl(LED_COUNT, LED_PIN_l, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripr(LED_COUNT, LED_PIN_r, NEO_GRB + NEO_KHZ800);
const int rs = 8, en = 9, d4 = 10, d5 =11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Adafruit_MPU6050 mpu;
int fs1=A2;
int fs2=A3;
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("Adafruit MPU6050 test!");
  lcd.begin(16, 2);
  lcd.print("   WELCOME");
  stripl.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  stripl.show();            // Turn OFF all pixels ASAP
  stripl.setBrightness(50);
    stripr.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  stripr.show();            // Turn OFF all pixels ASAP
  stripr.setBrightness(50);
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
  Serial.println("");
  delay(100);
  stripl.setPixelColor(0, stripl.Color(50,50,   50));         //  Set pixel's color (in RAM)
  stripl.setPixelColor(1, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(2, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(3, stripl.Color(50,50,   50));
  stripr.setPixelColor(0, stripr.Color(50,50,   50));         //  Set pixel's color (in RAM)
  stripr.setPixelColor(1, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(2, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(3, stripr.Color(50,50,   50));
  stripl.show();
  delay(200);
  stripr.show();
}
void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  Serial.print("   Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.print(" rad/s");
  Serial.print("   Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" degC");
  int f1val=analogRead(fs1);
  int f2val=analogRead(fs2);
  Serial.print("   FS1: ");
  Serial.print(f1val);
  Serial.print("  FS2: ");  
  Serial.println(f2val);
  delay(5);
  lcd.clear();
  lcd.print("X"+String(int(a.acceleration.x)) + " Y"+String(int(a.acceleration.y)) + "    Z"+String(int(a.acceleration.z)));
  lcd.setCursor(0,1);
  lcd.print("LF:"+String(f1val) + " RF"+String(f2val));
  if(f1val>10 || f2val>10)
  {
  if(f1val>10)
  {
  if(f1val>750)
  {
  stripl.setPixelColor(0, stripl.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripl.setPixelColor(1, stripl.Color(255,0,   0)); 
  stripl.setPixelColor(2, stripl.Color(255,0,   0)); 
  stripl.setPixelColor(3, stripl.Color(255,0,   0)); 
  }
    else if(f1val>500)
  {
  stripl.setPixelColor(1, stripl.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripl.setPixelColor(0, stripl.Color(255,0,   0)); 
  stripl.setPixelColor(2, stripl.Color(255,0,   0)); 
  stripl.setPixelColor(3, stripl.Color(50,50,   50)); 
  }
    else if(f1val>250)
  {
  stripl.setPixelColor(0, stripl.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripl.setPixelColor(1, stripl.Color(255,0,   0)); 
  stripl.setPixelColor(2, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(3, stripl.Color(50,50,   50)); 
  }
else if(f1val>10)
  {
  stripl.setPixelColor(0, stripl.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripl.setPixelColor(1, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(2, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(3, stripl.Color(50,50,   50)); 
  }
   stripl.show();
   delay(200);
  }
 if(f2val>10){
 if(f2val>750) {
    Serial.println("R4");
  stripr.setPixelColor(0, stripr.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripr.setPixelColor(1, stripr.Color(255,0,   0)); 
  stripr.setPixelColor(2, stripr.Color(255,0,   0)); 
  stripr.setPixelColor(3, stripr.Color(255,0,   0)); 
  }
 else if(f2val>500)
  {
    Serial.println("R3");
  stripr.setPixelColor(1, stripr.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripr.setPixelColor(0, stripr.Color(255,0,   0)); 
  stripr.setPixelColor(2, stripr.Color(255,0,   0)); 
  stripr.setPixelColor(3, stripr.Color(50,50,   50)); 
  }    else if(f2val>250)
  {
    Serial.println("R2");
  stripr.setPixelColor(0, stripr.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripr.setPixelColor(1, stripr.Color(255,0,   0)); 
  stripr.setPixelColor(2, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(3, stripr.Color(50,50,   50)); 
  }
    else if(f2val>10)
  {
    Serial.println("R1");
  stripr.setPixelColor(0, stripr.Color(255,0,   0));         //  Set pixel's color (in RAM)
  stripr.setPixelColor(1, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(2, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(3, stripr.Color(50,50,   50)); 
  }
  stripr.show();
  }
  delay(2000);

   stripl.setPixelColor(0, stripl.Color(50,50,   50));         //  Set pixel's color (in RAM)
  stripl.setPixelColor(1, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(2, stripl.Color(50,50,   50)); 
  stripl.setPixelColor(3, stripl.Color(50,50,   50));
  stripr.setPixelColor(0, stripr.Color(50,50,   50));         //  Set pixel's color (in RAM)
  stripr.setPixelColor(1, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(2, stripr.Color(50,50,   50)); 
  stripr.setPixelColor(3, stripr.Color(50,50,   50));
  stripl.show();
  delay(200);
  stripr.show();
}
}
