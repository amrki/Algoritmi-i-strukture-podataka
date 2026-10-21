/*Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi(po prezimenu),
e) briše odreðeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _osoba {
    char ime[50];
    char prez[50];
    int god_rod;
    struct _osoba* next;
} Osoba;

Osoba* NovaOsoba();
int DodajNaPocetak(Osoba*);
int DodajNaKraj(Osoba*);
Osoba* TraziPrezime(Osoba* head, const char* trazenoPrezime);
int Ispis(Osoba* head);
int BrisiTrazenog(Osoba*, const char*);
void FreeListu(Osoba*);

int main()
{
    Osoba* head = (Osoba*)malloc(sizeof(Osoba));
    if (head == NULL) {
        printf("Greska u alokaciji\n");
        return -1;
    }
    head->next = NULL;

    //a) i b)
    DodajNaPocetak(head);
    Ispis(head);

    //c) i b)
    DodajNaKraj(head);
    Ispis(head);

    //da dodamo jos malo u listu
    DodajNaPocetak(head);
    Ispis(head);
    DodajNaKraj(head);
    Ispis(head);

    //d)
    char trazenoPrezime[50];
    printf("\nTRAZI PREZIME\n");
    printf("\nUnesi prezime koje zelis pronaci: ");
    if (scanf("%49s", trazenoPrezime) == 1) {
        Osoba* pronadeni = TraziPrezime(head, trazenoPrezime);
        if (pronadeni != NULL) {
            printf("Pronaden: %s %s %d\n", pronadeni->ime, pronadeni->prez, pronadeni->god_rod);
        }
        else {
            printf("Osoba s prezimenom %s nije pronadena\n", trazenoPrezime);
        }
    }

    //e)
    char prezimeZaBrisati[50];
    printf("\nBRISANJE PREZIMENA\n");
    printf("\nUnesi prezime koje zelis obrisati: ");
    if (scanf("%49s", prezimeZaBrisati) == 1) {
        if (BrisiTrazenog(head, prezimeZaBrisati) == 0) {
            printf("Uspjesno obrisano\n");
        }
        else {
            printf("Brisanje nije uspjelo - prezime %s nije pronadeno\n", prezimeZaBrisati);
        }
    }

    //b)
    printf("\nISPIS\n");
    Ispis(head);

    FreeListu(head);

    return 0;
}

Osoba* NovaOsoba() {

    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    if (nova == NULL) {
        printf("Greska u alokaciji\n");
        return NULL;
    }

    printf("Unesi ime: ");
    if (scanf("%49s", nova->ime) != 1) {
        free(nova);
        return NULL;
    }

    printf("Unesi prezime: ");
    if (scanf("%49s", nova->prez) != 1) {
        free(nova);
        return NULL;
    }

    printf("Unesi godinu rodenja: ");
    if (scanf("%d", &nova->god_rod) != 1) {
        free(nova);
        return NULL;
    }

    nova->next = NULL;
    return nova;
}

int DodajNaPocetak(Osoba* head) {
    Osoba* nova = NovaOsoba();
    if (nova == NULL) {
        printf("Greska u alokaciji\n");
        return -1;
    }

    nova->next = head->next;
    head->next = nova;

    return 0;
}

int DodajNaKraj(Osoba* head) {

    if (head == NULL) {
        printf("Lista ne postoji\n");
        return -1;
    }

    Osoba* nova = NovaOsoba();
    if (nova == NULL) {
        printf("Greska u alokaciji\n");
        return -1;
    }

    Osoba* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nova;
    return 0;
}

Osoba* TraziPrezime(Osoba* head, const char* trazenoPrezime) {

    if (head == NULL) return NULL;

    Osoba* temp = head->next;   //head mi je dummy elem

    while (temp != NULL) {
        if (strcmp(temp->prez, trazenoPrezime) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

int Ispis(Osoba* head) {
    if (head == NULL) {
        printf("Lista ne postoji\n");
        return -1;
    }

    Osoba* temp = head->next; //head->next je prvi pravi elem

    if (temp == NULL) {
        printf("Prazna lista\n");
        return 0;
    }

    while (temp != NULL) {
        printf("%s %s %d\n", temp->ime, temp->prez, temp->god_rod);
        temp = temp->next;
    }
    return 0;
}

int BrisiTrazenog(Osoba* head, const char* prezimeZaBrisati) {

    if (head == NULL) {
        printf("Lista ne postoji\n");
        return -1;
    }

    Osoba* prev = head;         //krece od dummy heada
    Osoba* temp = head->next;   //krece od prvog pravog

    while (temp!=NULL) {
        if (strcmp(temp->prez, prezimeZaBrisati) == 0) {
            prev->next = temp->next;
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }

    return -1;  //nije pronaden
}

void FreeListu(Osoba* head) {
    Osoba* temp = head;

    while (temp != NULL) {
        Osoba* zaBrisati = temp;
        temp = temp->next;
        free(zaBrisati);
    }
}
