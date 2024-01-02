genitor(barb,pameron).
genitor(merle,pameron).
genitor(barb,cameron).
genitor(merle,cameron).
genitor(javier,manny).
genitor(gloria,manny).
genitor(jay,joe).
genitor(gloria,joe).
genitor(jay,mitchel).
genitor(dede,mitchel).
genitor(jay,claire).
genitor(dede,claire).
genitor(frank,phil).
genitor(grace,phil).
genitor(bo,calhoun).
genitor(pameron,calhoun).
genitor(mitchel,lily).
genitor(cameron,lily).
genitor(mitchel,rexford).
genitor(cameron,rexford).
genitor(phil,haley).
genitor(claire,haley).
genitor(phil,alex).
genitor(claire,alex).
genitor(phil,luke).
genitor(claire,luke).
genitor(dylan,george).
genitor(haley,george).
genitor(dylan,poppy).
genitor(haley,poppy).

homem(barb).
homem(phil).
homem(jay).
homem(mitchel).
homem(dylan).
homem(javier).
homem(bo).
homem(frank).

mulher(cameron).
mulher(pameron).
mulher(grace).
mulher(haley).
mulher(dede).
mulher(claire).
mulher(gloria).
mulher(merle).

mae(X,Y) :-
  mulher(X),
  genitor(X,Y).

pai(X,Y) :-
  homem(X),
  genitor(X,Y).

pais(X,Y,Z) :-
  genitor(X,Z),
  genitor(Y,Z),
  homem(X),
  mulher(Y).

irmaos(X,Y) :-
  genitor(Z,X),
  genitor(Z,Y),
  \+ (X == Y).

tio_tia(X,Y) :-
  mae(M,Y),
  irmaos(X,M).

avo(X,Y) :-
  genitor(X,Z),
  genitor(Z,Y).

avo_materna(X,Y) :-
  mae(X,Z),
  mae(Z,Y).

primos(X,Y) :-
  genitor(Z,X),
  genitor(W,Y),
  irmaos(Z,W).

ancestral(X,Y) :-
  genitor(X,Y).

ancestral(X,Y) :-
  genitor(X,Z),
  ancestral(Z,Y).

descendente(X,Y) :-
  ancestral(Y,X).
