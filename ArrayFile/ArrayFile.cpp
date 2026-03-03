#include <iostream>   // Для введення/виведення (cin, cout)
#include <fstream>    // Для роботи з файлами (ifstream, ofstream)
#include <vector>     // Для контейнера vector (завдання 3.4)
#include <ctime>      // Для генерації випадкових чисел (time)
#include <iomanip>    // Для форматування виводу (setw)

using namespace std;  // Використання стандартного простору імен

const int MAX_SIZE = 560; // Максимальний розмір для статичних масивів

//  3.1: Введення розміру
int ConsoleInputSizeArray(const int sizeMax) {
    int size = 0; // Змінна для розміру
    do {
        cout << "Введіть розмір масиву (0 < n < " << sizeMax << "): "; // Підказка
        cin >> size; // Читання розміру
    } while (size <= 0 || size >= sizeMax); // Перевірка коректності
    return size; // Повернення значення
}

//  3.1: Запис у текстовий файл
void WriteArrayTextFile(int n, double* arr, const char* fileName) {
    ofstream fout(fileName); // Відкриття файлу для запису
    if (!fout) return;       // Перевірка чи відкрився файл
    fout << n << endl;       // Запис кількості елементів
    for (int i = 0; i < n; i++) fout << arr[i] << " "; // Запис самих чисел
    fout.close();            // Закриття файлу
}

// 3.1: Читання з текстового файлу
int ReadArrayTextFile(int maxSize, double* arr, const char* fileName) {
    ifstream fin(fileName);  // Відкриття файлу для читання
    if (!fin) return 0;      // Якщо файлу немає — повертаємо 0
    int size;                // Змінна для розміру
    fin >> size;             // Читання розміру з файлу
    if (size <= 0 || size > maxSize) return 0; // Перевірка розміру
    for (int i = 0; i < size; i++) fin >> arr[i]; // Читання елементів у масив
    fin.close();             // Закриття файлу
    return size;             // Повернення кількості зчитаних даних
}

//  3.2: Запис у бінарний файл
void WriteArrayBinFile(int n, double* arr, const char* fileName) {
    ofstream fout(fileName, ios::binary); // Відкриття в бінарному режимі
    if (!fout) return;                    // Перевірка
    fout.write((char*)&n, sizeof(int));   // Бінарний запис розміру
    fout.write((char*)arr, n * sizeof(double)); // Бінарний запис масиву
    fout.close();                         // Закриття
}


// 3.3: сама логіка програм

void Task_Dynamic_Solutions() {
    cout << "\n--- Завдання 3.3 (Динамічні масиви) ---" << endl;

    // Читаємо дані, які ми ввели в Task 3.1
    double* A = new double[MAX_SIZE]; // Виділення пам'яті під масив А
    int n = ReadArrayTextFile(MAX_SIZE, A, "A.txt"); // Завантаження даних
    if (n == 0) { cout << "Помилка: файл A.txt порожній!" << endl; delete[] A; return; }

    // --- Задача 1: Мінімум серед додатних ---
    double minPositive = -1; // Тимчасове значення для мінімуму
    int minIdx = -1;         // Індекс мінімуму
    for (int i = 0; i < n; i++) {
        if (A[i] > 0) { // Перевірка чи число додатне
            if (minIdx == -1 || A[i] < minPositive) { // Пошук найменшого
                minPositive = A[i]; // Оновлення мінімуму
                minIdx = i;         // Оновлення індексу
            }
        }
    }
    cout << "1. Мінімальний додатний: " << (minIdx != -1 ? to_string(minPositive) : "немає")
         << ", Індекс: " << minIdx << endl;

    //  Задача 2: Максимальний серед від'ємних до першого елемента > T
    double T; // Число-поріг
    cout << "Введіть число T для задачі 2: "; // Запит T
    cin >> T; // Читання T
    double maxNeg = -1e18; // Дуже мале число для пошуку максимуму
    int maxNegIdx = -1;    // Індекс максимуму
    for (int i = 0; i < n; i++) {
        if (A[i] > T) break; // Вихід з циклу, якщо зустріли число більше T
        if (A[i] < 0) {      // Перевірка чи від'ємне
            if (A[i] > maxNeg) { // Пошук найбільшого від'ємного
                maxNeg = A[i];  // Оновлення максимуму
                maxNegIdx = i;  // Запис індексу
            }
        }
    }
    cout << "2. Номер першого макс. від'ємного до T: " << maxNegIdx << endl;
//  Задача 3: Двовимірний масив (Матриця n x m)
    int rows = 3, cols = 4; // Приклад розмірів для матриці
    double** matrix = new double*[rows]; // Створення масиву вказівників (рядки)
    for (int i = 0; i < rows; i++) matrix[i] = new double[cols]; // Створення стовпців

    cout << "3. Матриця " << rows << "x" << cols << " створена динамічно." << endl;
    // (Тут можна додати обчислення згідно варіанту для матриці)

    // Звільнення пам'яті
    for (int i = 0; i < rows; i++) delete[] matrix[i]; // Видалення стовпців
    delete[] matrix; // Видалення рядків
    delete[] A;      // Видалення масиву А
}

//  3.4: Робота з Vector
void Task_Vector_FromFile() {
    cout << "\n--- Завдання 3.4 (Vector) ---" << endl;
    ifstream fin("A.bin", ios::binary); // Відкриття бінарного файлу
    if (!fin) return; // Перевірка
    int size; // Змінна розміру
    fin.read((char*)&size, sizeof(int)); // Читання розміру
    vector<double> vec(size); // Створення вектора потрібного розміру
    fin.read((char*)vec.data(), size * sizeof(double)); // Читання даних у вектор
    fin.close(); // Закриття файлу
    cout << "Дані з вектора: ";
    for (double x : vec) cout << x << " "; // Вивід вектора в консоль
    cout << endl;
}

//  3.1: Введення вручну
void Task_TextFile() {
    cout << "--- Завдання 3.1 ---" << endl;
    double A[MAX_SIZE]; // Статичний масив
    int size = ConsoleInputSizeArray(MAX_SIZE); // Розмір
    for (int i = 0; i < size; i++) { cout << "A[" << i << "]="; cin >> A[i]; } // Ввід
    WriteArrayTextFile(size, A, "A.txt"); // Запис у текст
}

//  3.2: Випадкові числа
void Task_BinaryFile() {
    cout << "\n--- Завдання 3.2 ---" << endl;
    int size = ConsoleInputSizeArray(MAX_SIZE); // Розмір
    double* A = new double[size]; // Динамічний масив
    srand(time(0)); // Ініціалізація рандому
    for (int i = 0; i < size; i++) { A[i] = (rand() % 200 - 100) / 1.0; cout << A[i] << " "; } // Генерація
    WriteArrayBinFile(size, A, "A.bin"); // Запис у бінарний файл
    delete[] A; // Видалення
}

// головна функція
int main() {
    setlocale(LC_ALL, "Ukrainian"); // Підтримка кирилиці (залежить від терміналу)
    Task_TextFile();         // Виклик 3.1
    Task_BinaryFile();       // Виклик 3.2
    Task_Dynamic_Solutions(); // Виклик 3.3 (Ваші задачі)
    Task_Vector_FromFile();  // Виклик 3.4
    return 0; // Кінець програми
}
