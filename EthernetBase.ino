#include <SPI.h>
#include <Ethernet.h>

char programName[] = "ETHERNET BASE";

//////////////////////////////////////////////// ETHERNET DECLARATIONS //////////////////////////////////////////////////////////////////////////////////////////
byte mac[] = {0xA8, 0x61, 0x0A, 0xAE, 0x6C, 0xBA  };       ////////////////////////////////////////////////////////////////////////////
IPAddress ip(192,168,68,57);                                            // change to your Arduino Ethernet network settings/////////////////////////
IPAddress server(192,168,68,65);                                        // change to your HMC network settings
char serverName[] = "192.168.68.65";                                    // change to your HMC network settings
int serverPort = 14999;                                                 // change to your HMC network settings
EthernetServer Server(80);                                 ////////////////////////////////////////////////////////////////////////////                                     
EthernetClient client;                                                  // name HMC connection as 'client' for later calling                                        
int totalCount = 0;
char pageAdd[64];
String readString;

/////////////////////////////////////////////// GLOBAL PROP DECLARATIONS ///////////////////////////////////////////////////////////////////////////////////////////////
char propALLResetkeyWord[] = "resetAllprops";                      //////// INSERT KEYWORD FROM HMC FOR RESETTING ALL PROPS  ////////

/////////////////////////////////////////////// PROP ONE DECLARATIONS  ////////////////////////////////////////////
const int buttonPin1 = 11;                                       ///////// INPUT TO PROP /////////////////////   
const int buttonPin2 = 12;                                       ///////// INPUT TO PROP /////////////////////  
bool button_1_state = false;
bool button_2_state = false; 
const int propOneOutput=6;                                       ///////// OUTPUT FROM PROP /////////////////////  
bool REALpropOneStatus = false;
bool HMCpropOneStatus = false;
int propOneSystem = 0;
char propOneWinkeyWord[] = "/" "WinPropOne";                           //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////  MUST INCLUDE '/' BEFORE THE KEYWORD AS THIS IS BEING SENT 'TO' HMC
char propOneResetkeyWord[] = "resetPropOne";                       //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////DOES NOT REQUIRE '/' AS ARDUINO IS RECEIVING THIS KEYWORD 'FROM' HMC

//////////////////////////////////////////////////////////// PROP TWO DECLARATIONS ////////////////////////////////////////////
bool REALpropTwoStatus = false;
bool HMCpropTwoStatus = false;
int propTwoSystem = 0;
char propTwoWinkeyWord[] = "/" "WinPropTwo";                           //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////  MUST INCLUDE '/' BEFORE THE KEYWORD AS THIS IS BEING SENT 'TO' HMC
char propTwoResetkeyWord[] = "resetPropTwo";                       //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////   DOES NOT REQUIRE '/' AS ARDUINO IS RECEIVING THIS KEYWORD 'FROM' HMC

/////////////////////////////////////////////// PROP THREE DECLARATIONS ////////////////////////////////////////////
bool REALpropThreeStatus = false;
bool HMCpropThreeStatus = false;
int propThreeSystem = 0;
char propThreeWinkeyWord[] = "/" "WinPropThree";                          //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  /////////  MUST INCLUDE '/' BEFORE THE KEYWORD AS THIS IS BEING SENT 'TO' HMC
char propThreeResetkeyWord[] = "resetPropThree";                      //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////DOES NOT REQUIRE '/' AS ARDUINO IS RECEIVING THIS KEYWORD 'FROM' HMC

/////////////////////////////////////////////// PROP FOUR DECLARATIONS ////////////////////////////////////////////
bool REALpropFourStatus = false;
bool HMCpropFourStatus = false;
int propFourSystem = 0;
char propFourWinkeyWord[] = "/" "WinPropFour";                            //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  /////////  MUST INCLUDE '/' BEFORE THE KEYWORD AS THIS IS BEING SENT 'TO' HMC
char propFourResetkeyWord[] = "resetPropFour";                        //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////DOES NOT REQUIRE '/' AS ARDUINO IS RECEIVING THIS KEYWORD 'FROM' HMC

/////////////////////////////////////////////// PROP FIVE DECLARATIONS ////////////////////////////////////////////
bool REALpropFiveStatus = false;
bool HMCpropFiveStatus = false;
int propFiveSystem = 0;
char propFiveWinkeyWord[] = "/" "WinPropFive";                            //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  /////////  MUST INCLUDE '/' BEFORE THE KEYWORD AS THIS IS BEING SENT 'TO' HMC
char propFiveResetkeyWord[] = "resetPropFive";                        //////// INSERT KEYWORD FROM HMC FOR THIS PROP CALL  ////////DOES NOT REQUIRE '/' AS ARDUINO IS RECEIVING THIS KEYWORD 'FROM' HMC

