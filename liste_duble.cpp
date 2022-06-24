// liste_duble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<malloc.h>
#include<string.h>


//daca folosim typedef nu va mai trebui sa scriem de fiecare data struct Elev, vom folosi numai Elev
//sau typedef struct Elev Elev
typedef struct Elev {

	char* nume;
	int nrMatricol;

}Elev;
//acesta este aliasul;

typedef struct Nod Nod;

struct Nod {

	Elev informatie;
	Nod* urmator;
	Nod* anterior;

};

typedef struct ListaDubluInlantuita {

	Nod* prim;
	Nod* ultim;

}ListaDubluInlantuita;


Elev initializare(const char* nume, int nrMatricol) {
	Elev e;
	e.nrMatricol = nrMatricol;
	e.nume = (char*)malloc(sizeof(char) * (strlen(nume)+1));
	strcpy(e.nume, nume);
	return e;
}

void inserareInceput(ListaDubluInlantuita* lista, Elev e) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->anterior = NULL;
	nou->urmator = (*lista).prim;
	nou->informatie = e;


	if ((*lista).prim) {
		(*lista).prim->anterior = nou;
		(*lista).prim = nou;
	}
	else {
		(*lista).prim = nou;
		(*lista).ultim = nou;
	}

}


void inserareFinal(ListaDubluInlantuita* lista, Elev e) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->urmator = NULL;
	nou->anterior = lista->ultim;
	nou->informatie = e;

	if (lista->ultim) {
		lista->ultim->urmator = nou;	
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

//inserare pe pozitie data

void inserarePePozitieData(ListaDubluInlantuita* lista, int pozitie, Elev elev) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->informatie = elev;


	Nod* p = lista->prim;
	int index = 0;

	while (p && index < pozitie) {
		p = p->urmator;
		index++;
	}

	if (p) {
		//bucla s-a oprit la un nod din lista. Nodul nou se va seta dupa acest nod
		
		//pas1: legaturi din afara spre lista
		nou->anterior = p;
		nou->urmator = p->urmator;

		//pas 2 legaturi din lista spre nod

		//de la nod anterior la nou
		p->urmator = nou;

		//de la nod urmator la nou
		//verficare daca nou->urmator e null pt ca nu ar merge 
		if (nou->urmator != NULL) {
			nou->urmator->anterior = nou;
		}

	}
	else {
		inserareFinal(lista, elev);
	}




}





void afisareElev(Elev e) {
	printf("Numele elevului este: %s si are numarul matricol %d\n ", e.nume,e.nrMatricol);
}


void afisareListaInceput(ListaDubluInlantuita lista) {

	Nod* p = lista.prim;
	while (p) {
		afisareElev(p->informatie);
		p = p->urmator;
	}

}



void afisareListaSfarsit(ListaDubluInlantuita lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareElev(p->informatie);
		p = p->anterior;
	}

}



void stergereLista(ListaDubluInlantuita* lista) {

	
	if (lista->prim) {
		Nod* nou = lista->prim;
		while (nou->urmator) {

			free(nou->informatie.nume);
			nou = nou->urmator;
			free(nou->anterior);

			free(nou->informatie.nume);
			free(nou);
			lista->prim = NULL;
			lista->ultim = NULL;
		}

	}

}





int main()
{
	ListaDubluInlantuita lista;
	lista.prim = NULL;
	lista.ultim = NULL;


	inserareInceput(&lista, initializare("Andrei", 101));
	inserareInceput(&lista, initializare("George", 102));
	inserareInceput(&lista, initializare("Ionel", 103));
	inserareFinal(&lista, initializare("Vasile", 104));

	printf("\nAfisare inceput:\n");
	afisareListaInceput(lista);
	printf("\nAfisare sfarsit:\n");
	afisareListaSfarsit(lista);



	ListaDubluInlantuita lista2;
	lista2.prim = NULL;
	lista2.ultim = NULL;
	printf("\n");
	inserareFinal(&lista2, initializare("Mihail",105));
	afisareListaInceput(lista2);

	stergereLista(&lista2);
	printf("\nDupa stergere:\n");
	afisareListaInceput(lista2);

}




