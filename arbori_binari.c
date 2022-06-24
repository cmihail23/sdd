#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>


typedef struct Prajitura Prajitura;
typedef struct Nod Nod;

struct Prajitura {
	int id;
	char* producator;
	float pret;
};




struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Prajitura prajitura;
};

Prajitura initializarePrajitura(int id, const char* producator, float pret) {
	Prajitura p;
	p.id = id;
	p.pret = pret;
	p.producator = (char*)malloc((strlen(producator)+1)*sizeof(char));
	strcpy(p.producator, producator);
	return p;
}

void afisarePrajitura(Prajitura p) {
	printf("\nPrajitura  are ID:%d, este produsa de %s si are pretul:%.2f", p.id, p.producator,p.pret);
}



//inserare
void inserarePrajituraArbore(Nod** radacina, Prajitura p) {

	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->prajitura = p;
		*radacina = nou;
	}
	else {
		if (p.id > (*radacina)->prajitura.id ) {
			inserarePrajituraArbore(&(*radacina)->dreapta, p);
		}
		else if(p.id < (*radacina)->prajitura.id) {
			inserarePrajituraArbore(&(*radacina)->stanga, p);
		}

	}
}

//parcurgeri
//preordine - radacina, stanga, dreapta  RSD
//inordine - stanga, radacina, dreapta		SRD
//postordine - stanga, dreapta, radacina  SDR


void parcurgerePreOrdine(Nod* radacina) {
	if (radacina) {
		afisarePrajitura(radacina->prajitura);
		parcurgerePreOrdine(radacina->stanga);
		parcurgerePreOrdine(radacina->dreapta);
	}
}

void parcurgereInOrdine(Nod* radacina) {
	if (radacina) {
		parcurgereInOrdine(radacina->stanga);
		afisarePrajitura(radacina->prajitura);
		parcurgereInOrdine(radacina->dreapta);
	}

}

//cautare in arbore
Prajitura cautarePrajitura(int id, Nod* radacina) {

	if (radacina) {

		if (radacina->prajitura.id > id) {
			return cautarePrajitura(id, radacina->stanga);
		}
		else if(radacina->prajitura.id < id){
			return cautarePrajitura(id, radacina->dreapta);
		}
		else {
			Prajitura nou;
			nou.producator = (char*)malloc((sizeof(radacina->prajitura.producator) + 1) * sizeof(char));
			strcpy(nou.producator, radacina->prajitura.producator);
			nou.id = radacina->prajitura.id;
			nou.pret = radacina->prajitura.pret;
			return nou;
		}
	}
	else {
		Prajitura nou = initializarePrajitura(-1, "Not Found", 0);
		return nou;

	}
}


//stergere- se prefera postOrdine pt a sterge
void stergeArborePost(Nod** radacina) {
	if (*radacina) {
		stergeArborePost(&(*radacina)->stanga);
		stergeArborePost(&(*radacina)->dreapta);
		free((*radacina)->prajitura.producator);
		free((*radacina));
	}
	*radacina = NULL;
}


int inaltimeArbore(Nod* radacina) {

	if (radacina) {
		int st = inaltimeArbore(radacina->stanga);
		int dr = inaltimeArbore(radacina->dreapta);
		return((st > dr) ? st : dr)+1;
	}
	else {
		return 0;
	}
}




void main() {

	//Prajitura p = initializarePrajitura(100, "MaraMura", 12.5);
	//afisarePrajitura(p);

	Nod* radacina = NULL;

	inserarePrajituraArbore(&radacina, initializarePrajitura(7, "Cofetarie",7.5));
	inserarePrajituraArbore(&radacina, initializarePrajitura(4, "Patiserie", 12.5));
	inserarePrajituraArbore(&radacina, initializarePrajitura(10, "MaraMura", 11));
	inserarePrajituraArbore(&radacina, initializarePrajitura(2, "Cioco", 13));
	inserarePrajituraArbore(&radacina, initializarePrajitura(8, "Cofetarie", 6));
	
	printf("\n\n------------------\n");
	parcurgerePreOrdine(radacina);
	printf("\n\n------------------\n");
	parcurgereInOrdine(radacina);

	printf("\n\n------------------\n");
	Prajitura p = cautarePrajitura(2, radacina);
	afisarePrajitura(p);
	free(p.producator);
	int val = inaltimeArbore(radacina);
	printf("\nInaltimea arborelui este: %d\n", val);
	stergeArborePost(&radacina);

}

