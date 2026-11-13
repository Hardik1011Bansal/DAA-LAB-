
#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;

// Print optimal parenthesization
void printParenthesis(int i, int j,
                      vector<vector<int>>& split)
{
    if(i == j)
    {
        cout << "A" << i;
        return;
    }

    cout << "(";

    printParenthesis(i, split[i][j], split);

    printParenthesis(split[i][j] + 1, j, split);

    cout << ")";
}

// Matrix Chain Multiplication
void matrixChain(vector<int>& p, int n)
{
    vector<vector<long long>> dp(
        n + 1, vector<long long>(n + 1, 0));

    vector<vector<int>> split(
        n + 1, vector<int>(n + 1, 0));

    // Chain length
    for(int len = 2; len <= n; len++)
    {
        for(int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;

            dp[i][j] = LLONG_MAX;

            for(int k = i; k < j; k++)
            {
                long long cost = dp[i][k]
                               + dp[k+1][j]
                               + 1LL * p[i-1] * p[k] * p[j];

                if(cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    cout << "\nMinimum number of multiplications: "
         << dp[1][n];

    cout << "\nOptimal Parenthesization: ";

    printParenthesis(1, n, split);

    cout << endl;
}

int main()
{
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    if(n <= 0)
    {
        cout << "Invalid number of matrices";
        return 0;
    }

    vector<int> p(n + 1);

    cout << "Enter dimensions array ("
         << n + 1 << " values): ";

    for(int i = 0; i <= n; i++)
    {
        cin >> p[i];

        if(p[i] <= 0)
        {
            cout << "Dimensions must be positive";
            return 0;
        }
    }

    auto start = high_resolution_clock::now();

    matrixChain(p, n);

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<nanoseconds>(stop - start);

    cout << "Execution Time: "
         << duration.count() << " nanoseconds";

    return 0;
}
