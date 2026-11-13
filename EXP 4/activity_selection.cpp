#include <iostream>
#include <vector>
using namespace std;

// Merge two halves according to finishing time
void merge(vector<pair<int,int>>& arr, int low, int mid, int high)
{
    vector<pair<int,int>> temp;

    int i = low;
    int j = mid + 1;

    while(i <= mid && j <= high)
    {
        if(arr[i].second <= arr[j].second)
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

// Merge Sort
void mergeSort(vector<pair<int,int>>& arr, int low, int high)
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

    cout << "Enter number of activities: ";
    cin >> n;

    if(n <= 0)
    {
        cout << "Invalid number of activities";
        return 0;
    }

    vector<pair<int,int>> activities(n);

    cout << "Enter start and finish time of each activity:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "Activity " << i + 1 << ": ";
        cin >> activities[i].first >> activities[i].second;
    }

    // Sort activities using Merge Sort
    mergeSort(activities, 0, n - 1);

    cout << "\nSelected activities:\n";

    // Select first activity
    int lastFinish = activities[0].second;

    cout << "(" << activities[0].first << ", "
         << activities[0].second << ")\n";

    int count = 1;

    // Select remaining compatible activities
    for(int i = 1; i < n; i++)
    {
        if(activities[i].first >= lastFinish)
        {
            cout << "(" << activities[i].first << ", "
                 << activities[i].second << ")\n";

            lastFinish = activities[i].second;
            count++;
        }
    }

    cout << "\nMaximum number of activities: " << count;

    return 0;
}
