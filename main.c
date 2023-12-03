/* Submitted by EIG Team */

#include stdio.h
#include string.h

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 51  50 characters + 1 for null terminator
#define MAX_AGE 30
#define MAX_STUDY_YEAR 5

typedef struct {
    int ID;
    char name[MAX_NAME_LENGTH];
    char gender;
    int age;
    int studyYear;
    int valid;  To mark if the entry is valid or not
} Student;

void readStudentsFromFile(Student students[], int studentCount) {
    FILE file = fopen(students.txt, r);
    if (file == NULL) {
        printf(File not found or error opening file.n);
        return;
    }

    studentCount = 0;
    while ((studentCount  MAX_STUDENTS) &&
           fscanf(file, %d,%[^,],%c,%d,%dn, &students[studentCount].ID, students[studentCount].name,
                  &students[studentCount].gender, &students[studentCount].age,
                  &students[studentCount].studyYear) != EOF) {
        students[studentCount].valid = 1;
        (studentCount)++;
    }

    fclose(file);
    printf(Students data read from file.n);
}

void saveStudentsToFile(Student students[], int studentCount) {
    FILE file = fopen(students.txt, w);
    if (file == NULL) {
        printf(Error opening file.n);
        return;
    }

    for (int i = 0; i  studentCount; ++i) {
        if (students[i].valid) {
            fprintf(file, %d,%s,%c,%d,%dn, students[i].ID, students[i].name, students[i].gender,
                    students[i].age, students[i].studyYear);
        }
    }

    fclose(file);
    printf(Students data saved to file.n);
}

void addStudent(Student students[], int studentCount) {
    if (studentCount = MAX_STUDENTS) {
        printf(Maximum number of students reached.n);
        return;
    }

    printf(Enter student's full name (max 50 characters) );
    scanf( %[^n], students[studentCount].name);

    printf(Enter student's gender (mf) );
    scanf( %c, &students[studentCount].gender);
    if (students[studentCount].gender != 'm' && students[studentCount].gender != 'f') {
        printf(Invalid gender input. Please enter 'm' for male or 'f' for female.n);
        return;
    }

    printf(Enter student's age );
    scanf(%d, &students[studentCount].age);
    if (students[studentCount].age = 0  students[studentCount].age  MAX_AGE) {
        printf(Invalid age input. Please enter an age between 1 and %d.n, MAX_AGE);
        return;
    }

    printf(Enter student's study year );
    scanf(%d, &students[studentCount].studyYear);
    if (students[studentCount].studyYear = 0  students[studentCount].studyYear  MAX_STUDY_YEAR) {
        printf(Invalid study year input. Please enter a year between 1 and %d.n, MAX_STUDY_YEAR);
        return;
    }

    students[studentCount].ID = studentCount;
    students[studentCount].valid = 1;

    (studentCount)++;
}

void deleteStudent(Student students[], int studentCount) {
    int idToDelete;
    printf(Enter student ID to delete );
    scanf(%d, &idToDelete);

    if (idToDelete  0  idToDelete = studentCount  !students[idToDelete].valid) {
        printf(Invalid student ID.n);
        return;
    }

    students[idToDelete].valid = 0;
    printf(Student with ID %d deleted.n, idToDelete);
}

void displayAllStudents(Student students[], int studentCount) {
    printf(Student IDtNametGendertAgetStudy Yearn);
    for (int i = 0; i  studentCount; ++i) {
        if (students[i].valid) {
            printf(%dtt%st%ct%dt%dn, students[i].ID, students[i].name, students[i].gender,
                   students[i].age, students[i].studyYear);
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    readStudentsFromFile(students, &studentCount);

    int choice;
    do {
        printf(n1- Add new student data.n);
        printf(2- Delete existing student using student id.n);
        printf(3- Display all students.n);
        printf(4- Exit program.n);
        printf(Enter your choice );
        scanf(%d, &choice);

        switch (choice) {
            case 1
                addStudent(students, &studentCount);
                saveStudentsToFile(students, studentCount);
                break;
            case 2
                deleteStudent(students, &studentCount);
                saveStudentsToFile(students, studentCount);
                break;
            case 3
                displayAllStudents(students, studentCount);
                break;
            case 4
                printf(Exiting the program.n);
                break;
            default
                printf(Invalid choice. Please enter a valid option.n);
                break;
        }
    } while (choice != 4);

    return 0;
}