void setup() 
///////////////////////////////////////////////SETUP ETHERNET AND PROPS ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
{
/////////////////SETUP ETHERNET ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
  Serial.begin(9600);                                     // startup arduino 
  pinMode(4,OUTPUT);                                      // disable SD Card Reader
  digitalWrite(4,HIGH);                                   // disable SD Card Reader
  Serial.println(programName);                            // Readout program name
  Serial.println("Starting Arduino Ethernet¦");           // Readout ethernet bootup
  Ethernet.begin(mac, ip);      // Start ethernet connection
  Serial.println(Ethernet.localIP());                     // Readout ethernet connection
  delay(2000);
  Serial.println("Arduino Ready");                        // Readout success connection
  Server.begin();                                         // Listn for inbound communications to ethernet shield
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

/////////////////SETUP PROP //////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////// PROP ONE //////////////
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(propOneOutput,OUTPUT);

///////////////// PROP TWO //////////////

///////////////// PROP THREE ////////////

///////////////// PROP FOUR /////////////

///////////////// PROP FIVE /////////////
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                
}

void loop() 
{
/////////////////////////////////////////////// RECEIVE HTTP FROM HMC //////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  EthernetClient client = Server.available();             // Start connection to HMC
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
 if (client)
  {
    while (client.connected())
    {
      if(client.available())
      {
        char c=client.read();                             //read char by char http request
        if (readString.length()<100)
          {                                               /////////////////////////////////
          readString +=c;                                 ////store characters to string///    
          Serial.print(c);                                ///////////////////////////////// 
          }                               
        if (c == '\n') 
        {  
          delay(1);
           client.stop();
////////////////////////////////////  REMOTE WIN   PROP ONE   FROM HMC  //////////////////////////////////////////////////////////
           if (readString.indexOf(propOneWinkeyWord) >0)             // update Prop declaration variables for the keyword to listen for from HMC
           {
               Serial.println("Prop One WON Remotely");          // if call matches " " then do stuff /// replace with your keywords 
               HMCpropOneStatus = true;
               propOne(); 
               delay(1000);
               propOneSystem = 1;
           }
////////////////////////////////////  REMOTE WIN   PROP TWO   FROM HMC  //////////////////////////////////////////////////////////
           if (readString.indexOf(propTwoWinkeyWord) >0)             // replace " " with your specific call from HMC
           {
               Serial.println("Prop Two WON Remotely");          // if call matches " " then do stuff /// replace with your keywords 
               HMCpropTwoStatus = true;
               propTwo(); 
               delay(1000);
               propTwoSystem = 1;
           }
////////////////////////////////////  REMOTE WIN   PROP THREE   FROM HMC  //////////////////////////////////////////////////////////
           if (readString.indexOf(propThreeWinkeyWord) >0)             // replace " " with your specific call from HMC
           {
               Serial.println("Prop Three WON Remotely");          // if call matches " " then do stuff /// replace with your keywords 
               HMCpropThreeStatus = true;
               propThree(); 
               delay(1000);
               propThreeSystem = 1;
           }           
////////////////////////////////////  REMOTE WIN   PROP FOUR   FROM HMC  //////////////////////////////////////////////////////////
           if (readString.indexOf(propFourWinkeyWord) >0)             // replace " " with your specific call from HMC
           {
               Serial.println("Prop Four WON Remotely");          // if call matches " " then do stuff /// replace with your keywords 
               HMCpropFourStatus = true;
               propFour(); 
               delay(1000);
               propFourSystem = 1;
           }
////////////////////////////////////  REMOTE WIN   PROP FIVE   FROM HMC  //////////////////////////////////////////////////////////
           if (readString.indexOf(propFiveWinkeyWord) >0)             // replace " " with your specific call from HMC
           {
               Serial.println("Prop Five WON Remotely");          // if call matches " " then do stuff /// replace with your keywords 
               HMCpropFiveStatus = true;
               propFive(); 
               delay(1000);
               propFiveSystem = 1;
           }
//////////////////////////////////// RESET PROPS KEYWORDS FROM HMC  ////  CHANGE KEYWORDS TO MATCH YOUR HMC PROGRAM CALLS  /////////////////////////////////////////////////////////// 
           
           if (readString.indexOf(propOneResetkeyWord) >0)            // replace " " with your specific call from HMC
           {
               resetPropOne();                               // call reset function at bottom of program  // use one function for all props or individually create reset functions to be called
               delay(1000);
           }
           if (readString.indexOf(propTwoResetkeyWord) >0)            // replace " " with your specific call from HMC
           {
               resetPropTwo();                               // call reset function at bottom of program  // use one function for all props or individually create reset functions to be called
               delay(1000);
           }    
           if (readString.indexOf(propThreeResetkeyWord) >0)            // replace " " with your specific call from HMC
           {
               resetPropThree();                               // call reset function at bottom of program  // use one function for all props or individually create reset functions to be called
               delay(1000);
           }
           if (readString.indexOf(propFourResetkeyWord) >0)            // replace " " with your specific call from HMC
           {
               resetPropFour();                               // call reset function at bottom of program  // use one function for all props or individually create reset functions to be called
               delay(1000);
           }    
           if (readString.indexOf(propFiveResetkeyWord) >0)            // replace " " with your specific call from HMC
           {
               resetPropFive();                               // call reset function at bottom of program  // use one function for all props or individually create reset functions to be called
               delay(1000);
           }
           if (readString.indexOf(propALLResetkeyWord) >0)            // replace " " with your specific call from HMC
           {
               resetAllProps();                               // call reset function at bottom of program  // use one function for all props or individually create reset functions to be called
               delay(1000);
           }                                 
////////////////////////////////////  CLEAR VARIABLE TO LISTEN FOR NEW KEYWORD DURING NEXT LOOP THROUGH ///////////////////////////////////////////
           readString="";                                 // clear variable "readString" for next iteration through loop to check for new HMC calls
        }
      }
    }
  }

///////////////////////////////////////////////PHYSICAL PROP EXECUTION IF NOT TRIGGERED BY HMC CALL /////////////////////////////////////////////////////////////////////////////////  
  if (propOneSystem == 0)
  {
    propOne();
  }

    if (propTwoSystem == 0)
  {
    propTwo();
  }

    if (propThreeSystem == 0)
  {
    propThree();
  }

    if (propFourSystem == 0)
  {
    propFour();
  }

    if (propFiveSystem == 0)
  {
    propFive();
  }
}

