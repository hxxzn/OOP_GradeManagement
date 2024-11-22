#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // for std::accumulate
#include "grade.cpp"

class Course {
private:
    std::string courseID;       // 강의 코드
    std::string professorID;    // 교수 코드
    std::vector<Grade> grades;  // 학생 성적 목록

public:
    // 생성자
    Course(const std::string& cID, const std::string& pID)
        : courseID(cID), professorID(pID) {}

    // Grade 객체 추가
    void addGrade(const Grade& grade) {
        grades.push_back(grade);
    }

    // 통계 계산: 최소, 최대, 평균 점수
    void calculateStatistics(double& minScore, double& maxScore, double& meanScore) const {
        if (grades.empty()) {
            throw std::runtime_error("No grades available to calculate statistics.");
        }

        // 최종 점수 추출
        std::vector<double> scores;
        for (const auto& grade : grades) {
            scores.push_back(grade.getTotalScore());
        }

        // 최소값, 최대값 계산
        minScore = *std::min_element(scores.begin(), scores.end());
        maxScore = *std::max_element(scores.begin(), scores.end());

        // 평균 계산
        meanScore = std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
    }
};
