// variable with tokens
var app = {
	devices: {}
}


function rollDice() {
    var dice = new AnyBoard.Dice();
    var result = dice.roll();   
    //document.getElementById("dice").innerHTML = "Your Dice rolled: " + result;  
    return result;  
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
function addToken(token) {
    if(!app.devices[token.address]){
        app.devices[token.address] = token;
        newPlayer(token.address,token);
		$("#availableTokens").append('<br> <button type="button" class="btn btn-success" id="' + token.address + '" onclick="connect(' + "'" + token.address + "'" + ')" class="grey">' + token.name + ' </button><br />');
		
		token.on('connect',function(){
		    document.getElementById(token.address).className = 'green';
		});
    }
}
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



function sendDisplayDigitCmd(token,digit) {
    var completedFunction = function(data){
            //logging
            hyper.log("We HAPPY send the displayDigit command");
            hyper.log(data);
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
function sendDisplayXCmd(token) {

        // Function to be executed when LED is successfully turned on
        var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_X command");
            hyper.log(data)
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_X command");
            hyper.log(errorMsg);
        };

        // Turns on token led.
        token.displayX([1], // Instead of "green" color, on could also use array, e.g. [0, 255, 0]
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
    }
function sendVibrationCmd(token) {
     var completedFunction = function(data){
            hyper.log("We happily send the DISPLAY_X command");
            hyper.log(data)
        };

        // Function to be executed upon failure of LED
        var errorCallback = function(errorMsg) {
            hyper.log("Failed to send the DISPLAY_X command");
            hyper.log(errorMsg);
        };
                // Turns on token led.
        token.vibrate([100], // Instead of "green" color, on could also use array, e.g. [0, 255, 0]
            completedFunction,  // function to be executed when token signals
            errorCallback  // function to be executed in case of failure to send command to token
        );
}

function handleTokenTap(token) {
   
    var diceroll = this.rollDice();
    this.sendDisplayDigitCmd(token,diceroll);
    setTimeout(function(){ // endre senere til fargesensoren, endring i farge sender displayX
        sendDisplayXCmd(token);
    },5000);
    move(diceroll,token);
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
function handleTokenMove(token, constraint, options) {
    alert("Move detected");
    AnyBoard.Logger.log("Moved to tilee " + constraint);
}


