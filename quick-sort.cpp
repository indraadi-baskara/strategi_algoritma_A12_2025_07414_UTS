#include <iostream>
#include <iomanip>
using namespace std;

int const n = 10;
int arr[n] = {5, 8, 80, 3, 6, 8, 1, 10, 15, 75};

void tukar(int a, int b)
{
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int partitionAsc(int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      tukar(i, j);
    }
  }
  tukar(i + 1, high);
  return i + 1;
}

void quickSortAsc(int low, int high)
{
  if (low < high)
  {
    int pi = partitionAsc(low, high);
    quickSortAsc(low, pi - 1);
    quickSortAsc(pi + 1, high);
  }
}

int partitionDesc(int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
  {
    if (arr[j] > pivot)
    {
      i++;
      tukar(i, j);
    }
  }
  tukar(i + 1, high);
  return i + 1;
}

void quickSortDesc(int low, int high)
{
  if (low < high)
  {
    int pi = partitionDesc(low, high);
    quickSortDesc(low, pi - 1);
    quickSortDesc(pi + 1, high);
  }
}

int main()
{
  cout << "=== PROGRAM QUICK SORT ===\n";

  cout << "\nData Awal:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  quickSortAsc(0, n - 1);

  cout << "\n\nAscending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  quickSortDesc(0, n - 1);

  cout << "\n\nDescending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  cout << "\n\nSelesai\n";
  return 0;
}
