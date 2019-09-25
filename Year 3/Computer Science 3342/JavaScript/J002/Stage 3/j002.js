document.getElementByID("description").innerHTML = examdatabase.description;

var number = 0;
var result = true;

setInterval(checkTotal, 300);
setInterval(disableQA, 300);

function showQuestion(){
    if(result == true){
        var random = Math.floor(Math.random() * (36));
        number = random;
        document.getElementByID("question").innerHTML = examdatabase.questions[number].question;
        var answer = document.getElementByID("answer");
        if(answer.innerHTML != ""){
            document.getElementByID("answer").innerHTML = "";
        }
        result = false;
    }
}

function showAnswer(){
    document.getElementByID("answer").innerHTML = examdatabase.questions[number].answer;
}