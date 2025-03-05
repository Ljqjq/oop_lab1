#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

// ������� ��� ��������� ������ ��������
Student* createStudent(const char* surname, const char* name, const char* birthdate, float average_rating) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("������� �������� ���'��!\n");
        exit(1);
    }
    strcpy(newStudent->surname, surname);
    strcpy(newStudent->name, name);
    strcpy(newStudent->birthdate, birthdate);
    newStudent->average_rating = average_rating;
    newStudent->next = NULL;
    return newStudent;
}

// ������� ��� ��������� �������� �� ������
void addStudent(Student** head, const char* surname, const char* name, const char* birthdate, float average_rating) {
    Student* newStudent = createStudent(surname, name, birthdate, average_rating);
    newStudent->next = *head;
    *head = newStudent;
}

// ������� ��� ����� ������ � ������ �������
void printTable(Student* head) {
    printf("-----------------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-15s | %-15s |\n", "�������", "��'�", "���� ����������", "������� ���");
    printf("-----------------------------------------------------------------------------------\n");
    Student* current = head;
    while (current) {
        printf("| %-15s | %-15s | %-15s | %-15.2f |\n",
            current->surname, current->name, current->birthdate, current->average_rating);
        current = current->next;
    }
    printf("-----------------------------------------------------------------------------------\n");
}

void sortStudentsBySurname(Student** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    Student* current;
    

    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            if (strcmp(current->surname, current->next->surname) > 0) {
                // ̳����� ������ ���������
                Student* temp = current->next;
                current->next = current->next->next;
                temp->next = current;

                if (current == *head) {
                    *head = temp;
                }
                else {
                    Student* tempHead = *head;
                    while (tempHead->next != current) {
                        tempHead = tempHead->next;
                    }
                    tempHead->next = temp;
                }

                swapped = 1;
            }
            else {
                current = current->next;
            }
        }
        
    } while (swapped);
}

// ������� ��� ���������� ���� �������� �� �������� ������� �����
void findTopTwoStudents(Student* head) {
    if (head == NULL || head->next == NULL) {
        printf("����������� ����� ��� ���������� ���-2 ��������.\n");
        return;
    }

    Student* first = NULL;
    Student* second = NULL;

    Student* current = head;
    while (current != NULL) {
        if (first == NULL || current->average_rating > first->average_rating) {
            second = first;
            first = current;
        }
        else if (second == NULL || current->average_rating > second->average_rating) {
            second = current;
        }
        current = current->next;
    }

    printf("\n��� �������� � �������� ������� �����:\n");
    printf("1. %s %s (������� ���: %.2f)\n", first->surname, first->name, first->average_rating);
    printf("2. %s %s (������� ���: %.2f)\n", second->surname, second->name, second->average_rating);
}

// ������� ��� ������������ ����� �� �����
void loadStudentsFromFile(const char* filename, Student** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("�� ������� ������� ����!\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char surname[30], name[30], birthdate[15];
        float ratings[50];
        int num_ratings = 0;

        char* token = strtok(line, ",");
        strcpy(surname, token);

        token = strtok(NULL, ",");
        strcpy(name, token);

        token = strtok(NULL, ",");
        strcpy(birthdate, token);

        token = strtok(NULL, " ");
        while (token != NULL) {
            ratings[num_ratings++] = atof(token);
            token = strtok(NULL, " ");
        }

        // ���������� ���������� ��������
        float total = 0.0;
        for (int i = 0; i < num_ratings; i++) {
            total += ratings[i];
        }
        float average = total / num_ratings;

        // ��������� �������� �� ������
        addStudent(head, surname, name, birthdate, average);
    }

    fclose(file);
}

void deleteBelowAverage(Student** head) {
    float group_average = calculateGroupAverage(*head);
    Student* current = *head;
    Student* prev = NULL;

    while (current != NULL) {
        if (current->average_rating < group_average) {
            Student* toDelete = current;
            if (prev == NULL) {
                *head = current->next;
            }
            else {
                prev->next = current->next;
            }
            current = current->next;
            free(toDelete);
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

float calculateGroupAverage(Student* head) {
    if (head == NULL) return 0.0;
    float sum = 0.0;
    int count = 0;
    Student* current = head;
    while (current) {
        sum += current->average_rating;
        count++;
        current = current->next;
    }
    return count > 0 ? sum / count : 0.0;
}

void addNewStudent(Student** head) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    char surname[30], name[30];
    float average_rating;
    char birthdate[15];

    printf("������ ������ ��������:\n");
    printf("������ �������: ");
    gets(surname);
    printf("������ ��'�: ");
    gets(name);
    printf("������ ���� ���������: ");
    gets(birthdate);
    printf("������ ������): ");
    scanf("%f", &average_rating);

   

    // ��������� ������ �������� �� ������������� ������
    Student* ptr = *head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = newStudent;
    strcpy(newStudent->surname, surname);
    strcpy(newStudent->name, name);
    strcpy(newStudent->birthdate, birthdate);
    newStudent->average_rating = average_rating;
    newStudent->next = NULL;

}


