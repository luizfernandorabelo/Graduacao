soma_numeros([], 0).

soma_numeros([H|T], X) :-
  soma_numeros(T, Y),
  X is H + Y.
