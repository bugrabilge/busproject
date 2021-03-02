#include<stdio.h>
#include <conio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>


/* Degistirilebilir Dizi Limitleri */
#define KUCUK_OTOBUS_MAX_KOLTUK_SAYISI 29
#define MAX_OTOBUS_SAYISI 20
#define MAX_SEFER_SAYISI 20
#define MAX_REZERVASYON_SAYISI 100

/* Sayaclar */
int sayac_otobus = 0;
int sayac_sefer = 0;
int sayac_rezervasyon = 0;

/* Rezervasyon Bilgileri */
char ad[MAX_REZERVASYON_SAYISI][10];
char soyad[MAX_REZERVASYON_SAYISI][10];
int secilen_koltuk_no[MAX_REZERVASYON_SAYISI];
char rezervasyon_no_dizi[MAX_REZERVASYON_SAYISI][9];
char rezervasyon_sefer_no_dizi[MAX_REZERVASYON_SAYISI][7];

/* Sefer Bilgileri */
char sefer_no_dizi[MAX_SEFER_SAYISI][7];
char sefer_baslangic_sehri_dizi[MAX_SEFER_SAYISI][13];
char sefer_varis_sehri_dizi[MAX_SEFER_SAYISI][13];
int sefer_baslangic_saati_dizi[MAX_SEFER_SAYISI];
int sefer_varis_saati_dizi[MAX_SEFER_SAYISI];
int sefer_otobus_no_dizi[MAX_SEFER_SAYISI];
float hasilat_dizi[MAX_SEFER_SAYISI];
int koltuk_doluluk_dizi[MAX_SEFER_SAYISI][100];

/* Otobus Bilgileri */
int otobus_no_dizi[MAX_OTOBUS_SAYISI];
int kapasite_dizi[MAX_OTOBUS_SAYISI];
char model_dizi[MAX_OTOBUS_SAYISI][5];

const char * hex_digits = "0123456789ABCDEF";

int karsilastir(const void* a, const void* b)
{
    return ( *(int*)b - *(int*)a );
}

void bitir()
{
    system("cls");
    printf("IYI GUNLER DILERIZ...");
}

void sefer_koltuklari_goster(int sefer_index) {
    printf("       1     2         3     4\n");
    for (int i = 0; i < kapasite_dizi[sefer_otobus_no_dizi[sefer_index]]; ++i) {
        if (i % 4 == 0) {
            printf("  %d-%s [%c]   [%c]       [%c]   [%c]\n", i / 4 + 1,
                   (i / 4) + 1 < 10 ? " " : "",
                   koltuk_doluluk_dizi[sefer_index][i + 1] == 1 ? 'x' : ' ',
                   koltuk_doluluk_dizi[sefer_index][i + 2] == 1 ? 'x' : ' ',
                   koltuk_doluluk_dizi[sefer_index][i + 3] == 1 ? 'x' : ' ',
                   koltuk_doluluk_dizi[sefer_index][i + 4] == 1 ? 'x' : ' ');
        }
    }
}

void otobus_ekle()
{
    system("cls");

    sayac_otobus = sayac_otobus + 1;

    printf("1 - Kapasite:\n");
    scanf("%d", &kapasite_dizi[sayac_otobus]);

    printf("2 - Model giriniz:\n");
    scanf("%4s", &model_dizi[sayac_otobus]);

    otobus_no_dizi[sayac_otobus] = sayac_otobus;
    printf("3 - Otobus no: %d\n", sayac_otobus);

    printf("4 - Personel sayisi: %d\n\n", kapasite_dizi[sayac_otobus] <= KUCUK_OTOBUS_MAX_KOLTUK_SAYISI ? 2 : 3);

    if (kapasite_dizi[sayac_otobus]<= KUCUK_OTOBUS_MAX_KOLTUK_SAYISI){
        printf("Bir kisa yol otobusu eklediniz...\n\n");
    }
    else {
        printf("Bir uzun yol otobusu eklediniz...\n\n");
    }

    printf("Devam etmek icin bir tusa basin ...\n");
    getchar();
    getchar();
}

