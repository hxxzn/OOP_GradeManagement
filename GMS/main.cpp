#include <iostream>
#include <string>
#include "mode.cpp" // mode.cpp 포함

using namespace std;

int main() {
    

    string studentFile = "./관리자_파일/students.txt";
    string professorFile = "./관리자_파일/professors.txt";
    string adminFile="./관리자_파일/admin.txt";

    UserManager studentManager(studentFile);
    UserManager professorManager(professorFile);


    while (true) {
    main_display();
    int inputId;
    string inputName;

    cout << "ID(or 학번)을 입력하세요. 종료를 원하시면 0을 입력하세요: "; //로그인
    cin >> inputId;
     if (inputId == 0) {
        break;
    } 
    cout << "이름을 입력하세요: ";
    cin >> inputName;
    cout << "\n\n";




    if (verifyInFile(studentFile, inputId, inputName)) { //학생으로 로그인
        studentMode(inputId, inputName);
    } 
    else if (verifyInFile(professorFile, inputId, inputName)) { //교수로 로그인
        professorMode(inputId, inputName);
    } 
    else if (verifyInFile(adminFile, inputId, inputName)) { //관리자로 로그인
        adminMode(studentManager, professorManager);
    } 
    else {
        cout << "사용자가 존재하지 않습니다.\n" << endl;
    }

    // return 0;
    }
}