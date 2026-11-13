
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

using Matrix = vector<vector<int>>;

// Add two matrices
Matrix add(Matrix A, Matrix B, int n)
{
    Matrix C(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

// Subtract two matrices
Matrix subtract(Matrix A, Matrix B, int n)
{
    Matrix C(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}

// Strassen multiplication
Matrix strassen(Matrix A, Matrix B, int n)
{
    Matrix C(n, vector<int>(n));

    // Base case
    if(n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    Matrix A11(k, vector<int>(k));
    Matrix A12(k, vector<int>(k));
    Matrix A21(k, vector<int>(k));
    Matrix A22(k, vector<int>(k));

    Matrix B11(k, vector<int>(k));
    Matrix B12(k, vector<int>(k));
    Matrix B21(k, vector<int>(k));
    Matrix B22(k, vector<int>(k));

    // Divide matrices into four parts
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    // Calculate seven products
    Matrix M1 = strassen(add(A11,A22,k),
                         add(B11,B22,k),k);

    Matrix M2 = strassen(add(A21,A22,k),B11,k);

    Matrix M3 = strassen(A11,
                         subtract(B12,B22,k),k);

    Matrix M4 = strassen(A22,
                         subtract(B21,B11,k),k);

    Matrix M5 = strassen(add(A11,A12,k),B22,k);

    Matrix M6 = strassen(subtract(A21,A11,k),
                         add(B11,B12,k),k);

    Matrix M7 = strassen(subtract(A12,A22,k),
                         add(B21,B22,k),k);

    // Calculate result quadrants
    Matrix C11 = add(subtract(add(M1,M4,k),M5,k),M7,k);
    Matrix C12 = add(M3,M5,k);
    Matrix C21 = add(M2,M4,k);
    Matrix C22 = add(subtract(add(M1,M3,k),M2,k),M6,k);

    // Combine four quadrants
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }

    return C;
}

int main()
{
    int n;

    cout << "Enter order of square matrices: ";
    cin >> n;

    if(n <= 0 || (n & (n-1)) != 0)
    {
        cout << "Please enter a positive power of 2.";
        return 0;
    }

    Matrix A(n, vector<int>(n));
    Matrix B(n, vector<int>(n));

    cout << "Enter elements of first matrix:\n";

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter elements of second matrix:\n";

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> B[i][j];

    auto start = high_resolution_clock::now();

    Matrix C = strassen(A, B, n);

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<nanoseconds>(stop - start);

    cout << "\nResultant Matrix:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << C[i][j] << " ";

        cout << endl;
    }

    cout << "\nExecution Time: "
         << duration.count() << " nanoseconds";

    return 0;
}
