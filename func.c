#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_RATINGS 5

// Функція для створення нового студента
Student* createStudent(const char* surname, const char* name, const char* birthdate, float ratings[MAX_RATINGS]) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Помилка виділення пам'яті!\n");
        exit(1);
    }
    strcpy(newStudent->surname, surname);
    strcpy(newStudent->name, name);
    strcpy(newStudent->birthdate, birthdate);
    memcpy(newStudent->ratings, ratings, sizeof(float) * MAX_RATINGS);  // Копіюємо масив оцінок
    newStudent->next = NULL;
    return newStudent;
}

// Функція для додавання студента до списку
void addStudent(Student** head, const char* surname, const char* name, const char* birthdate, float ratings[MAX_RATINGS]) {
    Student* newStudent = createStudent(surname, name, birthdate, ratings);
    newStudent->next = *head;
    *head = newStudent;
}

// Функція для друку списку у вигляді таблиці
void printTable(Student* head) {
    printf("-----------------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-15s | %-15s |\n", "Прізвище", "Ім'я", "Дата народження", "Середній бал");
    printf("-----------------------------------------------------------------------------------\n");
    Student* current = head;
    while (current) {
        float average_rating = 0.0;
        for (int i = 0; i < MAX_RATINGS; i++) {
            average_rating += current->ratings[i];
        }
        average_rating /= MAX_RATINGS;
        printf("| %-15s | %-15s | %-15s | %-15.2f |\n", current->surname, current->name, current->birthdate, average_rating);
        current = current->next;
    }
    printf("-----------------------------------------------------------------------------------\n");
}

// Функція для сортування студентів за прізвищем
void sortStudentsBySurname(Student** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    Student* current;
    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            if (strcmp(current->surname, current->next->surname) > 0) {
                // Міняємо місцями вказівники
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

// Функція для обчислення середнього балу групи
float calculateGroupAverage(Student* head) {
    if (head == NULL) return 0.0;
    float sum = 0.0;
    int count = 0;
    Student* current = head;
    while (current) {
        float total = 0.0;
        for (int i = 0; i < MAX_RATINGS; i++) {
            total += current->ratings[i];
        }
        sum += total / MAX_RATINGS;
        count++;
        current = current->next;
    }
    return count > 0 ? sum / count : 0.0;
}

// Функція для завантаження даних із файлу
void loadStudentsFromFile(const char* filename, Student** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не вдалося відкрити файл!\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char surname[30], name[30], birthdate[15];
        float ratings[MAX_RATINGS];
        int num_ratings = 0;

        char* token = strtok(line, ",");
        strcpy(surname, token);

        token = strtok(NULL, ",");
        strcpy(name, token);

        token = strtok(NULL, ",");
        strcpy(birthdate, token);

        token = strtok(NULL, " ");
        while (token != NULL && num_ratings < MAX_RATINGS) {
            ratings[num_ratings++] = atof(token);
            token = strtok(NULL, " ");
        }

        // Додавання студента до списку
        addStudent(head, surname, name, birthdate, ratings);
    }

    fclose(file);
}

void deleteBelowAverage(Student** head) {
    float group_average = calculateGroupAverage(*head);  // Get the group average
    Student* current = *head;
    Student* prev = NULL;

    while (current != NULL) {
        // Calculate the student's average rating
        float student_average = 0.0;
        for (int i = 0; i < MAX_RATINGS; i++) {
            student_average += current->ratings[i];
        }
        student_average /= MAX_RATINGS;

        // If the student's average is below the group average, delete them
        if (student_average < group_average) {
            Student* toDelete = current;
            if (prev == NULL) {
                *head = current->next;  // Removing the first node
            }
            else {
                prev->next = current->next;  // Removing a node in the middle or end
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



// Helper function to calculate the average rating of a student
float calculateStudentAverage(Student* student) {
    float student_average = 0.0;
    for (int i = 0; i < MAX_RATINGS; i++) {
        student_average += student->ratings[i];
    }

    float result = student_average / 5.0;
    return result;
}

void findTopTwoStudents(Student* head) {
    if (head == NULL || head->next == NULL) {
        printf("Недостатньо даних для визначення топ-2 студентів.\n");
        return;
    }

    Student* first = NULL;
    Student* second = NULL;

    Student* current = head;
    while (current != NULL) {
        // Calculate the student's average rating from the ratings array
        float student_average = 0.0;
        for (int i = 0; i < MAX_RATINGS; i++) {
            student_average += current->ratings[i];
        }
        student_average /= MAX_RATINGS;

        // Determine if this student should be in the top two
        if (first == NULL || student_average > (first != NULL ? calculateStudentAverage(first) : 0.0)) {
            second = first;
            first = current;
        }
        else if (second == NULL || student_average > (second != NULL ? calculateStudentAverage(second) : 0.0)) {
            second = current;
        }

        current = current->next;
    }

    // Output the top two students
    if (first != NULL && second != NULL) {
        printf("\nДва студенти з найвищим середнім балом:\n");

        float first_avg = calculateStudentAverage(first);
        float second_avg = calculateStudentAverage(second);

        printf("1. %s %s (Середній бал: %f)\n", first->surname, first->name, first_avg);
        printf("2. %s %s (Середній бал: %f)\n", second->surname, second->name, second_avg);
    }
}

// Функція для додавання нового студента
void addNewStudent(Student** head) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    char surname[30], name[30];
    float ratings[MAX_RATINGS];
    char birthdate[15];

    printf("Додати нового студента:\n");
    printf("Введіть прізвище: ");
    gets(surname);
    printf("Введіть ім'я: ");
    gets(name);
    printf("Введіть дату народження: ");
    gets(birthdate);

    printf("Введіть 5 оцінок:\n");
    for (int i = 0; i < MAX_RATINGS; i++) {
        printf("Оцінка %d: ", i + 1);
        scanf("%f", &ratings[i]);
    }

    // Додавання нового студента до відсортованого списку
    addStudent(head, surname, name, birthdate, ratings);
}

void printMenu() {
    printf("\nМеню:\n");
    printf("1. Додати нового студента\n");
    printf("2. Вивести список студентів\n");
    printf("3. Відсортувати студентів за прізвищем\n");
    printf("4. Видалити студентів з середнім балом нижче середнього\n");
    printf("5. Знайти двох студентів з найвищими балами\n");
    printf("6. Завантажити студентів із файлу\n");
    printf("7. Завантажити студентів в файл\n");
    printf("0. Вийти\n");
    printf("Ваш вибір: ");
}

void writeStudentsInFile(const char* filename, Student *head) {
    FILE* file = fopen(filename, "w");

    if (!file) {
        printf("Не вдалося відкрити файл!\n");
        exit(1);
    }

    
    Student* curr = head;
    while (curr != NULL) {
        fprintf(file, "%s, %s, %s, %f %f %f %f %f\n", curr->surname, curr->name, curr->birthdate, curr->ratings[0], curr->ratings[1], curr->ratings[2], curr->ratings[3], curr->ratings[4]);
        curr = curr->next;
    }

    fclose(file);
    
}