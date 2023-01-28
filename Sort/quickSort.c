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

// ham tim chot
int findPivot(recordtype a[], int i, int j) // mang a, vi tri dau, vi tri cuoi
{
    keytype firstkey; // tao firstkey kieu keytype
    int k;
    firstkey = a[i].key;                       // firstkey = gia tri dau
    k = i + 1;                                 // k =  vi tri ke tiep cua i
    while ((k <= j) && (a[k].key == firstkey)) // trong khi k chua toi vi tri cuoi va key.k con bang gia tri dau
        k++;                                   // tang k
    if (k > j)                                 // k > j khong tim thay chot
        return -1;                             // tra ve -1
    if (a[k].key > firstkey)                   // neu key.k > firstkey tim thay chot o vi tri k
        return k;                              // tra ve k
    return i;                                  // nguoc lai chot la khoa dau
}

// ham phan hoach
int patition(recordtype a[], int i, int j, keytype pivot) // mang a, vi tri dau, vi tri cuoi, chot
{
    int L, R;
    L = i;         // L gan bang vi tri dau
    R = j;         // R gan = vi tri cuoi
    while (L <= R) // khi L van con nhon hon hoac bang R
    {
        while (a[L].key < pivot)  // trong khi key.L con nho hon chot
            L++;                  // tang L
        while (a[R].key >= pivot) // trong khi key.R con lon hon chot
            R--;                  // giam R
        if (L < R)                // khi tren dung neu L nho hon R
            Swap(&a[L], &a[R]);   // doi cho L va R
    }
    return L; // tra ve vi tri phan hoach cua L
}
// ham sap nhanh
void quickSort(recordtype a[], int i, int j) // mang a, vi tri dau,  vi tri cuoi
{
    keytype pivot;                   // khai bao chot kieu keytype
    int pivotindex, k;               // khia bao vi tri chot, vi tri phan hoach
    pivotindex = findPivot(a, i, j); // vi tri phan hoach dau tien cua mang a vi tri dau cuoi
    if (pivotindex != -1)            // neu co chot
    {
        pivot = a[pivotindex].key;    // gia tri cua chot  = pivotindex.key
        k = patition(a, i, j, pivot); // vi tri phan hoach cua mang a, vi tri dau, cuoi, chot
        quickSort(a, i, k - 1);       // de quy a, i, k-1
        quickSort(a, k, j);           // de quy a, k,j
    }
}

int main()
{
    recordtype a[100];
    int n;
    readData(a, &n);
    printf("Sap xep day so bang thuat toan Sap Xiep Nhanh (QuickSort):\n");
    printf("--------------------------------------------------------------------");
    printf("\nMang ban dau:\n");
    printData(a, n);
    printf("--------------------------------------------------------------------");
    printf("\nMang sau khi sap xep: \n");
    quickSort(a, 0, n - 1);
    printData(a, n);
    return 0;
}