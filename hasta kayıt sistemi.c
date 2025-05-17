#include <stdio.h>
#include <string.h>

struct hasta_bilgisi{
    int hasta_tc;
    char hasta_adi_soyadi[50];
    int hasta_yas;
    char hastalik_adi[50];
};

int secim_gir(void);
void hasta_ekle(FILE*);
void hasta_arama(FILE*);
void hasta_bilgisi_güncelleme(FILE*);
void hasta_listesini_yazdirma(FILE*);
void hasta_silme(FILE*);

int main() {
    FILE* dosya = fopen("hastalar.dat", "r+b");
    if (dosya == NULL) {
        dosya = fopen("hastalar.dat", "w+b");
        if (dosya == NULL) {
            printf("Dosya açılmadı veya oluşturulamadı.\n");
        }
    }

    int secim;
    do {
        secim = secim_gir();
        switch (secim) {
            case 1 : 
                hasta_ekle(dosya);
                break;
            
            case 2 : 
                hasta_arama(dosya);
                break;

            case 3 : 
                hasta_bilgisi_güncelleme(dosya);
                break;

            case 4:
                hasta_listesini_yazdirma(dosya);
                break;

            case 5 : 
                hasta_silme(dosya);
                break;

            case 0:
                printf("Çıkış yapılıyor...\n");
                break;

            default:
                printf("Geçersiz seçim.\n");
        }
    } while (secim != 0);
    fclose(dosya);
    return 0;
}

int secim_gir(void) {
    int secim;
    printf("\n=== HASTA KAYIT SİSTEMİ ===\n");
    printf("1. Hasta Ekle\n");
    printf("2. Hasta Ara\n");
    printf("3. Hasta Bilgi Güncelle\n");
    printf("4. Hasta Listesini Yazdır\n");
    printf("5. Hasta Silme\n");
    printf("0. Çıkış\n");
    printf("Seçiminizi girin: ");
    scanf("%d", &secim);
    return secim;
}

void hasta_ekle(FILE* dosya) {
    struct hasta_bilgisi yeni_hasta;
    printf("Hasta TC: ");
    scanf("%d", &yeni_hasta.hasta_tc);

    printf("Hasta Adı Soyadı: ");
    scanf(" %[^\n]", yeni_hasta.hasta_adi_soyadi);

    printf("Hasta Yaş: ");
    scanf("%d", &yeni_hasta.hasta_yas);

    printf("Hastanın Hastalığının Adı: ");
    scanf(" %[^\n]", yeni_hasta.hastalik_adi);

    fseek(dosya, 0, SEEK_END);
    fwrite(&yeni_hasta, sizeof(struct hasta_bilgisi), 1, dosya);
    printf("Hasta başarıyla eklendi.\n");
}

void hasta_arama(FILE* dosya) {
    int aranan_tc;
    int bulundu = 0;
    struct hasta_bilgisi hasta;

    printf("Hastanın TC numarasını girin: ");
    scanf("%d", &aranan_tc);

    rewind(dosya);
    while (fread(&hasta, sizeof(struct hasta_bilgisi), 1, dosya) == 1) {
        if (hasta.hasta_tc == aranan_tc) {
            printf("TC       : %d\n", hasta.hasta_tc);
            printf("Ad Soyad : %s\n", hasta.hasta_adi_soyadi);
            printf("Yaş      : %d\n", hasta.hasta_yas);
            printf("Hastalık : %s\n", hasta.hastalik_adi);
            return;
        }    
    }
    printf("Hasta Bilgisi Bulunamadı. Daha önce eklenmemiş ya da silinmiş olabilir.");
}

void hasta_bilgisi_güncelleme(FILE* dosya) {
    int aranan_tc;
    struct hasta_bilgisi hasta;
    printf("Güncellemek istediğiniz hastanın TC numarasını girin: ");
    scanf("%d", &aranan_tc);

    rewind(dosya);

    while (fread(&hasta, sizeof(struct hasta_bilgisi), 1, dosya) == 1) {
        if (hasta.hasta_tc == aranan_tc) {
            printf("Yeni TC: ");
            scanf("%d", &hasta.hasta_tc);

            printf("Yeni Ad Soyad: ");
            scanf(" %[^\n]", hasta.hasta_adi_soyadi);

            printf("Yeni Yaş: ");
            scanf("%d", &hasta.hasta_yas);

            printf("Yeni Hastalık Adı: ");
            scanf(" %[^\n]", hasta.hastalik_adi);

            fseek(dosya, -sizeof(struct hasta_bilgisi), SEEK_CUR);
            fwrite(&hasta, sizeof(struct  hasta_bilgisi), 1, dosya);
            printf("Hasta bilgileri başarıyla güncellendi.\n");
            return;
        }
    }
    printf("Hasta bulunamadı. TC numarasını kontrol edin.\n");
}

void hasta_listesini_yazdirma(FILE* dosya) {
    struct hasta_bilgisi hasta;
    rewind(dosya);

    printf("\n--- Hasta Listesi ---\n");
    int kayit_sayisi = 0;

    while (fread(&hasta, sizeof(struct hasta_bilgisi), 1, dosya) == 1) {
        printf("TC       : %d\n", hasta.hasta_tc);
        printf("Ad Soyad : %s\n", hasta.hasta_adi_soyadi);
        printf("Yaş      : %d\n", hasta.hasta_yas);
        printf("Hastalık : %s\n", hasta.hastalik_adi);
        printf("--------------------------\n");
        kayit_sayisi++;
    }
    if (kayit_sayisi == 0) {
        printf("Kayıtlı hasta bulunamadı.\n");
    }
}

/* karışık bir kısım silinmeyecek 
verileri yeni dosyaya yükleyip dosyanın adını değiştiriyor */

void hasta_silme(FILE* dosya) { 
    int silinecek_tc;
    struct hasta_bilgisi hasta;
    int bulundu = 0;

    printf("Silinecek hastanın TC numarasını girin: ");
    scanf("%d", &silinecek_tc);

    FILE* gecici_dosya = fopen("gecici_dosya.dat", "wb");
    if (gecici_dosya ==  NULL) {
        printf("Geçici dosya oluşturulamadı.\n");
        return; 
    }

    rewind(dosya);
    while (fread(&hasta, sizeof(struct hasta_bilgisi), 1, dosya) == 1) {
        if (hasta.hasta_tc != silinecek_tc) {
            fwrite(&hasta, sizeof(struct hasta_bilgisi), 1, gecici_dosya);
        }
        else {
            bulundu = 1;
        }
    }
    fclose(dosya);
    fclose(gecici_dosya);

    remove("hastalar.dat");                  // orijinal dosyayı sil
    rename("gecici_dosya.dat", "hastalar.dat");    // geçici dosyayı eski adla değiştir

    // dosya tekrar açılır, çünkü main fonksiyonundaki pointer artık geçersiz
    dosya = fopen("hastalar.dat", "r+b");

    if (bulundu) {
        printf("Hasta başarıyla silindi.\n");
    } else {
        printf("Girilen TC numarasına sahip hasta bulunamadı.\n");
    }
}