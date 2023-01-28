#include <stdio.h>
#include <string.h>
#include <malloc.h>

// khai bao cau truc mot loai do vat
typedef struct
{
    char TenDV[30]; // ten do vat
    int TL, SL, PA; // trong luong, so luong, so phuong n
    float GT;       // gia tri
} Dovat;

// ham doc file du lieu
Dovat *readData(int *W, int *n) // trong luong cai balo W, so luong do vat n
{
    FILE *f = fopen("balo2.txt", "r");            // mo file balo2 de doc
    fscanf(f, "%d", W);                           // lay trong luong balo
    Dovat *dsdv = (Dovat *)malloc(sizeof(Dovat)); // cap phat dong not danh sach do vat
    int i = 0;                                    // tao bien chay
    while (!feof(f))                              // khi chua den cuoi file
    {
        fscanf(f, "%d%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV); // trong luong, gia tri, so luong, ten do vat
        dsdv[i].PA = 0;                                                                   // ban dau phuong an duoc chon = 0
        i++;
        dsdv = (Dovat *)realloc(dsdv, sizeof(Dovat) * (i + 1)); // cap phat them bo nho noi duoi vao danh sach do vat
    }
    *n = i;      // so luong do vat = i
    fclose(f);   // dong file
    return dsdv; // tra ve danh sach do vat
}

// ham in danh sach
void inDanhsach(Dovat *dsdv, int n, int W) // danh sach do vat, so luong do vat, trong luong cai balo
{
    printf("\n\nTrong luong cai balo = %d\n", W);
    float TongGT = 0.0;
    int i, TongTL = 0;
    printf("|---|------------------------------|-------------|---------|----------|-----------|\n");
    printf("|%3s|%-30s|%12s|%-9s|%-10s|%-11s|\n", "STT", "          Ten do vat", " Trong luong ", " Gia tri", " So luong",
           " Phuong an");
    printf("|---|------------------------------|-------------|---------|----------|-----------|\n");

    for (i = 0; i < n; i++)
    {
        printf("|%3d|%-30s|%7d      |  %-7.2f|    %-6d|     %-6d|\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].PA);
        TongTL = TongGT + dsdv[i].PA * dsdv[i].TL;
        TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|------------------------------|-------------|---------|----------|-----------|\n");

    printf("Phuong an duoc chon: X{");
    for (i = 0; i < n - 1; i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d}.\n", dsdv[n - 1].PA);
    printf("Do vat duoc chon: X{");
    for (i = 0; i < n - 1; i++)
        printf("%s ->", dsdv[i].TenDV);
    printf("%s.\n", dsdv[n - 1].TenDV);
    printf("Trong trong luong do vat da cho vao = %d\n", TongTL);
    printf("Tong gia tri cac do vat da cho vao = %.2f\n", TongGT);
}
int min(int a, int b)
{
    return a < b ? a : b;
}
// ham tao bang
void taobang(Dovat *dsdv, int n, int W, float F[][W + 1], int X[][W + 1])
{
    int xk, yk, k; //
    int Xmax, v;
    float Fmax;
    // hang dau tien cua bang
    for (v = 0; v <= W; v++)
    {
        X[0][v] = v / dsdv[0].TL;
        F[0][v] = X[0][v] * dsdv[v].GT;
    }

    // cac dong con lai
    for (k = 1; k < n; k++)
        for (v = 0; v <= W; v++)
        {
            Fmax = F[k - 1][v];
            Xmax = 0;
            yk = v / dsdv[k].TL;
            // balo2 yk = min(dsdv[k].SL, V/dsdv[k].TL)
            // balo3 yk = min(1, V/dsdv[k].TL)
            for (xk = 1; xk <= yk; xk++)
                if (F[k - 1][v - xk * dsdv[k].TL] + xk * dsdv[k].GT > Fmax)
                {
                    Fmax = F[k - 1][v - xk * dsdv[k].TL] + xk * dsdv[k].GT;
                    Xmax = xk;
                }
            F[k][v] = Fmax;
            X[k][v] = Xmax;
        }
}

// ham in bang
void inbang(int n, int w, float F[][w + 1], int X[][w + 1])
{
    int v, k;
    printf("\nBang F va X: \n");
    for (k = 0; k < n; k++)
    {
        for (v = 0; v <= w; v++)
            printf("%c%4.1f|%2d", 186, F[k][v], X[k][v]);
        printf("\n");
    }
}
void trabang(Dovat *dsdv, int n, int W, int x[][W + 1])
{
    int v, k; // v trong luong con lai cua cai balo, k do vat thu k cua n
    v = W;
    for (k = n - 1; k >= 0; k--)
    {
        dsdv[k].PA = x[k][v]; //
        v = v - x[k][v] * dsdv[k].TL;
    }
}
int main()
{
    printf("********** BAI TOAN CAI BALO SU DUNG THUAT TOAN QUY HOACH DONG *********\n");

    int n, w;
    Dovat *dsdv = readData(&w, &n);
    float F[n][w + 1];
    int x[n][w + 1];
    taobang(dsdv, n, w, F, x);
    inbang(n, w, F, x);
    trabang(dsdv, n, w, x);
    inDanhsach(dsdv, n, w);
    free(dsdv);
    return 0;
}