var examdatabase = {
     "questiontemplate": {
        "question": "What is the answer?",
        "answer": "That which was asked for",
        "note": "optional note",
        "source": "SLSW# or ICD# where # is chapter number"
     },
  "description": "questions from which to construct the Winter 2017 final exam in CS3342b",
  "questions": [
     {
        "question": "Adding a feature to a programming language to make it easier to do something that was already doable is called adding ANSWER?",
        "answer": "syntactic sugar",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "Matz, the creator of Ruby, thinks that it is less important to optimize the execution (efficiency) of a programming language and more important to optimize the efficiency of ANSWER",
        "answer": "the programmers",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "A programming language is called ANSWER if it is executed by an interpreter rather than by first being compiled with a compiler",
        "answer": "interpreted",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "If the types of a programming language are bound at execution time rather than compile time, then the types are called ANSWER",
        "answer": "dynamically typed",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In describing the properties of an object oriented language, encapsulation means ANSWER",
        "answer": ["data and behavior are packaged together", "there is a mechanism for restricting access to an object's components"],
        "note": "the first is the textbook answer, but there are actually two usages of the term encapsulation in the object-oriented programming community https://en.wikipedia.org/wiki/Encapsulation_(computer_programming)",
        "source": "SLSW2"
     },
     {
        "question": "In discussing object oriented languages, objects are organized into a class tree to support the property of ANSWER",
        "answer": "inheritance",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In discussing object oriented languages, being able to handle objects of related types is called ANSWER",
        "answer": "polymorphism",
        "note": "polymorphism has a different usage in the object oriented programming community than in the functional programming community",
        "source": "SLSW# or ICD# where # is chapter number"
     },
     {
        "question": "The application that caused a significant increase in the popularity of Ruby was a web framework called ANSWER",
        "answer": "Rails (or Ruby on Rails)",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "The concurrency approach used in Ruby is ANSWER",
        "answer": "threads",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "The command name for the Ruby interpreter is",
        "answer": "irb",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, true.class returns ANSWER",
        "answer": "TrueClass",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "Ruby supports two common ways that boolean expressions are handled in programming languages.  In one approach both subexpressions of a boolean operator are evaluated before the boolean operator is evaluated.  In the other approach, called ANSWER, the first subexpression in a boolean expression is evaluated and if that is enough to know the result of the boolean expression, then the second subexpression is not evaluated.",
        "answer": "short-circuit evaluation",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, normally, when you try to add a String to a Fixnumm, you get an error message saying that a String can't be coerced to a Fixnum.  This is because Ruby is ANSWER typed.",
        "answer": "strongly",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "One way of checking types is to see what constructor was used to create an object that is a parameter.  Another way of checking types is to wait until a method is sent to an object and see if it supports the method.  This second way is called ANSWER",
        "answer": "duck typing",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "A major claim in object oriented design philosophy is that you should code to ANSWER rather than code to implementation",
        "answer": "interface",
        "note": "this is discussed in more detail elsewhere http://www.artima.com/lejava/articles/designprinciplesP.html",
        "source": "SLSW2"
     },
     {
        "question": "The & notation in the line of Ruby def george(&sam) is used to indicate that sam is ANSWER",
        "answer": "a code block",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "The : notation in the Ruby expressions :hi is used to indicate that hi is ANSWER",
        "answer": "a symbol",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "With respect to the value returned by the Ruby expression 'hi'.object_id == 'hi'.object_id, you can say it ANSWER",
        "answer": "could be either true or false",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "With respect to the value returned by the Ruby expression :hi.object_id == :hi.object_id, you can say it ANSWER",
        "answer": "will always be true",
        "note": "optional note",
        "source": "SLSW# or ICD# where # is chapter number"
     },
     {
        "question": "To execute a code block in Ruby that is passed to a method but doesn't appear on its parameter list, you use the keyword ANSWER",
        "answer": "yield",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "To execute a code block in Ruby that is passed to a method on its parameter list, you send that parameter the method ANSWER",
        "answer": "call",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "A code block is some lines of code surrounded by either curly braces or ANSWER",
        "answer": "do end",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, the expression Fixnum.class returns ANSWER",
        "answer": "Class",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "The root of the inheritance hierarchy in Ruby is the class ANSWER",
        "answer": "Object",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, the name of the method in the class Me that is automatically invoked when a new object of type Me is created with Me.new is ANSWER",
        "answer": "initialize",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, the @ is used to indicate that the variable @me is ANSWER",
        "answer": "an instance variable",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, the @@ is used to indicate that the variable @@me is ANSWER",
        "answer": "a class variable",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, by convention, the ? in the method me? is used to indicate that me is ANSWER",
        "answer": "boolean",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, the mixin is used to solve the object-oriented programming problem of ANSWER",
        "answer": "multiple inheritance",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "The feature of programs being able to `write programs' (creating application specific language features) is called ANSWER",
        "answer": "metaprogramming",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, if you declare a class with a class name that is already in use and put in it the definition of a new method, you have changed the functionality of the existing class (even if it is a predefined class like Fixnum).  The property of Ruby that allows this is ANSWER",
        "answer": "open classes",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "When you send a message to a Ruby object, Ruby first looks at the methods that object supports, and then starts working the inheritance chain.  If it still can't find the appropriate method, the message and its parameters get passed as a message to the object looking for a method called ANSWER",
        "answer": "method_missing",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In the Ruby community, the acronym DSL is an abbreviation for ANSWER",
        "answer": "domain specific language",
        "note": "optional note",
        "source": "SLSW2"
     },
     {
        "question": "In Ruby, if a line starts with a method name, that method is being sent to the object named ANSWER",
        "answer": "self",
        "note": "this crops up in understanding various example pieces of code in the chapter",
        "source": "SLSW2"
     },
     {
        "question": "When you define a method in a class, normally it is meant to be invoked on an object of that class (an instance method).  Sometimes it is meant to be invoked on the class name itself (a class method), like Date.parse('3rd Feb 2001').  In Ruby, to define a class method, we put ANSWER at the beginning of the method name in its definition.",
        "answer": "self.",
        "note": "this crops up in understanding various example pieces of code in the chapter",
        "source": "SLSW2"
     },

     null
  ]
}
