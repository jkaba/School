/* FACTS */
father(X,Y) :- parent(X,Y), male(X).
mother(X,Y) :- parent(X,Y), female(X).
brothers(X,Y) :- sibling(X,Y),male(X),male(Y),X\=Y.
sibling(X,Y) :- parent(Z,X), parent(Z,Y), X\=Y.
grandson(X,Y) :- parent(Y,Z), parent(Z,X), male(X).
cousin(X,Y) :- parent(Z,X), sibling(Z,A), parent(A,Y).
married(X,Y) :- father(X,Z), mother(Y,Z).
motherinlaw(X,Y) :- married(Z,Y), mother(X,Z).
motherinlaw(X,Y) :- married(Y,Z), mother(X,Z).
descendent(X,Y):- parent(Y,X). 
descendent(X,Y):- parent(P,X),descendent(P,Y). 

male(james).
male(drew).
male(ken).
male(tim).

female(vivian).
female(lisa).
female(amber).
female(amy).

parent(vivian,ken).
parent(james,ken).
parent(amber,james).
parent(amber,drew).
parent(drew,tim).
parent(amy,tim).
parent(lisa,vivian).
parent(lisa,amy).