var logic = {
    initiate: function() {
        var handleTokenMove = function(token, constraint, options) {
            AnyBoard.Logger.log(token.player + " moved to tilee " + constraint);
            token.player.location = constraint;





            // If the token is the only one, we will not expect any Token-Token events to occur before all (1) token
            // is placed on a tile. Therefore we check if the token is the only one, and trigger the TT-event manually
            // if it is
            if (token.player.location === 1) {

              hyper.log("handleTokenTokenTouch");
              if (typeof d.currentQuestionPos === "undefined") ui.activatePanel('game');
              else ui.nextQuestion();

                //handleTokenTokenTouch(token, token);
            }

            if (logic.everyOneHasAnswered()) {
                ui.showAnswer();
                return;
            }

        };

        var handleTokenTokenTouch = function(initiatingToken, respondingToken, options) {
			hyper.log("TTevent");
            if (respondingToken.player.location === 1) {
                hyper.log("handleTokenTokenTouch");
                if (typeof d.currentQuestionPos === "undefined") ui.activatePanel('game');
                else ui.nextQuestion();
            }
        };

        logic.addListener("game", logic.startGame);
        logic.addListener("summary", ui.finishGame);

        AnyBoard.TokenManager.onTokenConstraintEvent("MOVE_TO", handleTokenMove);
        AnyBoard.TokenManager.onTokenTokenEvent("MOVE_NEXT_TO", handleTokenTokenTouch)
    },

    // Discover bluetooth tokens in proximity
    discover: function() {
        var self = this;
        AnyBoard.TokenManager.scan(
            // success function to be executed upon _each_ token that is discovered
            function(token) {
                self.addDiscovered(token);
            },
            // function to be executed upon failure
            function(errorCode) {
                hyper.log(errorCode)
            }
        );
    },

    // Function to be executed upon having discovered a token
    addDiscovered: function(token) {
        if (!d.devices[token.address]) {
            d.devices[token.address] = token;

            // Add button for token to body
            $('#setup').append('<div class="token center"><button type="button" id="' + token.address +
            '" onclick="logic.connect(' + "'" + token.address + "'" +
            ')" class="grey token">' + token.name + ' </button>' +
            '<button class="player-icon' + '">&nbsp;</button>' + '</div>');

            // Add listener to be executed if the token connects
            token.on('connect', function() {
				if(token.driver.hasOwnProperty('print')){
					//don't assign player color etc. to printer
					return;
				}

                document.getElementById(token.address).className = 'green token';
                token.color = d.colors.pop();
                token.player = new AnyBoard.Player(
                    token.color + "-player",
                    {
                        "color": token.color,
                        "points": 0,
                        "locations": -1,
                        "token": token
                    }
                );
                d.players.push(token.player);
				hyper.log("Added player");
                $(document.getElementById(token.address)).next().addClass(token.color);
                for(i=0; i<4; i++)
				{
					token.ledOn('white')
					token.ledOn(token.color);
				}
            });

            // Add listener to be executed if the token disconnects
            token.on('disconnect', function() {
				if(token.driver.hasOwnProperty('print')){
					//printer was not assigned a color to be put back on the color stack
					return;
				}
                document.getElementById(token.address).className = 'grey token';
                $(document.getElementById(token.address)).next().removeClass(token.color);
                d.colors.push(token.color);
            })
        }

    },

    // Attempts to connect to token.
    connect: function(tokenAddress) {
        var token = d.devices[tokenAddress];

        // If already connecting, stop
        if (document.getElementById(tokenAddress).className.indexOf('blue') !== -1)
            return;

        // If already connected, disconnect
        if (document.getElementById(tokenAddress).className.indexOf('green') !== -1) {
            token.disconnect();
            return;
        }
        // Signal that we're attempting to connect
        document.getElementById(tokenAddress).className = 'blue token';

        // Send connect command.
        token.connect();
    },

    startGame: function(){
        hyper.log("startGame");
        d.questions = logic.shuffle(d.questions);
        d.currentQuestionPos = -1;
        ui.nextQuestion();
        for (var index in d.players) {
            if (d.players.hasOwnProperty(index))
                d.players[index].points = 0;
        }
    },

    shuffle: function(o){
        for(var j, x, i = o.length; i; j = Math.floor(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
        return o;
    },

    addListener: function(name, callback) {
        if (!d.listeners[name])
            d.listeners[name] = [];
        d.listeners[name].push(callback);
    },

    trigger: function(name, options) {
        hyper.log("trigger: " + name);
        if (d.listeners[name]) {
            for (var i = d.listeners[name].length - 1; i >= 0; i--) {
                d.listeners[name][i](options);
            }
        }
    },

    getCurrentQuestion: function() {
        return d.questions[d.currentQuestionPos];
    },

    getNextQuestion: function() {
        hyper.log("nextQuestion");
        d.currentQuestionPos += 1;
		d.pointsAwarded = false;
		questionsPerRound = 4
        if (d.currentQuestionPos >= d.questions.length || d.currentQuestionPos >= questionsPerRound) {
            return undefined; // returns undefined if no more questions left
        }
        return d.questions[d.currentQuestionPos];
    },

    givePoints: function() {
		if(d.pointsAwarded){
			return;
		}

        var question = logic.getCurrentQuestion();
        for (var key in d.players) {
            if (d.players.hasOwnProperty(key)) {
                var player = d.players[key];
                var answer = player.location;
				if(question.answer == d.locations[answer]){
					player.points += 1;
				}
            }
        }
		d.pointsAwarded = true;
    },

    everyOneHasAnswered: function() {
        var tokenSet = AnyBoard.TokenManager.tokens;
        for (var key in tokenSet) {
            if (tokenSet.hasOwnProperty(key) && tokenSet[key].isConnected()) {
				//ignoring any printer connected
				if (tokenSet[key].driver.hasOwnProperty('print')){
					continue;
				}

                if (tokenSet[key].player.location === 5) {
					hyper.log("Everyone has answered: False");
                    return false;
                }
            }
        }
		hyper.log("Everyone has answered: True");
        return true;
    },

    numberOfConnectedTokens: function() {
        var tokenSet = AnyBoard.TokenManager.tokens;
        var numOfConnected = 0;
        for (var key in tokenSet) {
            if (tokenSet.hasOwnProperty(key) && tokenSet[key].isConnected()) numOfConnected += 1;
        }
        return numOfConnected;
    },

	printCertificate: function() {
		hyper.log("Printing certificate");

        var tokenSet = AnyBoard.TokenManager.tokens;
		var printerToken = undefined;
        for (var key in tokenSet) {
            if (tokenSet.hasOwnProperty(key) && tokenSet[key].isConnected()) {
				if (tokenSet[key].driver.hasOwnProperty('print')){
					printerToken = tokenSet[key];
				}
			}
		}

		if(printerToken){
			var score = d.players[0].points;
			printerToken.print("##n##cCongratulations!##n##cYou scored " + score + " out of 4 points!##n##n##lBrought to you by AnyBoard##f##f##f##f");
		}else{
			hyper.log("Printing certificate failed, no printer connected");
		}
	}
};
