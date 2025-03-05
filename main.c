#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char surname[30];
    char name[30];
    char birthdate[15];
    float average_rating;
    struct Student* next;
} Student;


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice = 0;
    Student* head = NULL;

    // ������������ ����� �� �����
    loadStudentsFromFile("students.txt", &head);
    //add new student
    addNewStudent(&head);

    // ���������� ���������� �����
    printf("������ ���:\n");
    printTable(head);

    // ���������� �� ���������
    sortStudentsBySurname(&head);

    //�������� ��������
    deleteBelowAverage(&head);

    printf("\n��� ���� ���������� �� ���������:\n");
    printTable(head);

    // ���������� ���� �������� �� �������� ������� �����
    findTopTwoStudents(head);

    // ��������� ���'��
    while (head != NULL) {
        Student* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
