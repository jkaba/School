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

var numCorrect = 0;
var numIncorrect = 0;

document.getElementById("correct").innerHTML = numCorrect;
document.getElementById("incorrect").innerHTML = numIncorrect;

function incrementCorrect(){
    numCorrect++;
    result = true;
    document.getElementById("correct").innerHTML = numCorrect;
}

function incrementIncorrect(){
    numIncorrect++;
    result = true;
    document.getElementById("incorrect").innerHTML = numIncorrect;
}

function checkTotal(){
    if(numCorrect + numIncorrect == 36){
        document.getElementById("correct_btn").disabled = true;
        document.getElementById("incorrect_btn").disabled = true;
    }
}

function disableQA(){
    if(result == false){
        document.getElementById("question").disabled = true;
        document.getElementById("answer").disabled = true;
    }
    else{
        document.getElementById("question").disabled = false;
        document.getElementById("answer").disabled = false;
    }
}