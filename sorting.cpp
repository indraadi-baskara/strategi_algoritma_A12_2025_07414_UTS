#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
void gotoxy(int x, int y)
{
  COORD coord = {(SHORT)x, (SHORT)y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clearScreen() { system("cls"); }
#else
#include <cstdio>
void gotoxy(int x, int y) { printf("\033[%d;%dH", y + 1, x + 1); }
void clearScreen() { system("clear"); }
#endif

using namespace std;

struct Siswa {
  int    nis;
  string nama;
  int    nilai1;
  int    nilai2;
  int    rata;
  string keterangan;
};

vector<Siswa> arr;
int n;

void tukar(int a, int b)
{
  Siswa temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

// ── Exchange Sort ──────────────────────────────────────────────────────────
void exchangeSort(bool asc)
{
  for (int i = 0; i < n - 1; i++)
    for (int j = i + 1; j < n; j++)
      if (asc ? arr[i].rata > arr[j].rata : arr[i].rata < arr[j].rata)
        tukar(i, j);
}

// ── Bubble Sort ────────────────────────────────────────────────────────────
void bubbleSort(bool asc)
{
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
      if (asc ? arr[j].rata > arr[j + 1].rata : arr[j].rata < arr[j + 1].rata)
        tukar(j, j + 1);
}

// ── Quick Sort ─────────────────────────────────────────────────────────────
int partition(int low, int high, bool asc)
{
  int pivot = arr[high].rata;
  int i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (asc ? arr[j].rata < pivot : arr[j].rata > pivot)
    {
      i++;
      tukar(i, j);
    }
  }
  tukar(i + 1, high);
  return i + 1;
}

void quickSort(int low, int high, bool asc)
{
  if (low < high)
  {
    int pi = partition(low, high, asc);
    quickSort(low, pi - 1, asc);
    quickSort(pi + 1, high, asc);
  }
}

// ── Selection Sort ─────────────────────────────────────────────────────────
void selectionSort(bool asc)
{
  for (int i = 0; i < n - 1; i++)
  {
    int idx = i;
    for (int j = i + 1; j < n; j++)
      if (asc ? arr[j].rata < arr[idx].rata : arr[j].rata > arr[idx].rata)
        idx = j;
    tukar(i, idx);
  }
}

// ── Insertion Sort ─────────────────────────────────────────────────────────
void insertionSort(bool asc)
{
  for (int i = 1; i < n; i++)
  {
    Siswa key = arr[i];
    int j = i - 1;
    while (j >= 0 && (asc ? arr[j].rata > key.rata : arr[j].rata < key.rata))
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

// ── Merge Sort ─────────────────────────────────────────────────────────────
void merge(int l, int m, int r, bool asc)
{
  vector<Siswa> temp(n);
  int i = l, j = m + 1, k = l;
  while (i <= m && j <= r)
  {
    if (asc ? arr[i].rata <= arr[j].rata : arr[i].rata >= arr[j].rata)
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }
  while (i <= m) temp[k++] = arr[i++];
  while (j <= r) temp[k++] = arr[j++];
  for (int x = l; x <= r; x++) arr[x] = temp[x];
}

void mergeSort(int l, int r, bool asc)
{
  if (l < r)
  {
    int m = (l + r) / 2;
    mergeSort(l, m, asc);
    mergeSort(m + 1, r, asc);
    merge(l, m, r, asc);
  }
}

// ── Heap Sort ──────────────────────────────────────────────────────────────
void heapify(int size, int i, bool asc)
{
  int target = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < size && (asc ? arr[left].rata > arr[target].rata : arr[left].rata < arr[target].rata))
    target = left;
  if (right < size && (asc ? arr[right].rata > arr[target].rata : arr[right].rata < arr[target].rata))
    target = right;
  if (target != i)
  {
    tukar(i, target);
    heapify(size, target, asc);
  }
}

void heapSort(bool asc)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(n, i, asc);
  for (int i = n - 1; i > 0; i--)
  {
    tukar(0, i);
    heapify(i, 0, asc);
  }
}

// ── Number input menu ──────────────────────────────────────────────────────
int inputMenu(int x, int y, const string options[], int count)
{
  string sep(50, '=');
  gotoxy(x, y);
  cout << sep;
  for (int i = 0; i < count; i++)
  {
    gotoxy(x, y + 1 + i);
    cout << (i + 1) << ". " << options[i];
  }
  gotoxy(x, y + 1 + count);
  cout << sep;
  gotoxy(x, y + 2 + count);
  cout << "Masukkan pilihan [1";
  for (int i = 2; i <= count; i++) cout << "/" << i;
  cout << "]: ";
  int choice;
  cin >> choice;
  return choice;
}

// ── Helpers ────────────────────────────────────────────────────────────────
void drawHeader()
{
  gotoxy(0, 0);
  cout << "=== PROGRAM SORTING ===\n";
  cout << "Dibuat oleh: Indra Adi Baskara\n";
  cout << "NIM: A12.2025.07414\n";
  cout << "Strategi Algoritma\n";
}

void printTable()
{
  string sep(62, '=');
  cout << sep << "\n";
  cout << left
       << setw(5)  << "No"
       << setw(8)  << "NIS"
       << setw(15) << "Nama"
       << setw(9)  << "Nilai1"
       << setw(9)  << "Nilai2"
       << setw(12) << "Rata-rata"
       << "Keterangan\n";
  cout << sep << "\n";
  for (int i = 0; i < n; i++)
  {
    cout << left
         << setw(5)  << (i + 1)
         << setw(8)  << arr[i].nis
         << setw(15) << arr[i].nama
         << setw(9)  << arr[i].nilai1
         << setw(9)  << arr[i].nilai2
         << setw(12) << arr[i].rata
         << arr[i].keterangan << "\n";
  }
  cout << sep << "\n";
}

// ── Preset datasets ────────────────────────────────────────────────────────
void loadPreset(int choice)
{
  arr.clear();
  if (choice == 1)
    arr = {
      {1,  "Amir",  90, 80, 85, "Lulus"},
      {2,  "Budi",  55, 45, 50, "Tidak Lulus"},
      {3,  "Citra", 70, 90, 80, "Lulus"},
      {4,  "Dina",  40, 60, 50, "Tidak Lulus"},
      {5,  "Eko",   85, 75, 80, "Lulus"},
    };
  else if (choice == 2)
    arr = {
      {6,  "Fajar", 60, 70, 65, "Lulus"},
      {7,  "Gita",  90, 95, 92, "Lulus"},
      {8,  "Hadi",  30, 50, 40, "Tidak Lulus"},
      {9,  "Indah", 75, 85, 80, "Lulus"},
      {10, "Joko",  50, 40, 45, "Tidak Lulus"},
    };
  else if (choice == 3)
    arr = {
      {11, "Kiki",  95, 85, 90, "Lulus"},
      {12, "Lili",  45, 55, 50, "Tidak Lulus"},
      {13, "Miko",  70, 80, 75, "Lulus"},
      {14, "Nina",  60, 65, 62, "Lulus"},
      {15, "Omar",  25, 35, 30, "Tidak Lulus"},
    };
  else if (choice == 4)
    arr = {
      {16, "Putri", 80, 70, 75, "Lulus"},
      {17, "Qori",  55, 65, 60, "Lulus"},
      {18, "Raka",  90, 100,95, "Lulus"},
      {19, "Sari",  35, 45, 40, "Tidak Lulus"},
      {20, "Tono",  65, 75, 70, "Lulus"},
    };
  n = arr.size();
}

// ── Main ───────────────────────────────────────────────────────────────────
int main()
{
  while (true)
  {
    arr.clear();
    n = 0;

    // ── Pilih sumber data
    clearScreen();
    drawHeader();

    string sourceOpts[] = {"Gunakan data preset", "Input data sendiri"};
    int sourceChoice = inputMenu(0, 5, sourceOpts, 2);

    if (sourceChoice == 1)
    {
      clearScreen();
      drawHeader();

      string presetOpts[] = {"Dataset 1 - Kelas A", "Dataset 2 - Kelas B",
                             "Dataset 3 - Kelas C", "Dataset 4 - Kelas D"};
      int presetChoice = inputMenu(0, 5, presetOpts, 4);
      loadPreset(presetChoice);
    }
    else
    {
      // ── Input siswa manual
      char lagi = 'y';
      while (lagi == 'y' || lagi == 'Y')
      {
        clearScreen();
        drawHeader();

        gotoxy(0, 5);  cout << "Input Data Siswa";
        gotoxy(0, 6);  cout << string(50, '=');
        gotoxy(0, 7);  cout << "1. NIS      : ";
        gotoxy(0, 8);  cout << "2. Nama     : ";
        gotoxy(0, 9);  cout << "3. Nilai1   : ";
        gotoxy(0, 10); cout << "4. Nilai2   : ";
        gotoxy(0, 11); cout << "Rata-rata   : ";
        gotoxy(0, 12); cout << "Keterangan  : ";
        gotoxy(0, 13); cout << string(50, '=');
        gotoxy(0, 14); cout << "Lagi [y/t]  : ";

        Siswa s;
        gotoxy(14, 7);  cin >> s.nis;
        cin.ignore();
        gotoxy(14, 8);  getline(cin, s.nama);
        gotoxy(14, 9);  cin >> s.nilai1;
        gotoxy(14, 10); cin >> s.nilai2;

        s.rata = (s.nilai1 + s.nilai2) / 2;
        s.keterangan = s.rata >= 60 ? "Lulus" : "Tidak Lulus";

        gotoxy(14, 11); cout << s.rata;
        gotoxy(14, 12); cout << s.keterangan;

        arr.push_back(s);
        n++;

        gotoxy(14, 14); cin >> lagi;
      }
    }

    // ── Loop pilih metode sorting
    vector<Siswa> original = arr;
    bool keluar = false;

    while (!keluar)
    {
      arr = original;

      clearScreen();
      drawHeader();

      gotoxy(0, 5); cout << "Data siswa: " << n << " siswa terinput";

      string sortOpts[] = {"Exchange Sort", "Bubble Sort", "Quick Sort",
                           "Selection Sort", "Insertion Sort",
                           "Merge Sort", "Heap Sort", "Keluar"};
      int methodChoice = inputMenu(0, 7, sortOpts, 8);

      if (methodChoice == 8) { keluar = true; break; }

      // ── Pilih urutan
      clearScreen();
      drawHeader();

      string orderOpts[] = {"Ascending", "Descending"};
      int orderChoice = inputMenu(0, 5, orderOpts, 2);
      bool asc = (orderChoice == 1);

      string methodNames[] = {"Exchange Sort", "Bubble Sort", "Quick Sort",
                               "Selection Sort", "Insertion Sort",
                               "Merge Sort", "Heap Sort"};
      string methodName = methodNames[methodChoice - 1];
      string orderName = asc ? "Ascending" : "Descending";

      switch (methodChoice)
      {
      case 1: exchangeSort(asc); break;
      case 2: bubbleSort(asc); break;
      case 3: quickSort(0, n - 1, asc); break;
      case 4: selectionSort(asc); break;
      case 5: insertionSort(asc); break;
      case 6: mergeSort(0, n - 1, asc); break;
      case 7: heapSort(asc); break;
      }

      // ── Tampilkan hasil
      clearScreen();

      gotoxy(0, 0);
      cout << "=== HASIL SORTING ===\n";
      cout << "Metode    : " << methodName << " (" << orderName << ")\n\n";

      printTable();

      cout << "\nTekan enter untuk kembali ke menu...";
      cin.ignore();
      cin.get();
    }
  }

  return 0;
}