void sefer_bilgisi_ekle()
{
    system("cls");

    sayac_sefer = sayac_sefer + 1;
    sefer_no_dizi[sayac_sefer][0] = '0';
    sefer_no_dizi[sayac_sefer][1] = '4';

    for (int i = 2; i < 6; i++) {
        sefer_no_dizi[sayac_sefer][i] = hex_digits[rand() % 16];
    }


    printf("Sefer No:%s\n\n", sefer_no_dizi[sayac_sefer]);



    for (int i = 1; i <= sayac_otobus; ++i) {
        printf("Otobus No: %d\n", otobus_no_dizi[i]);
        printf("Kapasite : %d\n", kapasite_dizi[i]);
        printf("Model    : %s\n", model_dizi[i]);
        printf("Personel : %d\n", kapasite_dizi[i] <= KUCUK_OTOBUS_MAX_KOLTUK_SAYISI ? 2 : 3);
        printf("\n");

    }
    printf("Bir otobus numarasi seciniz:\n");

    int secilen_otobus;
    scanf("%d", & secilen_otobus);

    sefer_otobus_no_dizi[sayac_sefer] = secilen_otobus;

tekrar_sefer:
    printf("Sefer Baslangic Saati:\n\n");
    scanf("%d", & sefer_baslangic_saati_dizi[sayac_sefer]);

    int dakika = sefer_baslangic_saati_dizi[sayac_sefer] % 100;
    if (sefer_baslangic_saati_dizi[sayac_sefer]>= 0 && sefer_baslangic_saati_dizi[sayac_sefer]<2400 && dakika < 60)
    {
        if (dakika!= 4) {
            printf("Sefer bu saatte gerceklesemez.\n\n");

            sefer_baslangic_saati_dizi[sayac_sefer] = sefer_baslangic_saati_dizi[sayac_sefer] - dakika;
            sefer_baslangic_saati_dizi[sayac_sefer] = sefer_baslangic_saati_dizi[sayac_sefer] + 4;

            printf("Duzeltilen sefer saati : %d\n\n", sefer_baslangic_saati_dizi[sayac_sefer]);
        }
tekrar_varis:
        printf("Varis saati:\n\n");
        scanf("%d", & sefer_varis_saati_dizi[sayac_sefer]);
        if ((sefer_varis_saati_dizi[sayac_sefer] - sefer_baslangic_saati_dizi[sayac_sefer])>400 && kapasite_dizi[secilen_otobus]<= KUCUK_OTOBUS_MAX_KOLTUK_SAYISI) {
            printf("Bu yolculugunuzda kisa yol otobusu kullanilamaz.\nTekrar varis saati giriniz.\n\n");
            goto tekrar_varis;
        }

    }
    else
    {
        printf("Illegal saat, yeniden girininiz.\n\n");
        goto tekrar_sefer;
    }

    printf("Sefer baslangic sehri:\n\n");
    scanf("%s", & sefer_baslangic_sehri_dizi[sayac_sefer]);

    printf("Sefer varis sehri:\n\n");
    scanf("%s", & sefer_varis_sehri_dizi[sayac_sefer]);

    printf("Istenen toplam hasilat:\n\n");
    scanf("%f", & hasilat_dizi[sayac_sefer]);

    printf("Musteri basi ucret:%.2f\n\n", (hasilat_dizi[sayac_sefer] / (float)kapasite_dizi[secilen_otobus]));


    printf("Devam etmek icin bir tusa basin ...\n");
    getchar();
    getchar();
}

