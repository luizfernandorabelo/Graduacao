esta_contido(X, [X|_]).

esta_contido(X, [H|T]) :-
  esta_contido(X, T).