#include <iostream>
#include <string>
#include <limits>
#include "Windows.h"

#include "Windows.h"

using namespace std;

struct City {
    string Name; // �������� ������
    int numInhabitants; // ��������� ������
};

struct Graph {
    City Cities[10]; // ������ ������� (������)
    int adj_matrix[10][10]; // ������� ���������
    int last = 0; // ������ ���������� �������� ������ ������
} G;

void createGraph() {
    if (G.last == 10) {
        cout << "���������� ������������ ���������� ������� (10)!" << endl;
        return;
    }

    int numCities;
    cout << "������� ���������� �������: ";
    cin >> numCities;

    if (G.last + numCities > 10) {
        cout << "��������� ���������� ������� ��������� ������������ ���������� (10)!" << endl;
        return;
    }

    for (int i = 0; i < numCities; ++i) {
        cout << "������� �������� ������ " << G.last + 1 << ": ";
        cin >> G.Cities[G.last].Name;
        cout << "������� ���������� ������� � ������ " << G.Cities[G.last].Name << ": ";
        cin >> G.Cities[G.last].numInhabitants;
        G.last++;
    }

    cout << "���� ������� ������!" << endl;
}

void addVertex() {
    if (G.last == 10) {
        cout << "���������� ������������ ���������� ������� (10)!" << endl;
        return;
    }

    cout << "������� �������� ������ ������: ";
    cin >> G.Cities[G.last].Name;
    cout << "������� ���������� ������� � ����� ������: ";
    cin >> G.Cities[G.last].numInhabitants;
    G.last++;

    cout << "������� ������� ���������!" << endl;
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
    cout << "������� �������� ������ ��� ��������: ";
    cin >> cityName;

    int index = findCityIndex(cityName);

    if (index == -1) {
        cout << "����� �� ������!" << endl;
        return;
    }

    for (int i = index; i < G.last - 1; ++i) {
        G.Cities[i] = G.Cities[i + 1];
    }
    G.last--;

    cout << "������� ������� �������!" << endl;
}

void addEdge() {
    string from, to;
    cout << "������� �������� ������� ��� ���������� (������ ����): ";
    cin >> from >> to;

    int fromIndex = findCityIndex(from);
    int toIndex = findCityIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        cout << "�������� �������� ������!" << endl;
        return;
    }

    cout << "������� ���������� ����� " << from << " � " << to << ": ";
    int distance;
    cin >> distance;

    G.adj_matrix[fromIndex][toIndex] = distance;
    G.adj_matrix[toIndex][fromIndex] = distance;

    cout << "����� ������� ���������!" << endl;
}

void removeEdge() {
    string from, to;
    cout << "������� �������� ������� ��� ������������ (������ ����): ";
    cin >> from >> to;

    int fromIndex = findCityIndex(from);
    int toIndex = findCityIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        cout << "�������� �������� ������!" << endl;
        return;
    }

    G.adj_matrix[fromIndex][toIndex] = 0;
    G.adj_matrix[toIndex][fromIndex] = 0;

    cout << "����� ������� �������!" << endl;
}

void displayNeighbors() {
    cout << "���������� � �������:" << endl;
    for (int i = 0; i < G.last; ++i) {
        cout << "������ ������ " << G.Cities[i].Name << ": ";
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
    cout << "������� �������� ������ ��� �������: ";
    cin >> cityName;

    int index = findCityIndex(cityName);

    if (index == -1) {
        cout << "����� �� ������!" << endl;
        return;
    }

    int minPopulation = INT_MAX; // ���������� INT_MAX �� ������������� ����� <limits>
    string minCityName;

    cout << "������ ������ " << cityName << ": ";
    for (int j = 0; j < G.last; ++j) {
        if (G.adj_matrix[index][j] != 0) {
            cout << G.Cities[j].Name << " ";
            if (G.Cities[j].numInhabitants < minPopulation) {
                minPopulation = G.Cities[j].numInhabitants;
                minCityName = G.Cities[j].Name;
            }
        }
    }

    cout << endl << "����� � ����������� ���������� ����� �������: " << minCityName << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\n------ ���� ------\n";
        cout << "1. ������� ����\n";
        cout << "2. �������� �������\n";
        cout << "3. ������� �������\n";
        cout << "4. �������� �����\n";
        cout << "5. ������� �����\n";
        cout << "6. ������� �������\n";
        cout << "7. ������\n";
        cout << "8. �����\n";
        cout << "������� ��� �����: ";
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
            cout << "�����...\n";
            break;
        default:
            cout << "�������� �����! ����������, ������� �������������� �������.\n";
            break;
        }
    } while (choice != 8);

    return 0;
}
