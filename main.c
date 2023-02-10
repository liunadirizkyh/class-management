#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct database
{
    char nim[100];
    char nama[100];
    int asg, mid, fin;
}Mahasiswa;

int count = 0;
Mahasiswa mahasiswa[1000];

void menu();
void addStudent();
void entryScore();
void entrynewScore();
void showData();
int binarySearch(Mahasiswa mahasiswa[], char nim[], int kiri, int kanan);
void quickSort(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe);
int partition(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe);
void swap(Mahasiswa *mahasiswaA, Mahasiswa *mahasiswaB);
void enterToContinue();
void output();
void prosesInputNilai(int index, char tipe);
void outputNilai(int index);

int main()
{
    system("cls");
    unsigned short exit = 0, option, valid;

    FILE *fp = fopen("database.data", "a");
    if(fp == NULL) printf("File tidak ditemukan!\n");
    fclose(fp);

    do
    {
        menu();
        printf("Pilih menu: ");
        valid = scanf("%hu", &option);
        getchar();

        if(valid)
        {
            if(option == 0)
            {
                system("cls");
                printf("Keluar...");
                exit = 1;
            }
            else if(option == 1)
            {
                system("cls");
                addStudent();
            }
            else if(option == 2)
            {
                system("cls");
                entryScore();
            }
            else if(option == 3)
            {
                system("cls");
                showData();
            }
            else
            {
                system("cls");
                printf("Input invalid! Silahkan coba lagi!\n");
            }
        }
        else
        {
            system("cls");
            printf("Input invalid! Silahkan coba lagi!\n");
        }
    }while(!exit);
}   

void menu()
{
    printf("MENU PROGRAM\n");
    printf("1. Add Student\n");
    printf("2. Entry Score\n");
    printf("3. Show Data\n");
    printf("0. Exit\n");
    printf("=================\n");
}

void addStudent()
{
    Mahasiswa mahasiswadd;

    FILE *fp = fopen("database.data", "a");

    printf("Masukkan data anda\n");
    printf("==================\n");
    printf("NAME: ");
    scanf(" %[^\n]", mahasiswadd.nama);
    getchar();
    printf("NIM: ");
    scanf(" %s", mahasiswadd.nim);
    getchar();
    while(1)
    {
        if(!(strlen(mahasiswadd.nim) <= 10))
        {
            printf("NIM Tidak boleh di atas 10 Karakter!\n");
            printf("NIM : ");
            scanf(" %s", mahasiswadd.nim);
            getchar();
        }
        else
        {
            break;
        }
    }
    fprintf(fp, "%s#%s#%d#%d#%d\n", mahasiswadd.nama, mahasiswadd.nim, -1, -1, -1);
    fclose(fp);
    printf("Data sudah disimpan!\n");
    enterToContinue();
    system("cls");
}

void entryScore()
{
    int exit = 0;
    char input_nim_opsi[100];
    char input_score_opsi[100];

    FILE *fp = fopen("database.data", "r");
    count = 0;
    
    while(!feof(fp))
    {
        fscanf(fp," %[^#]#%[^#]#%d#%d#%d\n", mahasiswa[count].nama, mahasiswa[count].nim, &mahasiswa[count].asg, &mahasiswa[count].mid, &mahasiswa[count].fin);
        count++;
    }

    quickSort(mahasiswa, 0, count-1, 'n');

    int index;

    do
    {
        system("cls");
        
        output();

        printf("Silahkan pilih NIM siswa yang akan diubah!\n");
        printf("Ketik N untuk keluar!\n");
        printf("Input : ");
        scanf(" %s", input_nim_opsi);
        getchar();

        if(strcmp(input_nim_opsi, "N") == 0)
        {
            exit = 1;
        }
        else
        {
            index = binarySearch(mahasiswa,  input_nim_opsi, 0, count);
            if(index == -1)
            {
                printf("Data tidak ditemukan! silahkan coba lagi\n");
                enterToContinue();
            }
            else
            {
                int exit_score = 0;
                do
                {
                    system("cls");
                    printf("| %-10s | %-30s | %-3s | %-3s | %-3s |\n", "NIM", "NAMA LENGKAP", "ASG", "MID", "FIN");
                    printf("%s\n", "-----------------------------------------------------------------");
                    
                    outputNilai(index);
                    printf("\n> Merubah nilai %s\n", mahasiswa[index].nama);

                    printf("\nSilahkan pilih ASG atau MID atau FIN!\n");
                    printf("Ketik N untuk keluar!\n");
                    printf("Input : ");
                    scanf(" %s", input_score_opsi);
                    getchar();
                    if((strcmp(input_score_opsi, "ASG") == 0) || (strcmp(input_score_opsi, "MID") == 0) || (strcmp(input_score_opsi, "FIN") == 0) || (strcmp(input_score_opsi, "N") == 0))
                    {
                        if(strcmp(input_score_opsi, "N") == 0)
                        {
                            exit_score = 1;
                        }
                        else if(strcmp(input_score_opsi, "ASG") == 0)
                        {
                            prosesInputNilai(index, 'a');
                        }
                        else if(strcmp(input_score_opsi, "MID") == 0)
                        {
                            prosesInputNilai(index, 'm');
                        }
                        else if(strcmp(input_score_opsi, "FIN") == 0)
                        {
                            prosesInputNilai(index, 'f');
                        }
                    }
                    else
                    {
                        printf("Input salah! silahkan coba lagi!\n");
                    }
                }while(!exit_score);
                system("cls");
            }
        }
    }while(!exit);
    fclose(fp);
    
    entrynewScore();
    system("cls");
}

