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
		0: "green", // 
		2: "purple", // 
		1: "orange", // 
		5: "pink", // 
		3: "blue", // 
		4: "yellow" // 
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
    engine.players[token] = player;

}

function move(digit,token) {
	// body...
	//digit = Math.floor((Math.random()*6)+1) // to test random dice-throws

	var targetDiv = document.getElementsByClassName("col-"+engine.current_tile)[0];
	targetDiv.style.backgroundColor = "rgba(255, 255, 255, .4)";
	var pcolor = engine.players[token].color;
	var moves = (engine.players[token]).properties + digit;
	var counter = 1;
	var color = moves % 6;
	
	engine.previous_tile = (engine.players[token]).properties;
	engine.current_tile = moves;

	for(var i=engine.previous_tile; i<moves;i++) {
		setTimeout(callback(i+1,pcolor),(counter++)*1000);
	}

	if(engine.ladders[moves]) {
		sendVibrateCmd(token)
		setTimeout(callback(engine.ladders[moves],"rgba(255, 255, 255, .4)"),(counter++)*1000);
		engine.current_tile = engine.ladders[moves];
		(engine.players[token]).properties = engine.ladders[moves];
		for(var i=engine.previous_tile; i<moves;i++) {
			setTimeout(callback(i,""),(counter++)*1000);
		}
		setTimeout(callback(moves,""),counter*1000)
	}else if(engine.snakes[moves]) {
		sendVibrateCmd(token)
		setTimeout(callback(engine.snakes[moves],"rgba(255, 255, 255, .4)"),(counter++)*1000);
		engine.current_tile = engine.snakes[moves];
		(engine.players[token]).properties = engine.snakes[moves];
		for(var i=engine.previous_tile; i<moves;i++) {
			setTimeout(callback(i,""),(counter++)*1000);
		}
		setTimeout(callback(moves,""),counter*1000)
	}else {
		for(var i=engine.previous_tile; i<moves;i++) {
			setTimeout(callback(i,""),(counter++)*1000);
		}
		(engine.players[token]).properties = moves;
	}
	
	if(moves >= 31) {
		document.getElementById("msg").innerHTML = "The winner is: " + pcolor;
	}else {

		document.getElementById("msg").innerHTML = "Move to "+ engine.locations[color]+". Next player turn";
	}
}
function callback(tileID,color) {
	return function() {
			var targetDiv = document.getElementsByClassName("col-"+tileID)[0];
				targetDiv.style.backgroundColor = color;	
	}
}