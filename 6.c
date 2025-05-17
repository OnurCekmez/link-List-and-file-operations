// SORU A11 – Rastgele Erişimli Dosyada Müşteri Güncelleme
// Amaç: Binary dosyada kayıtlı müşterilerin bakiyesi güncellenecek
// Konular: struct, binary dosya, fseek, fread, fwrite, dosyada yerinde güncelleme

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Musteri {
    int no;
    char ad[30];
    float bakiye;
};

void musteriEkle(FILE *dosya) {
    struct Musteri m;
    printf("\nMüşteri numarası: "); scanf("%d", &m.no);
    printf("Ad: "); scanf(" %[^]", m.ad);
    printf("Bakiye: "); scanf("%f", &m.bakiye);

    fwrite(&m, sizeof(struct Musteri), 1, dosya);
    printf("Müşteri kaydedildi.\n");
}

void bakiyeGuncelle(FILE *dosya, int hedefNo) {
    struct Musteri m;
    rewind(dosya); // başa sar

    while (fread(&m, sizeof(struct Musteri), 1, dosya) == 1) {
        if (m.no == hedefNo) {
            printf("Mevcut bakiye: %.2f\n", m.bakiye);
            printf("Yeni bakiye: ");
            scanf("%f", &m.bakiye);

            fseek(dosya, -sizeof(struct Musteri), SEEK_CUR);
            fwrite(&m, sizeof(struct Musteri), 1, dosya);
            printf("Bakiye güncellendi.\n");
            return;
        }
    }
    printf("Müşteri bulunamadı.\n");
}

void musteriListele(FILE *dosya) {
    struct Musteri m;
    rewind(dosya);
    printf("\nTÜM MÜŞTERİLER:\n---------------------\n");
    while (fread(&m, sizeof(struct Musteri), 1, dosya) == 1) {
        printf("No: %d | Ad: %s | Bakiye: %.2f\n", m.no, m.ad, m.bakiye);
    }
}

int main() {
    FILE *dosya = fopen("musteriler.dat", "r+b");
    if (!dosya) {
        // Dosya yoksa oluştur
        dosya = fopen("musteriler.dat", "w+b");
        if (!dosya) {
            printf("Dosya açılamadı!\n");
            return 1;
        }
    }

    int secim, hedefNo;
    do {
        printf("\n1. Müşteri Ekle\n2. Bakiye Güncelle\n3. Listele\n0. Çıkış\nSeçim: ");
        scanf("%d", &secim);
        switch (secim) {
            case 1: musteriEkle(dosya); break;
            case 2:
                printf("Güncellenecek müşteri numarası: ");
                scanf("%d", &hedefNo);
                bakiyeGuncelle(dosya, hedefNo); break;
            case 3: musteriListele(dosya); break;
        }
    } while (secim != 0);

    fclose(dosya);
    return 0;
}