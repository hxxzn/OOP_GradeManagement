#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // for std::accumulate
#include "grade.cpp"

class Course {
private:
    std::string courseID;       // ���� �ڵ�
    std::string professorID;    // ���� �ڵ�
    std::vector<Grade> grades;  // �л� ���� ���

public:
    // ������
    Course(const std::string& cID, const std::string& pID)
        : courseID(cID), professorID(pID) {}

    // Grade ��ü �߰�
    void addGrade(const Grade& grade) {
        grades.push_back(grade);
    }

    // ��� ���: �ּ�, �ִ�, ��� ����
    void calculateStatistics(double& minScore, double& maxScore, double& meanScore) const {
        if (grades.empty()) {
            throw std::runtime_error("No grades available to calculate statistics.");
        }

        // ���� ���� ����
        std::vector<double> scores;
        for (const auto& grade : grades) {
            scores.push_back(grade.getTotalScore());
        }

        // �ּҰ�, �ִ밪 ���
        minScore = *std::min_element(scores.begin(), scores.end());
        maxScore = *std::max_element(scores.begin(), scores.end());

        // ��� ���
        meanScore = std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
    }
};
