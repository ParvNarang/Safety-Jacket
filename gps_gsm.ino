/* Owner-
    Parv Narang
*/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial portOne(4,5);//RX  TX GPS
SoftwareSerial portTwo(2,3);//RX  TX GSM
TinyGPSPlus gps;
const int key      = 6;
const int buzzer   = 9;
double lat_val, lng_val, alt_m_val;
volatile float minutes, seconds;
volatile int degree, secs, mins;
char latitude[10],longitude[10],total_loc[22];
bool loc_valid, alt_valid, send_flag=0;

void setup() 
{   Serial.begin(9600);portOne.begin(9600);portTwo.begin(9600);
    pinMode(key,INPUT_PULLUP);pinMode(buzzer,OUTPUT);
    digitalWrite(buzzer,LOW);gsm_init();
    Serial.println("GPS Initializing");
    Serial.print("  No GPS Range  ");
    Serial.println(" GPS Range Found ");
    Serial.println("  GPS is Ready  ");           
}

void loop() 
{   smartDelay(1000);
    unsigned long start;
    lat_val = gps.location.lat(); 
    loc_valid = gps.location.isValid(); 
    lng_val = gps.location.lng();
    alt_m_val = gps.altitude.meters(); 
    alt_valid = gps.altitude.isValid(); 
    if (!loc_valid)
    {   Serial.print("Latitude : ");
        Serial.println("*****");
        Serial.print("Longitude : ");
        Serial.println("*****");
        delay(4000);
    }
    else
    {   Serial.println("GPS READING: ");
        DegMinSec(lat_val);
        Serial.print("Latitude in Decimal Degrees : ");
        Serial.println(lat_val, 6);dtostrf(lat_val,2,6,latitude);
        DegMinSec(lng_val); 
        Serial.print("Longitude in Decimal Degrees : ");
        Serial.println(lng_val, 6);dtostrf(lng_val,2,6,longitude);
        delay(4000);
    }
    if(digitalRead(key) == LOW)
    {   digitalWrite(buzzer,HIGH);delay(200);digitalWrite(buzzer,LOW);SendMessage();
        while(digitalRead(key)==LOW)delay(100);        
    }
}
static void smartDelay(unsigned long ms)
{   unsigned long start = millis();
    do
    {   portOne.listen();
        while (portOne.available()) 
        gps.encode(portOne.read());
        if(digitalRead(key) == LOW){ms=0;}
    }
    while (millis() - start < ms);
}
void DegMinSec( double tot_val)
{   degree = (int)tot_val;
    minutes = tot_val - degree;
    seconds = 60 * minutes;
    minutes = (int)seconds;
    mins = (int)minutes;
    seconds = seconds - minutes;
    seconds = 60 * seconds;
    secs = (int)seconds;
}
/////////////////////////////////////////////////////////////////////
void gsm_init()
{   boolean at_flag=1,echo_flag=1,net_flag=1;
    Serial.println("GSM MODULE INIT.");
    Serial.println(" AT =           ");
    portTwo.listen();
    while(at_flag)
    {   portTwo.println("AT");Serial.println("AT");
        while(portTwo.available()>0)
        {   if(portTwo.find("OK"))at_flag=0,Serial.println("OK");
        }delay(2000);
    }
    Serial.println("ATE1 =          ");
    while(echo_flag)
    {   portTwo.println("ATE1");
        while(portTwo.available()>0)
        {   if(portTwo.find("OK"))echo_flag=0,Serial.println("OK");
        }delay(2000);
    } 
}
void SendMessage()
{   Serial.println("MESSAGE SEND....");
    Serial.println("Ph.............."); //add the number
    portTwo.listen();
    Serial.println("AT+CMGF=1");
    portTwo.println("AT+CMGF=1");delay(1000);
    Serial.println("AT+CMGS=\"+91....\"\r");       //add the number
    portTwo.println("AT+CMGS=\"+91....\"\r");delay(1000);    //add the number
    Serial.println("****** EMERGENCY ******");
    portTwo.println("****** EMERGENCY ******");delay(100);
    Serial.println("Please check the location");
    portTwo.println("Please check the location");delay(100);
    if(loc_valid)
    {   for(int g=0;g<9;g++){total_loc[g]=latitude[g];}total_loc[9]=',';
        for(int h=0;h<10;h++){total_loc[10+h]=longitude[h];}
        Serial.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
        Serial.print(total_loc);delay(100);        
        portTwo.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
        portTwo.print(total_loc);delay(100);        
    }
    else
    {   Serial.print("Latitude:") ;Serial.println("---------");
        Serial.print("Longitude:");Serial.println("---------");
        portTwo.print("Latitude:") ;portTwo.println("---------");delay(100);
        portTwo.print("Longitude:");portTwo.println("---------");delay(100);
    }
    //////////////////////////////////////////////////////////////////////////////////////
    delay(100);portTwo.println((char)26);delay(100);send_flag=1;
    Serial.println("    SEND OK  OUT   ");
}
