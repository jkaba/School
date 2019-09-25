/* Facts */
word(top, t,o,p).
word(dog, d,o,g).
word(run, r,u,n).
word(five, f,i,v,e).
word(four, f,o,u,r).
word(lost, l,o,s,t).
word(mess, m,e,s,s).
word(unit, u,n,i,t).
word(baker, b,a,k,e,r).
word(forum, f,o,r,u,m).
word(green, g,r,e,e,n).
word(super, s,u,p,e,r).
word(prolog, p,r,o,l,o,g).
word(vanish, v,a,n,i,s,h).
word(wonder, w,o,n,d,e,r).
word(yellow, y,e,l,l,o,w).

/* Solution */
crossword(V1, V2, V3, H1, H2) :-
word(V1, V1H1, _, V1H2 ,_),
word(V2, V2H1, _, V2H2),
word(V3, V3H1, _, V3H2 ,_),
word(H1, V1H1, _, V2H1, _, V3H1),
word(H2, V1H2, _, V2H2, _, V3H2, _).