void sefer_koltuk_bilgisi_goster()
{
    system("cls");
    printf("Sefer/koltuk bilgisi:\n\n");

    for (int i=1; i<=sayac_sefer; ++i) {
        printf("Sefer No %d:%s\n\n", i, sefer_no_dizi[i]);
    }

    int secilen_sefer;
    printf("Sefer No?\n\n");
    scanf("%d", & secilen_sefer);

    sefer_koltuklari_goster(secilen_sefer);

    int otobus = sefer_otobus_no_dizi[secilen_sefer];
    float musteri_basi_ucret = hasilat_dizi[secilen_sefer] / kapasite_dizi[otobus];
    float toplanan_hasilat = (float)(kapasite_dizi[otobus] - sefer_bos_koltuk_sayisi(secilen_sefer)) * musteri_basi_ucret;

    printf("Bilgilendirme kismi:\n\n");
    printf("Sefer no             : %s\n\n", sefer_no_dizi[secilen_sefer]);
    printf("Otobus no            : %d\n\n", sefer_otobus_no_dizi[secilen_sefer]);
    printf("Sefer baslangic saati: %d\n", sefer_baslangic_saati_dizi[secilen_sefer]);
    printf("Sefer varis saati    : %d\n", sefer_varis_saati_dizi[secilen_sefer]);
    printf("Sefer baslangic sehri: %s\n", sefer_baslangic_sehri_dizi[secilen_sefer]);
    printf("Sefer varis sehri    : %s\n", sefer_varis_sehri_dizi[secilen_sefer]);
    printf("Istenilen hasilat    : %.2f\n", hasilat_dizi[secilen_sefer]);
    printf("Toplanan hasilat     : %.2f\n", toplanan_hasilat);
    printf("Bos koltuk sayisi    : %d\n\n", sefer_bos_koltuk_sayisi(secilen_sefer));

    printf("Devam etmek icin bir tusa basin ...\n");
    getch();
}

void firma_girisi_menusu_goster()
{
    while (1) {
        system("cls");
        printf("FIRMA GIRISI\n\n 1 - OTOBUS EKLE\n 2 - SEFER BILGISI EKLE\n 3 - SEFER/KOLTUK BILGISI\n 4 - BIR UST MENUYE DON\n\n");

        int secim;
        scanf(" %d", & secim);

        if (secim == 4) {
            system("cls");
            break;
        }

        switch (secim) {
        case 1:
            otobus_ekle();
            break;

        case 2:
            sefer_bilgisi_ekle();
            break;

        case 3:
            sefer_koltuk_bilgisi_goster();
            break;

        default:
            printf("Hatali bir giris yaptiniz!!!\n\n");
            printf("Tekrar denemek icin bir tusa basiniz.");
            getch();
            break;

        }
    }
}

int integer_sefer_nodan_dizi_index_bul(int sefer_no)
{
    int index = -1;
    for (int i=1; i<=sayac_sefer; ++i) {
        int deger = strtol(sefer_no_dizi[i], NULL, 16);
        if (deger == sefer_no) {
            index = i;
        }
    }
    return index;
}

int string_sefer_nodan_dizi_index_bul(char sefer_no[7])
{
    int index = -1;
    for (int i=1; i<=sayac_sefer; ++i) {
        if (strcmp(sefer_no_dizi[i], sefer_no) == 0) {
            index = i;
        }
    }
    return index;
}

int sefer_bos_koltuk_sayisi(int sefer_index) {
    int otobus = sefer_otobus_no_dizi[sefer_index];
    int kapasite = kapasite_dizi[otobus];

    int bos_koltuk_sayisi = kapasite;
    for (int i = 0; i < kapasite; ++i) {
        if (koltuk_doluluk_dizi[sefer_index][i] == 1) {
            bos_koltuk_sayisi = bos_koltuk_sayisi - 1;
        }
    }
    return bos_koltuk_sayisi;
}

