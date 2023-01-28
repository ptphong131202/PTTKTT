#include <stdio.h>

typedef int keytype;     // khai bao keytype kieu so nguyen
typedef float othertype; // khai bao othertype kieu so thuc

// khai bao cau truc recordtype
typedef struct
{
    keytype key;          // key kieu so nguyen
    othertype otherfield; // otherfield kieu so thuc
} recordtype;

// ham swap hoan doi hai so
void Swap(recordtype *x, recordtype *y) // hai so x va y
{
    recordtype temp = *x;
    *x = *y;
    *y = temp;
}

// ham doc lay du lieu tu file
void readData(recordtype a[], int *n)
{
    FILE *f = fopen("data.txt", "r"); // mo file data de doc
    int i = 0;                        // khoi tao i = 0
    if (f != NULL)                    // neu file khong rong
        while (!feof(f))              // trong khi con tro con chua den cuoi file
        {
            fscanf(f, "%d%f", &a[i].key, &a[i].otherfield); // lay key va otherfield
            i++;                                            // tang i
        }
    else // nguoc lai
        printf("Loi mo file!\n");
    *n = i;    // do dai mang  = i
    fclose(f); // dong file lai
}

// in mang ket qua
void printData(recordtype a[], int n)
{
    int i;
    for (i = 0; i < n; i++)                                        // i chay tu 0 den n - 1
        printf("%3d%5d%8.2f\n", i + 1, a[i].key, a[i].otherfield); // in ket qua theo dong
}

// ham sap xiep xen
void insertSort(recordtype a[], int n)
{
    int i, j;
    for (i = 1; i <= n - 1; i++) // i chay tu 1 den n-1
    {
        j = i;                                   // j = i
        while (j > 0 && a[j].key < a[j - 1].key) // trong khi j > 0 va j.key < j-1.key
        {
            Swap(&a[j], &a[j - 1]); // hoan doi hai vi tri j va j-1
            j--;                    // giam i
        }
    }
}

int main()
{
    recordtype a[100];
    int n;
    readData(a, &n);
    printf("--------------------------------------------------------------------");
    printf("\nSap xep day so bang thuat toan Sap Xiep Xen (InsertionSort):\n");
    printf("--------------------------------------------------------------------");
    printf("\nMang ban dau:\n");
    printData(a, n);
    printf("--------------------------------------------------------------------");
    printf("\nMang sau khi sap xep: \n");
    insertSort(a, n);
    printData(a, n);
    return 0;
}