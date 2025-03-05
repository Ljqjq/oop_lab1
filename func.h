#ifndef FUNC_H
#define FUNC_H
typedef struct Student {
    char surname[30];
    char name[30];
    char birthdate[15];
    float average_rating;
    struct Student* next;
} Student;
Student* createStudent(const char* surname, const char* name, const char* birthdate, float average_rating);
void addStudent(Student** head, const char* surname, const char* name, const char* birthdate, float average_rating);
void printTable(Student* head);
void sortStudentsBySurname(Student** head);
void findTopTwoStudents(Student* head);
void loadStudentsFromFile(const char* filename, Student** head);
float calculateGroupAverage(Student* head);
void deleteBelowAverage(Student** head);
void addNewStudent(Student** head);
#endif;
