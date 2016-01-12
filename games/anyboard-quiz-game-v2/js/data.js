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
				{"text": "George Washington", "correct": true },
                {"text": "Abraham Lincoln", "correct": false },
                {"text": "Simone Mora", "correct": false },
                {"text": "Monica Divitini", "correct": false },
            ],
            "answer": "George Washington (February 22, 1732 – December 14, 1799) was the first President of the United States (1789–97), the Commander-in-Chief of the Continental Army during the American Revolutionary War, and one of the Founding Fathers of the United States."
        },
        {
            "question": "From which country comes Samsung?",
            "alternatives": [
                {"text": "Japan", "correct": false },
                {"text": "China", "correct": false },
                {"text": "Nepal", "correct": false },
                {"text": "South Korea", "correct": true },
            ],
            "answer": "Samsung is a South Korean multinational conglomerate company headquartered in Seoul. Samsung was founded by Lee Byung-chul in 1938 as a trading company. "
        },
		{
            "question": "Which city has the highest population?",
            "alternatives": [
                {"text": "New York", "correct": false },
                {"text": "Mexico", "correct": false },
                {"text": "Tokyo", "correct": true },
                {"text": "Jakarta", "correct": false },
            ],
            "answer": "Tokyo is one of the 47 prefectures of Japan, and is both the capital and largest city of Japan, with 13,297,629 inhabitants. It is the seat of the Emperor of Japan and the Japanese government."
        },
		{
            "question": "Who was the first man in space?",
            "alternatives": [
                {"text": "Alan Shepard", "correct": false },
                {"text": "Youri Gagarine", "correct": true },
                {"text": "John Glenn", "correct": false },
                {"text": "Neil Armstrong", "correct": false },
            ],
            "answer": "Yuri Alekseyevich Gagarin (9 March 1934 – 27 March 1968) was a Russian Soviet pilot and cosmonaut. He was the first human to journey into outer space, when his Vostok spacecraft completed an orbit of the Earth on 12 April 1961."
        },
		{
            "question": "What instrument did the jazz musician Miles Davis play?",
            "alternatives": [
                {"text": "Guitar", "correct": false },
                {"text": "Trumpet", "correct": true },
                {"text": "Saxophone", "correct": false },
                {"text": "Piano", "correct": false },
            ],
            "answer": "Miles Dewey Davis III (May 26, 1926 – September 28, 1991) was an American jazz musician, trumpeter, bandleader, and composer. Widely considered one of the most influential musicians of the 20th century, Miles Davis was, together with his musical groups, at the forefront of several major developments in jazz music, including bebop, cool jazz, hard bop, modal jazz, and jazz fusion."
        }
    ],
    devices: {},
    listeners: {},
    players: [],
    colors: ['white', 'green', 'red', 'blue'] // Player colors
};