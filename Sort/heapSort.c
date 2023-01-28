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

// ham pushdown
void pushdown(recordtype a[], int first, int last)
{                               // mang a,  vi tri dau, vi tri cuoi
    int r = first;              // gan r = gia tri dau
    while (r <= (last - 1) / 2) // khi vi tri dau <= (las-1)/2
    {
        if (last == 2 * r + 1) // neu last == 2r+1
        {
            if (a[r].key > a[last].key) // neu key.r > key.last
                Swap(&a[r], &a[last]);  // hoan doi last va r
            r = last;                   // ran r = last
        }
        else if (a[r].key > a[2 * r + 1].key && a[2 * r + 1].key <= a[2 * r + 2].key) // neu key.r > key.2r+1 va key.2r+1 <= key.2r+2
        {
            Swap(&a[r], &a[2 * r + 1]); // hoan doi r va 2r+1
            r = 2 * r + 1;              // gan r = 2r+1
        }
        else if (a[r].key > a[2 * r + 2].key && a[2 * r + 2].key < a[2 * r + 1].key) // neu key.r > key.2r+2 va key.2r+2 < key.2r+1
        {
            Swap(&a[r], &a[2 * r + 2]); // hoan doi r va 2r+2
            r = 2 * r + 2;              // gan r = 2r+2
        }
        else
            r = last; // nguoc lai r = last
    }
}

// ham sap vun dong
void heapSort(recordtype a[], int n)
{
    int i;
    for (i = (n - 2) / 2; i >= 0; i--) // head dau pushdown n-2/2 den 0
        pushdown(a, i, n - 1);
    for (i = n - 1; i >= 2; i--) // i chay tu n-1 den 2
    {
        Swap(&a[0], &a[i]);    // hoan doi vi tri dau va cuoi
        pushdown(a, 0, i - 1); // push tu 0 i-1
    }
    Swap(&a[0], &a[1]); // hoan doi hai vi tri con lai
}

int main()
{
    recordtype a[100];
    int n;
    readData(a, &n);
    printf("Sap xep day so bang thuat toan Sap Xiep Noi Vun Dong (HeapSort):\n");
    printf("--------------------------------------------------------------------");
    printf("\nMang ban dau:\n");
    printData(a, n);
    printf("--------------------------------------------------------------------");
    printf("\nMang sau khi sap xep: \n");
    heapSort(a, n);
    printData(a, n);
    return 0;
}