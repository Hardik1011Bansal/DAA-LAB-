
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n + 1);
    vector<int> profit(n + 1);

    cout << "Enter weight and profit of each item:\n";

    for (int i = 1; i <= n; i++)
    {
        cin >> weight[i] >> profit[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<vector<int>> dp(
        n + 1, vector<int>(capacity + 1, 0)
    );

    // Build the DP table
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (weight[i] <= w)
            {
                dp[i][w] = max(
                    dp[i - 1][w],
                    profit[i] + dp[i - 1][w - weight[i]]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum profit: "
         << dp[n][capacity] << "\n";

    cout << "Selected items:\n";

    int w = capacity;

    for (int i = n; i >= 1; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            cout << "Item " << i
                 << " (Weight: " << weight[i]
                 << ", Profit: " << profit[i] << ")\n";

            w -= weight[i];
        }
    }

    return 0;
}
