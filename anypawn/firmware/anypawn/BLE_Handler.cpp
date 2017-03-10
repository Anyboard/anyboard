#include "BLE_Handler.h"

BLE_Handler::BLE_Handler()//  Default constructor
{
    Connected = false;
}

// Code that executes everytime token is being connected to
void RFduinoBLE_onConnect()
{
    extern BLE_Handler BLE;
    BLE.Connected = true;
}

// Code that executes everytime token is being disconnected from
void RFduinoBLE_onDisconnect()
{
    extern BLE_Handler BLE;
    BLE.Connected = false;
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
    extern TokenFeedback tokenFeedback;
    
    if(Stack.count() == 0)
      return;
      
    TokenEvent *Event = NULL;
    Event = Stack.pop();

    if(Event == NULL)
      return;
      
    TokenEvent *Ack = new TokenEvent();
    Ack->EventCode = Event->EventCode;
    
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
        
      case GET_UUID:
        Ack->set(GET_UUID, UUID);
        SendEvent(Ack);
        break;
        
      case HAS_LED:
        Ack->Parameters[1] = 1;
        SendEvent(Ack);
        break;
        
      case HAS_LED_COLOR:
        Ack->Parameters[1] = 1;
        SendEvent(Ack);
        break;
        
      case HAS_VIBRATION:
        Ack->Parameters[1] = 0;
        SendEvent(Ack);
        break;
        
      case HAS_COLOR_DETECTION:
        Ack->Parameters[1] = 1;
        SendEvent(Ack);
        break;
        
      case HAS_LED_SCREEN:
        Ack->Parameters[1] = 0;
        SendEvent(Ack);
        break;
        
      case HAS_RFID:
        Ack->Parameters[1] = 0;
        SendEvent(Ack);
        break;
        
      case HAS_NFC:
        Ack->Parameters[1] = 0;
        SendEvent(Ack);
        break;
        
      case HAS_ACCELEROMETER:
        Ack->Parameters[1] = 0;
        SendEvent(Ack);
        break;
        
      case HAS_TEMPERATURE:
        Ack->Parameters[1] = 0;
        SendEvent(Ack);
        break;
        
      case VIBRATE:
        tokenFeedback.vibrate(Event->Parameters[0] * 10);
        SendEvent(Ack);
        break;
        
      case COUNT:
        tokenFeedback.displayCount();
        SendEvent(Ack);
        break;
        
      case DISPLAY_X:
        tokenFeedback.displayX();
        SendEvent(Ack);
        break;
        
      case DISPLAY_W:
        tokenFeedback.displayW();
        SendEvent(Ack);
        break;
        
      case DISPLAY_UP:
        tokenFeedback.displayUp();
        SendEvent(Ack);
        break;
        
      case DISPLAY_DOWN:
        tokenFeedback.displayDown();
        SendEvent(Ack);
        break;
        
      case DISPLAY_DIGIT:
        tokenFeedback.displayDigit(Event->Parameters[0]);
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

