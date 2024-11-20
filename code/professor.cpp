#include <iostream>
#include <map>
#include <string>

using namespace std;

class Professor {
private:
    map<string, double> gradeWeights;  // ����ġ ����
    map<string, double> gradeRate;  // ���� ���� ����

public:
    // ������
    

    // 1. ����ġ �Է�
    // ����ġ ���� �Լ�
    void setGradeWeights(double midterm, double finalExam, double assignment, double attendance) {
        gradeWeights["�߰����"] = midterm;
        gradeWeights["�⸻���"] = finalExam;
        gradeWeights["����"] = assignment;
        gradeWeights["�⼮"] = attendance;
    }

    // ����ġ ��ȯ �Լ�
    const map<string, double>& getGradeWeights() const {
        return gradeWeights;
    }

    // ���� ����ġ �Է� �Լ�
    void inputGradeWeights() {
        double midtermWeight, finalWeight, assignmentWeight, attendanceWeight;
        double totalWeight;

        // ���� �б� ����ġ ���� (������ ����� ���̶�� ����)
        bool lastSemesterWeightsExist = true;  // ���� �б� ����ġ�� �ִٰ� ����
        double lastMidtermWeight = 30.0, lastFinalWeight = 40.0, lastAssignmentWeight = 20.0, lastAttendanceWeight = 10.0;

        // ���� �б� ����ġ�� �����ϴ��� Ȯ��
        if (lastSemesterWeightsExist) {
            cout << "���� �б� ����ġ ����: " << endl;
            cout << "�߰����: " << lastMidtermWeight << "%, �⸻���: " << lastFinalWeight << "%, "
                << "����: " << lastAssignmentWeight << "%, �⼮: " << lastAttendanceWeight << "%" << endl;
            cout << "���� �б� ����ġ�� ����Ͻðڽ��ϱ�?" << endl;
            cout << "1. ���� �б� ����ġ �״�� ���\n";
            cout << "2. ���� ����ġ �Է�\n";
            cout << "����: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                // ���� �б� ����ġ �״�� ���
                cout << "���� �б� ����ġ�� �״�� ����մϴ�." << endl;
                cout << "����ġ ���� �Ϸ�!" << endl;
                setGradeWeights(lastMidtermWeight, lastFinalWeight, lastAssignmentWeight, lastAttendanceWeight);
                return;
            }
            else if (choice == 2) {
                // ���� ����ġ�� �Է� �ޱ�
                cout << "���ο� ����ġ�� �Է��ϼ���." << endl;
            }
            else {
                cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
                return;
            }
        }
        else {
            // ���� �б� ����ġ�� ���� ���
            cout << "���� �б� ����ġ ������ �����ϴ�." << endl;
            cout << "���ο� ����ġ�� �Է��ϼ���." << endl;
        }

        // ���� ����ġ�� �Է¹޴� �κ�
        while (true) {
            cout << "�߰���� ����ġ(%): ";
            cin >> midtermWeight;
            cout << "�⸻��� ����ġ(%): ";
            cin >> finalWeight;
            cout << "���� ����ġ(%): ";
            cin >> assignmentWeight;
            cout << "�⼮ ����ġ(%): ";
            cin >> attendanceWeight;

            // ����ġ �հ� ���
            totalWeight = midtermWeight + finalWeight + assignmentWeight + attendanceWeight;

            // ����ġ �հ谡 100%���� Ȯ��
            if (totalWeight == 100) {
                cout << "����ġ ���� �Ϸ�!" << endl;
                break;  // �հ谡 100%�� ���, �ݺ��� ����
            }
            else if (totalWeight > 100) {
                cout << "����ġ �հ谡 100%�� �ʰ��մϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else {
                cout << "����ġ �հ谡 100%���� �����ϴ�. �ٽ� �Է����ּ���." << endl;
            }
        }