void seferleri_listele()
{
    system("cls");
    int sefer_no_dizi_sirali[20];

    for (int i=1; i<=sayac_sefer; ++i) {
        sefer_no_dizi_sirali[i] = strtol(sefer_no_dizi[i], NULL, 16);
    }

    qsort(sefer_no_dizi_sirali + 1, sayac_sefer, sizeof(int), karsilastir);

    printf("Buyukten Kucuge Sirali Sefer No:\n\n");

    for (int i=1; i<=sayac_sefer; ++i) {
        int sefer_index = integer_sefer_nodan_dizi_index_bul(sefer_no_dizi_sirali[i]);
        int otobus_index = sefer_otobus_no_dizi[sefer_index];

        printf("Sefer No :  %06X\n\n", sefer_no_dizi_sirali[i]);
        printf("Otobus no            : %d\n\n", sefer_otobus_no_dizi[sefer_index]);
        printf("Sefer baslangic saati: %d\n", sefer_baslangic_saati_dizi[sefer_index]);
        printf("Sefer varis saati    : %d\n", sefer_varis_saati_dizi[sefer_index]);
        printf("Sefer baslangic sehri: %s\n", sefer_baslangic_sehri_dizi[sefer_index]);
        printf("Sefer varis sehri    : %s\n", sefer_varis_sehri_dizi[sefer_index]);
        printf("Musteri basi ucret   : %.2f\n", hasilat_dizi[sefer_index] / kapasite_dizi[otobus_index]);
        printf("Musait koltuk sayisi : %d\n\n\n", sefer_bos_koltuk_sayisi(sefer_index));
    }

    printf("Devam etmek icin bir tusa basin ...\n");
    getch();
}

void sefer_rezervasyon_yap()
{
    system("cls");
    printf("Sefer Rezervasyon yap\n\n");

    for (int i=1; i<=sayac_sefer; ++i) {
        printf("Sefer No %d:    %s\n\n", i, sefer_no_dizi[i]);
    }

    char secilen_sefer_no[7];
sefer_no_al:
    printf("Sefer no giriniz:\n\n");
    scanf("%s", &secilen_sefer_no);

    int sefer_index = string_sefer_nodan_dizi_index_bul(secilen_sefer_no);
    if (sefer_index == -1) {
        printf("Yanlis sefer no!\n\n");
        goto sefer_no_al;
    }

    sefer_koltuklari_goster(sefer_index);

    sayac_rezervasyon = sayac_rezervasyon + 1;

    printf("Ad          :");
    scanf("%s", &ad[sayac_rezervasyon]);
    printf("Soyad       :");
    scanf("%s", &soyad[sayac_rezervasyon]);

koltuk_sec:
    printf("Koltuk no   :");
    scanf("%d", & secilen_koltuk_no[sayac_rezervasyon]);

    int koltuk_no = secilen_koltuk_no[sayac_rezervasyon];

    if (koltuk_doluluk_dizi[sefer_index][koltuk_no] == 1) {
        printf("Sectiginiz koltuk dolu, baska koltuk seciniz..\n");
        goto koltuk_sec;
    } else {
        koltuk_doluluk_dizi[sefer_index][koltuk_no] = 1;
    }

    sefer_koltuklari_goster(sefer_index);

    char onay;
evet_hayir_secim:
    printf("Onayliyor musunuz? E/H\n");
    scanf(" %c", &onay);
    if (onay=='h' || onay=='H'){
        secilen_koltuk_no[sayac_rezervasyon] = 0;

        for(int i=0; i < 10; i++){
            ad[sayac_rezervasyon][i]= 0;
            soyad[sayac_rezervasyon][i]= 0;
        }

        sayac_rezervasyon = sayac_rezervasyon - 1;

        koltuk_doluluk_dizi[sefer_index][koltuk_no] = 0;

        printf("Rezervasyon iptal edildi. Devam etmek icin bir tusa basin.\n");
    }
    else if (onay=='e' || onay=='E'){
        for (int i = 0; i < 8; i++) {
            rezervasyon_no_dizi[sayac_rezervasyon][i] = hex_digits[rand() % 16];
        }

        strncpy(rezervasyon_sefer_no_dizi[sayac_rezervasyon], secilen_sefer_no, 6);

        printf("Rezervasyon numaraniz : %s\n", rezervasyon_no_dizi[sayac_rezervasyon]);
        printf("Rezervasyon yapildi. Devam etmek icin bir tusa basin.\n");
    }
    else{
        printf("Yanlis tusa bastiniz.\n");
        goto evet_hayir_secim;
    }

    getchar();
    getchar();
}

