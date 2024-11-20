#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "file.cpp"
#include "professor.cpp"

using namespace std;

class Grade {
private:

    string courseName;
    string courseID;
    string studentID;

    map<string, double> finalScores; // �л� ID�� ���� ���� ����
    vector<pair<string, double>> rankList; // ��� ��� ��� ����
    map<string, map<string, int>> studentGrades;

    double midScore; // �߰� 
    double finalScore; // �⸻
    double assignmentScore; // ����
    double attendanceScore; // �⼮
    double overallScore; // ���� ����...

public:
    // ������
    Grade(const string& cName, const string& cID, const string& sID)
        : courseName(cName), courseID(cID), studentID(sID),
        midScore(0), finalScore(0), assignmentScore(0), attendanceScore(0), overallScore(0) {}


    // �л� ������ ������ map�� �����ϴ� �Լ�
    void setGradeMap(File& file) {
        vector<vector<string>> data = file.getCSV();

        for (size_t i = 1; i < data.size(); ++i) {
            string studentID = data[i][3];
            map<string, int> grades;
            grades["�߰����"] = stoi(data[i][4]);
            grades["�⸻���"] = stoi(data[i][5]);
            grades["����"] = stoi(data[i][6]);
            grades["�⼮"] = stoi(data[i][7]);
            studentGrades[studentID] = grades;
        }
        cout << "������ ���������� ����Ǿ����ϴ�." << endl;
    }

    // ����ġ �ݿ� ���� ��� �Լ�
    void calculateScore(const Professor& professor, const string& studentID) {
        if (studentGrades.find(studentID) == studentGrades.end()) {
            cout << "����: �ش� �й��� �л� ���� �����Ͱ� �����ϴ�." << endl;
            return;
        }

        const map<string, double>& gradeWeights = professor.getGradeWeights();
        double midtermWeight = gradeWeights.at("�߰����");
        double finalWeight = gradeWeights.at("�⸻���");
        double assignmentWeight = gradeWeights.at("����");
        double attendanceWeight = gradeWeights.at("�⼮");

        midScore = studentGrades[studentID]["�߰����"];
        finalScore = studentGrades[studentID]["�⸻���"];
        assignmentScore = studentGrades[studentID]["����"];
        attendanceScore = studentGrades[studentID]["�⼮"];

        overallScore = (midScore * midtermWeight / 100) +
            (finalScore * finalWeight / 100) +
            (assignmentScore * assignmentWeight / 100) +
            (attendanceScore * attendanceWeight / 100);

        // ���� ������ finalScores�� ����
        finalScores[studentID] = overallScore;

        cout << "���� ���� ��� �Ϸ�: " << overallScore << endl;
    }




};
