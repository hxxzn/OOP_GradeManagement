#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Grade Ŭ���� ����
class Grade {
private:
    std::string studentID;   // �й�
    std::string studentName; // �л���
    double midtermScore, finalScore, assignmentScore, attendanceScore; // ������
    double totalScore; // ���� ����

public:
    // ������
    Grade(const std::string& id, const std::string& name,
        double mid, double fin, double assign, double attend)
        : studentID(id), studentName(name),
        midtermScore(mid), finalScore(fin),
        assignmentScore(assign), attendanceScore(attend),
        totalScore(0) {}

    // �� ���� ���
    void calculateTotalScore(double midWeight, double finalWeight, double assignWeight, double attendWeight) {
        totalScore = midtermScore * midWeight +
            finalScore * finalWeight +
            assignmentScore * assignWeight +
            attendanceScore * attendWeight;
    }

    double getTotalScore() const {
        return totalScore;
    }

};

// CSV ó�� �Լ�
void processCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;

    std::string professorCode, courseCode;
    double midtermWeight = 0, finalWeight = 0, assignmentWeight = 0, attendanceWeight = 0;

    std::vector<Grade> grades; // Grade ��ü�� ������ ����

    while (std::getline(file, line)) {
        lineNumber++;
        std::istringstream stream(line);

        // ù ��° �� ó��
        if (lineNumber == 1) {
            std::string midWeight, finalWeight, assignWeight, attendWeight;

            std::getline(stream, professorCode, ',');     // ���� �ڵ�
            std::getline(stream, courseCode, ',');        // ���� �ڵ�
            std::getline(stream, midWeight, ',');         // �߰���� ����ġ
            std::getline(stream, finalWeight, ',');       // �⸻��� ����ġ
            std::getline(stream, assignWeight, ',');      // ���� ����ġ
            std::getline(stream, attendWeight, ',');      // �⼮ ����ġ

            // ���ڿ��� double�� ��ȯ
            try {
                midtermWeight = std::stod(midWeight);
                finalWeight = std::stod(finalWeight);
                assignmentWeight = std::stod(assignWeight);
                attendanceWeight = std::stod(attendWeight);
            }
            catch (const std::exception& e) {
                std::cerr << "Error: Invalid weight format in line 1." << std::endl;
                return;
            }
        }
        // �� ��° �� ���� ������ ó��
        else if (lineNumber >= 3) {
            std::string id, name, midStr, finalStr, assignStr, attendStr;

            std::getline(stream, id, ',');        // �л� ID
            std::getline(stream, name, ',');      // �л� �̸�
            std::getline(stream, midStr, ',');    // �߰���� ����
            std::getline(stream, finalStr, ',');  // �⸻��� ����
            std::getline(stream, assignStr, ','); // ���� ����
            std::getline(stream, attendStr, ','); // �⼮ ����

            try {
                double midScore = std::stod(midStr);
                double finalScore = std::stod(finalStr);
                double assignScore = std::stod(assignStr);
                double attendScore = std::stod(attendStr);

                // Grade ��ü ���� �� ���Ϳ� �߰�
                Grade grade(id, name, midScore, finalScore, assignScore, attendScore);
                grade.calculateTotalScore(midtermWeight, finalWeight, assignmentWeight, attendanceWeight);
                grades.push_back(grade);
            }
            catch (const std::exception& e) {
                std::cerr << "Error: Invalid score format in line " << lineNumber << "." << std::endl;
                continue;
            }
        }
    }

    file.close();

}