
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item
{
    int weight;
    int profit;
    double ratio;
};

int main()
{
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter weight and profit of each item:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> items[i].weight >> items[i].profit;

        items[i].ratio =
            (double)items[i].profit / items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // Sort items by decreasing profit/weight ratio
    sort(items.begin(), items.end(),
         [](Item a, Item b)
         {
             return a.ratio > b.ratio;
         });

    int totalWeight = 0;
    int totalProfit = 0;

    cout << "\nSelected items:\n";

    for (int i = 0; i < n; i++)
    {
        if (totalWeight + items[i].weight <= capacity)
        {
            totalWeight += items[i].weight;
            totalProfit += items[i].profit;

            cout << "Weight: " << items[i].weight
                 << ", Profit: " << items[i].profit << "\n";
        }
    }

    cout << "\nTotal weight: " << totalWeight;
    cout << "\nTotal profit: " << totalProfit << "\n";

    return 0;
}
