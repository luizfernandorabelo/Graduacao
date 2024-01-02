fatorial(0, X) :- 
  X is 1.

fatorial(N, X) :-
  N > 0,
  Y is N - 1,
  fatorial(Y, F),
  X is N * F.
