// SORU A12: Rastgele erişimli dosyada ürün silme (bayrak işaretli)
// Amaç: struct kayıtlar binary dosyada tutulacak, "aktif" bayrağına göre silinmiş gibi davranılacak

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Urun {
    int id;
    char ad[30];
    float fiyat;
    int aktif; // 1 = aktif, 0 = silinmiş kabul et
};

void urunEkle(FILE *dosya) {
    struct Urun u;
    printf("\nUrun ID: "); scanf("%d", &u.id);
    printf("Ad: "); scanf(" %[^]", u.ad);
    printf("Fiyat: "); scanf("%f", &u.fiyat);
    u.aktif = 1;
    fwrite(&u, sizeof(struct Urun), 1, dosya);
    printf("Urun kaydedildi.\n");
}

void urunSil(FILE *dosya, int hedefID) {
    struct Urun u;
    rewind(dosya);
    while (fread(&u, sizeof(struct Urun), 1, dosya) == 1) {
        if (u.id == hedefID && u.aktif == 1) {
            u.aktif = 0;
            fseek(dosya, -sizeof(struct Urun), SEEK_CUR);
            fwrite(&u, sizeof(struct Urun), 1, dosya);
            printf("Urun silindi. (Pasif hale getirildi)\n");
            return;
        }
    }
    printf("Urun bulunamadi veya zaten silinmis.\n");
}

void urunListele(FILE *dosya) {
    struct Urun u;
    rewind(dosya);
    printf("\nAKTIF URUNLER:\n------------------\n");
    while (fread(&u, sizeof(struct Urun), 1, dosya) == 1) {
        if (u.aktif == 1) {
            printf("ID: %d | Ad: %s | Fiyat: %.2f\n", u.id, u.ad, u.fiyat);
        }
    }
}

int main() {
    FILE *dosya = fopen("urunler.dat", "r+b");
    if (!dosya) {
        dosya = fopen("urunler.dat", "w+b");
        if (!dosya) {
            printf("Dosya acilamadi!\n");
            return 1;
        }
    }

    int secim, hedefID;
    do {
        printf("\n1. Urun Ekle\n2. Urun Sil\n3. Listele\n0. Cikis\nSecim: ");
        scanf("%d", &secim);
        switch (secim) {
            case 1: urunEkle(dosya); break;
            case 2:
                printf("Silinecek urun ID: ");
                scanf("%d", &hedefID);
                urunSil(dosya, hedefID); break;
            case 3: urunListele(dosya); break;
        }
    } while (secim != 0);

    fclose(dosya);
    return 0;
}