// SORU A13: Sona Eklemeli Bağlı Liste (Hasta Kaydı Kuyruğu)
// Amaç: Her hasta sona eklenecek. Liste yazdırılacak. Hafıza temizlenecek.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Hasta {
    char ad[30];
    int yas;
    struct Hasta* next;
};

// Yeni hasta oluşturur ve sona ekler
void sonaEkle(struct Hasta** bas, char* ad, int yas) {
    struct Hasta* yeni = (struct Hasta*)malloc(sizeof(struct Hasta));
    if (!yeni) {
        printf("Bellek ayrilamadi!\n");
        exit(1);
    }
    strcpy(yeni->ad, ad);
    yeni->yas = yas;
    yeni->next = NULL;

    if (*bas == NULL) {
        *bas = yeni;
    } else {
        struct Hasta* gec = *bas;
        while (gec->next != NULL) {
            gec = gec->next;
        }
        gec->next = yeni;
    }
}

// Listeyi yazdır
void listele(struct Hasta* bas) {
    printf("\nHASTA LISTESI:\n----------------\n");
    while (bas != NULL) {
        printf("Ad: %s | Yas: %d\n", bas->ad, bas->yas);
        bas = bas->next;
    }
}

// Belleği temizle
void listeyiTemizle(struct Hasta* bas) {
    struct Hasta* tmp;
    while (bas != NULL) {
        tmp = bas;
        bas = bas->next;
        free(tmp);
    }
}

int main() {
    struct Hasta* bas = NULL;
    char ad[30];
    int yas, secim;

    do {
        printf("\n1. Hasta Ekle\n2. Listele\n0. Cikis\nSecim: ");
        scanf("%d", &secim);
        if (secim == 1) {
            printf("Ad: ");
            scanf(" %[^]", ad);
            printf("Yas: ");
            scanf("%d", &yas);
            sonaEkle(&bas, ad, yas);
        } else if (secim == 2) {
            listele(bas);
        }
    } while (secim != 0);

    listeyiTemizle(bas);
    return 0;
}