void entrynewScore()
{
    FILE *fp = fopen("database.data", "w");

    for(int i = 0; i < count; i++)
    {
        if(count == 1)
        {
            if(strlen(mahasiswa[i].nama) > 0);
            else continue;
        }
        fprintf(fp, "%s#%s#%d#%d#%d\n", mahasiswa[i].nama, mahasiswa[i].nim, mahasiswa[i].asg, mahasiswa[i].mid, mahasiswa[i].fin);
    }
    fclose(fp);
}

void showData()
{
    FILE *fp;
    fp = fopen("database.data", "r");
    if(fp == NULL)
    {
        printf("File doesn't exist...");
        exit(1);
    }
    count = 0;

    while(!feof(fp))
    {
        fscanf(fp," %[^#]#%[^#]#%d#%d#%d\n",mahasiswa[count].nama, mahasiswa[count].nim, &mahasiswa[count].asg, &mahasiswa[count].mid, &mahasiswa[count].fin);
        count++;
    }

    char input_sorting[50];
    do
    {
        printf("Pilih pengurutan data (NIM, ASG, MID, or FIN)\n");
        printf("Ketik N untuk keluar!\n");
        printf("Input : ");
        scanf(" %[^\n]", input_sorting);
        getchar();

        if((strcmp(input_sorting, "NIM") == 0) || (strcmp(input_sorting, "ASG") == 0) || (strcmp(input_sorting, "MID") == 0) || (strcmp(input_sorting, "FIN") == 0) || (strcmp(input_sorting, "N") == 0))
        {
            if(strcmp(input_sorting, "N") == 0)
            {
                break;
            }
            printf("Sorting berdasarkan %s!\n\n", input_sorting);

            if(strcmp(input_sorting, "NIM") == 0)
            {
                quickSort(mahasiswa, 0, count-1, 'n');
                output();
            }
            else if(strcmp(input_sorting, "ASG") == 0)
            {
                quickSort(mahasiswa, 0, count-1, 'a');
                output();
            }
            else if(strcmp(input_sorting, "MID") == 0)
            {
                quickSort(mahasiswa, 0, count-1, 'm');
                output();
            }
            else if(strcmp(input_sorting, "FIN") == 0)
            {
                quickSort(mahasiswa,0, count-1, 'f');
                output();
            }
            enterToContinue();
            system("cls");
        }
        else
        {
            system("cls");
            printf("Input invalid! Silahkan coba lagi!\n");
        }
    }while(1);
    enterToContinue();
    system("cls");
    fclose(fp);
}

int binarySearch(Mahasiswa mahasiswa[], char nim[], int kiri, int kanan)
{
    int tengah;
    while(kiri <= kanan)
    {
        tengah = (kiri + kanan) / 2;
        if(strcmp(nim, mahasiswa[tengah].nim) == 0)
        {
            return tengah;
        }
        if(strcmp(nim, mahasiswa[tengah].nim) < 0)
        {
            kanan = tengah - 1;
        }
        if(strcmp(nim, mahasiswa[tengah].nim) > 0)
        {
            kiri = tengah + 1;
        }
    }
    return -1;
}

void swap(Mahasiswa *mahasiswaA, Mahasiswa *mahasiswaB)
{
    Mahasiswa temp = *mahasiswaA;
    *mahasiswaA = *mahasiswaB;
    *mahasiswaB = temp;
}

