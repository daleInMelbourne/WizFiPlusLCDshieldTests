/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 
 */

/* Hardware pin allocation for Resets, CS' etc
//
// WizFi Shield Configuration
//
// WizFi SPI Bridge      2
// MAC ID                3
// SDCard                4
// Associate(active Low) 5 (GPIO28)
// WiFi Comms OK(low)    6 (GPIO31)
// Reset is hacked onto pin A1
//
// LCD Shield Configuration
//
// LCD SPI Bridge        A3
// MAC ID                4 (Used on WizFi as SD Card CS)
// SDCard                3 (Used on WizFi as MAC ID CS)
// Reset                 7
//
*/


#include <SPI.h>

// Need to include GorillaBuilderz WizFi Ethernet libraries
#include <Transport.h>
#include <WizFi210.h>
#include <GBEthernet.h>
#include <GBStatus.h>
#include <GB4DLcdDriver.h>
#include <GBIMAC.h>

GB4DSPILcdDriver lcd(A3);
GBIMAC macID(3);
byte macAddress[MAC_LENGTH],IPconnected = 0;
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(74,125,237,114); // Google

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  
    // start the serial library:
  Serial.begin(115200);

//    delay(3000);
  lcd.initialise();
  //lcd.version(true);
delay(1000);

  // Different ways to set the background color
  delay(1000);
  lcd.setBackgroundColor(SGC_COLORS.BLACK);
  lcd.clearScreen();
  lcd.drawString(0,0, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "GorillaBuilderz!!!");
  lcd.drawString(0,1, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "LCD+WizFi Sanity Test");  
  // Fonts, shapes and colors
  lcd.drawString(1,2, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE,"SMALL FONT - WHITE");    
  lcd.drawString(1,3, SGC_FONT_SIZE.MEDIUM, SGC_COLORS.WHITE,"MEDIUM FONT - WHITE");    
  lcd.drawString(1,4, SGC_FONT_SIZE.LARGE, SGC_COLORS.WHITE,"LARGE FONT - WHITE");    

  lcd.drawString(1,9, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "Establishing WiFi connection,");
  lcd.drawString(1,10, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "  please wait..."); 
  lcd.drawCircle(120, 150, 20,SGC_COLORS.YELLOW);


  Serial.println("");
  Serial.println("GB IMAC: Reading...");

  macID.read(macAddress);
//  Serial.print("GB IMAC: ", macID.format(macAddress));
int i;
for (i = 0; i < 6; i = i + 1) {
  Serial.print(macAddress[i],HEX);
}
Serial.println("");

  Serial.println("GorillaBuilderz Arduino WebClient for WiFi Shield");
  Serial.println("Initialising modem and ataching to network...");
  
  // Set the network name
  Ethernet.ssid("BatPhone");
  // Initialise secure network passphrase
  Ethernet.passphrase("password");

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  lcd.setBackgroundColor(SGC_COLORS.BLACK);
//  lcd.drawString(0,11, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "WizFI & LCD Shield test complete");  

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    if(!IPconnected){
      IPconnected=1;
      lcd.clearScreen(); 
      lcd.drawString(7,11, SGC_FONT_SIZE.MEDIUM, SGC_COLORS.WHITE, "WizFI Connected!");  
      lcd.drawCircle(120, 150, 20,SGC_COLORS.GREEN);
    }
  }
//if(  !digitalRead(6)  )
  //  Serial.println("Wif");

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    lcd.clearScreen(); 
    lcd.drawString(5,11, SGC_FONT_SIZE.MEDIUM, SGC_COLORS.WHITE, "WizFI Disconnecting!"); 
    lcd.drawCircle(120, 150, 20,SGC_COLORS.RED);
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}

