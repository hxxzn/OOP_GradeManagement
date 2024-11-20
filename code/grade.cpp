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

    map<string, double> finalScores; // 학생 ID와 최종 점수 저장
    vector<pair<string, double>> rankList; // 등수 계산 결과 저장
    map<string, map<string, int>> studentGrades;

    double midScore; // 중간 
    double finalScore; // 기말
    double assignmentScore; // 과제
    double attendanceScore; // 출석
    double overallScore; // 최종 성적...

public:
    // 생성자
    Grade(const string& cName, const string& cID, const string& sID)
        : courseName(cName), courseID(cID), studentID(sID),
        midScore(0), finalScore(0), assignmentScore(0), attendanceScore(0), overallScore(0) {}


    // 학생 성적을 가져와 map에 저장하는 함수
    void setGradeMap(File& file) {
        vector<vector<string>> data = file.getCSV();

        for (size_t i = 1; i < data.size(); ++i) {
            string studentID = data[i][3];
            map<string, int> grades;
            grades["중간고사"] = stoi(data[i][4]);
            grades["기말고사"] = stoi(data[i][5]);
            grades["과제"] = stoi(data[i][6]);
            grades["출석"] = stoi(data[i][7]);
            studentGrades[studentID] = grades;
        }
        cout << "성적이 성공적으로 저장되었습니다." << endl;
    }

    // 가중치 반영 성적 계산 함수
    void calculateScore(const Professor& professor, const string& studentID) {
        if (studentGrades.find(studentID) == studentGrades.end()) {
            cout << "오류: 해당 학번의 학생 성적 데이터가 없습니다." << endl;
            return;
        }

        const map<string, double>& gradeWeights = professor.getGradeWeights();
        double midtermWeight = gradeWeights.at("중간고사");
        double finalWeight = gradeWeights.at("기말고사");
        double assignmentWeight = gradeWeights.at("과제");
        double attendanceWeight = gradeWeights.at("출석");

        midScore = studentGrades[studentID]["중간고사"];
        finalScore = studentGrades[studentID]["기말고사"];
        assignmentScore = studentGrades[studentID]["과제"];
        attendanceScore = studentGrades[studentID]["출석"];

        overallScore = (midScore * midtermWeight / 100) +
            (finalScore * finalWeight / 100) +
            (assignmentScore * assignmentWeight / 100) +
            (attendanceScore * attendanceWeight / 100);

        // 최종 점수를 finalScores에 저장
        finalScores[studentID] = overallScore;

        cout << "최종 성적 계산 완료: " << overallScore << endl;
    }




};
