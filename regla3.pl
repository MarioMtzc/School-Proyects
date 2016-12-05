/*numero de alumnos que aprobaron una uea y que aprobaron otra en el trimestre anterior*/

/*miembro de la lista*/
miembro(X,[X|_]). 										
miembro(X,[_|Y]):-
	miembro(X,Y).

/*lista de alumnos*/
lista(L) :- findall(A,reg(A,_,_,_),L).

/*elimina repeticiones*/
ueas([],[]):- !.

ueas([X|Xs],Ys):-
	miembro(X,Xs), !, ueas(Xs,Ys).

ueas([X|Xs],[X|Ys]):-
	ueas(Xs,Ys).

listaSN (A,X):-
	lista(A,L),ueas(L,X).
/*comprobar que tenga 2 o mas ueas diferentes de NA*/

/*Ueas que aprobo el alumno */
uea Aprobada(Alum,tri,L) :- findall(U,(reg(Alum,U,C,Tri),C\==na),L);

/*Obtencion de la lista de alumnos que aprobaron una uea*/
aprueba(Uea,L) :- findall(Alum,(reg(Alum,Uea,C,_),C\==na),L);

/*verificar si son consecutivas*/
