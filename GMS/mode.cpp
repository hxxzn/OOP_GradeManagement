#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>
#include "UserManager.cpp"
#include "Users.cpp"
#include "display.cpp"

using namespace std;
namespace fs = std::filesystem;

vector<vector<string>> loadCSV1(const string& filePath) {
    vector<vector<string>> data;
    ifstream file(filePath);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        
        while (getline(ss, value, ',')) {
            row.push_back(value);
        }
        
        data.push_back(row);
    }
    
    return data;
}

// 파일에서 학번과 이름을 확인하는 함수
bool verifyInFile(const string& filePath, int inputId, const string& inputName) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filePath << endl;
        return false;
    }

    int id;
    string name;
    while (file >> id >> name) {
        if (id == inputId && name == inputName) {
            return true;
        }
    }

    return false;
}












void studentMode(int inputId, const string& inputName) {
    while (true) {
        vector<string> validFiles;       // 해당 학생의 ID가 포함된 파일 경로 저장
        vector<string> courseNames;     // 강의명 저장
        vector<string> classNumbers;    // 분반 정보 저장
        vector<string> fullCourseName;  // 강의명_분반 저장
        vector<string> fullFilePaths;   // 파일 경로 저장

        // 학생 ID 변환
        string studentID = to_string(inputId);

        for (const auto& entry : fs::directory_iterator("./grade_csv/")) { //디렉토리 탐색
            string filePath = entry.path().string();

            // CSV 파일만 처리
            if (filePath.substr(filePath.find_last_of(".") + 1) == "csv") {
                vector<vector<string>> csvData = loadCSV1(filePath);

                // CSV 데이터 확인
                for (size_t i = 1; i < csvData.size(); ++i) {
                    if (csvData[i].size() > 1 && csvData[i][1] == studentID) { // 2번째 열과 비교
                        validFiles.push_back(filePath);
                        string coursename = csvData[1][0];  // 강의명
                        string classnum = csvData[1][1];   // 분반 정보
                        fullCourseName.push_back(coursename + "_" + classnum);
                        fullFilePaths.push_back(filePath);
                        courseNames.push_back(coursename);
                        classNumbers.push_back(classnum);
                        break; // 학생 ID는 중복될 수 없으므로 탐색 종료
                    }
                }
            }
        }

        // 파일이 없는 경우
        if (validFiles.empty()) {
            cout << "학생의 ID와 일치하는 강의가 없습니다." << endl;
            break;
        }

        displayCourseSelection_stu(fullCourseName);
        
        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "학생 모드를 종료합니다.\n" << endl;
            break;
        }

        if (choice == 1) {
            vector<Student> students; // 학생 객체들을 담을 벡터

            // 전 과목 학점 출력
            cout << "┌─────────────────────────────────────┐"<<endl;
            cout << "│           전 과목 학점 출력         │" << endl;
            cout << "├─────────────────────────────────────┤" << endl;
            for (size_t i = 0; i < fullCourseName.size(); ++i) {
                string selectedFilePath = fullFilePaths[i];
                string selectedFilename = fullCourseName[i];
                string course_name = courseNames[i];
                string class_num = classNumbers[i];

                File file(selectedFilePath);
                file.loadCSV();
                if (file.getCSV().empty()) {
                    cout << "해당하는 강의가 존재하지 않습니다." << endl;
                    continue;
                }

                Course course(file.getCSV());
                Student s(inputName, studentID, course);
                cout << "└─────────────────────────────────────┘"<<endl;
                cout << "│"<< selectedFilename << "                         │"<<endl;
                s.getGrade();  // 전 과목 학점 출력
            }
            cout << "└─────────────────────────────────────┘";
            continue;
        }

        if (choice < 1 || choice > fullCourseName.size()) {
            cout << "잘못된 번호입니다. 다시 시도하세요." << endl;
            continue;
        }

        // 선택된 강의 정보 가져오기
        string selectedFilePath = fullFilePaths[choice - 2];
        string selectedFilename = fullCourseName[choice - 2];
        string course_name = courseNames[choice - 2];
        string class_num = classNumbers[choice - 2];

        File file(selectedFilePath);
        file.loadCSV();
        if (file.getCSV().empty()) {
            cout << "해당하는 강의가 존재하지 않습니다." << endl;
            continue;
        }

        Course course(file.getCSV());
        Student s(inputName, studentID, course);

        // 학생 작업 선택
        student_display();
        cin >> choice;

        if (choice == 0) {
            cout << "강의 선택으로 돌아갑니다.\n" << endl;
            break;
        } else if (choice == 1) {
            s.getGradedetail();
        } else if (choice == 2) {
            s.viewStatistics();
        } else if (choice == 3) {
            string category;
            cout << "중간, 기말, 과제, 출석 중 수정할 부분을 입력하시오: ";
            cin >> category;
            s.submitAppeal(category, selectedFilePath);

        } else {
            cout << "잘못된 입력입니다." << endl;
        }
    }
}

