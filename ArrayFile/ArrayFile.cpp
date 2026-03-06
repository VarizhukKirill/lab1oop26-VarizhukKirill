#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 560;

int ConsoleInputSizeArray(const int sizeMax) {
    int size = 0;
    do {
        cout << "Введіть розмір масиву (0 < n < " << sizeMax << "): ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}

void WriteArrayTextFile(int n, double* arr, const char* fileName) {
    ofstream fout(fileName);
    if (!fout) return;
    fout << n << endl;
    for (int i = 0; i < n; i++) fout << arr[i] << " ";
    fout.close();
}

int ReadArrayTextFile(int maxSize, double* arr, const char* fileName) {
    ifstream fin(fileName);
    if (!fin) return 0;
    int size;
    fin >> size;
    if (size <= 0 || size > maxSize) return 0;
    for (int i = 0; i < size; i++) fin >> arr[i];
    fin.close();
    return size;
}

void WriteArrayBinFile(int n, double* arr, const char* fileName) {
    ofstream fout(fileName, ios::binary);
    if (!fout) return;
    fout.write((char*)&n, sizeof(int));
    fout.write((char*)arr, n * sizeof(double));
    fout.close();
}

void Task_Dynamic_Solutions() {
    cout << "\n--- Завдання 3.3 (Динамічні масиви) ---" << endl;

    double* A = new double[MAX_SIZE];
    int n = ReadArrayTextFile(MAX_SIZE, A, "A.txt");
    if (n == 0) { cout << "Помилка: файл A.txt порожній!" << endl; delete[] A; return; }

    double minPositive = -1;
    int minIdx = -1;
    for (int i = 0; i < n; i++) {
        if (A[i] > 0) {
            if (minIdx == -1 || A[i] < minPositive) {
                minPositive = A[i];
                minIdx = i;
            }
        }
    }
    cout << "1. Мінімальний додатний: " << (minIdx != -1 ? to_string(minPositive) : "немає")
         << ", Індекс: " << minIdx << endl;

    double T;
    cout << "Введіть число T для задачі 2: ";
    cin >> T;
    double maxNeg = -1e18;
    int maxNegIdx = -1;
    for (int i = 0; i < n; i++) {
        if (A[i] > T) break;
        if (A[i] < 0) {
            if (A[i] > maxNeg) {
                maxNeg = A[i];
                maxNegIdx = i;
            }
        }
    }
    cout << "2. Номер першого макс. від'ємного до T: " << maxNegIdx << endl;

    int rows = 3, cols = 4;
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) matrix[i] = new double[cols];

    cout << "3. Матриця " << rows << "x" << cols << " створена динамічно." << endl;

    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;
    delete[] A;
}

void Task_Vector_FromFile() {
    cout << "\n--- Завдання 3.4 (Vector) ---" << endl;
    ifstream fin("A.bin", ios::binary);
    if (!fin) return;
    int size;
    fin.read((char*)&size, sizeof(int));
    vector<double> vec(size);
    fin.read((char*)vec.data(), size * sizeof(double));
    fin.close();
    cout << "Дані з вектора: ";
    for (double x : vec) cout << x << " ";
    cout << endl;
}

void Task_TextFile() {
    cout << "--- Завдання 3.1 ---" << endl;
    double A[MAX_SIZE];
    int size = ConsoleInputSizeArray(MAX_SIZE);
    for (int i = 0; i < size; i++) { cout << "A[" << i << "]="; cin >> A[i]; }
    WriteArrayTextFile(size, A, "A.txt");
}

void Task_BinaryFile() {
    cout << "\n--- Завдання 3.2 ---" << endl;
    int size = ConsoleInputSizeArray(MAX_SIZE);
    double* A = new double[size];
    srand(time(0));
    for (int i = 0; i < size; i++) { A[i] = (rand() % 200 - 100) / 1.0; cout << A[i] << " "; }
    WriteArrayBinFile(size, A, "A.bin");
    delete[] A;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    Task_TextFile();
    Task_BinaryFile();
    Task_Dynamic_Solutions();
    Task_Vector_FromFile();
    return 0;
}
