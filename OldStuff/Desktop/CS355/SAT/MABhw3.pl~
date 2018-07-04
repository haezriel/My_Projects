%Michael Allen-Bond
%michael.allen-bond@email.wsu.edu
%CS 355
%Dr. Dang
%Assignment 3


%Eval-var function.  X is the variable, if it's the first element pair in the list, it returns V, the second element. If not,  it recursively calls the tail of the list.  My first function, so it's a little weird looking.
eval-var(X,[[X,V]|_],V).
eval-var(X,[[_,_]|[[Y,T]|Z]],V):- eval-var(X,[[Y,T]|Z],V).






%Eval-clause function. If empty (no more clauses left to eval), X is set to true.
eval-clause(_,[],X):- X=true.
%If not empty, checks if H is a list([not,b]), and then fetches b (2nd element), assigns it to Elem, and then evals for false (to make clause true). If H is not a list, then evals for true, and if this fails as well, then X=false.
eval-clause(A,[H|T],X):- is_list(H)->  
    						nth1(2,H,Elem),
    						eval-var(Elem,A,false),
    						eval-clause(A,T,X);
    						eval-var(H,A,true)->  
    						eval-clause(A,T,X);
    						X=false.




%get-vars function.  flattens the list, deletes the 'not', sorts (removing duplicates).
get-vars(L,X):- flatten(L,Z),
    			delete(Z, not, K),
    			sort(K,X).
					
%Identical to get-vars function, since a size limit here is not necessary.
get-all-vars(L,X):- flatten(L,Z),
					delete(Z, not, K),
    				sort(K,X).



%unsat-clauses function. if clauses are empty, return empty.
unsat-clauses([],_,[]).
%Otherwise, evaluate each clause for a false value, and if so, append that clause to the recursive call. if not false, then move on to the recursive call using the tail.
unsat-clauses([H|T],K,X):- eval-clause(K,H,false) ->
							unsat-clauses(T,K,P),
    						append([H],P,X);
    						unsat-clauses(T,K,X).



%flip-var function. Two cases, one if the variable is true, the other for false. And the empty case, of course.
flip-var(_,[],[]).
%if the head's second value is false, we create a new list with the A value and 'true', and then append it to our list. the second case is if the head's second value is true, and does the same thing, but inverse.
flip-var(A,[[H,false]|Z],X):- A==H ->  
							V=[A,true],
    						append([V],Z,X);
  							flip-var(A,Z,K),
    						append([[H,false]],K,X).
flip-var(A,[[H,true]|Z],X):- A==H -> 
    						V=[A,false],
    						append([V],Z,X);
    						flip-var(A,Z,K),
							append([[H,true]],K,X).



%get-better-neighbor function. If conflicting variables list is empty, returns same state that was entered.Otherwise, grabs the head of the conflicting variables list, and calls flip-var on it, then calls unsat-clauses on the new state, then length on the returned clauses, then if that length is less than the former length, sets X=F, the new state.  If not, then recursively call get-better-neighbor with the tail of the list.
get-better-neighbor(_,B,[],_,B).
get-better-neighbor(A,B,[H|T],D,X):-
    flip-var(H,B,F),
    unsat-clauses(A,F,G),
    length(G,I),
    I<D ->  X=F;
    get-better-neighbor(A,B,T,D,X).



%simple-hill-climb function.  This is simpler than it should be, since it doesn't randomly reset to accomodate for plateaus or potentially less-than-optimal answers, but it recursively calls get-better-neighbor until we either have no more unsat-clauses, or our counter C hits 0.
simple-hill-climb(_,B,_,[],B).
simple-hill-climb(_,B,0,_,B).
simple-hill-climb(A,B,C,D,X):-
   get-all-vars(D,E),
  	length(D,F),
    get-better-neighbor(A,B,E,F,G),

    plus(C,-1,J),
    unsat-clauses(A,G,I),
    simple-hill-climb(A,G,J,I,X).

    
    

%These are all just the test cases I used, they can be ignored.                    

%simple-hill-climb([[a,[not,b],c],[c,[not,d],e],[a,[not,e],f]],
%	[[a,false],[b,true],[c,true],[d,false],[e,true],[f,true]],
%	10,[[a,[not,b],c],[c,[not,d],e],[a,[not,e],f]],X).

                  

%get-better-neighbor([[a,[not,b],c],[c,[not,d],e],[a,[not,e],f]],
  %     [[a,false],[b,true],[c,true],[d,false],[e,true],[f,true]],
   %    [a,b,c,d,e,f], 3, X).
                    
%eval-clause([[a,true],[b,false],[c,true],[d,false]],[a,[not,b],c],X).
%get-vars([a,[not,b],c],X).

%get-all-vars([[a,[not,b],c],[c,[not,d],e],[a,[not,e],f]],X).
%unsat-clauses([[a,[not,b],c],[a,[not,b],[not,c]],[a,[not,b],d]],[[a,false],[b,true],[c,true],[d,false]],X).
%flip-var(a,[[a,false],[b,true],[c,true],[d,false]],X).