// 교수 모드
void professorMode(int inputId, const string& inputName) {
    while (true) {
        int choice2;
        string studentId;

        vector<string> validFiles;
        vector<string> courseNames;         // 강의명 저장
        vector<string> ClassNumbers;        // 분반 정보 저장
        vector<string> fullCourseName;      // 강의명_분반 정보 저장
        vector<string> fullFilePaths;       // 파일 경로 저장

        // ./grade_csv/ 디렉토리 내의 파일을 탐색
        for (const auto& entry : fs::directory_iterator("./grade_csv/")) {
            string filePath = entry.path().string();

            // CSV 파일만 처리
            if (filePath.substr(filePath.find_last_of(".") + 1) == "csv") {
                vector<vector<string>> csvData = loadCSV1(filePath);

                // CSV의 3열이 교수 이름과 일치하는지 확인
                if (!csvData.empty() && csvData[1].size() > 2 && csvData[1][2] == inputName) {
                    validFiles.push_back(filePath);  // 일치하는 파일 경로 저장

                    // 강의명과 분반 정보를 저장
                    string coursename = csvData[1][0];  // 첫 번째 열, 두 번째 행 (강의명)
                    string classnum = csvData[1][1];   // 두 번째 열, 두 번째 행 (분반 정보)

                    // 강의명_분반 형식으로 저장
                    fullCourseName.push_back(coursename + "_" + classnum);
                    fullFilePaths.push_back(filePath);  // 전체 경로 저장
                    courseNames.push_back(coursename);  // 강의명 따로
                    ClassNumbers.push_back(classnum);   // 분반 따로
                }
            }
        }

        // 결과 출력
        if (validFiles.empty()) {
            cout << "교수님의 이름과 일치하는 강의 파일이 없습니다." << endl;
            break; // 파일이 없으면 종료
        } else {
            // 강의 목록을 번호와 함께 출력
            displayCourseSelection_prof(fullCourseName);

            // 교수님에게 번호를 입력받아 선택
            int choice;
            cout << "선택할 강의 번호를 입력하세요 (0: 종료): ";
            cin >> choice;

            if (choice == 0) {
                cout << "교수 모드를 종료합니다.\n" << endl; // 0번 선택 시 종료
                break;
            }

            if (choice < 1 || choice > fullCourseName.size()) {
                cout << "잘못된 번호입니다. 다시 시도하세요." << endl;
            } else {
                // 선택된 강의의 파일 이름 및 경로 가져오기
                string selectedFilePath = fullFilePaths[choice - 1];
                string selectedFilename = fullCourseName[choice - 1];
                string course_name = courseNames[choice - 1];
                string class_num = ClassNumbers[choice - 1];
                cout << "선택한 강의 파일: " << selectedFilename << endl;

                string id = to_string(inputId);
                Professor p(inputName, id, selectedFilePath);

                while (true) {
                    professor_display();
                    cin >> choice2;

                    if (choice2 == 0) {
                        cout << "교수 모드를 종료합니다.\n" << endl;
                        return; // 교수 모드 종료
                    }

                    else if (choice2 == 1) {
                        // 가중치 입력 및 처리
                        
                        float mid, final, assign, attend;
                        while (true) {
                            cout << "중간 시험 가중치를 입력해주세요 (백분율): ";
                            cin >> mid;
                            cout << "기말 시험 가중치를 입력해주세요 (백분율): ";
                            cin >> final;
                            cout << "과제 가중치를 입력해주세요 (백분율): ";
                            cin >> assign;
                            cout << "출석 가중치를 입력해주세요 (백분율): ";
                            cin >> attend;

                            float totalWeight = mid + final + assign + attend;
                            if (totalWeight == 100.0f) break;
                            cerr << "가중치의 합이 " << totalWeight << "입니다. 합이 반드시 100이 되어야 합니다. 다시 입력해주세요." << endl;
                        }

                        p.weight_fix(course_name, class_num, mid, final, assign, attend);
                        p.saveToFile(selectedFilePath);
                    } else if (choice2 == 2) {
                        
                        float aweight, bweight, cweight, dweight, fweight;
                            cout << "성적 비율을 입력해주세요. A~D 비율을 입력하면 F 비율은 자동 계산됩니다.\n";
                            cout << "입력된 비율이 100%를 넘지 않도록 주의해주세요.\n";

                            // A 비율 입력
                         while (true) {
                                cout << "A 비율 (10~35%): ";
                                cin >> aweight;
                                if (aweight >= 10 && aweight <= 35) break;
                                cout << "A 비율은 10~35% 범위여야 합니다. 다시 입력해주세요.\n";
                            }

                            // B 비율 입력
                            while (true) {
                                cout << "B 비율 (" << aweight << "% 초과 70% 이하): ";
                                cin >> bweight;
                                if (bweight > aweight && bweight <= 70) break;
                               cout << "B 비율은 " << aweight << "% 초과 70% 이하 범위여야 합니다. 다시 입력해주세요.\n";
                            }

                            // C 비율 입력
                            float totalRate = bweight;
                            while (true) {
                                cout << "C 비율 (" << totalRate << "% 초과 100% 이하): ";
                                cin >> cweight;
                                if (cweight > totalRate && cweight <= 100) break;
                                cout << "C 비율은 " << totalRate << "% 초과 100% 이하 범위여야 합니다. 다시 입력해주세요.\n";
                            }
                            totalRate = cweight;

                            // D 비율 입력
                            if (totalRate == 100) {
                                dweight = 100;
                                fweight = 100;
                                cout << "C 비율이 100%에 도달했으므로 D와 F 비율은 자동으로 100%로 설정됩니다.\n";
                            } else {
                                while (true) {
                                    cout << "D 비율 (" << totalRate << "% 초과 100% 이하)" << ": ";
                                   cin >> dweight;
                                   if (dweight > totalRate + 1 && dweight <= 100) break;
                                    cout << "D 비율은 " << totalRate + 1 << "% 초과 100% 이하 범위여야 합니다. 다시 입력해주세요.\n";
                                }
                                totalRate = dweight;
                                fweight = 100;
                            }
                            float a,b,c,d,f;
                            a = aweight;
                            b = bweight - aweight;
                            c = cweight - bweight;
                            d = dweight - cweight;
                            f = fweight - dweight;
                            cout << a << b<<c<<d<<f<<endl;

                            // abc_fix 함수 호출
                            p.abc_fix(course_name, class_num, a,b,c,d,f);

                            // 파일에 저장
                            p.saveToFile("./grade_csv/" + course_name + "_" + class_num + ".csv");
                    
                    } else if (choice2 == 3) {
                        string category;
                        int score;
                        cout << "수정할 학생의 학번을 입력하세요: ";
                        cin >> studentId;
                        cout << "중간, 기말, 과제, 출석 중 수정할 것을 입력하세요: ";
                        cin >> category;
                        cout << "점수를 입력하세요: ";
                        cin >> score;
                        p.score_fix(course_name, class_num, studentId, category, score);
                        p.saveToFile("./grade_csv/" + course_name + "_" + class_num + ".csv");

                    } else if (choice2 == 4) {
                        p.view_appeal(course_name, class_num);
                    } else if (choice2 == 5) {
                        p.viewData();
                    } else {
                        cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
                    }
                }
            }
        }
    }
}









