var ui = {
    initiate: function() {
        $('.activate-next-panel').click(function(){
            $(this).parents('.panel').hide();
            $(this).parents('.panel').next().show();
            logic.trigger($(this).parents('.panel').next()[0].id);
        });
        $('.init-game').click(function(){
            ui.activatePanel('game-init');
        });
        $('.discover-bluetooth').click(function(){
            logic.discover();
        });

        $('.activate-question').click(function(){
            ui.nextQuestion();
        });
        $('.activate-answer').click(ui.showAnswer);
    },

    activatePanel: function(panelName) {
        $('.panel:visible').hide();
        $('.panel.panel-' + panelName).show();
        logic.trigger(panelName);
    },

    nextQuestion: function(){
        var question = logic.getNextQuestion();

        if (question) {
            $('.question-wrapper').remove();
            var alternativesHTML = "";
            var alternatives = question.alternatives;
            for (var i = 0; i < alternatives.length; i++) {
                alternativesHTML += '<p class="alternative ' + d.locations[i+3] + '">' +
                '    ' + alternatives[i].text +
                '</p>'
            }
            $('#game').prepend("" +
                '<div class="question-wrapper">' +
                '<p class="question-text">' + question.question + '</p>' +
                alternativesHTML +
                '</div>'
            )
        } else {
            ui.activatePanel('summary');
        }
    },

    showAnswer: function() {
        var question = logic.getCurrentQuestion();
        logic.givePoints();
        $('.question-wrapper').remove();
        $('#game').prepend("" +
            '<div class="question-wrapper">' +
            '<p class="question-text">' + question.question + '</p>' +
            '<p class="answer">Answer: ' + question.answer + '</p>' +
            '<p class="game-instruction">Put your tokens back on black question tile when you\'re ready for the next question</p>' +
            '</div>'
        )
    },

    finishGame: function(){
        $('#summary .content').html('');
        $('#summary .content').prepend('<h4>Game over! - Results:</h4>');
        var playersHTML = "";
        for (var index in d.players) {
            playersHTML += '<div class="result"><button class="player-icon ' + d.players[index].color +
            '">&nbsp;</button>' + d.players[index].points + ' poeng</div>';
            d.players[index].points = 0;
        }
        $('#summary .content').append(playersHTML)
        d.currentQuestionPos = undefined;

    }
};