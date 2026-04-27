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

void selectionSortAscending()
{
  for (int i = 0; i < n - 1; i++)
  {
    int minIndex = i;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[minIndex])
        minIndex = j;
    }
    tukar(i, minIndex);
  }
}

void selectionSortDescending()
{
  for (int i = 0; i < n - 1; i++)
  {
    int maxIndex = i;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] > arr[maxIndex])
        maxIndex = j;
    }
    tukar(i, maxIndex);
  }
}

int main()
{
  cout << "=== PROGRAM SELECTION SORT ===\n";

  cout << "\nData Awal:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  selectionSortAscending();

  cout << "\n\nAscending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  selectionSortDescending();

  cout << "\n\nDescending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  cout << "\n\nSelesai\n";
  return 0;
}
