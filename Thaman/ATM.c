#include <stdio.h>
#include <string.h>
#include <malloc.h>

// khai bao caau truc mot loai tien
typedef struct
{
    char TenTien[30];      // ten loai tien
    int menhgia, phuongan; // menh gia va so phuong an duoc chon
} Tien;
// ham lay du lieu
Tien *readData(int *n)
{
    FILE *f = fopen("ATM.TXT", "r");           // mo file atm ra de doc
    Tien *dslt = (Tien *)malloc(sizeof(Tien)); // cap phat dong danh sach loai tien
    int i = 0;                                 // gan i = 0
    while (!feof(f))                           // trong khi chua den cuoi danh sach
    {
        fscanf(f, "%d", &dslt[i].menhgia);                    // lay menh gia bo vao danh sach tien
        fgets(dslt[i].TenTien, 30, f);                        // lay ten tien voi do dai toi da la 25 ky tu trong file f
        dslt[i].TenTien[strlen(dslt[i].TenTien) - 1] = '\0';  // khi toi vi tri cuoi cua dong thi cho no = vi tri ket thuc
        dslt[i].phuongan = 0;                                 // khoi tao danh sach phuong an deu = 0
        i++;                                                  // tang i
        dslt = (Tien *)realloc(dslt, sizeof(Tien) * (i + 1)); // noi them hang cho danh sach
    }
    *n = i;
    fclose(f);
    return dslt;
}
// ham swap hoan doi hai gia tri loai tien
void Swap(Tien *x, Tien *y)
{
    Tien temp = *x;
    *x = *y;
    *y = temp;
}
// ham sap xep noi bot sap xiep tien theo menh gia tu cao den thap
void bubbleSort(Tien *dslt, int n)
{
    int i, j;
    for (i = 0; i <= n - 2; i++)
        for (j = n - 1; j >= i + 1; j--)
            if (dslt[j].menhgia > dslt[j - 1].menhgia)
                Swap(&dslt[j], &dslt[j - 1]);
}

// ham  in ket qua
void inDS(Tien *dslt, int n, int sotienrut) // danh sach laoi tien, so luong loai tien, so tirn can rut
{
    int i;
    int tongtientra = 0; // so tien tra ra
    printf("|---|------------------------------|---------|---------|------------|\n");
    printf("|%3s|%-30s|%-9s|%-9s|%-10s|\n", "STT", "        Loai tien       ", " menhgia ", "  so to ", " Thanh tien ");
    printf("|---|------------------------------|---------|---------|------------|\n");
    for (i = 0; i < n; i++)
    {
        printf("|%3d|%-30s|%-9d|%-9d|%-12d|\n", i + 1, dslt[i].TenTien, dslt[i].menhgia, dslt[i].phuongan, dslt[i].menhgia * dslt[i].phuongan);
        tongtientra = tongtientra + dslt[i].menhgia * dslt[i].phuongan;
    }
    printf("|---|------------------------------|---------|---------|------------|\n");
    printf("So tien can rut = %9d\n", sotienrut);
    printf("So tien da tra = %9d\n", tongtientra);
}
// ham tham an may ATM
void thaman(Tien *dslt, int n, int tiencanrut) // danh sach tien, so luong loai tien, so tien can rut
{
    int i = 0;                      // i = 0
    while (i < n && tiencanrut > 0) // khi i chua den cuoi loai danh sach i=n va so tien > 0
    {
        dslt[i].phuongan = tiencanrut / dslt[i].menhgia;              // phuong an = tien rut div menhgia[i]
        tiencanrut = tiencanrut - dslt[i].phuongan * dslt[i].menhgia; // tien rut = phuongan[i]*menhgia[i]
        i++;                                                          // tang i
    }
}
int main()
{
    int n;
    Tien *dslt;
    dslt = readData(&n);
    bubbleSort(dslt, n);
    int k;
    printf("Nhap vao so tien ban muon rut (so tien > 50000 ): ");
    scanf("%d", &k);
    thaman(dslt, n, k);
    inDS(dslt, n, k);
    free(dslt);
    return 0;
}