/*
 * GarageServer
 * - API Arduino 1.5.x
 * - modified from WebServerPost
 */

#include <Arduino.h>
#include <SPI.h>
#include <UIPEthernet.h>
#include <TextFinder.h>
#include "WebServer.h"
#include "GarageServer.h"

#include "Relay.h"

// **** ETHERNET SETTING ****
//#include "peterethernet.h"

const byte mac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const IPAddress ip(192, 168, 1, 9);
char buffer[8]; // make this buffer big enough to hold requested page names

EthernetServer server(80);



void setup()
{
  Serial.begin(9600);
  Serial.println("Setup ");

  Ethernet.begin(mac, ip);
  server.begin();
  delay(3000);

  Serial.println(Ethernet.localIP());
}


void loop()
{
  // listen for incoming Ethernet connections:
  listenForEthernetClients();
}


/* ------- */

void listenForEthernetClients()
{
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("Got a client");

    TextFinder finder(client);
    int type = 0;
    while (client.connected())
    {
      if (client.available())
      {

        // GET, POST, or HEAD
        if (finder.getString("", "/", buffer, sizeof(buffer)))
        {
          if (strcmp(buffer, "POST ") == 0)
          {
            finder.find("\n\r"); // skip to the body

            // find string starting with "pin", stop on first blank line
            // the POST parameters expected in the form pinDx=Y
            // where x is the pin number and Y is 0 for LOW and 1 for HIGH
            while (finder.findUntil("pinD", "\n\r"))
            {
              int pin = finder.getValue(); // the pin number
              int val = finder.getValue(); // 0 or 1

              pinMode(pin, OUTPUT);
              digitalWrite(pin, val);
//              mom_on (pin);
            }
          }
          sendHeader(client, "Post example");

          //create HTML buttons to control pin 4
          client.println("<h2>Click buttons to turn pin 4 on or off</h2>");

          client.print("<form action='/' method='POST'><p><input type='hidden' name='pinD4'");
          client.println(" value='0'><input type='submit' value='Off'/></form>");

          client.print("<form action='/' method='POST'><p><input type='hidden' name='pinD4'");
          client.print(" value='1'><input type='submit' value='On'/></form>");

          client.print("<form action='/' method='POST'><p><input type='hidden' name='pinD4'");
          client.print(" value='9'><input type='submit' value='Mom_On'/></form>");

          client.println("</body></html>");


          client.stop();
        }
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}

void sendHeader(EthernetClient client, char *title)
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.print("<html><head><title>");
  client.print(title);
  client.println("</title><body>");
}



/* ------ */

/* all URLs on this server will start with /buzz because of how we
 * define the PREFIX value.  We also will listen on port 80, the
 * standard HTTP service port */
#define PREFIX "/buzz"
WebServer webserver(PREFIX, 80);

/* the piezo speaker on the Danger Shield is on PWM output pin #3 */
#define BUZZER_PIN 3

/* this is the number of microseconds to wait after turning the
 * speaker on before turning it off. */
int buzzDelay = 0;

/* toggle is used to only turn on the speaker every other loop
iteration. */
char toggle = 0;

/* This command is set as the default command for the server.  It
 * handles both GET and POST requests.  For a GET, it returns a simple
 * page with some buttons.  For a POST, it saves the value posted to
 * the buzzDelay variable, affecting the output of the speaker */
void serverCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those
       * buffers. */
      repeat = server.readPOSTparam(name, 16, value, 16);

      /* this is a standard string comparison function.  It returns 0
       * when there's an exact match.  We're looking for a parameter
       * named "buzz" here. */
      if (strcmp(name, "buzz") == 0)
      {
  /* use the STRing TO Unsigned Long function to turn the string
   * version of the delay number into our integer buzzDelay
   * variable */
        buzzDelay = strtoul(value, NULL, 10);
      }
    } while (repeat);

    // after procesing the POST data, tell the web browser to reload
    // the page using a GET method.
    server.httpSeeOther(PREFIX);
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" */
  server.httpSuccess();

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {
    /* store the HTML in program memory using the P macro */
    P(message) =
"<!DOCTYPE html><html><head>"
  "<title>Webduino AJAX Buzzer Example</title>"
  "<link href='http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/themes/base/jquery-ui.css' rel=stylesheet />"
  //"<meta http-equiv='Content-Script-Type' content='text/javascript'>"
  "<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.4/jquery.min.js'></script>"
  "<script src='http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/jquery-ui.min.js'></script>"
  "<style> #slider { margin: 10px; } </style>"
  "<script>"
    "function changeBuzz(event, ui) { $('#indicator').text(ui.value); $.post('/buzz', { buzz: ui.value } ); }"
    "$(document).ready(function(){ $('#slider').slider({min: 0, max:8000, change:changeBuzz}); });"
  "</script>"
"</head>"
"<body style='font-size:62.5%;'>"
  "<h1>Test the Buzzer!</h1>"
  "<div id=slider></div>"
  "<p id=indicator>0</p>"
"</body>"
"</html>";

    server.printP(message);
  }
}

