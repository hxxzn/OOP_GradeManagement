#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

// �л� �Ǵ� ���� ������ �����ϴ� Ŭ����
class UserManager {
private:
    map<int, string> users;  // ID�� Ű��, �̸��� ������ ����
    string filename;         // ���� �̸�

public:
    UserManager(const string& file) : filename(file) {
        loadFromFile();
    }

    // ���Ͽ��� �����͸� �ҷ�����
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "������ �� �� �����ϴ�: " << filename << endl;
            return;
        }

        users.clear();  // ���� ������ �ʱ�ȭ
        int id;
        string name;
        while (inFile >> id >> name) {
            users[id] = name;
        }
        inFile.close();
    }

    // ���Ͽ� ����
    void saveToFile() {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "������ �� �� �����ϴ�: " << filename << endl;
            return;
        }

        for (const auto& user : users) {
            outFile << user.first << " " << user.second << endl;
        }
        outFile.close();
    }

    // ����� �߰�
    void addUser(int id, const string& name) {
        users[id] = name;
        saveToFile();
    }

    // ����� ����
    void deleteUser(int id) {
        if (users.erase(id)) {
            cout << "ID " << id << " ������.\n";
        }
        else {
            cout << "ID " << id << "��(��) ã�� �� �����ϴ�.\n";
        }
        saveToFile();
    }

    // ����� ����
    void modifyUser(int id, const string& newName) {
        if (users.find(id) != users.end()) {
            users[id] = newName;
            cout << "ID " << id << "�� �̸��� ������.\n";
            saveToFile();
        }
        else {
            cout << "ID " << id << "��(��) ã�� �� �����ϴ�.\n";
        }
    }

    // ����� ���
    void displayUsers() {
        for (const auto& user : users) {
            cout << "ID: " << user.first << " �̸�: " << user.second << endl;
        }
    }
};

#endif