// 관리자 모드
void adminMode(UserManager& studentManager, UserManager& professorManager) {
    while (true) {
        int choice, id;
        string name;

        admin_display();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "학생 ID와 이름 입력: ";
                cin >> id >> name;
                studentManager.addUser(id, name);
                break;
            case 2:
                cout << "교수 ID와 이름 입력: ";
                cin >> id >> name;
                professorManager.addUser(id, name);
                break;
            case 3:
                cout << "삭제할 학생 ID 입력: ";
                cin >> id;
                studentManager.deleteUser(id);
                break;
            case 4:
                cout << "삭제할 교수 ID 입력: ";
                cin >> id;
                professorManager.deleteUser(id);
                break;
            case 5:
                cout << "수정할 학생 ID와 새로운 이름 입력: ";
                cin >> id >> name;
                studentManager.modifyUser(id, name);
                break;
            case 6:
                cout << "수정할 교수 ID와 새로운 이름 입력: ";
                cin >> id >> name;
                professorManager.modifyUser(id, name);
                break;
            case 7:
                studentManager.displayUsers();
                cout << "\n\n" << endl;
                break;
            case 8:
                professorManager.displayUsers();
                cout << "\n\n" << endl;
                break;
            case 0:
                cout << "관리자 모드를 종료합니다.\n" << endl;
                return;
            default:
                cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }
}
