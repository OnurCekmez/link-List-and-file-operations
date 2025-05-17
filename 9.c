// SORU //A14: Ortaya Eklemeli Sıralı Bağlı Liste (Büyy\u00fkten Küçüğe)
// Amaç: Öğrenciler notuna göre sıralı olacak şekilde bağlı listeye eklenir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ogrenci {
    char ad[30];
    float not;
    struct Ogrenci* next;
};

// Notuna göre sıralı ekler (büyy\u00fkten küçüğe)
void siraliEkle(struct Ogrenci** bas, char* ad, float not) {
    struct Ogrenci* yeni = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    if (!yeni) {
        printf("Bellek ayrilamadi!\n");
        exit(1);
    }
    strcpy(yeni->ad, ad);
    yeni->not = not;
    yeni->next = NULL;

    // En başa eklenecekse
    if (*bas == NULL || (*bas)->not < not) {
        yeni->next = *bas;
        *bas = yeni;
        return;
    }

    // Ortaya ya da sona
    struct Ogrenci* gec = *bas;
    while (gec->next != NULL && gec->next->not >= not) {
        gec = gec->next;
    }
    yeni->next = gec->next;
    gec->next = yeni;
}

void listele(struct Ogrenci* bas) {
    printf("\nSIRALI NOT LISTESI:\n------------------------\n");
    while (bas != NULL) {
        printf("Ad: %s | Not: %.2f\n", bas->ad, bas->not);
        bas = bas->next;
    }
}

void listeyiTemizle(struct Ogrenci* bas) {
    struct Ogrenci* tmp;
    while (bas != NULL) {
        tmp = bas;
        bas = bas->next;
        free(tmp);
    }
}

int main() {
    struct Ogrenci* bas = NULL;
    char ad[30];
    float not;
    int secim;

    do {
        printf("\n1. Ogrenci Ekle\n2. Listele\n0. Cikis\nSecim: ");
        scanf("%d", &secim);
        if (secim == 1) {
            printf("Ad: ");
            scanf(" %[^\n]", ad);
            printf("Not: ");
            scanf("%f", &not);
            siraliEkle(&bas, ad, not);
        } else if (secim == 2) {
            listele(bas);
        }
    } while (secim != 0);

    listeyiTemizle(bas);
    return 0;
}