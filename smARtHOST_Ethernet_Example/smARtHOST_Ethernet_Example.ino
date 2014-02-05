#include "etherShield.h"
#include "ETHER_28J60.h"

static uint8_t mac[6] = {0x23, 0x23, 0x23, 0x23, 0x23, 0x23};   //This just needs to be unique for your network, 
                                                                //So unless you have more than one of these boards
                                                                //Connected, you should be fine with this value.
                                                           
static uint8_t ip[4] = {192, 168, 0, 23};                       //The IP address for your board. Check your home hub
                                                                //To find an IP address not in use and pick that
                                                                //This or 10.0.0.15 are likely formats for an address
                                                                //That will work.

static uint16_t port = 80;                                      //Use port 80 - the standard for HTTP

ETHER_28J60 ethernet;

int photocellPin = A0;     // the cell and 10K pulldown are connected to a0
int photocellReading = 0;     // the analog reading from the analog resistor divider

int tempPin = A1;
int tempVal = 0;

char* Val = " ";
 
void setup() {
  
  //Serial.begin(9600);
  ethernet.setup(mac, ip, port);  
 
  pinMode(photocellPin, INPUT);
  pinMode(tempPin, INPUT);
}
 
void loop() {
  
if (ethernet.serviceRequest())
{   
  photocellReading = analogRead(photocellPin); 
  tempVal = analogRead(tempPin); 
  
  float voltage = tempVal * 5.0;
  voltage /= 1024;
  
  float tempC = (voltage - 0.5) * 100;
  
  float tempF = (tempC * 9.0 / 5.0) + 32;
  
  if (photocellReading >= 800)
  {
    Val = "Office Lights On";
  }
  else
  {
    Val = "Office Lights Off"; 
  }
  
  ethernet.print("<CENTER>");
  ethernet.print("<H1>smARtMAKER LAB Office Data</H1>");
  ethernet.print("<head><meta http-equiv='refresh' content='5'><head>");
  ethernet.print("<b>");
  ethernet.print("Light Value -       ");
  ethernet.print(photocellReading);     // the raw analog reading
  ethernet.print("<br>");
  ethernet.print(Val);
  ethernet.print("<br><br>");
  ethernet.print("Temperature In the Office - ");
  ethernet.print(tempF);     // the raw analog reading
  ethernet.print("&#176");
  ethernet.print("F");
  ethernet.print("</b>");
  ethernet.print("</CENTER>");
  
  ethernet.respond();
} 
  delay(100);
}

