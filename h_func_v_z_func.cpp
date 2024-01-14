#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Функция для вычисления хеш-значения строки
long long computeHash(const string& str) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hashValue = 0;
    long long p_pow = 1;

    for (char c : str) {
        hashValue = (hashValue * p + (c - 'a' + 1)) % m;
    }

    return hashValue;
}

// Функция для вычисления Z-функции
vector<int> computeZFunction(const string& str) {
    int n = str.length();
    vector<int> z(n, 0);

    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && str[z[i]] == str[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

// Функция для подсчета вхождений подстроки с использованием хеш-функции
int countSubstringHash(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    long long patternHash = computeHash(pattern);

    int count = 0;
    for (int i = 0; i <= textLength - patternLength; ++i) {
        string subtext = text.substr(i, patternLength);
        if (computeHash(subtext) == patternHash) {
            ++count;
        }
    }

    return count;
}

// Функция для подсчета вхождений подстроки с использованием Z-функции
int countSubstringZFunction(const string& text, const string& pattern) {
    string concatenated = pattern + "$" + text;
    vector<int> zValues = computeZFunction(concatenated);

    int patternLength = pattern.length();
    int count = 0;
    for (int i = patternLength + 1; i < concatenated.length(); ++i) {
        if (zValues[i] == patternLength) {
            ++count;
        }
    }

    return count;
}

int main() {
    // Чтение значений строки из файла
    ifstream textFile("text_file.txt");
    string text;
    if (textFile.is_open()) {
        getline(textFile, text);
        textFile.close();
    } else {
        cout << "Не удалось открыть файл с текстом." << endl;
        return 1;
    }

    // Чтение значения подстроки из файла
    ifstream patternFile("pattern_file.txt");
    string pattern;
    if (patternFile.is_open()) {
        getline(patternFile, pattern);
        patternFile.close();
    } else {
        cout << "Не удалось открыть файл с подстрокой." << endl;
        return 1;
    }

    // Измерение времени выполнения для хеш-функции
    clock_t startHash = clock();
    int hashCount = countSubstringHash(text, pattern);
    clock_t endHash = clock();

    // Измерение времени выполнения для Z-функции
    clock_t startZFunction = clock();
    int zFunctionCount = countSubstringZFunction(text, pattern);
    clock_t endZFunction = clock();

    // Вычисление длительности выполнения в секундах
    double durationHash = double(endHash - startHash) / CLOCKS_PER_SEC;
    double durationZFunction = double(endZFunction - startZFunction) / CLOCKS_PER_SEC;

    // Вывод результатов
    cout << "Текст: " << text << endl;
    cout << "Подстрока: " << pattern << endl;
    cout << "Количество вхождений (Хеш-функция): " << hashCount << endl;
    cout << "Время выполнения (Хеш-функция): " << durationHash << " секунд" << endl;

    cout << "Количество вхождений (Z-Функция): " << zFunctionCount << endl;
    cout << "Время выполнения (Z-Функция): " << durationZFunction << " секунд" << endl;

    return 0;
}