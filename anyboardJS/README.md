# AnyboardJS
*Authors: Thomas Fagerbekk, Simone Mora*

A simple JS-framework for creating Anyboard games.
AnyboardJS ground work and implementation details are reported in [Thomas' master thesis](https://brage.bibsys.no/xmlui/handle/11250/2380959).

- [Library documentation](documentation.md)
- [Examples](examples)

## How to: Use AnyboardJS without interactive tokens (anyPawn and anyDeck)

1. Click [here to download a full version](https://github.com/tomfa/anyboardjs/raw/master/dist/anyboard.js) or [here to download a minified one](https://github.com/tomfa/anyboardjs/raw/master/dist/anyboard.min.js).
2. Include the following in your head of your html file ``` <script src="dist/AnyBoard.js"></script> ```

For an example without IoT devices, check out the [examples/html-deck/](./examples/html-deck/). Examples run on smartphones using the [Evothings](https://evothings.com/download/) environment.

## How to: Use AnyboardJS with interactive tokens

AnyboardJS is decoupled from any bluetooth communication and environment. The communication is handled by separate drivers for anyPawn and anyDeck, which implement the sending and receiving of data from the tokens devices.

### Setup

1. Download and install [Evothings](https://evothings.com) to your PC/Mac
2. Download and install [Evothings](https://evothings.com) on your phone
3. Acquire one or more anyPawn and anyDeck tokens (with pre-installed firmware)
4. Create an index.html with the following inside ```<head>```:
```
    <!-- cordova.js -->
	<script src="cordova.js"></script>

    <!-- AnyboardJS libraries -->
    <script src="dist/anyboard.js"></script>

    <!-- Include evothings -->
    <script src="libs/evothings/evothings.js"></script>
    <script src="libs/evothings/easyble/easyble.js"></script>

    <!-- Include bluetooth discovery driver -->
    <script src="drivers/discovery.evothings.bluetooth.js"></script>

    <!-- Include driver for LightBlue Bean -->
    <script src="drivers/bean.evothings.bluetooth.js"></script>

    <!-- Include driver for AnyboardJS rfduino Pawn-->
    <script src="drivers/rfduino.evothings.bluetooth.js"></script>
```

	Now you're ready to start writing some code, e.g.
```
<script>
    AnyBoard.TokenManager.scan(function(token) {
            token.connect(function() {
                token.ledBlink("white");
            })
        }
    )
</script>
```

5. You can drag and drop the index.html file into the Evothings workbench in order to run the game on your phone.

More information in [Library documentation](documentation.md)
For examples of games with interactive tokens, check out the anyPawn and anyDeck in the [games directory](../games).

## Develop AnyboardJS further
If you wish to contribute to the development of the AnyBoard library, clone this repo.

### Setup
- Install [node](http://nodejs.org/)
- clone this repo ```git clone git@github.com:tomfa/anyboardjs.git``
- navigate to this folder in console: ```cd path/to/anyboardjs```
- install node dependencies: ```npm install```
- install grunt-cli ```npm install -g grunt-cli``` (potentially need sudo)

You've got what you need in order to develop efficiently! However, you should first note that the grunt build and copy commands (below) **will overwrite** the following code:
- Any code in firmware and drivers folder inside ```examples``` will be overwritten by firmware and drivers in the root folder
- Any code inside **all** ```dist``` folder will be replaced with compiled versions of AnyBoard, which is based on the code in the libs folders.

### Commands
- ```grunt test``` - runs all tests from files in the folder ```test```
- ```grunt build``` - creates a compiled version under ```/dist``` (full and minified)
- ```grunt doc``` - creates a new version of [documentation.md](documentation.md)
- ```grunt copy``` - copies ```/dist/anyboard.js``` to ```/dist/examples/*/dist/anyboard.js``` as well as replacing firmware in the examples.

### Change or add AnyboardJS entities
Change or add AnyboardJS entities by editing or adding files to the [libs](./libs) folder.
The changes will be automatically added to a new build of Anyboard.js upon ```grunt build```.

### Create new drivers
There are two type of drivers. One for discovering devices
([discovery.evothings.bluetooth.js](./drivers/discovery.evothings.bluetooth.js)) and one for spesific chips
( [rfdino.evothings.bluetooth.js](./drivers/rfdino.evothings.bluetooth.js) and  [bean.evothings.bluetooth.js](./drivers/bean.evothings.bluetooth.js)).

If you wish to create a driver for a new device, copy bean.evothing.bluetooth.js and adjust it to the new device.

A new firmware will also have to be made. Copy [BeanToken.ino](./firmware/BeanToken.ino) and adjust
it to the new device.
