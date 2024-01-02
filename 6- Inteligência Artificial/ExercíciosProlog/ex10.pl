ocorrencias(_, [], 0).

ocorrencias(E, [E|T], X) :-
  count_occurrences(E, T, Y),
  X is Y + 1.

ocorrencias(E, [H|T], X) :-
  count_occurrences(E, T, X).
