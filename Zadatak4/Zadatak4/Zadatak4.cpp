#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef struct _element {
    int koef;
    int eksp;
    struct _element* next;
} Element;

Element* StvoriElement(int koef, int eksp);
int SortiraniUnos(Element* head, int koef, int eksp);
int IspisPolinoma(Element* head);
int CitajIzDatoteke(Element* p1, Element* p2);
int ZbrojiPolinome(Element* p1, Element* p2, Element* rezZbroj);
int PomnoziPolinome(Element* p1, Element* p2, Element* rezUmnozak);
void FreePolinom(Element* head);

int main()
{
    Element head1 = { head1.koef = 0, head1.eksp = 0, head1.next = NULL };
    Element head2 = { head2.koef = 0, head2.eksp = 0, head2.next = NULL };
    Element rezZbroj = { rezZbroj.koef = 0, rezZbroj.eksp = 0, rezZbroj.next = NULL };
    Element rezUmnozak = { rezUmnozak.koef = 0, rezUmnozak.eksp = 0, rezUmnozak.next = NULL };

    if (CitajIzDatoteke(&head1, &head2) != 0) {
        return -1;
    }

    printf("Prvi polinom: ");
    IspisPolinoma(&head1);

    printf("Drugi polinom: ");
    IspisPolinoma(&head2);

    //zbrajanje
    ZbrojiPolinome(&head1, &head2, &rezZbroj);
    printf("\nZbroj: ");
    IspisPolinoma(&rezZbroj);

    //mnozenje
    PomnoziPolinome(&head1, &head2, &rezUmnozak);
    printf("Umnozak: ");
    IspisPolinoma(&rezUmnozak);

    //ne zaboraviii !!
    FreePolinom(&head1);
    FreePolinom(&head2);
    FreePolinom(&rezZbroj);
    FreePolinom(&rezUmnozak);

    return 0;
}

Element* StvoriElement(int koef, int eksp) {

    Element* novi = (Element*)malloc(sizeof(Element));
    if (novi == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    novi->koef = koef;
    novi->eksp = eksp;
    novi->next = NULL;
    return novi;
}

int SortiraniUnos(Element* head, int koef, int eksp) {
    if (koef == 0) return 0;

    Element* prev = head;
    Element* temp = head->next;

    while (temp != NULL && temp->eksp > eksp) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL && temp->eksp == eksp) {
        temp->koef += koef;
        if (temp->koef == 0) {
            prev->next = temp->next;
            free(temp);
        }
        return 0;
    }

    Element* novi = StvoriElement(koef, eksp);
    if (novi == NULL) return -1;

    novi->next = temp;
    prev->next = novi;

    return 0;
}

int CitajIzDatoteke(Element* p1, Element* p2) {
    FILE* fp = fopen("polinomi.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke 'polinomi.txt'!\n");
        return -1;
    }

    char buffer[MAX_LINE];
    char* pointer = NULL;
    int koef = 0, eksp = 0, pomak = 0;

    if (fgets(buffer, MAX_LINE, fp) != NULL) {
        pointer = buffer;
        while (sscanf(pointer, "%d %d %n", &koef, &eksp, &pomak) == 2) {
            SortiraniUnos(p1, koef, eksp);
            pointer += pomak;
        }
    }

    if (fgets(buffer, MAX_LINE, fp) != NULL) {
        pointer = buffer;
        while (sscanf(pointer, "%d %d %n", &koef, &eksp, &pomak) == 2) {
            SortiraniUnos(p2, koef, eksp);
            pointer += pomak;
        }
    }

    fclose(fp);
    return 0;
}

int ZbrojiPolinome(Element* p1, Element* p2, Element* rezZbroj) {
    Element* t1 = p1->next;
    Element* t2 = p2->next;

    while (t1 != NULL) {
        SortiraniUnos(rezZbroj, t1->koef, t1->eksp);
        t1 = t1->next;
    }

    while (t2 != NULL) {
        SortiraniUnos(rezZbroj, t2->koef, t2->eksp);
        t2 = t2->next;
    }

    return 0;
}

int PomnoziPolinome(Element* p1, Element* p2, Element* rezUmnozak) {
    Element* t1 = p1->next;

    while (t1 != NULL) {
        Element* t2 = p2->next;
        while (t2 != NULL) {
            int noviKoef = t1->koef * t2->koef;
            int noviEksp = t1->eksp + t2->eksp;

            SortiraniUnos(rezUmnozak, noviKoef, noviEksp);
            t2 = t2->next;
        }
        t1 = t1->next;
    }

    return 0;
}

int IspisPolinoma(Element* head) {
    Element* temp = head->next;

    if (temp == NULL) {
        printf("0\n");
        return 0;
    }

    while (temp != NULL) {
        if (temp->koef > 0 && temp != head->next) {
            printf("+ ");
        }
        else if (temp->koef < 0) {
            printf("- ");
        }

        int absKoef = abs(temp->koef);

        if (temp->eksp == 0) {
            printf("%d ", absKoef);
        }
        else if (temp->eksp == 1) {
            if (absKoef == 1) printf("x ");
            else printf("%dx ", absKoef);
        }
        else {
            if (absKoef == 1) printf("x^%d ", temp->eksp);
            else printf("%dx^%d ", absKoef, temp->eksp);
        }

        temp = temp->next;
    }
    printf("\n");
    return 0;
}

void FreePolinom(Element* head) {
    Element* temp = head->next;
    while (temp != NULL) {
        Element* zaBrisati = temp;
        temp = temp->next;
        free(zaBrisati);
    }
    head->next = NULL;
}