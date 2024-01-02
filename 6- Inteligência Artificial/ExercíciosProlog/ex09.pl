concatena(L1, [], L1).

concatena([], L2, L2).

concatena(L1, [H|T], L2) :-
  append(L1, [H], L3),
  concatena(L3, T, L2).
