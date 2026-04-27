#include <iostream>
#include <iomanip>
using namespace std;

int const n = 10;
int arr[n] = {5, 8, 80, 3, 6, 8, 1, 10, 15, 75};

void mergeAsc(int l, int m, int r)
{
  int temp[n];
  int i = l, j = m + 1, k = l;

  while (i <= m && j <= r)
  {
    if (arr[i] < arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  while (i <= m)
    temp[k++] = arr[i++];

  while (j <= r)
    temp[k++] = arr[j++];

  for (int x = l; x <= r; x++)
    arr[x] = temp[x];
}

void mergeSortAsc(int l, int r)
{
  if (l < r)
  {
    int m = (l + r) / 2;
    mergeSortAsc(l, m);
    mergeSortAsc(m + 1, r);
    mergeAsc(l, m, r);
  }
}

void mergeDesc(int l, int m, int r)
{
  int temp[n];
  int i = l, j = m + 1, k = l;

  while (i <= m && j <= r)
  {
    if (arr[i] > arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  while (i <= m)
    temp[k++] = arr[i++];

  while (j <= r)
    temp[k++] = arr[j++];

  for (int x = l; x <= r; x++)
    arr[x] = temp[x];
}

void mergeSortDesc(int l, int r)
{
  if (l < r)
  {
    int m = (l + r) / 2;
    mergeSortDesc(l, m);
    mergeSortDesc(m + 1, r);
    mergeDesc(l, m, r);
  }
}

int main()
{
  cout << "=== PROGRAM MERGE SORT ===\n";

  cout << "\nData Awal:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  mergeSortAsc(0, n - 1);

  cout << "\n\nAscending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  mergeSortDesc(0, n - 1);

  cout << "\n\nDescending:\n";
  for (int i = 0; i < n; i++)
    cout << setw(5) << arr[i];

  cout << "\n\nSelesai\n";
  return 0;
}
