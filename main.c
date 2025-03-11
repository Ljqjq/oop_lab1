#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char surname[30];
    char name[30];
    char birthdate[15];
    float marks[5];
    struct Student* next;
} Student;


int main() {
    SetConsoleOutputCP(1251);
    int choice = 0;
    Student* head = NULL;



    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // ��������� ������ ������ ����� ���� scanf

        switch (choice) {
        case 1:
            addNewStudent(&head);
            break;
        case 2:
            printTable(head);
            break;
        case 3:
            sortStudentsBySurname(&head);
            printf("�������� ����������.\n");
            break;
        case 4:
            deleteBelowAverage(&head);
            printf("�������� � ������� ������� ����� �������.\n");
            break;
        case 5:
            findTopTwoStudents(head);
            break;
        case 6:
            loadStudentsFromFile("students.txt", &head);
            printf("��� �������� ����������� �� �����.\n");
            break;
        case 7:
            writeStudentsInFile("studentsUser.txt", head);
            printf("��� �������� ����������� � ����.\n");
            break;
        case 0:
            printf("���������� ��������...\n");
            break;
        default:
            printf("������� ����, ��������� �� ���.\n");
        }
    } while (choice != 0);

    // ��������� ���'��
    while (head != NULL) {
        Student* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
