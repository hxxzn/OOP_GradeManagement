#include <iostream>

using namespace std;


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class File {
private:
    string filename;
    vector<vector<string>> data;

public:
    // ������
    File(const string& fname) : filename(fname) {}

    // CSV ���� �ε� �Լ�
    void loadCSV() {
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                vector<string> row;
                stringstream ss(line);
                string cell;

                while (getline(ss, cell, ',')) {
                    row.push_back(cell);
                }
                data.push_back(row);
            }
            file.close();
        }
        else {
            cerr << "������ �� �� �����ϴ�." << endl;
        }
    }

    // ���� ���� ��� �Լ�
    void viewFile() const {
        for (const auto& row : data) {
            for (const auto& cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    // ���� ������ CSV �����͸� ��ȯ�ϴ� �Լ�
    vector<vector<string>> getCSV() const {
        return data;
    }
};