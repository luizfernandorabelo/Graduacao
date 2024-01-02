soma(N1, N2, R) :-
  R is N1 + N2.

soma(N1, N2, N3, R) :-
  soma(N1, N2, N4),
  soma(N3, N4, R).

subtracao(N1, N2, R) :-
  R is N1 - N2.

subtracao(N1, N2, N3, R) :-
  subtracao(N1, N2, N4),
  subtracao(N4, N3, R).

multiplicacao(N1, N2, R) :-
  R is N1 * N2.

multiplicacao(N1, N2, N3, R) :-
  multiplicacao(N1, N2, N4),
  multiplicacao(N3, N4, R).

divisao(N1, N2, R) :-
  R is N1 / N2.

divisao(N1, N2, N3, R) :-
  divisao(N1, N2, N4),
  divisao(N4, N3, R).
