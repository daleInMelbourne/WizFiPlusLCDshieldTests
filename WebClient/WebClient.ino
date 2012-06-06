/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 
 */

#include <SPI.h>

// Need to include GorillaBuilderz WizFi Ethernet libraries
#include <Transport.h>
#include <WizFi210.h>
#include <GBEthernet.h>
#include <GBStatus.h>
#include <GB4DLcdDriver.h>

GB4DSPILcdDriver lcd(A3);

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
  
  
    delay(3000);
  lcd.initialise();
  lcd.version(true);

  // Different ways to set the background color
  delay(1000);
  lcd.setBackgroundColor(SGC_COLORS.WHITE);
  lcd.clearScreen();
  
  delay(1000);
  lcd.replaceBackgroundColor(SGC_COLORS.RED);
  
  delay(1000);    
  lcd.setBackgroundColor(SGC_COLORS.GREEN);
  lcd.clearScreen();  
  delay(1000);    
  lcd.setBackgroundColor(SGC_COLORS.BLUE);
  lcd.clearScreen();  
  delay(1000);    
  lcd.setBackgroundColor(SGC_COLORS.BLACK);
  lcd.clearScreen();  
  
  lcd.clearScreen();
  lcd.drawString(0,0, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "GorillaBuilderz!!!");
  lcd.drawString(0,1, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "4D LCD Shield 1");  

  // Fonts, shapes and colors
  lcd.drawString(1,3, SGC_FONT_SIZE.SMALL, SGC_COLORS.WHITE, "SMALL - WHITE");    
  lcd.drawCircle(100, 100, 20, SGC_COLORS.WHITE);
  lcd.drawPixel(150, 250, SGC_COLORS.WHITE);
  
  lcd.drawString(2,4, SGC_FONT_SIZE.MEDIUM, SGC_COLORS.RED, "MEDIUM - RED");    
  lcd.drawTriangle(50, 150, 200, 150, 100, 200, SGC_COLORS.RED);  
  lcd.drawRectangle(150, 5, 200, 50, SGC_COLORS.RED);  

  lcd.drawString(3,4, SGC_FONT_SIZE.LARGE, SGC_COLORS.GREEN, "LARGE - GREEN");  
  lcd.drawLine(20, 200, 50, 250, SGC_COLORS.GREEN);

  lcd.drawString(4,4, SGC_FONT_SIZE.LARGEST, SGC_COLORS.BLUE, "LARGETST - BLUE!");  

  lcd.drawElipse(200, 250, 15, 30, SGC_COLORS.BLUE);    

  lcd.drawString(0,38, SGC_FONT_SIZE.SMALL, SGC_COLORS.RED, "Bye Bye!");  

  lcd.drawGraphicsString(0, 100, SGC_FONT_SIZE.SMALL, SGC_COLORS.RED, "Graphics String!!!");     

  
  // start the serial library:
  Serial.begin(115200);

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
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
//if(  !digitalRead(6)  )
  //  Serial.println("Wif");

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}

