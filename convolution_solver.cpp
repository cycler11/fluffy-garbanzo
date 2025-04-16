
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

//метод решения Гаусса
void gaussElimination(vector<vector<double>>& A, vector<double>& b, vector<double>& x) {
    int n = A.size();
    
    for (int i = 0; i < n; ++i) {
        // Поиск главного элемента
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
            if (abs(A[k][i]) > abs(A[maxRow][i]))
                maxRow = k;

        // Перестановка строк
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // Приведение к треуг
        for (int k = i + 1; k < n; ++k) {
            double c = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j)
                A[k][j] -= c * A[i][j];
            b[k] -= c * b[i];
        }
    }

    // Обратный ход
    x.assign(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
}

int main() {

    int input[4][4] = {
        {4, 5, 8, 7},
        {1, 8, 8, 8},
        {3, 6, 6, 4},
        {6, 5, 7, 8}
    };


    int output[2][2] = {
        {122, 148},
        {126, 134}
    };

    vector<vector<double>> A;
    vector<double> b;

    //  система уравнений Ax = b
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            vector<double> row;
            for (int ki = 0; ki < 3; ++ki) {
                for (int kj = 0; kj < 3; ++kj) {
                    row.push_back(input[i + ki][j + kj]);
                }
            }
            A.push_back(row);
            b.push_back(output[i][j]);
        }
    }

    vector<double> kernel;
    gaussElimination(A, b, kernel);


    cout << "Обученное ядро свёртки 3x3:\n";
    for (int i = 0; i < 9; ++i) {
        cout << fixed << setprecision(2) << kernel[i] << "\t";
        if ((i + 1) % 3 == 0) cout << endl;
    }

    return 0;
}
