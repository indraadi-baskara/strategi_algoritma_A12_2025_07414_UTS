#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
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

vector<int> arr;
int n;

void tukar(int a, int b)
{
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

// ── Selection Sort ─────────────────────────────────────────────────────────
void selectionSort(bool asc)
{
  for (int i = 0; i < n - 1; i++)
  {
    int idx = i;
    for (int j = i + 1; j < n; j++)
    {
      if (asc ? arr[j] < arr[idx] : arr[j] > arr[idx])
        idx = j;
    }
    tukar(i, idx);
  }
}

// ── Merge Sort ─────────────────────────────────────────────────────────────
void merge(int l, int m, int r, bool asc)
{
  vector<int> temp(n);
  int i = l, j = m + 1, k = l;

  while (i <= m && j <= r)
  {
    if (asc ? arr[i] <= arr[j] : arr[i] >= arr[j])
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

// ── Quick Sort ─────────────────────────────────────────────────────────────
int partition(int low, int high, bool asc)
{
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
  {
    if (asc ? arr[j] < pivot : arr[j] > pivot)
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

// ── Heap Sort ──────────────────────────────────────────────────────────────
void heapify(int size, int i, bool asc)
{
  int target = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < size && (asc ? arr[left] > arr[target] : arr[left] < arr[target]))
    target = left;
  if (right < size && (asc ? arr[right] > arr[target] : arr[right] < arr[target]))
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

// ── Arrow-key menu selector ────────────────────────────────────────────────
// Returns 1-based index of the selected option.
#ifdef _WIN32
int selectMenu(int x, int y, const string options[], int count)
{
  int selected = 0;
  while (true)
  {
    for (int i = 0; i < count; i++)
    {
      gotoxy(x, y + i);
      if (i == selected)
        cout << "> " << options[i] << "   ";
      else
        cout << "  " << options[i] << "   ";
    }
    int key = _getch();
    if (key == 0 || key == 224)   // arrow key sends two bytes
    {
      key = _getch();
      if (key == 72 && selected > 0) selected--;           // up
      if (key == 80 && selected < count - 1) selected++;   // down
    }
    else if (key == 13) break;    // Enter
  }
  return selected + 1;
}
#else
int selectMenu(int x, int y, const string options[], int count)
{
  for (int i = 0; i < count; i++)
  {
    gotoxy(x, y + i);
    cout << "  " << (i + 1) << ". " << options[i];
  }
  gotoxy(x, y + count + 1);
  cout << "Pilihan: ";
  int choice;
  cin >> choice;
  return choice;
}
#endif

// ── Helpers ────────────────────────────────────────────────────────────────
void printArray(const vector<int> &a)
{
  for (int i = 0; i < (int)a.size(); i++)
    cout << setw(5) << a[i];
}

// ── Main ───────────────────────────────────────────────────────────────────
int main()
{
  while (true)
  {
  arr.clear();

  clearScreen();

  gotoxy(0, 0);
  cout << "=== PROGRAM SORTING ===\n";
  cout << "Dibuat oleh: Indra Adi Baskara\n";
  cout << "NIM: A12.2025.07414\n";
  cout << "Strategi Algoritma\n";

  gotoxy(0, 5);
  cout << "Masukkan data (pisahkan dengan spasi): ";
  string line;
  getline(cin, line);

  istringstream ss(line);
  int num;
  while (ss >> num) arr.push_back(num);
  n = arr.size();

  vector<int> original = arr;

  string sortMethods[] = {"Selection Sort", "Merge Sort", "Quick Sort", "Heap Sort"};
  gotoxy(0, 7);
  cout << "Pilih metode sorting:";
  int methodChoice = selectMenu(0, 8, sortMethods, 4);

  string orders[] = {"Ascending", "Descending"};
  gotoxy(0, 13);
  cout << "Pilih urutan:";
  int orderChoice = selectMenu(0, 14, orders, 2);
  bool asc = (orderChoice == 1);

  string methodNames[] = {"Selection Sort", "Merge Sort", "Quick Sort", "Heap Sort"};
  string methodName = (methodChoice >= 1 && methodChoice <= 4) ? methodNames[methodChoice - 1] : "Unknown";
  string orderName = asc ? "Ascending" : "Descending";

  switch (methodChoice)
  {
  case 1: selectionSort(asc); break;
  case 2: mergeSort(0, n - 1, asc); break;
  case 3: quickSort(0, n - 1, asc); break;
  case 4: heapSort(asc); break;
  }

  clearScreen();

  gotoxy(0, 0);
  cout << "=== HASIL SORTING ===\n";

  gotoxy(0, 2);
  cout << "Metode  : " << methodName << "\n";
  cout << "Urutan  : " << orderName << "\n";

  gotoxy(0, 5);
  cout << "Data Awal  : ";
  printArray(original);

  gotoxy(0, 6);
  cout << "Hasil Sort : ";
  printArray(arr);

  string aksiMenu[] = {"Kembali ke menu awal", "Keluar"};
  gotoxy(0, 8);
  cout << "Pilih aksi:";
  int aksi = selectMenu(0, 9, aksiMenu, 2);

  if (aksi == 2) break;
  } // end while

  return 0;
}
