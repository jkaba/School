document.getElementByID("description").innerHTML = examdatabase.description;

// Create variables
var number = 0;
var result = true;

// Set the timer intervals
setInterval(checkTotal, 300);
setInterval(disableQA, 300);

// Question function which gets a randomly generated question
function Question(){
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

// Answers function which gets the answer for the question
function Answers(){
    document.getElementByID("answer").innerHTML = examdatabase.questions[number].answer;
}

