#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* defining typedef "student" structure */
typedef struct{
    int studentID;
    char firstName[15];
    char lastName[15];
    int proj1Grade;
    int proj2Grade;
    float finalGrade;
} student;

/* prototype functions */
student **create_class_list(char *filename, int *sizePtr);
int find(int idNo, student **list, int size);
void input_grades(char *filename, student **list, int size);
void compute_final_course_grades();
void output_final_course_grades();
void print_list(student **list, int size);
void withdraw(int idNo, student **list, int *sizePtr);
void destroy_list(student **list, int *sizePtr);

int main() {
    int size;           // class size or # of students
    student **list;     // pointer to the beginning of array of pointers of each student

    /* create the class list */
    list = create_class_list("class_list.txt", &size);
    print_list(list, size);

    /* testing the find function */
    printf("index of %d is %d\n", 2512, find(2512, list, size));
    printf("index of %d is %d\n", 1200, find(1200, list, size));
    printf("\n");

    /* input grades into list */
    input_grades("project_grades.txt", list, size);
    print_list(list, size);



    free(list);
    return 0;
}

/* function reads the input file and puts elements into an array of structures */
student **create_class_list(char *filename, int *sizePtr) {
    FILE *filePtr = fopen(filename, "r");   // file pointer to filename

    /* exit code for if file does not exist */
    if(filePtr == NULL) {
        printf("ERROR: the file '%s' does not exist\n", filename);
        exit(1);
    }

    fscanf(filePtr, "%d", sizePtr);         // gets # of students from first line

    /* allocates memory for entire student list for the **list variable */
    student **list = malloc((*sizePtr)*(sizeof(student*)));

    /* iterates through each line and allocates memory for struct */
    int i;
    for(i = 0; i < *sizePtr; i++) {
        /* new allocation for each student struct, auto-sets values to 0*/
        list[i] = calloc(1, sizeof(student));
        fscanf(filePtr, "%d %s %s",     // scans each line of the file
            &list[i]->studentID,        // puts 1st num into studentID
            &list[i]->firstName,        // puts 2nd str into firstName
            &list[i]->lastName);        // puts 3rd str into lastName
    }

    fclose(filePtr);    // always close file after reading
    return list;
}

/* function returns index of desired studentID */
int find(int idNo, student **list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        if(list[i]->studentID == idNo) {
            return i;   // return index if idNo matches
        }
    }
    return -1;  // return -1 by default (if idNo is not in list)
}

void input_grades(char *filename, student **list, int size) {
    FILE *filePtr = fopen(filename, "r");   // file pointer to file name
    int idNo, pos;  // student id number and index position respectively

    /* exit code for if file does not exist */
    if(filePtr == NULL) {
        printf("ERROR: the file '%s' does not exist\n", filename);
        exit(1);
    }

    /* iterates through 'project_grades.txt' and adds grades to student list */
    int i;
    for(i = 0; i < size; i++) {
        fscanf(filePtr, "%d", &idNo);   // scans the student id number
        pos = find(idNo, list, size);   // finds the index of student id
        if(pos == -1) {
            /* print error and exit if id number is not in file */
            printf("ERROR: student in 'project_grades.txt' is not in 'class_list.txt'\n");
            exit(1);
        } else {
            fscanf(filePtr, "%d %d",
                &list[pos]->proj1Grade,     // assign project 1 grade into list
                &list[pos]->proj2Grade);    // assign project 2 grade into list
        }
    }
}

void compute_final_course_grades(student **list, int size) {
    
}

void output_final_course_grades() {

}

void print_list(student **list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%d\t%s %s\t%3d %3d %6.2f\n",
            list[i]->studentID,
            list[i]->firstName,
            list[i]->lastName,
            list[i]->proj1Grade,
            list[i]->proj2Grade,
            list[i]->finalGrade);
    }
    printf("\n");
}

void withdraw(int idNo, student **list, int *sizePtr) {

}

void destroy_list(student **list, int *sizePtr) {

}
