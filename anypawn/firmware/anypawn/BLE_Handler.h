#ifndef BLEHANDLER_h
#define BLEHANDLER_h

#include <RFduinoBLE.h>
#include <StackArray.h>
#include "protocol.h"
#include "TokenFeedback_Handler.h"
#include "TokenConstraintEvent_Handler.h"

class TokenConstraintEvent_Handler;
class TokenEvent;

class BLE_Handler
{
    public:
      BLE_Handler(); //  Default constructor
      void Transmit();
      void SendEvent(TokenEvent* Event);    
      void ReceiveEvent(char *Data, int Lenght);
      void ProcessEvents();
      void Emit(TokenEvent *Event);
      String AdvertiseName;
      bool Connected;
      bool EventReceived;   // true if an event has been Received, cleared with a call to ProcessEvents()
      bool EventToSend;     // true if there are events waiting to be send    
    private:            
      StackArray<TokenEvent*> Stack;   
};

class TokenEvent
{
  public:
    TokenEvent();
    void set(uint8_t Code, char* Param = NULL);
    String getParameterString();   
    uint8_t EventCode;
    char Parameters[19];     
};
#endif
