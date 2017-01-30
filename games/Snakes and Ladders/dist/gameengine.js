var engine = {
	previous_tile:{},
	current_tile:1,
	ladders: {3:22,5:8,11:26,20:29},
	snakes:{17:4,19:7,21:9,27:1},
	mappet:{},
	players:[],
	goal: false,
	number_of_tiles:30,
	locations: {
		1: "green", // 
		4: "purple", // 
		6: "red", // 
		5: "pink", // 
		3: "blue", // 
		2: "yellow" // 
	},
	number_of_players:0
}

function map() {
	var $table = $( "<div id='wrapper'></div>" )
	var counter = 25;
	var bytte = true;
	var c = 0;
	for(var i = 0; i<5; i++) {
		var $line = $("<div class='row-'></div>");
		if(bytte) {
			
			for(var j = 0; j<6;j++) {
				$line.append($( "<div class='col-"+(counter)+"'></div>" ));//.html(counter++)); //
				$table.append($line);
				//engine.mappet[counter] = counter;
				counter= counter+1;
			}
			bytte = false;
		}else {
			c= counter-7;
			for(var j = 5; j>=0;j--) {
				$line.append($( "<div class='col-"+(c)+"'></div>" ));//.html( c-- )); //
				$table.append($line);
				c=c-1;
				//engine.mappet[counter] = counter;
			}
			counter = c -5;
			bytte = true;
		}	
	}

	$("#map").html($table);
}
function startGame() {

	map();
	$("#msg").innerHTML = "Start the game";
	engine.current_tile = 1;
	
}

function newPlayer(name,token) {
	//var name = engine.locations[engine.number_of_players++];
	
	var player = new AnyBoard.Player(name);
	player.properties = 0;
	player.color = engine.locations[engine.number_of_players++];
	player.tile = 0;
    engine.players[token] = player;

}
function move_detected(token,constrain,digit) {
	// body...
	
	if(engine.players[token].tile != constrain) {
		//alert("move detected: "+constrain );
		move(digit,token);
		engine.players[token].tile = constrain;
		//AnyBoard.TokenManager.onceTokenConstraintEvent("MOVE_TO",handleTokenMove);
	}
}

function move(digit,token) {
	// body...
	//digit = Math.floor((Math.random()*6)+1) // to test random dice-throws
	var targetDiv = document.getElementsByClassName("col-"+engine.current_tile)[0];
	targetDiv.style.backgroundColor = "rgba(255, 255, 255, .4)";
	var pcolor = engine.players[token].color;
	var moves = (engine.players[token]).properties + digit;
	var counter = 1;
	//var color = moves % 6;
	
	engine.previous_tile = (engine.players[token]).properties;
	engine.current_tile = moves;

	if(engine.ladders[moves]) {
		sendVibrationCmd(token);
		sendDisplayUp(token);
		(engine.players[token]).properties = engine.ladders[moves];
	}else if(engine.snakes[moves]) {
		sendVibrationCmd
		sendDisplayDown(token);
		(engine.players[token]).properties = engine.snakes[moves];
	} else {
		(engine.players[token]).properties = moves;
	}

	if(moves >= 31) {
		document.getElementById("msg").innerHTML = "The winner is: " + pcolor;
		sendDisplayW(token);
		sendVibrationCmd(token);
	}
	moveOnScreen(digit,token);
}

function moveOnScreen(digit,token) {

	var targetDiv = document.getElementsByClassName("col-"+engine.current_tile)[0];
	targetDiv.style.backgroundColor = "rgba(255, 255, 255, .4)";
	var pcolor = engine.players[token].color;
	var moves = (engine.players[token]).properties;
	var counter = 1;
	
	engine.previous_tile = (engine.players[token]).properties - digit;
	engine.current_tile = moves;


	for(var i=engine.previous_tile; i<moves;i++) {
		setTimeout(callback(i+1,pcolor),(counter++)*1000);
	}

	if(engine.ladders[moves]) {

		setTimeout(callback(engine.ladders[moves],"rgba(255, 255, 255, .4)"),(counter++)*1000);
		engine.current_tile = engine.ladders[moves];
		for(var i=engine.previous_tile; i<moves;i++) {
			setTimeout(callback(i,""),(counter++)*1000);
		}
		setTimeout(callback(moves,""),counter*1000)

	}else if(engine.snakes[moves]) {

		setTimeout(callback(engine.snakes[moves],"rgba(255, 255, 255, .4)"),(counter++)*1000);
		engine.current_tile = engine.snakes[moves];
		for(var i=engine.previous_tile; i<moves;i++) {
			setTimeout(callback(i,""),(counter++)*1000);
		}
		setTimeout(callback(moves,""),counter*1000)

	}else {

		for(var i=engine.previous_tile; i<moves;i++) {
			setTimeout(callback(i,""),(counter++)*1000);
		}
		
	}
	
}

function callback(tileID,color) {
	return function() {
			var targetDiv = document.getElementsByClassName("col-"+tileID)[0];
				targetDiv.style.backgroundColor = color;	
	}
}