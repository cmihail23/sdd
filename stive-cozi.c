#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//se pot implementa pe liste simple, duble si vectori

typedef struct Tara Tara;
typedef struct Nod Nod;

typedef struct Tara {
	char* denumire;
	int populatie;
};


struct Tara creareTara(const char* den, int pop) {

	Tara a;
	a.denumire = (char*)malloc((strlen(den) + 1) * sizeof(char));
	strcpy(a.denumire, den);
	a.populatie = pop;
	return a;

}

void afisareTara(Tara t) {

	printf("\n%s %d",t.denumire,t.populatie);

}




struct Nod {
	Tara tara;
	Nod* next;
};



Nod* push(Nod* cap, Tara t){

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->tara = t;
	nou->next = cap;
	return nou;

}

Tara pop(Nod** cap) {
	
	if (*cap) {
		Nod* copy = *cap;
		(*cap) = (*cap)->next;
		Tara t = copy->tara;
		free(copy);
		return t;
	}
	else {
		
		Tara t = creareTara("Anonim", 0);
		return t;
	};

}


void afisareStiva(Nod** stiva) {
	while (*stiva) {
		Tara t = pop(stiva);
		afisareTara(t);
		free(t.denumire);
	}
}



void stergeElement(Nod** stiva, char* nume) {

	Nod* temp = NULL;
	
	while ((*stiva) && (strcmp(nume, (*stiva)->tara.denumire)!=0)) {

		Tara aux = pop(stiva);
		temp = push(temp,aux);

	}
	if (*stiva != NULL) {
		Tara a = pop(stiva);
		free(a.denumire);
	}

	while (temp) {
		Tara aux = pop(&temp);
		*stiva = push(*stiva, aux);
	}


}








void main() {


	Nod* stiva = NULL;

	stiva = push(stiva, creareTara("Romania", 10));
	stiva = push(stiva, creareTara("Franta", 20));
	stiva = push(stiva, creareTara("Italia", 15));

	
	
	stergeElement(&stiva, "Franta");
	afisareStiva(&stiva);

}