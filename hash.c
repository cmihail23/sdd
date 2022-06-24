#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Elev Elev;
typedef struct Nod Nod;

struct Elev {
	char* nume;
	int nrMatricol;
};


struct Nod {
	Nod* urmator;
	Elev e;
};

typedef struct hashTable hashTable;
struct hashTable {
	Nod** tabela;
	int dim;
};


Elev creareElev(const char* nume, int nrMatricol) {
	Elev e;
	e.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(e.nume, nume);
	e.nrMatricol = nrMatricol;
	return e;
}




//are nev de nrm si dimensiune pentru a aduce la interval
int functieHash(Elev e, hashTable ht) {

	return e.nrMatricol % ht.dim;

}


hashTable creareHashTable(int dimensiune) {
	hashTable ht;
	ht.tabela = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.tabela[i] = NULL;
	}
	ht.dim = dimensiune;
	return ht;
}


void inserareSfarsitLista(Nod* *cap, Elev e) {
	Nod* p= (*cap);

	Nod* nou=(Nod*)malloc(sizeof(Nod));
	nou->urmator = NULL;
	nou->e = e;
	if (p) {
		while (p->urmator) {
			p = p->urmator;
		}
		p->urmator = nou;
	}
	else {
		*cap = nou;
	}

}




void inserareNodHash(hashTable ht, Elev e) {


	if (ht.dim > 0) {

		int pozitie = functieHash(e,ht);
		if (ht.tabela[pozitie] != NULL) {
			//aici are loc coliziune si se va adauga in capatul listei
			inserareSfarsitLista(&ht.tabela[pozitie], e);
		}
		else {
			//nu e coliziune, se adauga elementul
			inserareSfarsitLista(&ht.tabela[pozitie], e);
		}
	}

}


void afisareElev(Elev e) {
	printf("Numele: %s, nr matricol: %d\n", e.nume, e.nrMatricol);

}

void afisareLista(Nod* cap){
	while (cap) {
		afisareElev(cap->e);
		cap = cap->urmator;
	}
}


void afisareHash(hashTable ht) {
	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] == NULL) {
			printf("-\n");
		}
		else {
			afisareLista(ht.tabela[i]);
		}

	}
}

//fct de cautare elev cu nrm specific in hashtable
Elev cautareElev(int nr, hashTable ht){

	if (ht.dim > 0) {

		Elev temp = creareElev("Nu exista", nr);

		int pozitie = functieHash(temp,ht);
		if (pozitie<ht.dim)
		{
			Nod* f = ht.tabela[pozitie];
			while (f) {
				if (f->e.nrMatricol == nr) {
					return f->e;
				}
				f = f->urmator;
			}
		}
		return temp;
	}

}



void stergeHash(hashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {

		Nod* p = ht->tabela[i];
		while (p){
			Nod* temp = p;
			p = p->urmator;
			free(temp->e.nume);
			free(temp);
		}
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;
}





void main() {

	hashTable tabel = creareHashTable(10);


	inserareNodHash(tabel, creareElev("Vasile", 5));
	inserareNodHash(tabel, creareElev("Ionel", 15));
	inserareNodHash(tabel, creareElev("Mihail", 107));
	inserareNodHash(tabel, creareElev("Gerogel", 12));

	afisareHash(tabel);

	printf("\n\n");
	afisareElev(cautareElev(15,tabel));
	stergeHash(&tabel);

	afisareHash(tabel);

}