byte getPage(IPAddress ipBuf,int thisPort, char *page)
{
  int inChar;
  char outBuf[128];
  Serial.print(F("connecting:"));
  delay(100);
    if(client.connect(ipBuf,thisPort) == 1)
    {
      Serial.println(F("connected"));
      sprintf(outBuf,"GET %s HTTP/1.1",page);
      client.println(outBuf);
      sprintf(outBuf,"Host: %s",serverName);
      client.println(outBuf);
      client.println(F("Connection: close\r\n"));
    }
    
    else
    {
      Serial.println(F("failed"));
      return 0;
    }
//////////////////////////////HMC TIME OUT CONTROL/////////////////////////////////////////////////////////////////////
  int connectLoop = 0;                                                   // start with connect loop variable at 0                                                  
    while(client.connected())
    {
        while(client.available())                                      // see if HMC connection is available  
        {
          inChar = client.read();                                        // read HMC Call 
          Serial.write(inChar);                                          // store HMC Call (packet)     
          connectLoop = 0;                                               // set connectLoop to zero if a packet arrives
        }
    connectLoop++;                                                     // increase connectLoop variable by 1 if no packet received.  
        if(connectLoop > 10000)                                            // if more than 10000 milliseconds since the last packet then close the connection from this end.                       
        {
          Serial.println(F("Timeout"));
          client.stop();
        }
    delay(1);
    }
  Serial.println();  
  Serial.println(F("disconnecting."));
  client.stop();                                                      // close client end  
  return 1;
}

//////////////////////////////////////////////////////////////// SEND HTTP TO HMC ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void talkToHMC(char keyWord[])
{
        getPage(server, serverPort, keyWord);    // send request to HMC, notifying Gamemaster that puzzle is complete
  
}