        // ���� ��ü�� ����ġ ����
        setGradeWeights(midtermWeight, finalWeight, assignmentWeight, attendanceWeight);

        const map<string, double>& weights = getGradeWeights();
        cout << "\n�������� ����ġ ����:" << endl;
        cout << "�߰����: " << weights.at("�߰����") << "%" << endl;
        cout << "�⸻���: " << weights.at("�⸻���") << "%" << endl;
        cout << "����: " << weights.at("����") << "%" << endl;
        cout << "�⼮: " << weights.at("�⼮") << "%" << endl;
    }



    // 2. ���� ����ġ �Է�
    // ���� ���� ���� �Լ�
    void setGradeRate(double A_rate, double B_rate, double C_rate, double D_rate, double F_rate) {
        gradeRate["A ����"] = A_rate;
        gradeRate["B ����"] = B_rate;
        gradeRate["C ����"] = C_rate;
        gradeRate["D ����"] = D_rate;
        gradeRate["F ����"] = F_rate;
    }

    // ���� ���� ��ȯ �Լ�
    const map<string, double>& getGradeRate() const {
        return gradeRate;
    }


    // ���� ���� �Է� �Լ�
    void inputGradeRate() {
        double A_rate, B_rate, C_rate, D_rate, F_rate; // �� ���� ����
        double totalRate = 0;                         // ������� �Էµ� �� ����
        const double MAX_RATE = 100.0;                // ���� �ִ�ġ

        cout << "���� ������ �Է����ּ���. A~D ������ �Է��ϸ� F ������ �ڵ� ���˴ϴ�.\n";
        cout << "�Էµ� ������ 100%�� ���� �ʵ��� �������ּ���.\n";

        // A ���� �Է�
        while (true) {
            cout << "A ���� (10~30%): ";
            cin >> A_rate;
            if (A_rate >= 10 && A_rate <= 30) break;
            cout << "A ������ 10~30% �������� �մϴ�. �ٽ� �Է����ּ���.\n";
        }
        totalRate = A_rate;

        // B ���� �Է�
        while (true) {
            cout << "B ���� (" << A_rate + 1 << "~70%): ";
            cin >> B_rate;
            if (B_rate >= A_rate + 1 && B_rate <= 70) break;
            cout << "B ������ " << A_rate + 1 << "~70% �������� �մϴ�. �ٽ� �Է����ּ���.\n";
        }
        totalRate = B_rate;

        // C ���� �Է�
        while (true) {
            cout << "C ���� (" << totalRate + 1 << "~" << MAX_RATE << "%): ";
            cin >> C_rate;
            if (C_rate >= totalRate + 1 && C_rate <= MAX_RATE) break;
            cout << "C ������ " << totalRate + 1 << "~" << MAX_RATE << "% �������� �մϴ�. �ٽ� �Է����ּ���.\n";
        }
        totalRate = C_rate;

        // D ���� �Է�
        while (true) {
            cout << "D ���� (" << totalRate + 1 << "~" << MAX_RATE << "%): ";
            cin >> D_rate;
            if (D_rate >= totalRate + 1 && D_rate <= MAX_RATE) break;
            cout << "D ������ " << totalRate + 1 << "~" << MAX_RATE << "% �������� �մϴ�. �ٽ� �Է����ּ���.\n";
        }
        totalRate = D_rate;

        // F ���� �ڵ� ���
        F_rate = MAX_RATE - totalRate;

        if (F_rate < 0) {
            cout << "���� �հ谡 100%�� �ʰ��߽��ϴ�. �Է��� �ٽ� �����ϼ���.\n";
        }

        // ���� ���� ����
        setGradeRate(A_rate, B_rate, C_rate, D_rate, F_rate);

        // ��� ���
        const map<string, double>& gradeRates = getGradeRate();
        cout << "\n���� ���� ���� ����:\n";
        for (const auto& grade : gradeRates) {
            cout << grade.first << ": " << grade.second << "%\n";
        }
    }







};
