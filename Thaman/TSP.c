#include <stdio.h>
#define max 30 // Toi thieu la 30 thanh pho

// Cau truc cua mot canh
typedef struct
{
    float dodai;   // Do dai cua canh do
    int dau, cuoi; // Diem dau va cuoi cua canh
} Canh;

void readData(char file_name[], Canh a[], int *n) // Doc file vao mang canh a voi n phan tu
{
    int i, j, t;
    float temp;
    FILE *f = fopen(file_name, "r"); // Mo file de doc
    if (f == NULL)                   // neu file f rong
    {
        printf("Loi mo file!\n"); // thong bao loi
        return;                   // khong thuc hien gi nuaw
    }
    // nguoc lai neu file f khong rong
    fscanf(f, "%d", n); // Luu gia tri dau tien cua trong file la do dai cua mang
    int k = 0;
    for (i = 0; i < *n; i++)                // i di tu dau den cuoi mang (0 -> n-1)
        for (j = i; j < *n; j++)            // j  di tu i den cuoi mang (i -> n-1)
            if (i == j)                     // neu i = j
                for (t = 0; t <= j; t++)    // bo cac phan tu nam duoi duong cheo i = j
                    fscanf(f, "%f", &temp); // luu cac phan tu do vao bien tam
            else                            // Luu cac phan tu phia tren duong cheo
            {
                fscanf(f, "%f", &a[k].dodai); // luu lai do dai
                a[k].dau = i;                 // diem dau = i
                a[k].cuoi = j;                // diem cuoi = j
                k++;
            }
    fclose(f); // dong file
}

// in danh sach mang cac canh
void in_ds_canh(Canh a[], int m, int Phuong_An) // in mang canh a voi m phan tu va 1 phuong an
{
    int i;
    float tong = 0.0;       // khoi tao bien tong  = 0
    for (i = 0; i < m; i++) // i di tu dau den cuoi danh sach (0 -> m-1)
    {
        printf("%3d %c%c = %8.2f\n", i + 1, a[i].dau + 65, a[i].cuoi + 65, a[i].dodai); // in danh sach voi stt, diem dau, diem cuoi, do dai canh thu i.
        if (Phuong_An)                                                                  // neu co phuong an
            tong += a[i].dodai;                                                         // tong = tong  + do dai canh thu i
    }
    if (Phuong_An)                                      // neu co phuong an
        printf("Tong do dai duong di = %8.2f\n", tong); // in ra tong cac canh
}

// Ham Swap hoan doi do dai hai canh
void Swap(Canh *x, Canh *y)
{
    Canh temp = *x;
    *x = *y;
    *y = temp;
}

// ham BubbleSort(sap xep noi bot) sap xep lai cac phan tu tu thap den cao
void BubbleSort(Canh a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
            if (a[j].dodai < a[j - 1].dodai)
                Swap(&a[j], &a[j - 1]);
}

int dinh_cap_3(Canh Phuong_An[], int k, Canh moi) // Danh sach canh phuong an, so luong phan tu k, canh moi
{
    int i, dem;
    i = 0;
    dem = 1;
    while (i < k && dem < 3) // khi chua cuoi danh sach va chua tao dinh cap 3 thi
    {
        if (moi.dau == Phuong_An[i].dau || moi.dau == Phuong_An[i].cuoi) // diem dau canh moi = voi diem dau or diem cuoi phuong an thu i
            dem++;                                                       // tang dem
        i++;
    }
    if (dem == 3) // neu dem = 3 => tao ra dinh cap 3
        return 1; // tra ve 1 => true
    i = 0;
    dem = 1;
    while (i < k && dem < 3)
    {
        if (moi.cuoi == Phuong_An[i].dau || moi.cuoi == Phuong_An[i].cuoi) // diem cuoi canh moi = voi diem dau or diem cuoi phuong an thu i
            dem++;                                                         // tang dem
        i++;
    }
    return dem == 3; // neu dem = 3 => tao ra dinh cap 3 va tra ve 1
}

// Ham tao 1 rung
void init_forest(int parent[], int n)
{
    for (int i = 0; i < n; i++) // i di tu dau den cuoi danh sach
        parent[i] = i;          // khoi tao cac nut deu la goc
}

// Ham tim goc
int find_root(int parent[], int u)
{
    while (u != parent[u]) // khi u con cha
        u = parent[u];     // u = cha
    return u;              // tra ve nut u
}

// Ham kiem tra chu trinh
int chu_trinh(int r_dau, int r_cuoi)
{
    return r_dau == r_cuoi; // dau cua canh nay  = cuoi cua canh kia tra ve 1
}

// Ham hop goc cua hai rung
void update_forest(int parent[], int r1, int r2)
{
    parent[r2] = r1; // cho goc cua rung r1 la goc cua rung r2
}

// Ham tham an tim duong di
void greedy(Canh ds_canh[], int n, Canh Phuong_An[]) // danh sach tat ca cac canh voi n phan tu va danh sach cac phuong an
{
    int i, j, parent[n];
    init_forest(parent, n);
    int r_dau, r_cuoi;
    // chon cac canh bho nhat tao thanh 1 chu trinh khong tao thanh dinh cap 3
    j = 0;
    for (i = 0; i < n * (n - 1) / 2 && j < n - 1; i++)
    {
        r_dau = find_root(parent, ds_canh[i].dau);                              // tim diem dau
        r_cuoi = find_root(parent, ds_canh[i].cuoi);                            // tim diem cuoi
        if (!dinh_cap_3(Phuong_An, j, ds_canh[i]) && !chu_trinh(r_dau, r_cuoi)) // khong tao thanh dinh cap 3 va khong tao chu trinh thieu
        {
            Phuong_An[j] = ds_canh[i]; // dua vao danh sach phuong an
            j++;
            update_forest(parent, r_dau, r_cuoi); // cap nhat lai rung hop nhat 2 cay
        }
    }
    // den phuong an cuoi de tao thanh 1 chu trinh kin
    for (; i < n * (n - 1) / 2; i++)
    {
        r_dau = find_root(parent, ds_canh[i].dau);                                 // tim diem dau
        r_cuoi = find_root(parent, ds_canh[i].cuoi);                               // tim diem cuoi
        if (!dinh_cap_3(Phuong_An, n - 1, ds_canh[i]) && chu_trinh(r_dau, r_cuoi)) // khong tao thanh dinh cap 3 va phai tao chu trinh
        {
            Phuong_An[n - 1] = ds_canh[i]; // dua vao danh sach phuong an
            break;                         // dung lai
        }
    }
}
int main()
{
    int n;
    Canh a[max];
    readData("TSP2.txt", a, &n);
    printf("Danh sach mang:\n");
    in_ds_canh(a, n * (n - 1) / 2, 0);
    BubbleSort(a, n * (n - 1) / 2);
    printf("Danh sach mang cac canh sau khi Sap Xep:\n");
    in_ds_canh(a, n * (n - 1) / 2, 0);
    Canh Phuong_An[n];
    greedy(a, n, Phuong_An);
    printf("Phuong an duoc chon: \n");
    in_ds_canh(Phuong_An, n, 1);
    return 0;
}