//////////////////////////////////////////////////////////////// PROP ONE FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void propOne()
{
  if (REALpropOneStatus == false) ///////// ALL PROPS START WITH THIS CONDITION ///// PREVENTS LOOPING THROUGH THIS CODE IF PROP IS ALREADY IN A WON STATE /////
  { 
///////////////////////////////////// START CUSTOM PROP CODE HERE ////////////////////////////////    
    if (button_1_state == false)
    {
      if(digitalRead(buttonPin1) == HIGH)                                     //read button 1, if pressed then set button state variable to true
      {
        button_1_state = true;
        Serial.println("Button 1 Pressed");      
      }
    }
    if (button_2_state == false)
    {
      if (digitalRead(buttonPin2) == HIGH)                                    //read button 2, if pressed then set button state variable to true
      {
        button_2_state = true;  
        Serial.println("Button 2 Pressed");
      } 
    }
    if(button_1_state == true && button_2_state == true)                   //read button states, if both are true, then do stuff
    {
      REALpropOneStatus = true;
    }
  }

////////////////////////////////////////  
  if (propOneSystem == 0)
  {

    if (REALpropOneStatus == true || HMCpropOneStatus == true)
    {
      digitalWrite(propOneOutput,HIGH); 
      delay(1000);
      if (HMCpropOneStatus == false)
      {
        talkToHMC(propOneWinkeyWord);
        HMCpropOneStatus = true;                                            // this stops the call to HMC running on a forever loop
      }      
      Serial.println("Prop 1 WON!");
      delay(1000);
      propOneSystem = 1;
      REALpropOneStatus = true;                                                   ////////////SET PROP TO 'WON' ///// PREVENTS LOOPING THROUGH THIS CODE IF PROP IS ALREADY IN A WON STATE ///// 
    }
  }
}

//////////////////////////////////////////////////////////////// PROP TWO FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void propTwo()
{
///////////////////////////////////////////////////  
//  if (prop2Status == false) ///////// ALL PROPS START WITH THIS IF STATEMENT ///// PREVENTS LOOPING THROUGH THIS CODE IF PROP IS ALREADY IN A WON STATE ///////////////////
//  { 
/////////////////////////////////////// START CUSTOM PROP CODE HERE ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      prop2Status = true;                                  ////////////SET PROP TO 'WON' ///// PREVENTS LOOPING THROUGH THIS CODE IF PROP IS WON  ////////////////////// 
//    }
///////////////////////////////////// START CUSTOM PROP CODE HERE ////////////////////////////////////////////////////////////////////////////////////////////////////////  
}

//////////////////////////////////////////////////////////////// PROP THREE FUNCTION ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void propThree()
{
  
}

//////////////////////////////////////////////////////////////// PROP FOUR FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void propFour()
{
  
}

//////////////////////////////////////////////////////////////// PROP FIVE FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void propFive()
{
  
}

//////////////////////////////////////////////////////////////// RESET ALL PROPS // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetAllProps()
{
  resetPropOne();
  resetPropTwo();
  resetPropThree();
  resetPropFour();
  resetPropFive();
  Serial.println("All props reset");              // if call matches " " then do stuff /// replace with your keywords 
}

//////////////////////////////////////////////////////////////// RESET PROP ONE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetPropOne()
{
  propOneSystem = 0;                                                     // this blocks the prop from being 'WON' remotely after it has already been 'WON' physically      
  REALpropOneStatus = false;
  HMCpropOneStatus = false; 
  button_2_state = false;
  button_1_state = false;
  digitalWrite(propOneOutput,LOW);
    
  Serial.print("Prop One System State: ");
  Serial.println(REALpropOneStatus);
  Serial.print("REAL prop One State: ");
  Serial.println(REALpropOneStatus);
  Serial.print("HMC prop One State: ");
  Serial.println(HMCpropOneStatus); 
  Serial.print("Button 1 State: ");
  Serial.println(button_1_state);
  Serial.print("Button 2 State: ");
  Serial.println(button_2_state);
  Serial.print("Prop One Output State: ");
  Serial.println(digitalRead(propOneOutput));    
}

//////////////////////////////////////////////////////////////// RESET PROP TWO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetPropTwo()
{
  REALpropTwoStatus = false;
  HMCpropTwoStatus = false;
  propTwoSystem = 0;  
}

//////////////////////////////////////////////////////////////// RESET PROP THREE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetPropThree()
{
  REALpropThreeStatus = false;
  HMCpropThreeStatus = false;
  propThreeSystem = 0;
}

//////////////////////////////////////////////////////////////// RESET PROP FOUR ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetPropFour()
{
  REALpropFourStatus = false;
  HMCpropFourStatus = false;
  propFourSystem = 0; 
}

//////////////////////////////////////////////////////////////// RESET PROP FIVE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetPropFive()
{
  REALpropFiveStatus = false;
  HMCpropFiveStatus = false;
  propFiveSystem = 0; 
}
