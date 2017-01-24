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
            $("#functions").append('<button type="button" onclick="sendVibrationCmd('+ "'" + token.address + "'" +')" class="indicator3"> Vibrate </button><br />');
            $("#functions").append('<button type="button" onclick="sendCountCmd('+ "'" + token.address + "'" +')" class="indicator3"> Count </button><br />');
            $("#functions").append('<button type="button" onclick="sendDisplayXCmd('+ "'" + token.address + "'" +')"class="indicator3"> Display a cross </button><br />');
            $("#functions").append('<button type="button" onclick="sendDisplayDigitCmd('+ "'" + token.address + "'" +')"class="indicator3"> Display digit 6 </button><br />');
            $("#functions").append('<button type="button" onclick="sendDisplayW('+ "'" + token.address + "'" +')"class="indicator3"> Display a W </button><br />');
            $("#functions").append('<button type="button" onclick="sendDisplayUp('+ "'" + token.address + "'" +')"class="indicator3"> Display an arrow up </button><br />');
            $("#functions").append('<button type="button" onclick="sendDisplayDown('+ "'" + token.address + "'" +')"class="indicator3"> Display an arrow down </button><br />');
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

    app.token = token;
    // Send connect command.
    token.connect(weHaveConnectedToPawn());

}
function weHaveConnectedToPawn() {
	$("#weHaveConnectedToPawn").show();
    $("#availableTokens").hide(); // hide the available tokens after connecting to one. If multiple tokens are needed: remove this line. 
	//$("#summary").hide();
    $("#functions").show();
}

/* The sendDisplayDigitCmd function will trigger the token.displayDigit found in the driver rfduino.evothings.bluethooth.js
   file. This will display the digit on the pawn LED screen.
*/

function sendDisplayDigitCmd(tokenName,digit) {
    var token = app.devices[tokenName];
    digit = 6; //template purpose only
   
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
function sendDisplayXCmd(tokenName) {
var token = app.devices[tokenName];

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

function sendVibrationCmd(tokenName) {
    var token = app.devices[tokenName];
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
function sendDisplayW(tokenName) {
    var token = app.devices[tokenName];
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
function sendDisplayUp(tokenName) {
    var token = app.devices[tokenName];
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
function sendDisplayDown(tokenName) {
    var token = app.devices[tokenName];
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

function sendCountCmd(tokenName) {
    var token = app.devices[tokenName];
    // Function to be executed when LED is successfully turned on
    var completedFunction = function(data){
        hyper.log("We happily send the COUNT command");
        hyper.log(data)
    };

    // Function to be executed upon failure of LED
    var errorCallback = function(errorMsg) {
        hyper.log("Failed to send the COUNT command");
        hyper.log(errorMsg);
    };

    // Turns on token led.
    token.count([1], // Instead of "green" color, on could also use array, e.g. [0, 255, 0]
        completedFunction,  // function to be executed when token signals
        errorCallback  // function to be executed in case of failure to send command to token
    );
}
/*THe following functions are mapped to AnyBoard.TokenManager-tokenlistener ...*/
function handleTokenTap(token) {
   // alert("This is a single tap");
   document.getElementById("msg").innerHTML = "This is a tap";
}
function handleTokenDoubleTap(token) {
   // alert("This is a double tap");
   document.getElementById("msg").innerHTML = "This is a Double_tap";
}
function handleTokenShake(token) {
  //  alert("This is a shake");
  document.getElementById("msg").innerHTML = "This is a SHAKE";
}
function handleTokenTilt(token) {
  //  alert("This is a tilt");
  document.getElementById("msg").innerHTML = "This is a TILT";
}

/* AnyBoard.TokenManager.onTokenMove only detects if there have been an change from one color to another.
   These settings are manually set in the firmware/driver
*/
function handleTokenMove(token, constraint, options) { //Needs an update with color recogniztion to be used efficiently
    AnyBoard.Logger.log("Moved to tilee " + constraint);
  //  alert("This is a move");
  document.getElementById("msg").innerHTML = "This is a MOVE";
}

function singleTokenTap(token) {
     alert("Will only trigger once. TAP");
}

function singleTokenDoubleTap(token) {
     alert("Will only trigger once. DOUBLE_TAP");
}
function singleTokenShake(token) {
     alert("Will only trigger once. SHAKE");
}
function singleTokenTilt(token) {
     alert("Will only trigger once. TILT");
}
function singleTokenMove(token,constraint,options) {
    alert("Will only trigger once. MOVE_TO");
}


