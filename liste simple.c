#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Avion {
	char* compania;
	int capacitate;
};

struct Nod {
	struct Avion avion;
	struct Nod* next;
};


struct Nod* inserareInceput(struct Nod* cap, struct Avion a) {
	//creem nod
	//copiem info utila
	//legam nodul de lista(la primul nod)
	//Se muta capul la nodul inserat
	//return nod nou

	//struct Nod* nou;

	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->avion = a;
	nou->next = cap;

	return nou;
}


struct Avion creareAvion(const char* Companie, int Capacitate) {

	struct Avion a;
	a.compania = (char*)malloc((strlen(Companie)+1)*sizeof(char));
	strcpy_s(a.compania, strlen(Companie) + 1, Companie);
	//strcpy(a.compania, Companie);
	a.capacitate = Capacitate;
	
	return a;
}




void afisareAvion(struct Avion a) {
	printf("%s\t", a.compania);
	printf("%d\n", a.capacitate);

}



void afisareLista(struct Nod* cap) {

	while (cap) {
		afisareAvion(cap->avion);
		cap = cap->next;
	}
}

void stergereLista(struct Nod** cap) {

	
	while ((*cap)) {
		free((*cap)->avion.compania);
		struct Nod* aux = (*cap);
		*cap = (*cap)->next;
		free(aux);
	}

}



void insereazaFinal(struct Nod** cap, struct Avion a) {

	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->avion = a;
	nou->next = NULL;

	if (*cap != NULL) {
		struct Nod* p= *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}

}



void insereazaMijloc(struct Nod** lista, struct Nod nodul, struct Avion a) {






}






int main() {

	struct Nod* lista = NULL;

	lista = inserareInceput(lista, creareAvion("Turkish Airlines", 300));
	//functia va returna adresa noului nod in lista 
	lista = inserareInceput(lista, creareAvion("Tarom", 400));
	lista = inserareInceput(lista, creareAvion("Fly", 400));


	insereazaFinal(&lista, creareAvion("Mihail", 1000));
	afisareLista(lista);

	stergereLista(&lista);

}