#include <stdio.h>
#include <string.h>
#include <malloc.h>

// khai bao cau truc do vat
typedef struct
{
    char TenDV[30];   // ten do vat co do dai toi da 30 ky
    float TL, GT, DG; // trong luong, gia tri, don gia
    int PA, SL;       // so luong cua do vat, so phuong an duoc chon
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
// ham lay file

Dovat *readData(float *W, int *n) // trong luong cai balo W, so luong do vat n
{
    FILE *f;
    f = fopen("balo2.txt", "r");                  // mo file de doc
    fscanf(f, "%f", W);                           // Xac dinh trong luong Ba lo
    Dovat *dsdv = (Dovat *)malloc(sizeof(Dovat)); // khoi tao mot danh sach do vat
    int i = 0;
    while (!feof(f)) // khi con tro con trong file
    {
        fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV); // luu lai trong luong, gia tri, ten do vat
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;                                             // don gia = gia tri / trong luong
        dsdv[i].PA = 0;
        i++;
        dsdv = (Dovat *)realloc(dsdv, sizeof(Dovat) * (i + 1)); // noi tiep 1 do vat moi vao danh sach do vat
    }
    *n = i;
    fclose(f);   // dong file
    return dsdv; // tra ve danh sach do vat
}
// in danh sach do vat
void in_dsdv(Dovat *dsdv, int n, float W)
{
    int i;
    float TongTL = 0.0, TongGT = 0.0; // khoi ta tong gia tri va tong trong luong = 0
    printf("\nPhuong an Cai Ba lo 1 dung thuat toan THAM AN nhu sau:\n");
    printf("\nTrong luong cua ba lo = %-9.2f\n", W);
    printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
    printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don Gia | So luong | Phuong an |\n");
    printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
    for (i = 0; i < n; i++)
    {
        printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%5d     |%6d     |\n",
               i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA);
        TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
        TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
    printf("Phuong an (theo thu tu DG giam dan): X(");
    for (i = 0; i < n - 1; i++)
    {
        printf("%d,", dsdv[i].PA);
    }
    printf("%d)", dsdv[n - 1].PA);
    printf("\nTong trong luong = %-9.2f\n", TongTL);
    printf("Tong gia tri = %-9.2f\n", TongGT);
}

// tinh cac dai luong tai nut goc
void tao_nut_goc(float *TGT, float *CT, float *GLNTT, float W, float *TLconlai, float dongia_LN) // trong luong balo, trong luong con lai cua balo, can tren, gia lon nhat tam thoi, tong gia tri, don gia vat lon nhat con lai
{
    *TGT = 0.0;                  // tong gia tri nut goc = 0
    *TLconlai = W;               // trong luong con lai laf trong luong cai balo
    *CT = *TLconlai * dongia_LN; // trong luong con lai * don gia vat lon nhat con lai
    *GLNTT = 0.0;                // gia lon nhat tam thoi  = 0
}

// ghi nhan phuong an tot nhat tam thoi
void update_PA_TNTT(float TGT, float *GLNTT, int x[], Dovat *dsdv, int n) // tong gia tri, gia lon nhat tam thoi,
{
    int i;
    if (*GLNTT < TGT) // quay lui neu gia lon nhat tam thoi < tong gia tri
    {
        *GLNTT = TGT; // cap nhat lai gia moi
        for (i = 0; i < n; i++)
            dsdv[i].PA = x[i]; //
    }
}

int min(int a, int b)
{
    return a < b ? a : b;
}

// nhanh can
void nhanhcan(float *TGT, float *CT, float *GLNTT, float *TLconlai, int x[], int i, Dovat *dsdv, int n)
{
    int j; // so do vat duoc chon
    int sodovatlonnhat_cothechon = min(*TLconlai / dsdv[i].TL, dsdv[i].SL);
    for (j = sodovatlonnhat_cothechon; j >= 0; j--)
    {
        *TGT = *TGT + j * dsdv[i].GT;
        *TLconlai = *TLconlai - j * dsdv[i].TL;
        *CT = *TGT + *TLconlai * dsdv[i + 1].DG;

        if (*CT > *GLNTT)
        {
            x[i] = j;
            if (i == n - 1 || *TLconlai == 0.0)
                update_PA_TNTT(*TGT, GLNTT, x, dsdv, n);
            else
                nhanhcan(TGT, CT, GLNTT, TLconlai, x, i + 1, dsdv, n);
        }
        x[i] = 0;
        *TGT = *TGT - j * dsdv[i].GT;
        *TLconlai = *TLconlai + j * dsdv[i].TL;
    }
}

int main()
{
    int n;
    float TGT, CT, GLNTT, W, TLconlai;
    int x[n];
    Dovat *dsdv = readData(&W, &n);
    bubbleSort(dsdv, n);
    tao_nut_goc(&TGT, &CT, &GLNTT, W, &TLconlai, dsdv[0].DG);
    nhanhcan(&TGT, &CT, &GLNTT, &TLconlai, x, 0, dsdv, n);
    in_dsdv(dsdv, n, W);
    free(dsdv);
    return 0;
}