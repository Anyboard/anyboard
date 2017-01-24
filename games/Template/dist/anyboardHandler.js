// variable with tokens
var app = {
	devices: {},
    tiles : {
        1: "White",
        2: "White"
    },
    token:{}
}

function discoverTokens() {
    var self = this;
    AnyBoard.TokenManager.scan(
        function(token) {
            self.addToken(token);
        },
        function(errorCode) {
            console.log(errorCode)
        }
    );
}
/* The addToken function will check if the device(parameter) is already added. 
   If not the device will be added and a button with the option to connect to that token will be displayed.
   When connected the button will change its color to green. 
*/
function addToken(token) {
    if(!app.devices[token.address]){
        app.devices[token.address] = token;
		$("#availableTokens").append('<br> <button type="button" class="btn btn-success" id="' + token.address + '" onclick="connect(' + "'" + token.address + "'" + ')" class="grey">' + token.name + ' </button><br />');
		
		token.on('connect',function(){
		    document.getElementById(token.address).className = 'green';
		});
    }
}


/* The connect function is called when the "Connect to device" button is pressed. 
    This will trigger the driver.connect (token.connect) found in the "discovery.evothings.bluethooth.js" file.
    The function "weHaveConnectedToPawn" will be executed when complete.
*/
function connect(tokenName) {
    var token = app.devices[tokenName];

    // If already connecting, stop
    if (document.getElementById(tokenName).className == 'blue') {
        return;
    }

	// If already connected, attempt to send green led command
    if (document.getElementById(tokenName).className == 'green') {
        this.weHaveConnectedToPawn();
        return;
    }

    // Signal that we're attempting to connect
    document.getElementById(tokenName).className = 'blue';


    // Send connect command.
    token.connect(weHaveConnectedToPawn());

}
function weHaveConnectedToPawn() {
	$("#weHaveConnectedToPawn").show();

	//$("#summary").hide();
}

/* The sendDisplayDigitCmd function will trigger the token.displayDigit found in the driver rfduino.evothings.bluethooth.js
   file. This will display the digit on the pawn LED screen.
*/

function sendDisplayDigitCmd(token,digit) {
    var completedFunction = function(data){
            //logging
            hyper.log("We HAPPY send the displayDigit command");
           
        };
        var errorCallback = function(errorMsg) {
            //logging
            hyper.log("Failed to send the displayDigit command");
            hyper.log(errorMsg);
        };
        token.displayDigit([digit], 
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
}

/* The sendDisplayXCmd function will trigger the token.displayX found in the driver rfduino.evothings.bluethooth.js
   file. This will display an X on the pawn LED screen.
*/
function sendDisplayXCmd(token) {

        // Function to be executed when LED is successfully turned on
        var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_X command");
           
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_X command");
            hyper.log(errorMsg);
        };

        // Turns on token led.
        token.displayX([1], // 
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
    }

/* The sendVibrationCmd function will trigger the token.vibrate found in the driver rfduino.evothings.bluethooth.js
   file. The value sent is the length of the vibration in ms.
*/

function sendVibrationCmd(token) {
     var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_X command");
            
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_X command");
            hyper.log(errorMsg);
        };
                // Turns on token led.
        token.vibrate([100], // 
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
}

/* The sendDisplayW function will trigger the token.displayW found in the driver rfduino.evothings.bluethooth.js
   file. This will display a W on the pawn LED screen.
*/
function sendDisplayW(token) {
     var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_W command");
            hyper.log(data)
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_W command");
            hyper.log(errorMsg);
        };
                // Turns on token led.
        token.displayW([1], // 
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
}

/* The sendDisplayUp function will trigger the token.displayUp found in the driver rfduino.evothings.bluethooth.js
   file. This will display an arrow pointing up on the pawn LED screen.
*/
function sendDisplayUp(token) {
     var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_UP command");
            
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_UP command");
            hyper.log(errorMsg);
        };
                // Turns on token led.
        token.displayUp([1], // 
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
}

/* The sendDisplayDown function will trigger the token.displayDown found in the driver rfduino.evothings.bluethooth.js
   file. This will display an arrow pointing down on the pawn LED screen.
*/
function sendDisplayDown(token) {
     var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_DOWN command");
           
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_DOWN command");
            hyper.log(errorMsg);
        };
                // Turns on token led.
        token.displayDown([1], //
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
}

function handleTokenTap(token) {
   // alert("This is a single tap");
}
function handleTokenDoubleTap(token) {
   // alert("This is a double tap");
}
function handleTokenShake(token) {
  //  alert("This is a shake");
}
function handleTokenTilt(token) {
  //  alert("This is a tilt");
}
function handleTokenMove(token, constraint, options) { //Needs an update with color recogniztion to be used efficiently
    AnyBoard.Logger.log("Moved to tilee " + constraint);
  //  alert("This is a move");
}

function singleTokenTap(token) {
    // alert("Will only trigger once. TAP");
}

function singleTokenDoubleTap(token) {
    // alert("Will only trigger once. DOUBLE_TAP");
}
function singleTokenShake(token) {
    // alert("Will only trigger once. SHAKE");
}
function singleTokenTilt(token) {
    // alert("Will only trigger once. TILT");
}
function singleTokenMove(token,constraint,options) {
    //alert("Will only trigger once. MOVE_TO");
}


