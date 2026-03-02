#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * Vector3D Class
 * Represents a 3-dimensional vector with basic operations
 */
class Vector3D {
private:
    double data[3];  // Store three components

public:
    /**
     * Constructor with optional initialization
     * @param x First component (default 0)
     * @param y Second component (default 0)
     * @param z Third component (default 0)
     */
    Vector3D(double x = 0, double y = 0, double z = 0) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    /**
     * Overloaded index operator (non-const)
     * @param index Index to access (0-2)
     * @return Reference to the component
     */
    double& operator[](int index) {
        if (index < 0 || index >= 3) {
            throw out_of_range("Vector3D index out of range");
        }
        return data[index];
    }

    /**
     * Overloaded index operator (const)
     * @param index Index to access (0-2)
     * @return Const reference to the component
     */
    const double& operator[](int index) const {
        if (index < 0 || index >= 3) {
            throw out_of_range("Vector3D index out of range");
        }
        return data[index];
    }

    /**
     * Print vector components
     */
    void print() const {
        cout << "(" << data[0] << ", " << data[1] << ", " << data[2] << ")" << endl;
    }
};

/**
 * Matrix Class
 * Represents a matrix with maximum dimensions 10x10
 * Provides fundamental linear algebra operations
 */
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
    static const int M = 10;  // Maximum number of rows
    static const int N = 10;  // Maximum number of columns
    double A[M][N];         // 2D array for matrix storage
    int m;                  // Actual number of rows
    int n;                  // Actual number of columns

    // Helper functions for 3x3 matrix operations
    double minor(int row, int col) const;
    double cofactor(int row, int col) const;
};

/**
 * Default constructor
 * Initializes matrix to empty (0x0) and all entries to zero
 */
Matrix::Matrix() : m(0), n(0) {
    // Initialize all entries to 0
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 0.0;
        }
    }
}

/**
 * Read matrix entries from user input
 * Prompts for dimensions and entries row by row
 */
void Matrix::read() {
    cout << "Enter number of rows: ";
    cin >> m;
    cout << "Enter number of columns: ";
    cin >> n;

    // Validate dimensions
    if (m > M || n > N) {
        cout << "Error: Matrix dimensions exceed maximum size ("
            << M << "x" << N << ")" << endl;
        m = n = 0;
        return;
    }

    cout << "Enter matrix entries row by row:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Enter A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }
}

/**
 * Print matrix entries
 * Displays dimensions and formatted entries row by row
 */
void Matrix::print() {
    cout << "Matrix (" << m << "x" << n << "):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(4) << A[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Matrix multiplication
 * @param other Matrix to multiply with
 * @return Product matrix (empty if multiplication undefined)
 */
Matrix Matrix::multiply(Matrix other) {
    Matrix result;

    // Check if multiplication is defined
    if (this->n != other.m) {
        cout << "Error: Matrix multiplication not defined. ";
        cout << "Number of columns of first matrix (" << this->n << ") ";
        cout << "must equal number of rows of second matrix (" << other.m << ")" << endl;
        return result; // Return empty matrix
    }

    result.m = this->m;
    result.n = other.n;

    // Perform matrix multiplication
    for (int i = 0; i < result.m; i++) {
        for (int j = 0; j < result.n; j++) {
            result.A[i][j] = 0;
            for (int k = 0; k < this->n; k++) {
                result.A[i][j] += this->A[i][k] * other.A[k][j];
            }
        }
    }

    return result;
}

/**
 * Compute matrix transpose
 * @return Transposed matrix
 */
Matrix Matrix::transpose() {
    Matrix result;
    result.m = this->n;
    result.n = this->m;

    for (int i = 0; i < result.m; i++) {
        for (int j = 0; j < result.n; j++) {
            result.A[i][j] = this->A[j][i];
        }
    }

    return result;
}

/**
 * Compute minor for 3x3 matrix
 * Minor M_ij is determinant of submatrix after removing row i and column j
 * @param row Row index
 * @param col Column index
 * @return Minor value
 */
double Matrix::minor(int row, int col) const {
    if (m != 3 || n != 3) {
        return 0;
    }

    // Create 2x2 submatrix by removing specified row and column
    double submatrix[2][2];
    int sub_i = 0;

    for (int i = 0; i < 3; i++) {
        if (i == row) continue;
        int sub_j = 0;
        for (int j = 0; j < 3; j++) {
            if (j == col) continue;
            submatrix[sub_i][sub_j] = A[i][j];
            sub_j++;
        }
        sub_i++;
    }

    // Calculate determinant of 2x2 submatrix
    return submatrix[0][0] * submatrix[1][1] - submatrix[0][1] * submatrix[1][0];
}

/**
 * Compute cofactor for 3x3 matrix
 * Cofactor C_ij = (-1)^(i+j) * minor(i,j)
 * @param row Row index
 * @param col Column index
 * @return Cofactor value
 */
double Matrix::cofactor(int row, int col) const {
    double min = minor(row, col);
    // (-1)^(i+j) * minor
    return ((row + col) % 2 == 0) ? min : -min;
}

/**
 * Compute determinant of 3x3 matrix
 * @return Determinant value (0 if matrix not 3x3)
 */
double Matrix::determinant() {
    if (m != 3 || n != 3) {
        cout << "Error: Determinant can only be computed for 3x3 matrices" << endl;
        return 0;
    }

    // Using cofactor expansion along first row
    double det = 0;
    for (int j = 0; j < 3; j++) {
        det += A[0][j] * cofactor(0, j);
    }

    return det;
}

/**
 * Compute inverse of 3x3 matrix using adjugate matrix method
 * A^(-1) = (1/det) * adj(A)
 * @return Inverse matrix (empty if singular or not 3x3)
 */
Matrix Matrix::inverse() {
    Matrix result;

    if (m != 3 || n != 3) {
        cout << "Error: Inverse can only be computed for 3x3 matrices" << endl;
        return result;
    }

    double det = determinant();

    // Check if matrix is singular (determinant effectively zero)
    if (abs(det) < 1e-10) {
        cout << "Error: Matrix is singular (determinant = 0), inverse does not exist" << endl;
        return result;
    }

    result.m = 3;
    result.n = 3;

    // Compute cofactor matrix
    double cofactorMatrix[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cofactorMatrix[i][j] = cofactor(i, j);
        }
    }

    // Transpose to get adjugate matrix and divide by determinant
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.A[i][j] = cofactorMatrix[j][i] / det;
        }
    }

    return result;
}

