#include <stdio.h>
#define max 50 // toi da 50 thanh pho

// cau truc mot canh
typedef struct
{
    float dodai;            // do dai 1 cnh
    int dau, cuoi, da_dung; // diem dau, diem cuoi, so duong da su dung
} Canh;

// ham swap hoan doi vi tri hai canh
void swap(Canh *x, Canh *y)
{
    Canh temp = *x;
    *x = *y;
    *y = temp;
}

// ham bubbleStrot sap xep canh co do dai tu thap den cao
void bubbleSort(Canh *dscanh, int n)
{
    int i, j;
    for (i = 0; i <= n - 2; i++)
        for (j = n - 1; j >= i + 1; j--)
            if (dscanh[j].dodai < dscanh[j - 1].dodai)
                swap(&dscanh[j], &dscanh[j - 1]);
}

// ham mo file de doc
void readData(char file[], Canh a[][max], int *n) // ten file, danh sach canh, so thanh pho
{
    FILE *f = fopen(file, "r"); // mo file de doc
    if (f == NULL)              // file rong
    {
        printf("Loi mo file!\n");
        return; // khong lam gi het
    }
    // nguoc lai
    int i, j;
    fscanf(f, "%d", n); // lay so thanh pho
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
        {
            fscanf(f, "%f", &a[i][j].dodai);
            a[i][j].dau = i;
            a[i][j].cuoi = j;
            a[i][j].da_dung = 0;
        }
    fclose(f);
}

// in ma tran
void in_matran(Canh a[][max], int n)
{
    int i, j;
    printf("Ma tran trong so cua do thi: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%c%C = %.2f", a[i][j].dau + 65, a[i][j].cuoi + 65, a[i][j].dodai);
        printf("\n");
    }
}

// in phuong an
void in_phuongan(Canh PA[], int n)
{
    int i;
    float sum = 0.0;
    printf("Phuong an tim duoc: \n");
    for (i = 0; i < n; i++)
    {
        sum += PA[i].dodai;
        printf("Canh %c%c = %.2f\n", PA[i].dau + 65, PA[i].cuoi + 65, PA[i].dodai);
    }
    printf("Tong do di cac canh cua chu trinh = %.2f", sum);
}

// tim cnh nho nhat
float canh_NN(Canh a[][max], int n)
{
    float Cmin = 3.40282e+38; // vo cung
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (i != j && !a[i][j].da_dung && a[i][j].dodai < Cmin) // i khac j  va chua dung va do dai nho hon cmin
                Cmin = a[i][j].dodai;                               // cmin = do dai
    return Cmin;
}

// tim can duoi
float Can_duoi(Canh a[][max], float TGT, int n, int i)
{
    return TGT + (n - i) * canh_NN(a, n);
}

// ghi nhan phuong an tot nhat tam thoi
void update_PA_TT(float TGT, float *GNNTT, Canh a[][max], int n, Canh x[], Canh PA[])
{
    int i;
    x[n - 1] = a[x[n - 2].cuoi][x[0].dau];
    TGT = TGT + x[n - 1].dodai;
    if (*GNNTT > TGT)
    {
        *GNNTT = TGT;
        for (i = 0; i < n; i++)
            PA[i] = x[i];
    }
}

// co chu trinh
int co_chutrinh(Canh x[], int k, int canh_ke)
{
    int i = 0, co_CT = 0;
    while (i < k && !co_CT)
        if (canh_ke == x[i].dau)
            co_CT = 1;
        else
            i++;
    return co_CT;
}
void nhanhcan(float *TGT, float *CD, float *GNNTT, Canh a[][max], int n, int i, int dau, Canh x[], Canh PA[])
{
    int j;
    for (j = 0; j < n; j++)
        if (dau != j && !a[dau][j].da_dung && !co_chutrinh(x, i, j))
        {
            *TGT = *TGT + a[dau][j].dodai;
            *CD = Can_duoi(a, *TGT, n, i + 1);
            if (*CD < *GNNTT)
            {
                x[i] = a[dau][j];
                a[dau][j].da_dung = 1;
                a[j][dau].da_dung = 1;
                if (i == n - 2)
                {
                    update_PA_TT(*TGT, GNNTT, a, n, x, PA);
                }
                else
                    nhanhcan(TGT, CD, GNNTT, a, n, i + 1, j, x, PA);
            }

            *TGT = *TGT - a[dau][j].dodai;
            a[dau][j].da_dung = 0;
            a[j][dau].da_dung = 0;
        }
}

int main()
{
    Canh a[max][max];
    int n;
    readData("TSP2.txt", a, &n);
    Canh PA[n], x[n];
    char tyxp, yn;

    fflush(stdin);
    in_matran(a, n);
    float TGT = 0.0, CD = 0.0, GNNTT = 3.40282e+38;
    printf("\nXut phat tu phan tu nao?(trong cac Thanh pho tu A den %c): ", n - 1 + 65);
    scanf("%c", &tyxp);
    if (tyxp >= 97)
        tyxp = tyxp - 32;
    nhanhcan(&TGT, &CD, &GNNTT, a, n, 0, tyxp - 65, x, PA);
    in_phuongan(PA, n);
    return 0;
}
