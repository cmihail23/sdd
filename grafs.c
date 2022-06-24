#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<malloc.h>


//graf prin reprezentare de tip lista de adiacenta

//nod graf = nod de pe lista principala
//nod simplu - nod de lista ce are pointer la nod graf
//info utila- oras

//parcurgei:
//in adancime
//in latime




typedef struct Oras Oras;
typedef struct Nod Nod;
typedef struct NodGraf NodGraf;


struct Oras {
	char* nume;
	int id;
};

Oras initialziareOras(const char* nume, int id) {
	Oras a;
	a.id = id;
	a.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(a.nume, nume);
	return a;
}
void afisareOras(Oras a) {
	printf("\nOrasul cu id: %d si nume: %s",a.id,a.nume);
}


struct NodGraf {
	Oras oras;
	NodGraf* next;
	Nod* legaturi;

};

struct Nod {
	Nod* next;
	NodGraf* info;
};



void inserareNodGraf(NodGraf** cap, Oras o) {
	NodGraf* nou = (NodGraf*)malloc(sizeof(NodGraf));
	nou->oras = o;
	nou->legaturi = NULL;
	nou->next = NULL;

	if (*cap) {
		NodGraf* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else *cap = nou;
}


void inserareListaSimpla(Nod** cap, NodGraf* info) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = info;
	nou->next = NULL;
	if (*cap) {

		Nod* iterator = *cap;
		while (iterator->next) {
			iterator = iterator->next;
		}

		iterator->next = nou;
	}
	else {
		*cap = nou;
	}

}

void afisareVeciniListaSimpla(Nod* nod) {

	Nod* it = nod;
	while (it) {
		printf("\n\t Vecin: id: %d, nume: %s", it->info->oras.id, it->info->oras.nume);
		it = it->next;
	}

}

void afisareGraf(NodGraf* graf) {

	NodGraf* iterator = graf;
	while (iterator) {
		afisareOras(iterator->oras);
		afisareVeciniListaSimpla(iterator->legaturi);
		iterator = iterator->next;
	}
}


NodGraf* cautareNod(int id,NodGraf* cap) {

	NodGraf* tmp = cap;

	while (tmp!=NULL && tmp->oras.id!=id) {
		tmp = tmp->next;
	}

	return tmp;

}


void creareMuchie(NodGraf* cap, int id1, int id2) {

	NodGraf* nod1 = cautareNod(id1, cap);
	NodGraf* nod2 = cautareNod(id2, cap);
	if (nod1 != NULL && nod2 != NULL) {
		inserareListaSimpla(&(nod1->legaturi), nod2);
		inserareListaSimpla(&(nod2->legaturi), nod1);
	}
}



//parcurgerea in latime
//nod de start, vizitam toti vecinii



typedef struct Lista Lista;
typedef struct NodCoada NodCoada;

struct NodCoada {
	NodCoada* urmator;
	NodCoada* anterior;
	int id;
};

struct Lista {
	NodCoada* prim;
	NodCoada* ultim;
};

//adauga la inceput
void adauga(Lista* lista, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->anterior = NULL;
	nou->urmator = lista->prim;
	nou->id = id;

	if (lista->prim) {
		lista->prim->anterior = nou;
	}
	else {
		lista->ultim = nou;
	}

	lista->prim = nou;

}

void adaugaStiva(Lista* lista, int id) {

	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->urmator = NULL;
	nou->anterior = lista->ultim;
	nou->id = id;
	if (lista->ultim) {
		lista->ultim->urmator = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

//extrage de la final

int extrage(Lista* lista) {
	int id=-1;
	if (lista->ultim!=NULL) {
		id = lista->ultim->id;
		lista->ultim = lista->ultim->anterior;
		if (lista->ultim) {
			 free(lista->ultim->urmator);
			 lista->ultim->urmator = NULL;
		}
		else {
			free(lista->prim);
			lista->prim = NULL;
	
		}
	}
	return id;
}


//bag nod curent in coada, adaug toti vecinii nevizitati in coada
//vetor de stare pentru a verifica daca nodul a fost vizitat anterior
//scoatem din coada pe rand noduri si verificam vecinii acestora + adaugam in coada


int numaraNoduriGraf(NodGraf* graf) {
	int contor = 0;
	while (graf) {
		graf = graf->next;
		contor++;
	}

	return contor;

}




void parcurgereInLatime(int idStart,NodGraf* graf ) {

	int dim = numaraNoduriGraf(graf);
	char* vector = (char*)malloc(sizeof(char) * dim);
	for (int i = 0; i < dim; i++) {
		vector[i] = 0;
	}
	Lista coada;

	coada.prim = NULL;
	coada.ultim = NULL;

	adauga(&coada, idStart);
	vector[idStart - 1] = 1;


	while (coada.prim != NULL) {
		int rezultat = extrage(&coada);
		NodGraf* nodCurent = cautareNod(rezultat, graf);
		afisareOras(nodCurent->oras);
		Nod* iterator = nodCurent->legaturi;
		while (iterator){
			
			if (vector[iterator->info->oras.id - 1] == 0) {
				adauga(&coada, iterator->info->oras.id);
				vector[iterator->info->oras.id - 1] = 1;
			}

			iterator = iterator->next;
		}
	}
}


void parcurgereInAdancime(int idStart, NodGraf* graf) {

	int dim = numaraNoduriGraf(graf);
	char* vector = (char*)malloc(sizeof(char) * dim);
	for (int i = 0; i < dim; i++) {
		vector[i] = 0;
	}
	Lista stiva;

	stiva.prim = NULL;
	stiva.ultim = NULL;

	adaugaStiva(&stiva, idStart);
	vector[idStart - 1] = 1;


	while (stiva.prim != NULL) {
		int rezultat = extrage(&stiva);
		NodGraf* nodCurent = cautareNod(rezultat, graf);
		afisareOras(nodCurent->oras);
		Nod* iterator = nodCurent->legaturi;
		while (iterator) {

			if (vector[iterator->info->oras.id - 1] == 0) {
				adaugaStiva(&stiva, iterator->info->oras.id);
				vector[iterator->info->oras.id - 1] = 1;
			}

			iterator = iterator->next;
		}
	}
}




void stergereListaDeListe(NodGraf** graf) {

	NodGraf* p = *graf;	
	while (p) {

		Nod* q = p->legaturi;
		while (q) {
			Nod* aux = q;
			q = q->next;
			free(aux);
		}
		free(p->oras.nume);
		Nod* aux = p;
		p = p->next;
		free(aux);
	}

	*graf = NULL;

}




void main(){


	NodGraf* graf = NULL;


	inserareNodGraf(&graf,initialziareOras("Bucuresti",1));
	inserareNodGraf(&graf,initialziareOras("Targoviste",2));
	inserareNodGraf(&graf,initialziareOras("Ploiesti",3));
	inserareNodGraf(&graf,initialziareOras("Iasi",4));
	inserareNodGraf(&graf,initialziareOras("Timisoara",5));
	inserareNodGraf(&graf,initialziareOras("Cluj",6));

	afisareGraf(graf);

	creareMuchie(graf,1,4);
	creareMuchie(graf,1,3);
	creareMuchie(graf,1,2);
	creareMuchie(graf,2,3);
	creareMuchie(graf,2,5);
	creareMuchie(graf,6,2);
	creareMuchie(graf,5,6);
	creareMuchie(graf,4,3);

	afisareGraf(graf);

	parcurgereInLatime(1,graf);
	printf("\n\n\n");
	parcurgereInAdancime(1, graf);

	stergereListaDeListe(&graf);


}



