#ifndef TOKENSOLOEVENT_h
#define TOKENSOLOEVENT_h

class TokenSoloEvent
{
    public:
      TokenSoloEvent(); //  Default constructor
      virtual int RefreshValues() = 0;   //Function to be implemented by the daugthers class
      
    protected:
      bool Triggered;   // An event has been triggered
      int EventCode;   // Code of the event according to protocol.h
};

#endif