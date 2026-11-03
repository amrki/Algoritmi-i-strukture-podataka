#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _osoba {
    char ime[50];
    char prez[50];
    int god_rod;
    struct _osoba* next;
} Osoba;

//staro
Osoba* NovaOsoba();
int DodajNaPocetak(Osoba* head);
int DodajNaKraj(Osoba* head);
Osoba* TraziPrezime(Osoba* head, const char* trazenoPrezime);
int Ispis(Osoba* head);
int BrisiTrazenog(Osoba* head, const char* prezimeZaBrisati);
void FreeListu(Osoba* head);

//nove fje
int DodajIza(Osoba* head, const char* ciljnoPrezime);
int DodajIspred(Osoba* head, const char* ciljnoPrezime);
int SortirajPoPrezimenu(Osoba* head);
int UpisUDatoteku(Osoba* head);
int CitanjeIzDatoteke(Osoba* head);

int main()
{
    Osoba* head = (Osoba*)malloc(sizeof(Osoba));
    if (head == NULL) {
        printf("Greska u alokaciji\n");
        return -1;
    }
    head->next = NULL;

    DodajNaPocetak(head);
    DodajNaPocetak(head);
    printf("\nTrenutna lista:\n");
    Ispis(head);

    //a)
    char trazeno[50];
    printf("Unesi prezime iza kojeg zelis dodati osobu: ");
    if (scanf("%49s", trazeno) == 1) {
        if (DodajIza(head, trazeno) == 0) {
            printf("Uspjesno dodano iza %s\n", trazeno);
        }
        else {
            printf("Prezime %s nije pronadeno\n", trazeno);
        }
    }
    Ispis(head);

    //b)
    printf("\nUnesi prezime ispred kojeg zelis dodati osobu: ");
    if (scanf("%49s", trazeno) == 1) {
        if (DodajIspred(head, trazeno) == 0) {
            printf("Uspjesno dodano ispred %s\n", trazeno);
        }
        else {
            printf("Prezime %s nije pronadeno\n", trazeno);
        }
    }
    Ispis(head);

    //c)
    printf("\nSort:\n");
    SortirajPoPrezimenu(head);
    Ispis(head);

    //d)
    printf("\nUpis u datoteku:\n");
    if (UpisUDatoteku(head) == 0) {
        printf("Lista uspjesno upisana u datoteku\n");
    }

    //e)
    printf("\nCitanje iz datoteke\n");
    Osoba* novaListaHead = (Osoba*)malloc(sizeof(Osoba));
    if (novaListaHead != NULL) {
        novaListaHead->next = NULL;
        if (CitanjeIzDatoteke(novaListaHead) == 0) {
            printf("Elementi procitani iz datoteke:\n");
            Ispis(novaListaHead);
        }
        FreeListu(novaListaHead);
    }

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
    if (head == NULL) return -1;

    Osoba* nova = NovaOsoba();
    if (nova == NULL) return -1;

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
    if (nova == NULL) return -1;

    Osoba* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nova;
    return 0;
}

Osoba* TraziPrezime(Osoba* head, const char* trazenoPrezime) {
    if (head == NULL) return NULL;

    Osoba* temp = head->next;
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

    Osoba* temp = head->next;
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

    Osoba* prev = head;
    Osoba* temp = head->next;

    while (temp != NULL) {
        if (strcmp(temp->prez, prezimeZaBrisati) == 0) {
            prev->next = temp->next;
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }

    return -1;
}

void FreeListu(Osoba* head) {
    Osoba* temp = head;
    while (temp != NULL) {
        Osoba* zaBrisati = temp;
        temp = temp->next;
        free(zaBrisati);
    }
}

int DodajIza(Osoba* head, const char* ciljnoPrezime) {
    Osoba* ciljni = TraziPrezime(head, ciljnoPrezime);
    if (ciljni == NULL) {
        return -1;
    }

    Osoba* nova = NovaOsoba();
    if (nova == NULL) return -1;

    nova->next = ciljni->next;
    ciljni->next = nova;
    return 0;
}

int DodajIspred(Osoba* head, const char* ciljnoPrezime) {
    if (head == NULL) return -1;

    Osoba* prev = head;
    Osoba* temp = head->next;

    while (temp != NULL && strcmp(temp->prez, ciljnoPrezime) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return -1;
    }

    Osoba* nova = NovaOsoba();
    if (nova == NULL) return -1;

    nova->next = temp;
    prev->next = nova;
    return 0;
}

int SortirajPoPrezimenu(Osoba* head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }

    Osoba* j;
    Osoba* prevJ;
    Osoba* end = NULL;

    while (head->next != end) {
        prevJ = head;
        j = head->next;

        while (j->next != end) {
            if (strcmp(j->prez, j->next->prez) > 0) {
                Osoba* sljedeci = j->next;
                j->next = sljedeci->next;
                sljedeci->next = j;
                prevJ->next = sljedeci;

                prevJ = sljedeci;
            }
            else {
                prevJ = j;
                j = j->next;
            }
        }
        end = j;
    }

    return 0;
}

int UpisUDatoteku(Osoba* head) {
    if (head == NULL) return -1;

    FILE* fp = fopen("osoba.txt", "w");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje!\n");
        return -1;
    }

    Osoba* temp = head->next;
    while (temp != NULL) {
        fprintf(fp, "%s %s %d\n", temp->ime, temp->prez, temp->god_rod);
        temp = temp->next;
    }

    fclose(fp);
    return 0;
}

int CitanjeIzDatoteke(Osoba* head) {
    if (head == NULL) return -1;

    FILE* fp = fopen("osoba.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za citanje!\n");
        return -1;
    }

    Osoba* zadnji = head;
    while (zadnji->next != NULL) {
        zadnji = zadnji->next;
    }

    char ime[50];
    char prez[50];
    int god;

    while (fscanf(fp, "%49s %49s %d", ime, prez, &god) == 3) {
        Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
        if (nova == NULL) {
            printf("Greska pri alokaciji!\n");
            fclose(fp);
            return -1;
        }

        strcpy(nova->ime, ime);
        strcpy(nova->prez, prez);
        nova->god_rod = god;
        nova->next = NULL;

        zadnji->next = nova;
        zadnji = nova;
    }

    fclose(fp);
    return 0;
}