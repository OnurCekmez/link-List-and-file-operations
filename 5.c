#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Randevu {
    char ad[30];
    char tarih[11]; // "gg.aa.yyyy"
    char saat[6];   // "ss:dd"
    struct Randevu* next;
};

// Randevuları tarihe göre karşılaştıran fonksiyon
int karsilastir(struct Randevu* a, struct Randevu* b) {
    return strcmp(a->tarih, b->tarih); // küçükse önce gelir
}

// Bubble Sort (veri değişimiyle)
void bubbleSort(struct Randevu* bas) {
    int degisti;
    struct Randevu* p;
    do {
        degisti = 0;
        p = bas;
        while (p->next != NULL) {
            if (karsilastir(p, p->next) > 0) {
                // Verileri değiştir (düğüm değil!)
                struct Randevu tmp = *p;
                *p = *(p->next);
                *(p->next) = tmp;
                // Ama pointerlar karıştığı için düzelt
                struct Randevu* t = p->next->next;
                p->next->next = p;
                p->next = t;
                degisti = 1;
            }
            p = p->next;
        }
    } while (degisti);
}

// Listeye randevu ekler
struct Randevu* randevuEkle(struct Randevu* bas) {
    struct Randevu* yeni = (struct Randevu*) malloc(sizeof(struct Randevu));
    if (!yeni) {
        printf("Bellek ayrilamadi.\n");
        exit(1);
    }

    printf("Ad: ");
    scanf(" %[^\n]s", yeni->ad);
    printf("Tarih (gg.aa.yyyy): ");
    scanf(" %[^\n]", yeni->tarih);
    printf("Saat (ss:dd): ");
    scanf(" %[^\n]", yeni->saat);

    yeni->next = bas;
    return yeni;
}

// Listeyi yazdır
void listele(struct Randevu* bas) {
    printf("\nSIRALI RANDEVU LISTESI:\n");
    while (bas != NULL) {
        printf("Ad: %s | Tarih: %s | Saat: %s\n", bas->ad, bas->tarih, bas->saat);
        bas = bas->next;
    }
}

// Belleği serbest bırak
void listeyiSil(struct Randevu* bas) {
    struct Randevu* tmp;
    while (bas != NULL) {
        tmp = bas;
        bas = bas->next;
        free(tmp);
    }
}

int main() {
    struct Randevu* bas = NULL;

    int secim;
    while (1) {
        printf("\n1. Randevu Ekle\n0. Bitir ve Listele\nSecim: ");
        scanf("%d", &secim);
        if (secim == 0)
            break;
        bas = randevuEkle(bas);
    }

    bubbleSort(bas);
    listele(bas);
    listeyiSil(bas);

    return 0;
}