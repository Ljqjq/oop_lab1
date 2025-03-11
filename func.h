#ifndef FUNC_H
#define FUNC_H
#define MAX_RATINGS 5
typedef struct Student {
    char surname[50];
    char name[50];
    char birthdate[15];
    float ratings[5];  // Масив оцінок
    struct Student* next;
} Student;
Student* createStudent(const char* surname, const char* name, const char* birthdate, float ratings[MAX_RATINGS]);
void addStudent(Student** head, const char* surname, const char* name, const char* birthdate, float ratings[MAX_RATINGS]);
void printTable(Student* head);
void sortStudentsBySurname(Student** head);
void findTopTwoStudents(Student* head);
void loadStudentsFromFile(const char* filename, Student** head);
float calculateGroupAverage(Student* head);
void deleteBelowAverage(Student** head);
void addNewStudent(Student** head);
void printMenu();
void writeStudentsInFile(Student** head);
#endif;
