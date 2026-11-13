
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

void merge(vector<int>& arr, int low, int mid, int high)
{
    vector<int> temp;

    int i = low;
    int j = mid + 1;

    while(i <= mid && j <= high)
    {
        if(arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while(i <= mid)
        temp.push_back(arr[i++]);

    while(j <= high)
        temp.push_back(arr[j++]);

    for(int k = low; k <= high; k++)
        arr[k] = temp[k - low];
}

void mergeSort(vector<int>& arr, int low, int high)
{
    if(low < high)
    {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if(n <= 0)
    {
        cout << "Invalid array size";
        return 0;
    }

    vector<int> arr(n);

    cout << "Enter array elements: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    auto start = high_resolution_clock::now();

    mergeSort(arr, 0, n - 1);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "\nSorted array: ";
    for(int x : arr)
        cout << x << " ";

    cout << "\nExecution Time: "
         << duration.count() << " nanoseconds";

    return 0;
}
