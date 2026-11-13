
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
    int r1, c1, r2, c2;

    cout << "Enter rows and columns of first matrix: ";
    cin >> r1 >> c1;

    cout << "Enter rows and columns of second matrix: ";
    cin >> r2 >> c2;

    if(c1 != r2)
    {
        cout << "Matrix multiplication not possible!";
        return 0;
    }

    vector<vector<int>> A(r1, vector<int>(c1));
    vector<vector<int>> B(r2, vector<int>(c2));
    vector<vector<int>> C(r1, vector<int>(c2, 0));

    cout << "\nEnter first matrix elements:\n";

    for(int i = 0; i < r1; i++)
        for(int j = 0; j < c1; j++)
            cin >> A[i][j];

    cout << "\nEnter second matrix elements:\n";

    for(int i = 0; i < r2; i++)
        for(int j = 0; j < c2; j++)
            cin >> B[i][j];

    // Start measuring time
    auto start = high_resolution_clock::now();

    // Traditional matrix multiplication
    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j < c2; j++)
        {
            for(int k = 0; k < c1; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Stop measuring time
    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<nanoseconds>(stop - start);

    cout << "\nResultant Matrix:\n";

    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j < c2; j++)
            cout << C[i][j] << " ";

        cout << endl;
    }

    cout << "\nExecution Time: "
         << duration.count() << " nanoseconds";

    return 0;
}
