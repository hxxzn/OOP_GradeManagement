#include <iostream>
using namespace std;


void main_display() {
    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║   Welcome to the Grade Management System (GMS)!          ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║   What you can do based on your role:                    ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║     [1] 학생(Student):                                   ║" << endl;
    cout << "║         - View your grades                               ║" << endl;
    cout << "║         - Analyze your performance statistics            ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║     [2] 교수(Professor):                                 ║" << endl;
    cout << "║         - View and manage student grades                 ║" << endl;
    cout << "║         - Analyze class performance                      ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║     [3] 관리자(Admin):                                   ║" << endl;
    cout << "║         - Add or remove users                            ║" << endl;
    cout << "║         - Manage user and grade data                     ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
}

void student_display() {
    
    cout << "┌───────────────────────────────┐" << endl;
    cout << "│       성 적 관 리 시 스 템    │" << endl;
    cout << "├───────────────────────────────┤" << endl;
    cout << "│  환영합니다, " << "학생" << "님!          │" << endl;
    cout << "├───────────────────────────────┤" << endl;
    cout << "│  1. 학점 보기                 │" << endl;
    cout << "│  2. 세부 성적 보기            │" << endl;
    cout << "│  3. 이의신청하기              │" << endl;
    cout << "│  0. 종료                      │" << endl;
    cout << "└───────────────────────────────┘" << endl;
    cout << "선택: ";
}



void professor_display() {

    cout << "\n\n" << endl;
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║                성적 관리 시스템                  ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║  환영합니다, " << " 교수님!                            ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║  1. 성적 가중치 입력                             ║" << endl;
    cout << "║  2. 성적 비율 입력 (예: A: 35%, B: 50%, ...)     ║" << endl;
    cout << "║  3. 성적 수정                                    ║" << endl;
    cout << "║  4. 이의 신청 보기                               ║" << endl;
    cout << "║  5. 수강 인원 및 성적 보기                       ║" << endl;
    cout << "║  0. 종료                                         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << ">> 메뉴를 선택하세요: ";
}


void admin_display() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║               관리자님 환영합니다!               ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║              할 일을 선택해주세요!               ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║  1. 학생 추가                                    ║" << endl;
    cout << "║  2. 교수 추가                                    ║" << endl;
    cout << "║  3. 학생 삭제                                    ║" << endl;
    cout << "║  4. 교수 삭제                                    ║" << endl;
    cout << "║  5. 학생 수정                                    ║" << endl;
    cout << "║  6. 교수 수정                                    ║" << endl;
    cout << "║  7. 학생 출력                                    ║" << endl;
    cout << "║  8. 교수 출력                                    ║" << endl;
    cout << "║  0. 종료                                         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << ">> 선택: ";
}

void displayCourseSelection_prof(const vector<string>& fullCourseName) {
    cout << "\n\n" << endl;
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║               교수님 강의 선택 화면              ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║    아래 목록에서 관리할 강의를 선택하세요!       ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║                                                  ║"<<endl;

    // 강의 목록 표시
    for (size_t i = 0; i < fullCourseName.size(); ++i) {
        cout << "║  " << setw(2) <<i + 1 << ". " << setw(40) << left << fullCourseName[i] << "         ║" << endl;
    }

    // 종료 옵션 추가
    cout << "║  0. 종료                                         ║" << endl;
    cout << "║                                                  ║"<<endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << ">> 번호를 입력하세요: ";
}

void displayCourseSelection_stu(const vector<string>& fullCourseName) {

        cout << "\n\n";
        cout << "╔══════════════════════════════════════════════════╗" << endl;
        cout << "║               학생님 강의 선택 화면              ║" << endl;
        cout << "╠══════════════════════════════════════════════════╣" << endl;
        cout << "║    아래 목록에서 확인할 강의를 선택하세요!       ║" << endl;
        cout << "╠══════════════════════════════════════════════════╣" << endl;
        cout << "║                                                  ║"<<endl;
        cout << "║  1. 전 과목 학점 출력                             ║" << endl;


        for (size_t i = 0; i < fullCourseName.size(); ++i) {
            cout << "║  " << setw(2) << i + 2 << ". " << setw(40) << left << fullCourseName[i] << "         ║" << endl;
        }

        cout << "║  0. 종료                                         ║" << endl;
        cout << "║                                                  ║"<<endl;
        cout << "╚══════════════════════════════════════════════════╝" << endl;
        cout << ">> 번호를 입력하세요: ";
        }