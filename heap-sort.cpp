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

void heapifyAsc(int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i)
  {
    tukar(i, largest);
    heapifyAsc(n, largest);
  }
}

void heapSortAsc()
{
  for (int i = n / 2 - 1; i >= 0; i--)
    heapifyAsc(n, i);

  for (int i = n - 1; i > 0; i--)
  {
    tukar(0, i);
    heapifyAsc(i, 0);
  }
}

void heapifyDesc(int n, int i)
{
  int smallest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] < arr[smallest])
    smallest = left;

  if (right < n && arr[right] < arr[smallest])
    smallest = right;

  if (smallest != i)
  {
    tukar(i, smallest);
    heapifyDesc(n, smallest);
  }
}

void heapSortDesc()
{
  for (int i = n / 2 - 1; i >= 0; i--)
    heapifyDesc(n, i);

  for (int i = n - 1; i > 0; i--)
  {
    tukar(0, i);
    heapifyDesc(i, 0);
  }
}

int main()
{
  cout << "=== PROGRAM HEAP SORT ===\n";

  cout << "\nData Awal:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  heapSortAsc();

  cout << "\n\nAscending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  heapSortDesc();

  cout << "\n\nDescending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  cout << "\n\nSelesai\n";
  return 0;
}
