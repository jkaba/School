last(X,[X]).
last(X,[Y|Xs]):-last(X,Xs).

adjacent(X,Y,[X,Y|Zs]).
adjacent(Y,X,[X,Y|Zs]).
adjacent(X,Y,[Z|Zs]):-adjacent(X,Y,Zs).

substitute(X,Y,[],[]).
substitute(X,Y,[X|Xs],[Y|Ys]):-substitute(X,Y,Xs,Ys).
substitute(X,Y,[Z|Xs],[Z|Ys]):-X\=Z, substitute(X,Y,Xs,Ys).