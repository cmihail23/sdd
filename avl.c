#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Prajitura Prajitura;
struct Prajitura {
    int id;
    char* prod;
    float pret;
};

typedef struct Node Node;
struct Node {
    Node* st;
    Node* dr;
    Prajitura info;
};

Prajitura initInfo(int id, const char* prod, float pret) {
    Prajitura p;
    p.id = id;
    p.prod = (char*)malloc(sizeof(char) * (strlen(prod) + 1));
    strcpy(p.prod, prod);
    p.pret = pret;
    return p;
}

void inserarePrajitura(Node** root, Prajitura info) {
    if (*root) {
        if ((*root)->info.id < info.id) {
            inserarePrajitura(&(*root)->dr, info);
        }
        else if ((*root)->info.id > info.id) {
            inserarePrajitura(&(*root)->st, info);
        }
    }
    else {
        Node* nou = (Node*)malloc(sizeof(Node));
        nou->info = info;
        nou->st = NULL;
        nou->dr = NULL;
        (*root) = nou;
    }
}

void afisarePrajitura(Prajitura info) {
    printf("\nID=%d, Producator='%s', Pret=%.3f", info.id, info.prod, info.pret);
}

// Preordine
void afisareRSD(Node* root) {
    if (root) {
        afisarePrajitura(root->info);
        afisareRSD(root->st);
        afisareRSD(root->dr);
    }
}

// In ordine
void afisareSRD(Node* root) {
    if (root) {
        afisareSRD(root->st);
        afisarePrajitura(root->info);
        afisareSRD(root->dr);
    }
}

Prajitura cautareInArbore(Node* root, int id) {
    if (root) {
        if (root->info.id > id) {
            return cautareInArbore(root->st, id);
        }
        else if (root->info.id < id) {
            return cautareInArbore(root->dr, id);
        }
        else {
            return initInfo(id, root->info.prod, root->info.pret);
        }
    }
    else {
        return initInfo(-1, "Not Found", 0);
    }
}

void stergereArbore(Node** root) {
    if (*root) {
        stergereArbore(&(*root)->st);
        stergereArbore(&(*root)->dr);
        free((*root)->info.prod);
        free(*root);
    }

    *root = NULL;
}

int inaltimeArbore(Node* root) {
    if (root) {
        int st = inaltimeArbore(root->st);
        int dr = inaltimeArbore(root->dr);

        return ((st > dr) ? st : dr) + 1;
    }
    else return 0;
}




//arbori dezechilibrati si echilibrarea acestora


int gradEchilibru(Node* radacina) {

    if (radacina) {
        int st = inaltimeArbore(radacina->st);
        int dr = inaltimeArbore(radacina->dr);
        return st - dr;
    }
    else {
        return 0;
    }
}


void rotireStanga(Node** radacina){

    Node* temp = (*radacina)->dr;
    (*radacina)->dr = temp->st;
    temp->st = *radacina;
    *radacina = temp;
}

void rotireDreapta(Node** radacina) {

    Node* temp = (*radacina)->st;
    (*radacina)->st = temp ->dr;
    temp->dr = *radacina;
    *radacina = temp;

}


//AVL = Adelson-Velskii and Landis
void inserareAVL(Node** radacina, Prajitura prajitura) {

    if (*radacina) {
        if ((*radacina)->info.id < prajitura.id) {
            inserareAVL(&(*radacina)->dr,prajitura);
        }
        else if ((*radacina)->info.id > prajitura.id) {
            inserareAVL(&(*radacina)->st, prajitura);
        }

        //echilibrare

        int echilibru = gradEchilibru(*radacina);
        if (echilibru == -2) {
            int echDr = gradEchilibru((*radacina)->dr);
            if (echDr == 1) {
                rotireDreapta(&(*radacina)->dr);
            }
            rotireStanga(radacina);
        }
        if (echilibru == 2) {
            int echSt = gradEchilibru((*radacina)->st);
            if (echSt == -1) {
                rotireStanga(&(*radacina)->st);
            }
            rotireDreapta(radacina);
        }


    }
    else {
        Node* nou = (Node*)malloc(sizeof(Node));
        nou->info = prajitura;
        nou->st = NULL;
        nou->dr = NULL;
        *radacina = nou;
    }





}









void main() {
    Node* root = NULL;

    /*inserarePrajitura(&root, initInfo(7, "Patiseria A", 6));
    inserarePrajitura(&root, initInfo(4, "Patiseria B", 6));
    inserarePrajitura(&root, initInfo(10, "Patiseria C", 5));
    inserarePrajitura(&root, initInfo(2, "Patiseria D", 4));
    inserarePrajitura(&root, initInfo(6, "Patiseria E", 3));
    inserarePrajitura(&root, initInfo(8, "Patiseria F", 7));*/

    /*printf("\nAfisare RSD (Preordine):");
    afisareRSD(root);

    printf("\n\nAfisare SRD (In ordine):");
    afisareSRD(root);

    printf("\n\nCautare prajituri:");
    Prajitura p1 = cautareInArbore(root, 2);
    Prajitura p2 = cautareInArbore(root, 1);
    afisarePrajitura(p1);
    afisarePrajitura(p2);
    free(p1.prod);
    free(p2.prod);*/

    //printf("\n\nInaltime arbore: %d", inaltimeArbore(root));

    //stergereArbore(&root);
    //printf("\n\nArbore sters: %s", ((root == NULL) ? "TRUE" : "FALSE"));
    //afisareSRD(root);

    printf("\n");


    inserareAVL(&root, initInfo(1, "Patiseria A", 6));
    inserareAVL(&root, initInfo(2, "Patiseria B", 6));
    inserareAVL(&root, initInfo(3, "Patiseria C", 5));
    inserareAVL(&root, initInfo(4, "Patiseria D", 4));
    inserareAVL(&root, initInfo(5, "Patiseria E", 3));
    inserareAVL(&root, initInfo(6, "Patiseria F", 7));

    afisareSRD(root);
    int inaltime = inaltimeArbore(root);

    printf("\n\nInaltime arbore: %d", inaltimeArbore(root));



}