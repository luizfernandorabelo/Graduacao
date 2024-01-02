comprimento([], 0).

comprimento([_|T], X) :-
  comprimento(T, Y),
  X is Y + 1.
