#include <iostream>
#include <map>
#include <string>

using namespace std;

class Professor {
private:
    map<string, double> gradeWeights;  // 가중치 저장
    map<string, double> gradeRate;  // 학점 비율 저장

public:
    // 생성자
    

    // 1. 가중치 입력
    // 가중치 저장 함수
    void setGradeWeights(double midterm, double finalExam, double assignment, double attendance) {
        gradeWeights["중간고사"] = midterm;
        gradeWeights["기말고사"] = finalExam;
        gradeWeights["과제"] = assignment;
        gradeWeights["출석"] = attendance;
    }

    // 가중치 반환 함수
    const map<string, double>& getGradeWeights() const {
        return gradeWeights;
    }

    // 성적 가중치 입력 함수
    void inputGradeWeights() {
        double midtermWeight, finalWeight, assignmentWeight, attendanceWeight;
        double totalWeight;

        // 지난 학기 가중치 정보 (실제로 저장된 값이라고 가정)
        bool lastSemesterWeightsExist = true;  // 지난 학기 가중치가 있다고 가정
        double lastMidtermWeight = 30.0, lastFinalWeight = 40.0, lastAssignmentWeight = 20.0, lastAttendanceWeight = 10.0;

        // 지난 학기 가중치가 존재하는지 확인
        if (lastSemesterWeightsExist) {
            cout << "지난 학기 가중치 정보: " << endl;
            cout << "중간고사: " << lastMidtermWeight << "%, 기말고사: " << lastFinalWeight << "%, "
                << "과제: " << lastAssignmentWeight << "%, 출석: " << lastAttendanceWeight << "%" << endl;
            cout << "지난 학기 가중치를 사용하시겠습니까?" << endl;
            cout << "1. 지난 학기 가중치 그대로 사용\n";
            cout << "2. 새로 가중치 입력\n";
            cout << "선택: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                // 지난 학기 가중치 그대로 사용
                cout << "지난 학기 가중치를 그대로 사용합니다." << endl;
                cout << "가중치 설정 완료!" << endl;
                setGradeWeights(lastMidtermWeight, lastFinalWeight, lastAssignmentWeight, lastAttendanceWeight);
                return;
            }
            else if (choice == 2) {
                // 새로 가중치를 입력 받기
                cout << "새로운 가중치를 입력하세요." << endl;
            }
            else {
                cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
                return;
            }
        }
        else {
            // 지난 학기 가중치가 없는 경우
            cout << "지난 학기 가중치 정보가 없습니다." << endl;
            cout << "새로운 가중치를 입력하세요." << endl;
        }

        // 새로 가중치를 입력받는 부분
        while (true) {
            cout << "중간고사 가중치(%): ";
            cin >> midtermWeight;
            cout << "기말고사 가중치(%): ";
            cin >> finalWeight;
            cout << "과제 가중치(%): ";
            cin >> assignmentWeight;
            cout << "출석 가중치(%): ";
            cin >> attendanceWeight;

            // 가중치 합계 계산
            totalWeight = midtermWeight + finalWeight + assignmentWeight + attendanceWeight;

            // 가중치 합계가 100%인지 확인
            if (totalWeight == 100) {
                cout << "가중치 설정 완료!" << endl;
                break;  // 합계가 100%일 경우, 반복을 종료
            }
            else if (totalWeight > 100) {
                cout << "가중치 합계가 100%를 초과합니다. 다시 입력해주세요." << endl;
            }
            else {
                cout << "가중치 합계가 100%보다 적습니다. 다시 입력해주세요." << endl;
            }
        }

        // 교수 객체에 가중치 저장
        setGradeWeights(midtermWeight, finalWeight, assignmentWeight, attendanceWeight);

        const map<string, double>& weights = getGradeWeights();
        cout << "\n교수님의 가중치 설정:" << endl;
        cout << "중간고사: " << weights.at("중간고사") << "%" << endl;
        cout << "기말고사: " << weights.at("기말고사") << "%" << endl;
        cout << "과제: " << weights.at("과제") << "%" << endl;
        cout << "출석: " << weights.at("출석") << "%" << endl;
    }



    // 2. 학점 기준치 입력
    // 학점 비율 설정 함수
    void setGradeRate(double A_rate, double B_rate, double C_rate, double D_rate, double F_rate) {
        gradeRate["A 비율"] = A_rate;
        gradeRate["B 비율"] = B_rate;
        gradeRate["C 비율"] = C_rate;
        gradeRate["D 비율"] = D_rate;
        gradeRate["F 비율"] = F_rate;
    }

    // 학점 비율 반환 함수
    const map<string, double>& getGradeRate() const {
        return gradeRate;
    }


    // 학점 비율 입력 함수
    void inputGradeRate() {
        double A_rate, B_rate, C_rate, D_rate, F_rate; // 각 학점 비율
        double totalRate = 0;                         // 현재까지 입력된 총 비율
        const double MAX_RATE = 100.0;                // 총합 최대치

        cout << "성적 비율을 입력해주세요. A~D 비율을 입력하면 F 비율은 자동 계산됩니다.\n";
        cout << "입력된 비율이 100%를 넘지 않도록 주의해주세요.\n";

        // A 비율 입력
        while (true) {
            cout << "A 비율 (10~30%): ";
            cin >> A_rate;
            if (A_rate >= 10 && A_rate <= 30) break;
            cout << "A 비율은 10~30% 범위여야 합니다. 다시 입력해주세요.\n";
        }
        totalRate = A_rate;

        // B 비율 입력
        while (true) {
            cout << "B 비율 (" << A_rate + 1 << "~70%): ";
            cin >> B_rate;
            if (B_rate >= A_rate + 1 && B_rate <= 70) break;
            cout << "B 비율은 " << A_rate + 1 << "~70% 범위여야 합니다. 다시 입력해주세요.\n";
        }
        totalRate = B_rate;

        // C 비율 입력
        while (true) {
            cout << "C 비율 (" << totalRate + 1 << "~" << MAX_RATE << "%): ";
            cin >> C_rate;
            if (C_rate >= totalRate + 1 && C_rate <= MAX_RATE) break;
            cout << "C 비율은 " << totalRate + 1 << "~" << MAX_RATE << "% 범위여야 합니다. 다시 입력해주세요.\n";
        }
        totalRate = C_rate;

        // D 비율 입력
        while (true) {
            cout << "D 비율 (" << totalRate + 1 << "~" << MAX_RATE << "%): ";
            cin >> D_rate;
            if (D_rate >= totalRate + 1 && D_rate <= MAX_RATE) break;
            cout << "D 비율은 " << totalRate + 1 << "~" << MAX_RATE << "% 범위여야 합니다. 다시 입력해주세요.\n";
        }
        totalRate = D_rate;

        // F 비율 자동 계산
        F_rate = MAX_RATE - totalRate;

        if (F_rate < 0) {
            cout << "비율 합계가 100%를 초과했습니다. 입력을 다시 시작하세요.\n";
        }

        // 성적 비율 설정
        setGradeRate(A_rate, B_rate, C_rate, D_rate, F_rate);

        // 결과 출력
        const map<string, double>& gradeRates = getGradeRate();
        cout << "\n최종 성적 비율 설정:\n";
        for (const auto& grade : gradeRates) {
            cout << grade.first << ": " << grade.second << "%\n";
        }
    }







};
