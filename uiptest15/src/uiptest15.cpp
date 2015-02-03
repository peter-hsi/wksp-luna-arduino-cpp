/*
 * from http://www.tweaking4all.com/hardware/arduino/arduino-enc28j60-ethernet/
 * NOTE:
 *  Vcc 3.3v
 *  Pins are mapped as follows:
 *  SS    10 (not 8)
 *  MOSI  11
 *  MISO  12
 *  SCK   13
 */

#include <Arduino.h>
#include <UIPEthernet.h> // Used for Ethernet

// **** ETHERNET SETTING ****
byte mac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31  };
IPAddress ip(192, 168, 1, 9);
EthernetServer server(80);

void setup() {
  Serial.begin(9600);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client)
  {
    Serial.println("-> New Connection");

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          client.println("<html><title>Hello World!</title><body><h3>Hello World!</h3></body>");
          break;
        }

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
    Serial.println("   Disconnected\n");
  }
}
