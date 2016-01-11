// short for data. "data" variable seems to be overwritten, perhaps by evothings tools, and unavailable
var d = {
    locations: {
        1: "red", // 12228
        2: "black", // 5737
        3: "yellow", // 18330
        4: "green", // 4560
        5: "purple", // 8550
        6: "blue", // 6306
        7: "brown", // 5920
        8: "grey" // 8436
    },
    currentQuestionPos: undefined,
    questions: [
        {
            "question": "Who was the first president of USA?",
            "alternatives": [
                {"text": "Abraham Lincoln", "correct": true },
                {"text": "George Washington", "correct": true },
                {"text": "Simone Mora", "correct": false },
                {"text": "Monica Divitini", "correct": false },
            ],
            "answer": "George Washington bla bla bla bla"
        },
        {
            "question": "From which country comes Samsung?",
            "alternatives": [
                {"text": "Japan", "correct": true },
                {"text": "China", "correct": false },
                {"text": "South Korea", "correct": false },
                {"text": "Nepal", "correct": false },
            ],
            "answer": "Japan bla bla bla bla"
        }
    ],
    devices: {},
    listeners: {},
    players: [],
    colors: ['white', 'green', 'red', 'blue'] // Player colors
};