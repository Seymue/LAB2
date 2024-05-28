#include <iostream>
#include <string>
#include <limits>
#include "Windows.h"

#include "Windows.h"

using namespace std;

struct City {
    string Name; // Название города
    int numInhabitants; // Население города
};

struct Graph {
    City Cities[10]; // список городов (вершин)
    int adj_matrix[10][10]; // матрица смежности
    int last = 0; // индекс последнего элемента списка вершин
} G;

void createGraph() {
    if (G.last == 10) {
        cout << "Достигнуто максимальное количество городов (10)!" << endl;
        return;
    }

    int numCities;
    cout << "Введите количество городов: ";
    cin >> numCities;

    if (G.last + numCities > 10) {
        cout << "Суммарное количество городов превышает максимальное количество (10)!" << endl;
        return;
    }

    for (int i = 0; i < numCities; ++i) {
        cout << "Введите название города " << G.last + 1 << ": ";
        cin >> G.Cities[G.last].Name;
        cout << "Введите количество жителей в городе " << G.Cities[G.last].Name << ": ";
        cin >> G.Cities[G.last].numInhabitants;
        G.last++;
    }

    cout << "Граф успешно создан!" << endl;
}

void addVertex() {
    if (G.last == 10) {
        cout << "Достигнуто максимальное количество городов (10)!" << endl;
        return;
    }

    cout << "Введите название нового города: ";
    cin >> G.Cities[G.last].Name;
    cout << "Введите количество жителей в новом городе: ";
    cin >> G.Cities[G.last].numInhabitants;
    G.last++;

    cout << "Вершина успешно добавлена!" << endl;
}

int findCityIndex(const string& cityName) {
    for (int i = 0; i < G.last; ++i) {
        if (G.Cities[i].Name == cityName) {
            return i;
        }
    }
    return -1;
}

void removeVertex() {
    string cityName;
    cout << "Введите название города для удаления: ";
    cin >> cityName;

    int index = findCityIndex(cityName);

    if (index == -1) {
        cout << "Город не найден!" << endl;
        return;
    }

    for (int i = index; i < G.last - 1; ++i) {
        G.Cities[i] = G.Cities[i + 1];
    }
    G.last--;

    cout << "Вершина успешно удалена!" << endl;
}

void addEdge() {
    string from, to;
    cout << "Введите название городов для соединения (откуда куда): ";
    cin >> from >> to;

    int fromIndex = findCityIndex(from);
    int toIndex = findCityIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        cout << "Неверное название города!" << endl;
        return;
    }

    cout << "Введите расстояние между " << from << " и " << to << ": ";
    int distance;
    cin >> distance;

    G.adj_matrix[fromIndex][toIndex] = distance;
    G.adj_matrix[toIndex][fromIndex] = distance;

    cout << "Ребро успешно добавлено!" << endl;
}

void removeEdge() {
    string from, to;
    cout << "Введите название городов для разъединения (откуда куда): ";
    cin >> from >> to;

    int fromIndex = findCityIndex(from);
    int toIndex = findCityIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        cout << "Неверное название города!" << endl;
        return;
    }

    G.adj_matrix[fromIndex][toIndex] = 0;
    G.adj_matrix[toIndex][fromIndex] = 0;

    cout << "Ребро успешно удалено!" << endl;
}

void displayNeighbors() {
    cout << "Информация о соседях:" << endl;
    for (int i = 0; i < G.last; ++i) {
        cout << "Соседи города " << G.Cities[i].Name << ": ";
        for (int j = 0; j < G.last; ++j) {
            if (G.adj_matrix[i][j] != 0) {
                cout << G.Cities[j].Name << " ";
            }
        }
        cout << endl;
    }
}

void query() {
    string cityName;
    cout << "Введите название города для запроса: ";
    cin >> cityName;

    int index = findCityIndex(cityName);

    if (index == -1) {
        cout << "Город не найден!" << endl;
        return;
    }

    int minPopulation = INT_MAX; // Используем INT_MAX из заголовочного файла <limits>
    string minCityName;

    cout << "Соседи города " << cityName << ": ";
    for (int j = 0; j < G.last; ++j) {
        if (G.adj_matrix[index][j] != 0) {
            cout << G.Cities[j].Name << " ";
            if (G.Cities[j].numInhabitants < minPopulation) {
                minPopulation = G.Cities[j].numInhabitants;
                minCityName = G.Cities[j].Name;
            }
        }
    }

    cout << endl << "Город с минимальным населением среди соседей: " << minCityName << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\n------ Меню ------\n";
        cout << "1. Создать граф\n";
        cout << "2. Добавить вершину\n";
        cout << "3. Удалить вершину\n";
        cout << "4. Добавить ребро\n";
        cout << "5. Удалить ребро\n";
        cout << "6. Вывести соседей\n";
        cout << "7. Запрос\n";
        cout << "8. Выйти\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createGraph();
            break;
        case 2:
            addVertex();
            break;
        case 3:
            removeVertex();
            break;
        case 4:
            addEdge();
            break;
        case 5:
            removeEdge();
            break;
        case 6:
            displayNeighbors();
            break;
        case 7:
            query();
            break;
        case 8:
            cout << "Выход...\n";
            break;
        default:
            cout << "Неверный выбор! Пожалуйста, введите действительный вариант.\n";
            break;
        }
    } while (choice != 8);

    return 0;
}
