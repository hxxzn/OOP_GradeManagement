#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>  // sort �Լ��� ����ϱ� ���� ���
#include <limits>     // �ִ�, �ּҰ��� ����ϱ� ���� ���
#include "grade.cpp"   // ���� ���� �������� ��� ����

using namespace std;

class Course {
private:
    string courseName;
    string courseID;
    string professorName;

    map<string, map<string, int>> studentGrades;  // �л� ���� ����
    map<string, map<string, int>> studentRank;    // �л� ��� ����

    double meanScore[4];  // �������
    int maxScore[4];      // �ִ�����
    int minScore[4];      // �ּ�����
    size_t studentCount;  // �л� ��

public:
    // ������
    Course(const string& cName, const string& cID, const string& pName)
        : courseName(cName), courseID(cID), professorName(pName), studentCount(0) {
        for (int i = 0; i < 4; ++i) {
            maxScore[i] = numeric_limits<int>::min();
            minScore[i] = numeric_limits<int>::max();
            meanScore[i] = 0.0;
        }
    }

    

    // �� �׸񺰷� ����� ����ϴ� �Լ�
    void calculateRankAndStatistics() {
        vector<pair<string, int>> midtermScores;
        vector<pair<string, int>> finalScores;
        vector<pair<string, int>> assignmentScores;
        vector<pair<string, int>> attendanceScores;

        int sum[4] = { 0, 0, 0, 0 };  // �հ踦 ����ϱ� ���� �迭

        // �л����� ������ ���Ϳ� ���� (�й�, ����)
        for (const auto& student : studentGrades) {
            midtermScores.push_back({ student.first, student.second.at("�߰����") });
            finalScores.push_back({ student.first, student.second.at("�⸻���") });
            assignmentScores.push_back({ student.first, student.second.at("����") });
            attendanceScores.push_back({ student.first, student.second.at("�⼮") });

            // �� �׸񺰷� �հ� ���, �ִ밪, �ּҰ� ����
            int scores[4] = { student.second.at("�߰����"), student.second.at("�⸻���"), student.second.at("����"), student.second.at("�⼮") };
            for (int i = 0; i < 4; ++i) {
                sum[i] += scores[i];
                if (scores[i] > maxScore[i]) maxScore[i] = scores[i];
                if (scores[i] < minScore[i]) minScore[i] = scores[i];
            }
        }

        // ��� ���
        for (int i = 0; i < 4; ++i) {
            meanScore[i] = static_cast<double>(sum[i]) / studentCount;
        }

        // �� ������ ������������ ����
        auto compare = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
            };
        sort(midtermScores.begin(), midtermScores.end(), compare);
        sort(finalScores.begin(), finalScores.end(), compare);
        sort(assignmentScores.begin(), assignmentScores.end(), compare);
        sort(attendanceScores.begin(), attendanceScores.end(), compare);

        // ��� ��� �� ����
        for (size_t i = 0; i < midtermScores.size(); ++i) {
            studentRank[midtermScores[i].first]["�߰����"] = i + 1;
            studentRank[finalScores[i].first]["�⸻���"] = i + 1;
            studentRank[assignmentScores[i].first]["����"] = i + 1;
            studentRank[attendanceScores[i].first]["�⼮"] = i + 1;
        }

        cout << "����� ��谡 ���������� ���Ǿ����ϴ�." << endl;
    }

    // ������ ���, ��� ��� ��� �Լ�
    void printGradesAndStatistics() const {
        const string labels[4] = { "�߰����", "�⸻���", "����", "�⼮" };

        for (const auto& student : studentGrades) {
            cout << "�й�: " << student.first << endl;
            for (int i = 0; i < 4; ++i) {
                string category = labels[i];
                cout << category << ": " << student.second.at(category)
                    << " (Rank: " << studentRank.at(student.first).at(category) << "/" << studentCount
                    << ", Min: " << minScore[i] << ", Max: " << maxScore[i]
                    << ", Mean: " << meanScore[i] << ")" << endl;
            }
            cout << endl;
        }
    }

    // Ư�� �л��� ������ ��� ��� �Լ�
    void printStudentStatistics(const string& studentID) const {
        if (studentGrades.find(studentID) == studentGrades.end()) {
            cout << "�ش� �й�(" << studentID << ")�� �л� ������ �����ϴ�." << endl;
            return;
        }

        const string labels[4] = { "�߰����", "�⸻���", "����", "�⼮" };

        cout << "�й�: " << studentID << endl;
        for (int i = 0; i < 4; ++i) {
            string category = labels[i];
            cout << category << ": " << studentGrades.at(studentID).at(category)
                << " (Rank: " << studentRank.at(studentID).at(category) << "/" << studentCount
                << ", Min: " << minScore[i] << ", Max: " << maxScore[i]
                << ", Mean: " << meanScore[i] << ")" << endl;
        }
        cout << endl;
    }
};
