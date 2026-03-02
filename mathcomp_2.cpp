#include <iostream>
#include <iomanip>
using namespace std;

// ----------------------
// Vector3D Class
// ----------------------

class Vector3D {
public:
    double x, y, z;

    // Default constructor
    Vector3D() {
        x = 0;
        y = 0;
        z = 0;
    }

    // Constructor with values
    Vector3D(double xVal, double yVal, double zVal) {
        x = xVal;
        y = yVal;
        z = zVal;
    }

    void print() {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }
};


// ----------------------
// Matrix Class
// ----------------------

class Matrix
{
public:
    Matrix();

    void read();
    void print();
    Matrix multiply(Matrix other);
    Matrix transpose();
    double determinant();
    Matrix inverse();
    Vector3D multiply(Vector3D v);

private:
    static const int M = 10;
    static const int N = 10;
    double A[M][N];
    int m; // actual rows
    int n; // actual columns
};


// ----------------------
// Constructor
// ----------------------

Matrix::Matrix() {
    m = 0;
    n = 0;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = 0;
}


// ----------------------
// Read Matrix
// ----------------------

void Matrix::read() {

    cout << "Enter number of rows: ";
    cin >> m;

    cout << "Enter number of columns: ";
    cin >> n;

    cout << "Enter matrix entries row by row:\n";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];
}


// ----------------------
// Print Matrix
// ----------------------

void Matrix::print() {

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(10) << A[i][j] << " ";
        cout << endl;
    }
}


// ----------------------
// Matrix Multiplication
// ----------------------

Matrix Matrix::multiply(Matrix other) {

    Matrix result;

    if (n != other.m) {
        cout << "Matrix multiplication not defined!" << endl;
        return result;
    }

    result.m = m;
    result.n = other.n;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < other.n; j++) {

            result.A[i][j] = 0;

            for (int k = 0; k < n; k++) {
                result.A[i][j] += A[i][k] * other.A[k][j];
            }
        }
    }

    return result;
}


// ----------------------
// Transpose
// ----------------------

Matrix Matrix::transpose() {

    Matrix result;

    result.m = n;
    result.n = m;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result.A[j][i] = A[i][j];

    return result;
}


// ----------------------
// Determinant (3x3 only)
// ----------------------

double Matrix::determinant() {

    if (m != 3 || n != 3) {
        cout << "Determinant only defined for 3x3 matrices." << endl;
        return 0;
    }

    double det =
        A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1])
        - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0])
        + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);

    return det;
}


// ----------------------
// Inverse (3x3 only)
// ----------------------

Matrix Matrix::inverse() {

    Matrix inv;

    if (m != 3 || n != 3) {
        cout << "Inverse only defined for 3x3 matrices." << endl;
        return inv;
    }

    double det = determinant();

    if (det == 0) {
        cout << "Matrix is singular. No inverse exists." << endl;
        return inv;
    }

    inv.m = 3;
    inv.n = 3;

    inv.A[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) / det;
    inv.A[0][1] = -(A[0][1] * A[2][2] - A[0][2] * A[2][1]) / det;
    inv.A[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) / det;

    inv.A[1][0] = -(A[1][0] * A[2][2] - A[1][2] * A[2][0]) / det;
    inv.A[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) / det;
    inv.A[1][2] = -(A[0][0] * A[1][2] - A[0][2] * A[1][0]) / det;

    inv.A[2][0] = (A[1][0] * A[2][1] - A[1][1] * A[2][0]) / det;
    inv.A[2][1] = -(A[0][0] * A[2][1] - A[0][1] * A[2][0]) / det;
    inv.A[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / det;

    return inv;
}


// ----------------------
// Matrix-Vector Multiplication
// ----------------------

Vector3D Matrix::multiply(Vector3D v) {

    Vector3D result;

    if (m != 3 || n != 3) {
        cout << "Matrix-vector multiplication requires 3x3 matrix." << endl;
        return result;
    }

    result.x = A[0][0] * v.x + A[0][1] * v.y + A[0][2] * v.z;
    result.y = A[1][0] * v.x + A[1][1] * v.y + A[1][2] * v.z;
    result.z = A[2][0] * v.x + A[2][1] * v.y + A[2][2] * v.z;

    return result;
}


// ----------------------
// Main Function (Testing)
// ----------------------

int main() {

    Matrix A, B;

    cout << "Enter Matrix A:\n";
    A.read();

    cout << "\nEnter Matrix B:\n";
    B.read();

    cout << "\nMatrix A:\n";
    A.print();

    cout << "\nMatrix B:\n";
    B.print();

    cout << "\nA * B:\n";
    Matrix C = A.multiply(B);
    C.print();

    cout << "\nTranspose of A:\n";
    Matrix AT = A.transpose();
    AT.print();

    cout << "\nTranspose of B:\n";
    Matrix BT = B.transpose();
    BT.print();

    cout << "\nDeterminant of A:\n";
    cout << A.determinant() << endl;

    cout << "\nDeterminant of B:\n";
    cout << B.determinant() << endl;

    cout << "\nInverse of A:\n";
    Matrix Ainv = A.inverse();
    Ainv.print();

    cout << "\nInverse of B:\n";
    Matrix Binv = B.inverse();
    Binv.print();

    Vector3D v(1, 2, 3);
    cout << "\nA * (1,2,3):\n";
    Vector3D result = A.multiply(v);
    result.print();

    Vector3D v(1, 2, 3);
    cout << "\nB * (1,2,3):\n";
    Vector3D result = A.multiply(v);
    result.print();

    return 0;
}