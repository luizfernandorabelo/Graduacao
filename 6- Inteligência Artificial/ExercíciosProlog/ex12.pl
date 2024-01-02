inverte_lista([], []).

inverte_lista([H|T], L) :-
  inverte_lista(T, X),
  append(X, [H], L).
