fibonnacci(N, X) :-
  N =< 1,
  X is N.

fibonnacci(N, X) :-
  N > 1,
  Y1 is N - 1,
  Y2 is N - 2,
  fibonnacci(Y1, X1),
  fibonnacci(Y2, X2),
  X is X1 + X2.