int rezervasyon_nodan_rezervasyon_index_bul(char rezervasyon_no[9])
{
    int index = -1;
    for (int i=1; i<=sayac_rezervasyon; ++i) {
        if (strcmp(rezervasyon_no_dizi[i], rezervasyon_no) == 0) {
            index = i;
        }
    }
    return index;
}

void rezervasyon_goster()
{
    system("cls");
    char secilen_rezervasyon_no[9];
rezervasyon_no_al:
    printf("Rezervasyon numaranizi giriniz  :\n\n");
    scanf("%s",&secilen_rezervasyon_no);

    int rezervasyon_index = rezervasyon_nodan_rezervasyon_index_bul(secilen_rezervasyon_no);

    int sefer_index = string_sefer_nodan_dizi_index_bul(rezervasyon_sefer_no_dizi[rezervasyon_index]);
    int otobus_index = sefer_otobus_no_dizi[sefer_index];

    if (rezervasyon_index != -1 && sefer_index != -1) {
        printf("\n\nBilgilendirme ekrani:\n\n");
        printf("Rezervasyon no       :%s\n", secilen_rezervasyon_no);
        printf("Ad                   :%s\n", ad[rezervasyon_index]);
        printf("Soyad                :%s\n", soyad[rezervasyon_index]);
        printf("Koltuk no            :%d\n", secilen_koltuk_no[rezervasyon_index]);

        printf("Sefer no             :%s\n", sefer_no_dizi[sefer_index]);
        printf("Otobus no            :%d\n\n", sefer_otobus_no_dizi[sefer_index]);
        printf("Sefer baslangic saati:%d\n", sefer_baslangic_saati_dizi[sefer_index]);
        printf("Sefer varis saati    :%d\n", sefer_varis_saati_dizi[sefer_index]);
        printf("Sefer baslangic sehri:%s\n", sefer_baslangic_sehri_dizi[sefer_index]);
        printf("Sefer varis sehri    :%s\n", sefer_varis_sehri_dizi[sefer_index]);
        printf("Ucret                :%.2f\n\n", hasilat_dizi[sefer_index] / kapasite_dizi[otobus_index]);
        printf("Devam etmek icin bir tusa basiniz...");
    }
    else {
        printf("Yanlis rezervasyon no girdiniz! Tekrar deneyiniz...!\n\n");
        goto rezervasyon_no_al;
    }

    getch();
}

void musteri_girisi_menusu_goster()
{
    while (1) {
        system("cls");
        printf("MUSTERI GIRISI\n\n 1 - SEFERLERI LISTELE\n 2 - SEFER REZERVASYON YAP\n 3 - BIR UST MENUYE DON\n 4 - REZERVASYON GOSTER\n\n");

        int secim;
        scanf("%d", & secim);



        if (secim == 3) {
            system("cls");
            break;
        }

        switch (secim) {
        case 1:
            seferleri_listele();
            break;

        case 2:
            sefer_rezervasyon_yap();
            break;

        case 4:
            rezervasyon_goster();
            break;

        default:
            printf("Hatali bir giris yaptiniz!!!\n\n");
            printf("Tekrar denemek icin bir tusa basiniz.");
            getch();
            break;

        }

    }

}



int main()
{


    srand(time(NULL));

    while (1) {
        printf("ANA MENU\n\n1 - FIRMA GIRISI\n2 - MUSTERI GIRISI\n3 - CIKIS\n\n");

        int secim;
        scanf(" %d", & secim);

        if (secim == 3) {
            bitir();
            break;
        }

        switch (secim) {
        case 1:
            firma_girisi_menusu_goster();
            break;
        case 2:
            musteri_girisi_menusu_goster();
            break;
        default:
            printf("Hatali bir giris yaptiniz!!!\n\n");
            break;
        }
    }

    return 0;
}


