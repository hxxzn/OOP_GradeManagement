#include <iostream>
#include <string>
#include "course.cpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// User 클래스 정의----------------------------------------------------------------------------------------------------
class User {
protected:
    string name;  // 사용자 이름
    string id;       // 사용자 ID

public:
    // 생성자
    User(const string& userName, string userId) : name(userName), id(userId) {}

    // 통계 보기 (기본 구현, 필요 시 재정의 가능)
    virtual void viewStatistics() {
        cout << "User: " << name << " (ID: " << id << ")" << endl;
    }

    // 가상 소멸자 (다형성을 위한 설정)
    virtual ~User() {}
};





// Student 클래스 정의 (User 상속)-----------------------------------------------------------------------------------------
class Student : public User {

private:
    Course enrolledCourse;
    vector<vector<string>> data;

    
public:
    // 생성자
    // 생성자 (Course 객체를 초기화)
    Student(const string& studentName, string studentId, const Course& course)
        : User(studentName, studentId), enrolledCourse(course) {

            data = course.raw_data;

        }

    // 소멸자
    ~Student() {}

    void getGradedetail() {
    
        // 성적 통계 계산 
        enrolledCourse.calculateGrades();

        // 성적 및 통계 출력
        cout << endl;
        // course.printGradesAndStatistics();

        // // 특정 학생의 성적 및 통계 출력
        cout << endl;
        
        enrolledCourse.getGradedetailByStudentId(id);
        // enrolledCourse.viewStatistics(id);
        cout << "\n\n\n" << endl;
    }


    void getGrade() {

        enrolledCourse.calculateGrades();
        
        enrolledCourse.getGradeByStudentId(id);

    }



    void viewStatistics() {
    enrolledCourse.viewStatistics(id);
    }


    void submitAppeal(const string& appealTarget, const string& route) {
    bool foundStudent = false;
    File file(route);

    for (auto& row : data) {
        if (row.size() > 6 && row[1] == id) { // 학번 확인
            foundStudent = true;
            bool dataChanged = false;


            if (row[6] != "1") {
                row[6] = "1"; // 이의신청 상태를 '1'로 설정
                dataChanged = true;
            }

            if (row[7] != appealTarget) {
                row[7] = appealTarget; // 이의신청 대상 수정
                dataChanged = true;
            }

            cout << "학생 " << row[0] << " (학번: " << id
                 << ")의 이의신청이 성공적으로 수정되었습니다." << endl;


            // 데이터 변경 시에만 파일 저장
            if (dataChanged) {
                file.saveToFile(route, data);
                cout << "변경 사항이 파일에 저장되었습니다." << endl;
                cout << "\n\n\n" << endl;
            } else {
                cout << "변경 사항이 없습니다. 파일 저장을 건너뜁니다." << endl;
            }
            return;
        }
    }
    if (!foundStudent) {
        cout << "해당 학번(" << id << ")을 찾을 수 없습니다." << endl;
    }
  }   
};

// Professor 클래스 정의 (User 상속)----------------------------------------------------------------------------------------------------
class Professor : public User{
private:
    File file; // File 클래스 객체
    vector<vector<string>> data;

public:
    // 생성자
Professor(const string& name, const string& id, const string& filename)
        : User(name, id), file(filename) {
        file.loadCSV();
        data = file.getCSV();
    }

// 가중치 수정 함수
void weight_fix(const string& courseName, const string& section, double newMidWeight, double newFinalWeight, double newTaskWeight, double newAttendanceWeight) {
    // 백분율을 0 ~ 1 범위로 변환
    newMidWeight /= 100.0;
    newFinalWeight /= 100.0;
    newTaskWeight /= 100.0;
    newAttendanceWeight /= 100.0;

    if (data.empty()) {
        cout << "해당 강의가 존재하지 않습니다" << endl;
    }
    else {
        for (auto& row : data) {
            if (row.size() >= 4 && row[0] == courseName && row[1] == section) {
                // 변환된 값을 그대로 저장
                row[3] = to_string(newMidWeight);
                row[4] = to_string(newFinalWeight);
                row[5] = to_string(newTaskWeight);
                row[6] = to_string(newAttendanceWeight);
                cout << "가중치가 성공적으로 수정되었습니다." << endl;
                return;
            }
        }
        cerr << "과목 이름 또는 분반을 찾을 수 없습니다." << endl;
    }
}


