#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>


//HEAP - COADA DE PRIORITATI

typedef struct Camion Camion;
typedef struct Heap Heap;

struct Camion {
	char* nrInmatriculare;
	float capacitate;
};

struct Heap {
	int dim;
	int dimTotala;
	Camion* vector;
};


Camion creareCamion(const char* nrm, float cap) {
	Camion a;
	a.nrInmatriculare = (char*)malloc((strlen(nrm) + 1) * sizeof(char));
	strcpy(a.nrInmatriculare, nrm);
	a.capacitate = cap;
	return a;
}

void afisareCamion(Camion a) {
	printf("\nCamion cu numarul: %s, capaciitate: %.2f",a.nrInmatriculare,a.capacitate);
}



void afisareHeap(Heap h) {

	for (int i = 0; i < h.dim; i++) {
		afisareCamion(h.vector[i]);
	}
}


void filtrareHeap(Heap h, int index) {

	int is = 2 * index + 1;
	int id = 2 * index + 2;

	//comparare nod curent cu fii sai

	int max = index;
	

	if (is < h.dim && h.vector[is].capacitate > h.vector[max].capacitate) {
		max = is;
	}
	if (id < h.dim && h.vector[id].capacitate > h.vector[max].capacitate) {
		max = id;
	}
	if (max != index) {
		Camion aux;
		aux = h.vector[max];
		h.vector[max] = h.vector[index];
		h.vector[index] = aux;
		if (max < h.dim / 2)
		{
			filtrareHeap(h, max);
		}
	}

}



Camion extragere(Heap* h) {

	if (h){
		Camion aux = h->vector[0];
		h->vector[0] = h->vector[h->dim - 1];
		h->vector[h->dim - 1] = aux;

		h->dim--;
		Camion cam = creareCamion(aux.nrInmatriculare,aux.capacitate);

		filtrareHeap(*h, 0);

		return cam;

	}
	else {
		return creareCamion("ANONIM", 0);
	}





}







void main() {

	Heap h;
	h.dim = 6;
	h.dimTotala = 6;
	h.vector = (Camion*)malloc(h.dim * sizeof(Camion));
	h.vector[0] = creareCamion("B77abc", 100);
	h.vector[1] = creareCamion("DB12efg", 120);
	h.vector[2] = creareCamion("TL38jbj", 80);
	h.vector[3] = creareCamion("B101LLL", 90);
	h.vector[4] = creareCamion("PH86PGE", 170);
	h.vector[5] = creareCamion("B02uau", 200);
	afisareHeap(h);




	for(int i = h.dim/2-1; i >= 0; i--) {
		filtrareHeap(h, i);
	}

	printf("\n\n");
	afisareHeap(h);


	printf("\n\n");
	Camion ceva = extragere(&h);
	afisareCamion(ceva);
	while (h.dim > 0) {
		afisareCamion(extragere(&h));
	}
	
	printf("\n\n");
	for (int i = 0; i < h.dimTotala; i++) {
		afisareCamion(h.vector[i]);
	}

	//tema:
	//sterge vector (info + vector)
	//inserare in heap filtrat, adaugare la inceput adaugare spatiu si adaugare element, filtrare heap




}