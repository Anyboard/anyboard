#include "BLE_Handler.h"

BLE_Handler::BLE_Handler()//  Default constructor
{
    Connected = false;
    
    String MAC = String(*(uint8_t *)0x100000a4, HEX);
    AdvertiseName = "AnyPawn_" + MAC;  
}

// Code that executes everytime token is being connected to
void RFduinoBLE_onConnect()
{
    extern BLE_Handler BLE;
    BLE.Connected = true;
    Serial.println("Pawn connected to device.");
}

// Code that executes everytime token is being disconnected from
void RFduinoBLE_onDisconnect()
{
    extern BLE_Handler BLE;
    BLE.Connected = false;
    Serial.println("Pawn disconnected from device");
}

void BLE_Handler::Emit(TokenEvent *Event)
{
    if(Event != NULL)
    {
      Serial.println("Added Event !");
      Stack.push(Event);  
    }
}


void BLE_Handler::SendEvent(TokenEvent* Event)
{
    char sendData[20] = {0};
    uint8_t Length = sizeof(Event->Parameters);

    sendData[0] = Event->EventCode;
    
    for (int i = 0; i < Length; i++) 
    {
      sendData[i + 1] = Event->Parameters[i];
    }
  
    RFduinoBLE.send(sendData, 1+ Length);
    Serial.print("Event sent: ");Serial.print(sendData[0],DEC);Serial.print(" , ");Serial.println(sendData[1],DEC);
}

// Code to run upon receiving data over bluetooth
void RFduinoBLE_onReceive(char *data, int length)
{
    extern BLE_Handler BLE;
    BLE.ReceiveEvent(data, length);
}

void BLE_Handler::ReceiveEvent(char *Data, int Lenght)
{ 
    TokenEvent *NewEvent = new TokenEvent();
    NewEvent->EventCode = Data[0];   
    // Stores the rest of the incoming data in the Parameters field
    for (int i = 1; i < Lenght; i++)
    {
      NewEvent->Parameters[i-1] = Data[i];
    }
    //Adding Event to the stack
    Stack.push(NewEvent);
}

// Executes command
void BLE_Handler::ProcessEvents()
{
    String R;
    String G;
    String B;
    
    if(Stack.count() == 0)
      return;
      
    TokenEvent *Event = NULL;
    Event = Stack.pop();

    if(Event == NULL)
      return;
      
    TokenEvent *Ack = new TokenEvent();
    Ack->EventCode = Event->EventCode;

    extern TokenFeedback_Handler TokenFeedback;
    extern TokenConstraintEvent_Handler TokenConstraintEvent;
    
    Serial.print("Event received : "); Serial.print(Event->EventCode); Serial.print("    Param : "); Serial.println(Event->getParameterString()); 
    
    switch (Event->EventCode)
    {
      case GET_NAME:
        Ack->set(GET_NAME, NAME);
        SendEvent(Ack);
      break;
      case GET_VERSION:
        Ack->set(GET_VERSION, VERSION);
        SendEvent(Ack);
      break;
      case LED_ON:
        R = String(Event->Parameters[0], HEX);
        if(R.length() == 1)
          R = String("0") + R;
        G = String(Event->Parameters[1], HEX);
        if(G.length() == 1)
          G = String("0") + G;
        B = String(Event->Parameters[2], HEX);
        if(B.length() == 1)
        B = String("0") + B;     
        TokenFeedback.setColor(String(R+G+B));
        SendEvent(Ack);
      break;

      case LED_BLINK:
        TokenFeedback.BlinkLED(Event->Parameters[0]*1000, Event->Parameters[1]*10);
        Ack->set(130);
        SendEvent(Ack);
        break;
        
      case VIBRATE:
        TokenFeedback.Vibrate(Event->Parameters[0] * 10);
        SendEvent(Ack);
        break;
        
      case DISPLAY_DIGIT:
        TokenFeedback.DisplayDigit(Event->Parameters[0], 1000);
        SendEvent(Ack);
        break;
                
      case DISPLAY_PATTERN:
        TokenFeedback.DisplayPattern((uint8_t*)(Event->Parameters));
        SendEvent(Ack);
        break;     
                   
      case PAPER_SELECT:
        TokenConstraintEvent.setPaper(Event->Parameters[0]);
        SendEvent(Ack);
        break;
        
      default:
        Ack->EventCode = 0;
        SendEvent(Ack);
    }
}

/***************************************/

TokenEvent::TokenEvent()
{
    EventCode = 0;
    memset(Parameters, 0, sizeof(Parameters));
}

void TokenEvent::set(uint8_t Code, char* Param)
{
    EventCode = Code;

    if(Param == NULL)
      return;

    // Warning, sizeof won't work with dynamic allocated array !
    // Furthermore if the type is changed from char, need to divide by sizeof(new type)
    for(uint8_t i = 0; i < sizeof(Param) && i < 19; i++)
    {
        Parameters[i] = Param[i];
    }
}

String TokenEvent::getParameterString()
{
    String Param = Parameters;
    return Param;
}

