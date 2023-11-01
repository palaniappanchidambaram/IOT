 #include <ESP8266WiFi.h>
const char* ssid = "Pavankumar"; //ssid of your wifi  // Mavayya-5G
const char* password = "12345678"; //password of your wifi
WiFiServer server(80);
////////////////////////////////////
#include <Arduino_JSON.h>
String inputData = "";
boolean data_complete = false;
String vala;
String valb;
String valc;
String vald;
/////////////////////////////////////

void setup()

{
 Serial.begin(115200);
 inputData.reserve(200);
 Serial.println("Hello");
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password); //connecting to wifi
 while (WiFi.status() != WL_CONNECTED)// while wifi not connected
 {
   delay(500);
   Serial.print("."); //print "...."
 }
 Serial.println("");
 Serial.println("WiFi connected");
 server.begin();
 Serial.println("Server started");
 Serial.println(WiFi.localIP());  // Print the IP address
}
void loop()
{
 while(Serial.available() > 0)
 {
  char inChar = Serial.read();
  if( inChar == '\r')
  {
   inputData = "";
  }
  else if(inChar == '\n')
  {
   data_complete = true;
  }
  else
  {
   inputData+=inChar;
  }
 }

 if(data_complete)
 {
  data_complete = false;
  Serial.println(inputData);
  demoParse();
 }
 //int a=vala.toInt();

 WiFiClient client = server.available(); // Check if a client has connected
/* if (!client)
 {
  return;
 }   */ 
 String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>..........</title> <style>";
 s += "a:link {background-color: RED;text-decoration: none;}";
 s += "table, th, td </style> </head> <body> <h1  style=";
 s += "font-size:250%;";
 s += " ALIGN=CENTER> Dustbin data</h1>";
 s += "<p ALIGN=CENTER style=""font-size:200%;""";
 s += "> <b> Location -001</b></p> <table ALIGN=CENTER style=";
 s += "width:10%";
 s += "> <tr> <th>Level : </th>";
 s += "<td ALIGN=CENTER >";
 s += vala;
 //s += "</td> </tr> <tr> <th>Tds Value : </th> <td ALIGN=CENTER >";
 //s += valb;
 //s += "</td> </tr> <tr>  <th>Water Level</th> <td ALIGN=CENTER >";
 //s += valc;
 //s += "</td></tr> <tr> <th>Water intake</th> <td ALIGN=CENTER >";
 //s += vald;
 s += "</td>  </tr> </table> ";
 s += "</body> </html>";
 client.print(s); // all the values are send to the webpage
 delay(100);
}
void demoParse() 
{
 Serial.println("parse");
 Serial.println(vala);
 Serial.println("=====");
 JSONVar myObject = JSON.parse(inputData);    
 if (JSON.typeof(myObject) == "undefined") 
 {
  Serial.println("Parsing input failed!");
  return;
 }
 Serial.print("JSON.typeof(myObject) = ");
 Serial.println(JSON.typeof(myObject)); // prints: object
 // myObject.hasOwnProperty(key) checks if the object contains an entry for key
 if (myObject.hasOwnProperty("anloga")) {
 Serial.print("myObject[\"anloga\"] = ");
 vala = (const char*) myObject["anloga"];//to get value in  vala
 Serial.println(vala);
 Serial.println((const char*) myObject["anloga"]);
}
 if (myObject.hasOwnProperty("anlogb")) {
   Serial.print("myObject[\"anlogb\"] = ");
   valb = (const char*) myObject["anlogb"];
   Serial.println(valb); 
   Serial.println((const char*) myObject["anlogb"]);
 }
 if (myObject.hasOwnProperty("anlogc")) {
   Serial.print("myObject[\"anlogc\"] = ");
   valc = (const char*) myObject["anlogc"];
   Serial.println(valc); 
   Serial.println((const char*) myObject["anlogc"]);
 }
 if (myObject.hasOwnProperty("anlogd")) {
   Serial.print("myObject[\"anlogd\"] = ");
   vald = (const char*) myObject["anlogd"];
   Serial.println(vald); 
   Serial.println((const char*) myObject["anlogd"]);
 }
 // JSON vars can be printed using print or println
 Serial.print("myObject = ");
 Serial.println(myObject);
 Serial.println();
}
