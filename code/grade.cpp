#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Grade 클래스 정의
class Grade {
private:
    std::string studentID;   // 학번
    std::string studentName; // 학생명
    double midtermScore, finalScore, assignmentScore, attendanceScore; // 점수들
    double totalScore; // 최종 점수

public:
    // 생성자
    Grade(const std::string& id, const std::string& name,
        double mid, double fin, double assign, double attend)
        : studentID(id), studentName(name),
        midtermScore(mid), finalScore(fin),
        assignmentScore(assign), attendanceScore(attend),
        totalScore(0) {}

    // 총 점수 계산
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

// CSV 처리 함수
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

    std::vector<Grade> grades; // Grade 객체를 저장할 벡터

    while (std::getline(file, line)) {
        lineNumber++;
        std::istringstream stream(line);

        // 첫 번째 행 처리
        if (lineNumber == 1) {
            std::string midWeight, finalWeight, assignWeight, attendWeight;

            std::getline(stream, professorCode, ',');     // 교수 코드
            std::getline(stream, courseCode, ',');        // 강의 코드
            std::getline(stream, midWeight, ',');         // 중간고사 가중치
            std::getline(stream, finalWeight, ',');       // 기말고사 가중치
            std::getline(stream, assignWeight, ',');      // 과제 가중치
            std::getline(stream, attendWeight, ',');      // 출석 가중치

            // 문자열을 double로 변환
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
        // 세 번째 행 이후 데이터 처리
        else if (lineNumber >= 3) {
            std::string id, name, midStr, finalStr, assignStr, attendStr;

            std::getline(stream, id, ',');        // 학생 ID
            std::getline(stream, name, ',');      // 학생 이름
            std::getline(stream, midStr, ',');    // 중간고사 점수
            std::getline(stream, finalStr, ',');  // 기말고사 점수
            std::getline(stream, assignStr, ','); // 과제 점수
            std::getline(stream, attendStr, ','); // 출석 점수

            try {
                double midScore = std::stod(midStr);
                double finalScore = std::stod(finalStr);
                double assignScore = std::stod(assignStr);
                double attendScore = std::stod(attendStr);

                // Grade 객체 생성 및 벡터에 추가
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