    // a,b,c 함수
    void abc_fix(const string& courseName, const string& section, double AWeight, double BWeight, double CWeight, double DWeight, double FWeight) {
    // 백분율로 변환
    AWeight /= 100.0;
    BWeight /= 100.0;
    CWeight /= 100.0;
    DWeight /= 100.0;
    FWeight /= 100.0;

    // 데이터에서 과목 이름과 분반을 찾음
    for (auto& row : data) {
        if (row.size() >= 4 && row[0] == courseName && row[1] == section) {
            // 성적 비율 값 수정
            row[7] = to_string(AWeight);
            row[8] = to_string(BWeight);
            row[9] = to_string(CWeight);
            row[10] = to_string(DWeight);
            row[11] = to_string(FWeight);

            cout << "성적 비율이 성공적으로 수정되었습니다." << endl;
            return;  // 수정 후 종료
        }
    }

    // 과목 이름 또는 분반을 찾을 수 없는 경우
    cerr << "과목 이름 또는 분반을 찾을 수 없습니다." << endl;
}


    // 학생 점수 수정 함수
    void score_fix(const string& courseName, const string& section, const string& studentId, const string& category, int newScore) {
        bool courseFound = false;
        for (auto& row : data) {
            if (row.size() >= 4 && row[0] == courseName && row[1] == section) {
                courseFound = true;
                // 학생 데이터 시작 위치를 찾음
                size_t studentDataStartIndex = find(data.begin(), data.end(), row) - data.begin() + 2;
                for (size_t i = studentDataStartIndex; i < data.size(); ++i) {
                    if (data[i][1] == studentId) {
                        // 카테고리에 따라 점수 수정
                        if (category == "중간") {
                            data[i][2] = to_string(newScore);
                        } else if (category == "기말") {
                            data[i][3] = to_string(newScore);
                        } else if (category == "과제") {
                            data[i][4] = to_string(newScore);
                        } else if (category == "출석") {
                            data[i][5] = to_string(newScore);
                        } else {
                            cerr << "잘못된 카테고리입니다." << endl;
                            return;
                        }
                        cout << "학생 점수가 성공적으로 수정되었습니다." << endl;
                        data[i][6] = "0";
                        data[i][7] = ""; //성적 수정 시 이의 신청 칸 비우기
                        return;
                    }
                }
                cerr << "해당 학번을 찾을 수 없습니다." << endl;
                return;
            }
        }
        if (!courseFound) {
            cerr << "과목 이름 또는 분반을 찾을 수 없습니다." << endl;
        }
    }

    // 데이터 저장 함수
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    file << row[i];
                    if (i != row.size() - 1) file << ",";
                }
                file << endl;
            }
            file.close();
            cout << "변경 사항이 파일에 저장되었습니다." << endl;
        } else {
            cerr << "파일을 저장할 수 없습니다!" << endl;
        }
    }


void view_appeal(const string& courseName, const string& section) {
        bool foundCourse = false;
        cout << "\n\n" << endl;
        cout << "<<이의신청을 한 학생 목록>>\n" << endl;
        cout << " <이름>\t  <학번>\t<이의신청 대상>" << endl;

        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i][0] == courseName && data[i][1] == section) {
                foundCourse = true;

                // 학생 데이터 시작 위치를 찾기
                for (size_t j = i + 2; j < data.size(); ++j) {
                    if (data[j].size() > 6 && data[j][6] == "1") { // 이의신청 여부 확인
                        string studentName = data[j][0];
                        string studentId = data[j][1];
                        string appealTarget = data[j].size() > 7 ? data[j][7] : "없음";
                        cout << studentName << "\t" << studentId << "\t" << appealTarget << endl;
                    }
                }
                return; // 과목과 분반이 일치하는 경우만 확인 후 종료
            }
        }

        if (!foundCourse) {
            cout << "해당 과목(" << courseName << ")과 분반(" << section << ")에 대한 정보를 찾을 수 없습니다." << endl;
        }
    }


    void viewData() {
        cout << "\n   <<수강 인원>>\n\n";
        cout << "╔═════════════════════════════════════════╗" << endl; //════════════════════════
        cout << "║|이름|   |학번|   |중간||기말||과제||출석║" << endl;
        for (size_t i = 3; i < data.size(); ++i) {
            cout << "║"; // 4번째 행부터 (0-based index)
            for (size_t j = 0; j < 6; ++j) {       // 앞의 2열만
                cout << data[i][j] << "   ";
            }
            cout << "║";
            cout << endl;
        }
        cout << "╚═════════════════════════════════════════╝" << endl;
    }


};