int partition(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe)
{
    Mahasiswa pivot = mahasiswa[akhir];
    int i  = (mulai - 1);

    if(tipe == 'n')
    {
        for(int j = mulai; j <= akhir - 1; j++)
        {
            if(strcmp(mahasiswa[j].nim, pivot.nim) < 0)
            {
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    else if(tipe == 'a')
    {
        for(int j = mulai; j <= akhir - 1; j++)
        {
            if(mahasiswa[j].asg < pivot.asg)
            {
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    else if(tipe == 'm')
    {
        for(int j = mulai; j <= akhir - 1; j++)
        {
            if(mahasiswa[j].mid < pivot.mid)
            {
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    else if(tipe == 'f')
    {
        for(int j = mulai; j <= akhir - 1; j++)
        {
            if(mahasiswa[j].fin < pivot.fin)
            {
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    swap(&mahasiswa[i + 1], &mahasiswa[akhir]);
    return(i+1);
}

void quickSort(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe)
{
    if(mulai < akhir)
    {
        int tengah = partition(mahasiswa, mulai, akhir, tipe);
        quickSort(mahasiswa, mulai, tengah - 1, tipe);
        quickSort(mahasiswa, tengah + 1, akhir, tipe);
    }
}

void enterToContinue()
{
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
}

void output()
{
    printf("%s\n", "-----------------------------------------------------------------");
    printf("| %-10s | %-30s | %-3s | %-3s | %-3s |\n", "NIM", "NAMA LENGKAP", "ASG", "MID", "FIN");
    printf("%s\n", "-----------------------------------------------------------------");

    for(int i = 0; i < count; i++)
    {
        if(count == 1)
        {
            if(strlen(mahasiswa[i].nama) > 0)
            {
                printf("| %-10s | %-30s | ", mahasiswa[i].nim, mahasiswa[i].nama);
                if(mahasiswa[i].asg == -1)
                {
                    printf("%-3s | ", "N/A");
                }
                else
                {
                    printf("%-3d | ", mahasiswa[i].asg);
                }
                
                if(mahasiswa[i].mid == -1)
                {
                    printf("%-3s | ", "N/A");
                }
                else
                {
                    printf("%-3d | ", mahasiswa[i].mid);
                }

                if(mahasiswa[i].fin == -1)
                {
                    printf("%-3s |\n", "N/A");
                }
                else
                {
                    printf("%-3d |\n", mahasiswa[i].fin);
                }
            }
            else
            {
                printf("\t\t\t Data masih kosong\n");
            }
        }
        else
        {
            printf("| %-10s | %-30s | ", mahasiswa[i].nim, mahasiswa[i].nama);
            if(mahasiswa[i].asg == -1)
            {
                printf("%-3s | ", "N/A");
            }
            else
            {
                printf("%-3d | ", mahasiswa[i].asg);
            }
                
            if(mahasiswa[i].mid == -1)
            {
                printf("%-3s | ", "N/A");
            }
            else
            {
                printf("%-3d | ", mahasiswa[i].mid);
            }

            if(mahasiswa[i].fin == -1)
            {
                printf("%-3s |\n", "N/A");
            }
            else
            {
                printf("%-3d |\n", mahasiswa[i].fin);
            }
        }
    }
    printf("%s\n", "-----------------------------------------------------------------");
    if(count == 1)
    {
        if(strlen(mahasiswa[0].nama) > 0)
        {
            printf("Total data tersedia: %d\n\n", count);
        }
        else
        {
            printf("Total data tersedia: %d\n\n", count - 1);
        }
    }
    else
    {
        printf("Total data tersedia: %d\n\n", count);
    }
}

void prosesInputNilai(int index, char tipe)
{
    int nilaitemp;
    printf("Silahkan masukkan nilainya: ");
    scanf("%d", &nilaitemp);
    getchar();

    if(tipe == 'a')
    {
        mahasiswa[index].asg = nilaitemp;
    }
    else if(tipe == 'm')
    {
        mahasiswa[index].mid = nilaitemp;
    }
    else if(tipe == 'f')
    {
        mahasiswa[index].fin = nilaitemp;
    }
    outputNilai(index);
}

void outputNilai(int index)
{
    printf("| %-10s | %-30s | ", mahasiswa[index].nim, mahasiswa[index].nama);
    if(mahasiswa[index].asg == -1)
    {
        printf("%-3s | ", "N/A");
    }
    else
    {
        printf("%-3d | ", mahasiswa[index].asg);
    }
    if(mahasiswa[index].mid == -1)
    {
        printf("%-3s | ", "N/A");
    }
    else
    {
        printf("%-3d | ", mahasiswa[index].mid);
    }
    if(mahasiswa[index].fin == -1)
    {
        printf("%-3s | \n", "N/A");
    }
    else
    {
        printf("%-3d | \n", mahasiswa[index].fin);
    }
}