#include <stdio.h>
#include <string.h>
#include <malloc.h>

// khai bao cau truc do vat
typedef struct
{
    char TenDV[30];   // ten do vat
    float TL, GT, DG; // trong luong, gia tri, don gia
    int PA;           // so phuong an duoc chon
} Dovat;

// ham swap hoan doi do vat
void Swap(Dovat *x, Dovat *y)
{
    Dovat temp = *x;
    *x = *y;
    *y = temp;
}

// ham sap xep noi bot sap xep don gia tu thap den cao
void bubbleSort(Dovat *dsdv, int n)
{
    int i, j;
    for (i = 0; i <= n - 2; i++)
        for (j = n - 1; j >= i + 1; j--)
            if (dsdv[j].DG > dsdv[j - 1].DG)
                Swap(&dsdv[j], &dsdv[j - 1]);
}

Dovat *readData(float *W, int *n) // trong luong cai balo W, so luong do vat n
{
    FILE *f;
    f = fopen("balo1.txt", "r");                  // mo file de doc
    fscanf(f, "%f", W);                           // Xac dinh trong luong Ba lo
    Dovat *dsdv = (Dovat *)malloc(sizeof(Dovat)); // khoi tao mot danh sach do vat
    int i = 0;
    while (!feof(f)) // khi con tro con trong file
    {
        fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV); // luu lai trong luong, gia tri, ten do vat
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;                              // don gia = gia tri / trong luong
        dsdv[i].PA = 0;
        i++;
        dsdv = (Dovat *)realloc(dsdv, sizeof(Dovat) * (i + 1)); // noi tiep 1 do vat moi vao danh sach do vat
    }
    *n = i;
    fclose(f);   // dong file
    return dsdv; // tra ve danh sach do vat
}
void in_dsdv(Dovat *dsdv, int n, float W)
{
    int i;
    float TongTL = 0.0, TongGT = 0.0; // khoi ta tong gia tri va tong trong luong = 0
    printf("\nPhuong an Cai Ba lo 1 dung thuat toan THAM AN nhu sau:\n");
    printf("\nTrong luong cua ba lo = %-9.2f\n", W);
    printf("|---|--------------------|---------|---------|---------|-----------|\n");
    printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don Gia | Phuong an |\n");
    printf("|---|--------------------|---------|---------|---------|-----------|\n");
    for (i = 0; i < n; i++)
    {
        printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d     |\n",
               i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
        TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
        TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|--------------------|---------|---------|---------|-----------|\n");
    printf("Phuong an (theo thu tu DG giam dan): X(");
    for (i = 0; i < n - 1; i++)
    {
        printf("%d,", dsdv[i].PA);
    }
    printf("%d)", dsdv[n - 1].PA);
    printf("\nTong trong luong = %-9.2f\n", TongTL);
    printf("Tong gia tri = %-9.2f\n", TongGT);
}
void thaman(Dovat *dsdv, int n, float W)
{
    for (int i = 0; i < n; i++)
    {
        dsdv[i].PA = W / dsdv[i].TL;     // phuongan[i] = div trong luong balo con lai voi trong luong dovat[i]
        W = W - dsdv[i].PA * dsdv[i].TL; // w con lai  = w con lai - phuong an[i]*trongluong[i]
    }
}
int main()
{
    int n;
    float w;
    Dovat *dsdv = readData(&w, &n);
    bubbleSort(dsdv, n);
    thaman(dsdv, n, w);
    in_dsdv(dsdv, n, w);
    free(dsdv);
    return 0;
}