

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int tc;
    char ad_soyad[50];
    int yas;
    char hastalik[50];
} Hasta;

typedef struct Node {
    Hasta veri;
    struct Node* next;
} Node;

// Yeni düğüm oluştur
Node* yeni_dugum(Hasta h) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->veri = h;
    n->next = NULL;
    return n;
}

// Listenin sonuna ekle
void sona_ekle(Node** bas, Hasta h) {
    Node* yeni = yeni_dugum(h);
    if (*bas == NULL) {
        *bas = yeni;
        return;
    }
    Node* tmp = *bas;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = yeni;
}

// Başa ekle
void basa_ekle(Node** bas, Hasta h) {
    Node* yeni = yeni_dugum(h);
    yeni->next = *bas;
    *bas = yeni;
}

// Ortaya (belirli TC'den sonra) ekle
void ortaya_ekle(Node* bas, int sonra_tc, Hasta h) {
    while (bas != NULL && bas->veri.tc != sonra_tc)
        bas = bas->next;
    if (bas == NULL) return;
    Node* yeni = yeni_dugum(h);
    yeni->next = bas->next;
    bas->next = yeni;
}

// Listele
void listele(Node* bas) {
    while (bas != NULL) {
        printf("TC: %d, Ad: %s, Yas: %d, Hastalik: %s\n", 
               bas->veri.tc, bas->veri.ad_soyad, bas->veri.yas, bas->veri.hastalik);
        bas = bas->next;
    }
}

// TC ile arama
void ara(Node* bas, int tc) {
    while (bas != NULL) {
        if (bas->veri.tc == tc) {
            printf("Bulundu -> TC: %d, Ad: %s, Yas: %d, Hastalik: %s\n",
                   bas->veri.tc, bas->veri.ad_soyad, bas->veri.yas, bas->veri.hastalik);
            return;
        }
        bas = bas->next;
    }
    printf("Kayıt bulunamadı.\n");
}

// TC ile silme
void sil(Node** bas, int tc) {
    Node* tmp = *bas;
    Node* once = NULL;
    while (tmp != NULL && tmp->veri.tc != tc) {
        once = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return; // bulunamadı
    if (once == NULL)
        *bas = tmp->next;
    else
        once->next = tmp->next;
    free(tmp);
}

// İki listeyi birleştir
void liste_birlestir(Node** liste1, Node* liste2) {
    if (*liste1 == NULL) {
        *liste1 = liste2;
        return;
    }
    Node* tmp = *liste1;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = liste2;
}

// Tüm listeyi sil
void liste_sil(Node** bas) {
    Node* tmp;
    while (*bas != NULL) {
        tmp = *bas;
        *bas = (*bas)->next;
        free(tmp);
    }
}

// Örnek kullanım
int main() {
    Node* liste = NULL;

    Hasta h1 = {1001, "Ali Cihan", 25, "Grip"};
    Hasta h2 = {1002, "Mehmet Yılmaz", 30, "Migren"};
    Hasta h3 = {1003, "Ayşe Demir", 28, "Covid"};

    sona_ekle(&liste, h1);
    basa_ekle(&liste, h2);
    ortaya_ekle(liste, 1002, h3); // 1002'den sonra ekle

    printf("Tüm hastalar:\n");
    listele(liste);

    printf("\n1003 TC'li hasta aranıyor:\n");
    ara(liste, 1003);

    printf("\n1002 TC'li hasta siliniyor:\n");
    sil(&liste, 1002);
    listele(liste);

    // İkinci liste
    Node* ikinci_liste = NULL;
    Hasta h4 = {1004, "Fatma Kaya", 32, "Diyabet"};
    Hasta h5 = {1005, "Can Berk", 40, "Tansiyon"};
    sona_ekle(&ikinci_liste, h4);
    sona_ekle(&ikinci_liste, h5);

    printf("\nİkinci liste birleştiriliyor...\n");
    liste_birlestir(&liste, ikinci_liste);
    listele(liste);

    liste_sil(&liste);
    return 0;
}
