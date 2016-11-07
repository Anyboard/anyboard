// COMMANDS
const uint8_t GET_NAME             = 32;
const uint8_t GET_VERSION          = 33;
const uint8_t GET_UUID             = 34;
const uint8_t HAS_LED              = 64;
const uint8_t HAS_LED_COLOR        = 65;
const uint8_t HAS_VIBRATION        = 66;
const uint8_t HAS_COLOR_DETECTION  = 67;
const uint8_t HAS_LED_SCREEN       = 68;
const uint8_t HAS_RFID             = 71;
const uint8_t HAS_NFC              = 72;
const uint8_t HAS_ACCELEROMETER    = 73;
const uint8_t HAS_TEMPERATURE      = 74;

const uint8_t LED_OFF2             = 128;
const uint8_t LED_ON2              = 129;
const uint8_t LED_BLINK            = 130;
const uint8_t READ_COLOR           = 136;

//EVENTS
const uint8_t MOVE                 = 194; //C2

const uint8_t TAP				           = 201; //C9
const uint8_t DOUBLE_TAP		       = 202; //CA
const uint8_t SHAKE				         = 203; //CB
const uint8_t TILT                 = 204; //CC

//COMMANDS
const uint8_t COUNT                = 205; //CD
const uint8_t DISPLAY_X            = 206; //CE
const uint8_t VIBRATE              = 200; //C8
const uint8_t DISPLAY_DIGIT		   = 207;