#include <stdio.h>
#include <string.h>
#include <malloc.h>

// khai baos cau truc mot loai do vat
typedef struct
{
    char TenDV[30];   // ten do vat khong qua 30 ky tu
    float TL, GT, DG; // trong luong, gia tri, don gia
    int SL, PA;       // so luong cua mot do vat, so phuong an duoc chon
} Dovat;

// ham lay du lieu tu file
Dovat *readData(float *W, int *n) // trong luong balo, so loai do vat
{
    FILE *f = fopen("balo2.txt", "r");            // mo file de doc
    fscanf(f, "%f", W);                           // lay trong luong cua cai balo
    Dovat *dsdv = (Dovat *)malloc(sizeof(Dovat)); // cap phat dong danh sach do vat
    int i = 0;                                    // khoi tao i = 0
    while (!feof(f))                              // trong khi chua den cuoi file
    {
        fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV); // lay trong luong, gia tri, so luong, ten do vat
        dsdv[i].PA = 0;                                                                   // khoi tao phuong an  = 0
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;                                             // don gia  = gia tri / trong luong
        i++;                                                                              // tang i
        dsdv = (Dovat *)realloc(dsdv, sizeof(Dovat) * (i + 1));                           // cap phat dong noi tiep danh sach ddo vat
    }
    *n = i;      // so loai do vat = i
    fclose(f);   // dong file
    return dsdv; // tra ve danh sach ddo vat
}

// ham Swap hoan doi vi tri hai do vat
void Swap(Dovat *x, Dovat *y)
{
    Dovat temp = *x;
    *x = *y;
    *y = temp;
}

// ham sap xep noi bot sap xiep danh sach don gia tu cao den thap
void bublleSort(Dovat *dsdv, int n)
{
    int i, j;
    for (i = 0; i <= n - 2; i++)
        for (j = n - 1; j >= i + 1; j--)
            if (dsdv[j].DG > dsdv[j - 1].DG)  // neu don gia j > j-1 thi
                Swap(&dsdv[j], &dsdv[j - 1]); // hoan doi j  va j-1
}

// ham in danh sach do vat
void inDanhsach(Dovat *dsdv, int n, float W) // danh sach do vat, so loai do vat, trong luong ba lo
{
    float TongTL = 0.0, TongGT = 0.0;
    int i;
    printf("********** PHUONG AN CAI BA LO 2 SU DUNG THUAT TOAN THAM AN **********\n");
    printf("Trong luong cai ba lo: %8.2f\n", W);
    printf("|---|------------------------------|-------------|----------|----------|----------|-----------|------------|\n");
    printf("|%-3s|%-30s|%-12s|%-10s|%-10s|%-10s|%-11s|%-12s|\n", "STT", "           Ten do vat",
           " Trong luong ", " Gia tri", " So luong", " Don Gia", " Phuong an", " Thanh tien ");
    printf("|---|------------------------------|-------------|----------|----------|----------|-----------|------------|\n");
    for (i = 0; i < n; i++)
    {
        printf("|%3d|%-30s|%13.2f|%10.2f|%10.2f|%10d|%11d|%12.2f|\n", i + 1, dsdv[i].TenDV, dsdv[i].TL,
               dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA, dsdv[i].PA * dsdv[i].GT);
    }
    for (i = 0; i < n; i++)
    {
        TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
        TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|------------------------------|-------------|----------|----------|----------|-----------|------------|\n");
    printf("Phuong an theo thu tu giam dan: X{");
    for (i = 0; i < n - 1; i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d}\n", dsdv[n - 1].PA);
    printf("Ten do vat theo thu tu giam dan: ");
    for (i = 0; i < n - 1; i++)
        printf("%s ->", dsdv[i].TenDV);
    printf("%s\n", dsdv[n - 1].TenDV);
    printf("Tong trong luong = %.2f\n", TongTL);
    printf("Tong gia tri = %.2f\n", TongGT);
}

void thaman(Dovat *dsdv, int n, float W) // danh sach do vat, so loai do vat, trong luong cai balo
{
    int i;
    for (i = 0; i < n; i++) // i chay tu do vat dau den do vat cuoi
    {
        dsdv[i].PA = W / dsdv[i].TL;     // phuong an cua do vat thu i = trong luong con lai cua cai balo div trong luong luong do vat do
        if (dsdv[i].PA > dsdv[i].SL)     // neu phuong an do vat thu i lon hon so luong do do do
            dsdv[i].PA = dsdv[i].SL;     // phuong an = soluong
        W = W - dsdv[i].PA * dsdv[i].TL; // trong luong con lai cua cai ba lo = trong luong con lai - phuong an do vat thu i * trong luong do vat do
    }
}
int main()
{
    int n;
    float W;
    Dovat *dsdv = readData(&W, &n);
    bublleSort(dsdv, n);
    thaman(dsdv, n, W);
    inDanhsach(dsdv, n, W);
    free(dsdv);
    return 0;
}