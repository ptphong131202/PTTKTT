#include <stdio.h>
#define max 50

/// ham doc file du lieu
void readData(int a[][max], int *n)
{
    FILE *f = fopen("tamgiacso.txt", "r"); /// mo file de doc
    int i = 0, j;                          // khoi tao bien tao
    while (!feof(f))                       // trong khi chua den cuoi file
    {
        for (j = 0; j <= i; j++)       // j chay tu 0 den do dai hang i
            fscanf(f, "%d", &a[i][j]); // chep vao mang
        i++;                           // tang i
    }
    *n = i;    // so luong phan tu  = i
    fclose(f); // dong file
}

// int danh sach mang
void inDanhsach(int a[][max], int n)
{
    printf("Danh sach mang ban dau: \n");
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= i; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

// tim chi so max
int cs_max(int n, int F[][max], int i, int j)
{
    if (j == 0)                                                             /// j  = 0 hang dau (hang 0)
        return F[i - 1][0] > F[i - 1][1] ? 0 : 1;                           // hang thu 2 (hang 1) chon so lon nhat
    if (i == j)                                                             // i = j nam o duong cheo
        return i - 1;                                                       /// i -1
    if (j == i - 1)                                                         // nam o cot dau
        return F[i - 1][i - 1] > F[i - 1][i - 2] ? i - 1 : i - 2;           // lay max cot 0 va cot 1
    if (F[i - 1][j - 1] > F[i - 1][j] && F[i - 1][j - 1] > F[i - 1][j + 1]) // j-1 > j va j-1 > j+1
        return j - 1;                                                       // j-1
    if (F[i - 1][j] > F[i - 1][j - 1] && F[i - 1][j] > F[i - 1][j + 1])     // j > j-1 va j > j +1
        return j;                                                           // j
    if (F[i - 1][j + 1] > F[i - 1][j] && F[i - 1][j + 1] > F[i - 1][j - 1]) // j+1 > j va j + 1 > j -1
        return j + 1;                                                       // j + 1
}

// tao bang
void taobang(int a[][max], int n, int F[][max])
{
    int i, j;
    F[0][0] = a[0][0]; // hang 0
    // hang 1
    F[1][0] = a[1][0] + F[0][0];
    F[1][1] = a[1][1] + F[0][0];
    // hang thu 2 ve sau
    for (i = 2; i < n; i++)
        for (j = 0; j <= i; j++)
        {
            int k = cs_max(n, F, i, j);      // lay chi so max
            F[i][j] = a[i][j] + F[i - 1][k]; // aij + fi-1k
        }
}
// in bang
void inbang(int f[][max], int n)
{
    printf("Bang F: \n");
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= i; j++)
            printf("%d ", f[i][j]);
        printf("\n");
    }
    printf("\n");
}

// chi so max dong cuoi
int cs_max_dongcuoi(int f[], int j) // mang hang cuoi
{
    int somax = f[0]; // gan chi so max  = chi so dau
    int maxindex = 0; // vi ban dau = 0
    int k;
    for (k = 0; k < j; k++) // chay hang j
        if (f[k] > somax)   // neu gia tri thu k > so max
        {
            somax = f[k]; // so max = gia tri o k
            maxindex = k; // vi tri max = k
        }
    return maxindex; // tra ve vi tri
}

// tra bang
void traBang(int a[][max], int n, int f[][max], int pa[]) // bang a, so dong, bng f, mang phuong an
{
    int i, j;
    j = cs_max_dongcuoi(f[n - 1], n - 1); // xac inh chi so max dong cuoi
    pa[n - 1] = a[n - 1][j];              // phuong dong cuoi
    for (i = n - 1; i >= 1; i--)
    {
        j = cs_max(n, f, i, j);
        pa[i - 1] = a[i - 1][j];
    }
}

// int phuong an
void inphuongan(int pa[], int n)
{
    int i;
    printf("Phuong phap Quy hoach dong: \n");
    printf("Phuong an la duong di cu cac so: %d ", pa[0]);
    int TongDoDai = pa[0];
    for (i = 1; i < n - 1; i++)
    {
        printf("=> %d ", pa[i]);
        TongDoDai += pa[i];
    }
    printf("\nTong do dai duong di = %d", TongDoDai);
}
int main()
{
    int a[max][max];
    int f[max][max];
    int n;
    int pa[n];
    readData(a, &n);
    inDanhsach(a, n);
    taobang(a, n, f);
    inbang(f, n);
    traBang(a, n, f, pa);
    inphuongan(pa, n);
    return 0;
}