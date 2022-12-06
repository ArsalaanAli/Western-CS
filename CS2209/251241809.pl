%Question 1: Family Tree

male(john1).
male(peter).
male(rob).
male(george).
male(john2).
male(jay).

female(sue).
female(ida).
female(estelle).
female(grace).
female(mary).

parent(sue, estelle).
parent(john1, rob).
parent(john1, estelle).
parent(sue, rob).

parent(ida, grace).
parent(peter, george).
parent(ida, george).
parent(peter, grace).

parent(estelle, john2).
parent(estelle, mary).
parent(estelle, jay).
parent(george, john2).
parent(george, mary).
parent(george, jay).

grandfather(X, Y) :- 
    male(X),
    parent(X, Z),
    parent(Z, Y).

grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

ancestor(X, Y) :- 
	parent(X, Y).
ancestor(X, Y) :- 
	parent(X, Z), ancestor(Z, Y).

brother(X, Y) :-
    male(X),
    parent(A, X),
    parent(A, Y),
    X\=Y.

a_pair_of_brother(X, Y) :-
    male(X),
    male(Y),
    parent(A, X),
    parent(A, Y),
    X \= Y.

uncle(X, Y) :-
    male(X),
    parent(A, Y),
    brother(X, A).

married(X, Y) :-
    parent(X, A),
    parent(Y, A),
    X \= Y.

mother_in_law(X, Y) :-
    female(X),
    parent(X, A),
    married(A, Y).

%Question 2: Facts:

%Cities
city(chicago).
city(toronto).
city(detroit).
city(orlando).

%Airport names
airport(chicago, midway).
airport(chicago, ohare).
airport(toronto, pearson).
airport(toronto, bishop).
airport(orlando, international).
airport(orlando, sanford).
airport(detroit, metro).
airport(detroit, willow).

%WW2 Heroes
ww2hero(ohare).
ww2hero(bishop).
ww2hero(jackson).
ww2hero(schindler).
ww2hero(wallenberg).
ww2hero(duckwitz).

ww2battle(midway).
ww2battle(bulge).
ww2battle(normandy).
ww2battle(kursk).

%Question 3a) Last in List:

last1(X,[X]).
last1(X,[_|Z]):-
    last1(X,Z).

%Question 3b) Adjacent:

adjacent1(X,Y,[X,Y|_]).
adjacent1(X,Y,[_|T]):-
	adjacent1(X,Y,T).

%Question 3c) Palindrome:

palindrome(L):-
  reverse(L, L).

%Question 4: Fibonacci:

fibo(0, 0) :- !.
fibo(1, 1) :- !.
fibo(N, F) :-
        N > 1,
        N1 is N-1,
        N2 is N-2,
        fibo(N1, F1),
        fibo(N2, F2),
        F is F1+F2.

%Question 5:


%Sum of a list:
sum([],0).
sum([X|R],A):-
	sum(R,P),
	A is P+X.

%Average of a list:
average(List, Average):- 
    sum(List, Sum),
    length(List, Length),
    Length > 0, 
    Average is Sum / Length.


%Min of List:
min([Item], Item).
min([Item | List], Item) :- 
	min(List, List_Answer),
	Item =< List_Answer, !.
min([_Item | List], Answer) :-
	min(List, Answer).


%Max of List:
max([Max], Max).
max([Head | List], Max) :-
  max(List, Maxoflist),
  ( Head > Maxoflist -> Max = Head ; Max = Maxoflist ).