/**
 * Multiply matrix by 3D vector
 * @param v 3D vector
 * @return Resulting 3D vector
 */
Vector3D Matrix::multiply(Vector3D v) {
    Vector3D result;

    if (m != 3 || n != 3) {
        cout << "Error: Matrix must be 3x3 for multiplication with Vector3D" << endl;
        return result;
    }

    for (int i = 0; i < 3; i++) {
        double sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += A[i][j] * v[j];
        }
        result[i] = sum;
    }

    return result;
}

/**
 * Comprehensive test function
 * Tests all matrix operations with sample data
 */
void runTests() {
    cout << "========================================" << endl;
    cout << "TESTING MATRIX CLASS IMPLEMENTATION" << endl;
    cout << "========================================" << endl << endl;

    // Test 1: Matrix from slide 5, week 5
    cout << "Test 1: Matrix from slide 5, week 5" << endl;
    cout << "----------------------------------------" << endl;
    Matrix A;
    A.read(); // User should input: 3x3 matrix with values from slide

    cout << "\nOriginal matrix A:" << endl;
    A.print();

    cout << "\nTranspose of A:" << endl;
    Matrix A_transpose = A.transpose();
    A_transpose.print();

    // Test 2: Matrix multiplication
    cout << "\nTest 2: Matrix Multiplication" << endl;
    cout << "----------------------------------------" << endl;
    Matrix B;
    B.read(); // User should input another 3x3 matrix

    cout << "\nMatrix B:" << endl;
    B.print();

    cout << "\nA * B:" << endl;
    Matrix C = A.multiply(B);
    C.print();

    // Test 3: Determinant
    cout << "\nTest 3: Determinant of A" << endl;
    cout << "----------------------------------------" << endl;
    double det = A.determinant();
    cout << "det(A) = " << fixed << setprecision(4) << det << endl;

    // Test 4: Inverse
    cout << "\nTest 4: Inverse of A (from slide 10, week 6)" << endl;
    cout << "----------------------------------------" << endl;
    Matrix A_inv = A.inverse();
    if (abs(det) > 1e-10) {
        cout << "A^(-1):" << endl;
        A_inv.print();

        // Verify: A * A^(-1) should be identity
        cout << "\nVerification: A * A^(-1):" << endl;
        Matrix I = A.multiply(A_inv);
        I.print();
    }

    // Test 5: Matrix-Vector multiplication
    cout << "\nTest 5: Matrix-Vector Multiplication" << endl;
    cout << "----------------------------------------" << endl;
    Vector3D v(1, 2, 3);
    cout << "Vector v: ";
    v.print();

    Vector3D Av = A.multiply(v);
    cout << "A * v: ";
    Av.print();

    cout << "\n========================================" << endl;
    cout << "ALL TESTS COMPLETED" << endl;
    cout << "========================================" << endl;
}

/**
 * Main function
 * Entry point for the program
 */
int main() {
    runTests();
    return 0;
}