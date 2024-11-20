#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "course.cpp"
#include "UserManager.cpp" // UserManager Ŭ���� ����

using namespace std;

// ���� ���Ͽ��� �й��� �̸��� Ȯ���ϴ� �Լ� ========================
bool verifyInFile(const string& filePath, int inputId, const string& inputName) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filePath << endl;
        return false;
    }

    int id;
    string name;

    // ���Ͽ��� �й��� �̸��� �о�� ��
    while (file >> id >> name) {
        if (id == inputId && name == inputName) {
            return true; // ��ġ�ϸ� true ��ȯ
        }
    }

    return false; // ���� ������ Ȯ���ص� ������ false ��ȯ
} // ���� ���Ͽ��� �й��� �̸��� Ȯ���ϴ� �Լ� Fin ========================

int main() {


    cout << "????????????????????????????????????????????????????????????" << endl;
    cout << "?                                                          ?" << endl;
    cout << "?   Welcome to the Grade Management System (GMS)!          ?" << endl;
    cout << "?                                                          ?" << endl;
    cout << "?   What you can do based on your role:                    ?" << endl;
    cout << "?                                                          ?" << endl;
    cout << "?     [1] �л�(Student):                                   ?" << endl;
    cout << "?         - View your grades                               ?" << endl;
    cout << "?         - Analyze your performance statistics            ?" << endl;
    cout << "?                                                          ?" << endl;
    cout << "?     [2] ����(Professor):                                 ?" << endl;
    cout << "?         - View and manage student grades                 ?" << endl;
    cout << "?         - Analyze class performance                      ?" << endl;
    cout << "?                                                          ?" << endl;
    cout << "?     [3] ������(Admin):                                   ?" << endl;
    cout << "?         - Add or remove users                            ?" << endl;
    cout << "?         - Manage user and grade data                     ?" << endl;
    cout << "?                                                          ?" << endl;
    cout << "?                                                          ?" << endl;
    cout << "????????????????????????????????????????????????????????????" << endl;


    string studentFile = "./������_����/students.txt";  // �л� ���� ����
    string professorFile = "./������_����/professors.txt";  // ���� ���� ����
    // ������_����
    UserManager studentManager(studentFile);    // �л� ����
    UserManager professorManager(professorFile); // ���� ����

    int inputId;
    string inputName;

    cout << "ID(or �й�)�� �Է��ϼ���: ";
    cin >> inputId;
    cout << "�̸��� �Է��ϼ���: ";
    cin >> inputName;





    // �л� ���Ͽ��� Ȯ��-> �л��� ���� ���---------------------------------------------------------------------------
    if (verifyInFile(studentFile, inputId, inputName)) {
        cout << "ȯ���մϴ� (" << inputName << ")�л���!" << endl;

        // ���� csv ������ �ҷ��ͼ� ��� �� ������ ��ȯ
        string class_name;
        string c_num;
        string studentID;

        cout << "������ Ȯ���� ���Ǹ� �Է��ϼ���: ";
        cin >> class_name;
        cout << "�й��� �Է��ϼ���: ";
        cin >> c_num;
        cout << "�й��� �Է��ϼ���: ";
        cin >> studentID;


        Grade grade(class_name, c_num, studentID);
        File file("./grade_csv/" + class_name + "_" + c_num + ".csv");
        file.loadCSV();  // ���� �ҷ�����

        // csv ������ ������ �ҷ��ͼ� ����
        grade.setGradeMap(file);






        /*
        Course course(class_name, c_num, "ȫ�浿");
        File file("./grade_csv/" + class_name + "_" + c_num + ".csv");
        file.loadCSV();  // ���� �ҷ�����


        // file ��ü���� CSV ������ ������ �ҷ��ͼ� map���·� ���� 
        // {'20240001': {'�߰����':100, '�⸻���':90, '����':50, '�⼮ ����':20}, }
        // course.setGradeMap(file);


        // ���� ��� ��� 
        course.calculateRankAndStatistics();

        // ���� �� ��� ���
        cout << endl;
        // course.printGradesAndStatistics();


    // // Ư�� �л��� ���� �� ��� ���
        cout << endl;
        course.printStudentStatistics(studentID);
        return 0;
        */

    }






    // ���� ���Ͽ��� Ȯ��
    //     ������ ������ ��==========================================================================================
    else if (inputId == 123456789 && inputName == "����") {
        cout << "ȯ���մϴ� (" << inputName << ")������!" << endl;

        // ���� ����
        string class_name;
        string c_num;

        cout << "���Ǹ� �Է��ϼ���: ";
        cin >> class_name;
        cout << "�й��� �Է��ϼ���: ";
        cin >> c_num;


        Professor professor;


        // �޴� ���
        while (true) {
            int choice, id;
            string name;
            cout << "\n1. ���� ����ġ\n2. ���� �ο�\n3. ������ ��ȸ\n4. ���� ����\n5. ����\n";
            cout << "����: ";
            cin >> choice;

            switch (choice) {
            case 1: // ���� ����ġ
                professor.inputGradeWeights();
                break;
            case 2: // ���� �ο�
                professor.inputGradeRate();
                break;
            case 3: // ������ ��ȸ
                break;
            case 4: // ���� ����
                break;
            case 5:  // ����
                return 0;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
            }
        }
    }







    // ������ id: 202412345, �̸�:����
    //     �����ڷ� ������ ��==========================================================================================
    else if (inputId == 202412345 && inputName == "����") {

        cout << "�����ڴ� ȯ���մϴ�..! �� ���� �������ּ���..!" << endl;
        while (true) {
            int choice, id;
            string name;
            cout << "\n1. �л� �߰�\n2. ���� �߰�\n3. �л� ����\n4. ���� ����\n";
            cout << "5. �л� ����\n6. ���� ����\n7. �л� ���\n8. ���� ���\n9. ����\n";
            cout << "����: ";
            cin >> choice;

            switch (choice) {
            case 1:  // �л� �߰�
                cout << "�л� ID�� �̸� �Է�: ";
                cin >> id >> name;
                studentManager.addUser(id, name);
                break;
            case 2:  // ���� �߰�
                cout << "���� ID�� �̸� �Է�: ";
                cin >> id >> name;
                professorManager.addUser(id, name);
                break;
            case 3:  // �л� ����
                cout << "������ �л� ID �Է�: ";
                cin >> id;
                studentManager.deleteUser(id);
                break;
            case 4:  // ���� ����
                cout << "������ ���� ID �Է�: ";
                cin >> id;
                professorManager.deleteUser(id);
                break;
            case 5:  // �л� ����
                cout << "������ �л� ID�� ���ο� �̸� �Է�: ";
                cin >> id >> name;
                studentManager.modifyUser(id, name);
                break;
            case 6:  // ���� ����
                cout << "������ ���� ID�� ���ο� �̸� �Է�: ";
                cin >> id >> name;
                professorManager.modifyUser(id, name);
                break;
            case 7:  // �л� ���
                studentManager.displayUsers();
                break;
            case 8:  // ���� ���
                professorManager.displayUsers();
                break;
            case 9:  // ����
                return 0;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
            }
        }


    }




    // �� ��
    else {
        cout << "����ڰ� �������� �ʽ��ϴ�." << endl;
    }

}
