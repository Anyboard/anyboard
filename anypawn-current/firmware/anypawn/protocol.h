#ifndef PROTOCOL_h
#define PROTOCOL_h

// TOKEN FIRMWARE METADATA
#define NAME    "AnyBoard Pawn"
#define VERSION "0.1"
#define UUID    "3191-6275-32g4"


// Status commands
const uint8_t GET_NAME             = 32;
const uint8_t GET_VERSION          = 33;
const uint8_t GET_UUID             = 34;

//Token-solo events
const uint8_t TAP				   = 201; //C9
const uint8_t DOUBLE_TAP		   = 202; //CA
const uint8_t SHAKE				   = 203; //CB
const uint8_t TILT                 = 204; //CC
const uint8_t ROTATION             = 220;

//Token-constraint events
const uint8_t MOVE                 = 194; //C2 (+ 2nd and 3rd bytes for current and last sector)
const uint8_t PAPER_SELECT         = 195;

//Token-token events
//TBD

//feedbacks
const uint8_t VIBRATE              = 200; //C8 (+ 2nd and 3rd bypte for time and period)
const uint8_t DISPLAY_PATTERN      = 230; //CE
const uint8_t DISPLAY_DIGIT		   = 207;

const uint8_t LED_OFF             = 128;
const uint8_t LED_ON              = 129;
const uint8_t LED_BLINK           = 130;
#endif
