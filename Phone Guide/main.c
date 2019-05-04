#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct telephone
{
    char isim[100];
    long int kod;
    long int numara;
};

void duraksama()
{
    printf("\n");
    printf("Menüye dönmek için herhangi bir tuþa bas%cn ...  ",253);
    system("pause > null");
    printf("\n");
}

void kayitEkle();
void kayitListele();
void kayitDuzenle();
void kayitBulmaNo();
void kayitBulmaAd();
void kayitSilme();
void tekrarSor();
int hesap();

int main()
{
    setlocale(LC_ALL, "Turkish");

    int m;

    while(1)
    {
        printf("\n     ###     =>  TELEFON REHBER%c SEÇ%cM MENÜSÜ  <=     ###     ",221,221);
        printf("\n\n");
        printf("   # Kay%ct eklemek için => 1 <= basin ...\n", 253);
        printf("   # Telefonlar%c listelemek icin => 2 <= basin ...\n",253);
        printf("   # Kayd%c düzenlemek için => 3 <= basin ...\n",253);
        printf("   # Numara ile kay%ct bulmak icin => 4 <= basin ...\n",253);
        printf("   # %csim ile kay%ct bulmak icin => 5 <= basin ...\n",221,253);
        printf("   # Kay%ct silmek icin => 6 <= basin ...\n",253);
        printf("   # Ç%ckmak icin => 0 <= basin ...\n\n",253);
        printf("Menu seciminiz : ");
        scanf("%d", &m);

        if(m==1)
        {
            kayitEkle();
            duraksama();
        }
        else if(m==2)
        {
            kayitListele();
            duraksama();
        }
        else if(m==3)
        {
            kayitDuzenle();
            duraksama();
        }
        else if(m==4)
        {
            kayitBulmaNo();
            duraksama();
        }
        else if(m==5)
        {
            kayitBulmaAd();
            duraksama();
        }
        else if(m==6)
        {
            kayitSilme();
            duraksama();
        }
        else if(m==0)
        {
            break;
        }
    }
    return 0;
}

void kayitEkle()
{
    FILE *fp;
    struct telephone tel;
    fp=fopen("TelefonRehber.txt","a+");
    if(fp==NULL)
    {
        printf("Dosya açma hatasi ! \n");
        exit(1);
    }
    printf("Isim : ");
    scanf("%s", tel.isim);
    printf("Kod : ");
    scanf("%ld", &tel.kod);
    printf("Numara : ");
    scanf("%ld", &tel.numara);

    if(fwrite(&tel, sizeof(tel), 1, fp) !=1)
    {
        printf("Dosya yazma hatasi ! \n");
        exit(1);
    }
    fclose(fp);
}

void kayitListele()
{
    FILE *fp;
    struct telephone tel;
    fp=fopen("TelefonRehber.txt","r");
    if(fp==NULL)
    {
        printf("Dosya açma hatasi ! \n");
        exit(1);

    }
    while(fread(&tel, sizeof(tel), 1, fp) == 1)
    {
        printf("Isim : %s \n", tel.isim);
        printf("Kod : %ld \n", tel.kod);
        printf("Numara : %ld \n", tel.numara);
        printf("\n");
    }
    fclose(fp);
}

void kayitDuzenle()
{
    FILE *fp1, *fp2;
    struct telephone tel;
    char duzenle[100];
    int sayac=0;

    while(1)
        {
    fp1=fopen("TelefonRehber.txt","r");
    fp2=fopen("TelefonRehber1.txt","w");

    printf("\nDuzenlenecek kayidin ismi : ");
    scanf("%s", duzenle);

    while(fread(&tel, sizeof(tel), 1, fp1)==1)
    {

        if(strstr(tel.isim,duzenle))
        {
            printf("Yeni isim : ");
            scanf("%s", tel.isim);
            printf("Yeni kod : ");
            scanf("%ld", &tel.kod);
            printf("Yeni numara : ");
            scanf("%ld", &tel.numara);
            fwrite(&tel, sizeof(tel), 1, fp2);
            sayac++;
            continue;
        }

        else
            fwrite(&tel, sizeof(tel), 1, fp2);

    }

    fclose(fp1);
    fclose(fp2);

    remove("TelefonRehber.txt");
    rename("TelefonRehber1.txt","TelefonRehber.txt");

        if(sayac==0)
        {
            printf("\nDuzenlenecek kisi bulunamadi.Yeniden arama yapmak ister misiniz? <E/H> ");
            if(toupper(getche())=='H')
                    break;
        }
        else
            break;

        }


}

void kayitBulmaNo()
{
    FILE *fp;
    struct telephone tel;
    long int alinan;
    printf("Aranacak numarayi giriniz : ");
    scanf("%ld", &alinan);
    fp=fopen("TelefonRehber.txt","r");
    if(fp==NULL)
    {
        printf("Dosya açma hatasi ! \n");
        exit(1);

    }
    while(!feof(fp))
    {
        fread(&tel, sizeof(tel), 1, fp);
        if(tel.numara==alinan)
        {
            printf("Isim : %s \n", tel.isim);
            printf("Kod : %ld \n", tel.kod);
            printf("Numara : %ld \n", tel.numara);
            printf("\n");
            break;
        }
    }
    fclose(fp);

}

void kayitBulmaAd()
{
    FILE *fp;
    struct telephone tel;
    char alinan[100];
    printf("Aranacak ismi giriniz : ");
    scanf("%s", alinan);
    fp=fopen("TelefonRehber.txt","r");
    if(fp==NULL)
    {
        printf("Dosya açma hatasi ! \n");
        exit(1);

    }
    while(!feof(fp))
    {
        fread(&tel, sizeof(tel), 1, fp);
        if(strcmp(tel.isim,alinan)==0)
        {
            printf("Isim : %s \n", tel.isim);
            printf("Kod : %ld \n", tel.kod);
            printf("Numara : %ld \n", tel.numara);
            printf("\n");
            break;
        }
    }
    fclose(fp);
}

void kayitSilme()
{
    FILE *fp1,*fp2;
    struct telephone tel;
    long int aranan;
    int sayac=0;
    while(1)
    {
    fp1=fopen("TelefonRehber.txt","r");
    fp2=fopen("TelefonRehber1.txt","w");

    printf("\nSilinecek kisinin kodu : ");
    scanf("%ld",&aranan);

    while(fread(&tel, sizeof(tel), 1, fp1)==1)
    {

        if(tel.kod==aranan)
        {
            sayac++;
            continue;
        }
        else
            fwrite(&tel, sizeof(tel), 1, fp2);

    }

    fclose(fp1);
    fclose(fp2);

    remove("TelefonRehber.txt");
    rename("TelefonRehber1.txt","TelefonRehber.txt");

            if(sayac==0)
        {
            printf("\nSilinecek kisi bulunamadi! Yeniden arama yapmak ister misiniz? <E/H> ");
            if(toupper(getche())=='H')
                    break;
        }
        else
            break;
    }
}
