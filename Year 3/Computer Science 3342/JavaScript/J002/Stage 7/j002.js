//Stage 1
document.getElementById("description").innerHTML = examdatabase.description;

// Create variables
var number = 0;
var result = true;

// Set the timer intervals
setInterval(checkTotal, 300);
setInterval(disableQA, 300);

// Question function which gets a randomly generated question
function showQuestion(){
	if(result == true){
		var random = Math.floor(Math.random() * (36));
	 	number = random;
		document.getElementById("question").innerHTML = examdatabase.questions[number].question;
		var answer = document.getElementById("answer");
		if(answer.innerHTML != ""){
			document.getElementById("answer").innerHTML = "";
		}
		result = false;
	}
}

// Answers function which gets the answer for the question
function showAnswer(){
	document.getElementById("answer").innerHTML = examdatabase.questions[number].answer;
}

// More variables
var numCorrect = 0;
var numIncorrect = 0;

// Get the elements for use
document.getElementById("correct").innerHTML = numCorrect;
document.getElementById("incorrect").innerHTML = numIncorrect;

// Increment correct function used to increase number of correct questions
function incrementCorrect(){
	numCorrect++;
	result = true;
	document.getElementById("correct").innerHTML = numCorrect;
}

// Increment incorrect function used to increase number of incorrect questions
function incrementIncorrect(){
	numIncorrect++;
	result = true;
	document.getElementById("incorrect").innerHTML = numIncorrect;
}

// Check total function used to check the total correct and incorrect
function checkTotal(){
	if(numCorrect + numIncorrect == 36){
		document.getElementById("correct_btn").disabled = true;
		document.getElementById("incorrect_btn").disabled = true;
	}
}

// disable QA function used to disable the ability to get questions or answers
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