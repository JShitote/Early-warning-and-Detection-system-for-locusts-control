
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WaziDev.h>
#include <DHT.h>
#include <MQ2.h>
#include <Wire.h>

#define DHTPIN 2        // what pin on the arduino is the DHT data line connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
void displayInfo();
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
float la = 0;
float lo = 0;

int phPin = 0; // the cell and 10K pulldown are connected to A0
int ph; // the analog reading from the analog resistor divider

int slPin = A2;
int sHum = -1;

int Anlg_Inp = A5;
int lpg, co, smoke;
MQ2 mq2(Anlg_Inp);

// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

int VaneValue;// raw analog value from wind vane
int Direction;// translated 0 - 360 direction
int CalDirection;// converted value with offset applied
int LastValue;
#define Offset 0;

// new WaziDev with node address = 8
WaziDev wazidev("MyDevice", 8);

void setup() {
  Serial.begin(38400);
  wazidev.setup();

  Serial.println("Init DHT11");
  dht.begin();
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  ss.begin(GPSBaud);
  Serial.print("Init TinyGPS++");
  Serial.println(TinyGPSPlus::libraryVersion());

  mq2.begin();
  analogReference(EXTERNAL);

  Serial.println("Vane Value");
  LastValue = 1;

  delay(2000);
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }


  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }

  ph = analogRead(phPin);
  Serial.print("A= ");
  Serial.print(ph); // the raw analog reading
  delay(2000);

  sHum = analogRead(slPin);
  Serial.println(sHum);
  delay(100);

  float* values = mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
  Serial.print(lpg);
  Serial.print(co);
  Serial.print(smoke);
  delay(1000);
  
  // read the sensor on analog A1:
  int sensorReading = analogRead(A1);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // range value:
 /* switch (range) {
    case 0:    // Sensor getting wet
      Serial.println("Flood");
      break;
    case 1:    // Sensor getting wet
      Serial.println("Rain Warning");
      break;
    case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
      Serial.println("Not Raining");
      break;
  }*/
  delay(1);  // delay between reads
  VaneValue = analogRead(A4);
  Direction = map(VaneValue, 0, 1023, 0, 360);
  CalDirection = Direction + Offset;

  if (CalDirection > 360)
    CalDirection = CalDirection - 360;

  if (CalDirection < 0)
    CalDirection = CalDirection + 360;

  // Only update the display if change greater than 2 degrees.
  if (abs(CalDirection - LastValue) > 5)
  {
    Serial.print(VaneValue); Serial.print("\t\t");
    Serial.print(CalDirection); Serial.print("\t\t");
 //   getHeading(CalDirection);
    LastValue = CalDirection;
  }

  WaziDev::SensorVal fields[6] = {{"TC", t}, {"HUM", h}, {"LA", la}, {"LO", lo}, {"PH", ph}, {"sHUM", sHum}};
  //Send temperature as sensor "TC"
  wazidev.sendSensorValues(fields, 6);

  char tf[10]; ftoa(tf, t, 2);
  char hf[10]; ftoa(hf, h, 2);
  
  wazidev.writeSerial("%s %% %s °C\n", hf, tf);
  Serial.flush();
  // Wait a few seconds between measurements. The DHT11 should not be read at a higher frequency of
  // about once every 2 seconds. So we add a 3 second delay to cover this.
  delay(3000);
}

void displayInfo()
{
  if (gps.location.isValid())
  {
     la = (gps.location.lat(), 6);
     lo = (gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}

// Converts compass direction to heading
/*void getHeading(int direction) {
  if (direction < 22)
    Serial.println("N");
  else if (direction < 67)
    Serial.println("NE");
  else if (direction < 112)
    Serial.println("E");
  else if (direction < 157)
    Serial.println("SE");
  else if (direction < 212)
    Serial.println("S");
  else if (direction < 247)
    Serial.println("SW");
  else if (direction < 292)
    Serial.println("W");
  else if (direction < 337)
    Serial.println("NW");
  else
    Serial.println("N");
}*/
