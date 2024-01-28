#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeAll(struct data* database){
    while (database->next){
        struct data *next = database->next->next;
        free(database->next->student->first_name);
        free(database->next->student->last_name);
        free(database->next->student);
        free(database->next);
        database->next = next;
    }
    free(database->next);
}

int add_student(struct data *database, char* id, char* surname, char* name){

    //check if student already exists
    while (database->next){
        if (strcmp(database->next->student->id, id) == 0){
            printf("This student already exists.\n");
            return 0;
        }
        database = database->next;
    }

    //allocate memory for new student
    database->next = malloc(sizeof(struct data));
    if (database->next == NULL){
        free(database->next);
        printf("Error in memory\n");
        return 0;
    }
    database->next->student = malloc(sizeof(Student));
    if (database->next->student == NULL){
        free(database->next->student);
        printf("Error in memory\n");
        return 0;
    }
    strncpy(database->next->student->id, id, 7);
    database->next->student->first_name = malloc(strlen(name) + 1);
    strcpy(database->next->student->first_name, name);
    database->next->student->last_name = malloc(strlen(surname) + 1);
    strcpy(database->next->student->last_name, surname);
    for (int i = 0; i < 6; i++){
        database->next->student->points[i] = 0;
    }
    database->next->student->total_point = 0;
    database->next->next = NULL;
    return 1;
}

int update_points(struct data *database, char* id, int round, int pts){
    //check if the student is in the database
    int exist = 0;
    while (database->next){
        if (strcmp(database->next->student->id, id) == 0){
            exist = 1;
            break;
        }
        database = database->next;
    }
    
    if (!exist){
        printf("Student does not exist.\n");
        return 0;
    }
    //update point
    for (int i = 0; i < 6; i++){
        if (i == (round - 1)){
            if (pts < 0){
                printf("Student cannot have negative points.\n");
                return 0;
            }
            database->next->student->total_point -= database->next->student->points[i];
            database->next->student->points[i] = pts;
            database->next->student->total_point += pts;
            return 1;
        }
    }
    //if the round is not between 1 and 6
    printf("Round cannot be less than 1 or larger than 6\n");
    return 0;
}

int compareNum(const void* a, const void* b) {
    if (*(int*) a > *(int*) b){return -1;}
    else if (*(int*)a == *(int*)b){return 0;}
    else {return 1;}
}

int print_data(struct data *database){
    struct data *first_node = database;
    //find the total number of student
    int total_stu = 0;
    while (database->next){
        total_stu++;
        database = database->next;
    }

    database = first_node;
    int score_record[total_stu];
    memset(score_record, 0, total_stu); //score of all student
    int i = 0;
    while (database->next){
        int dup = 0;
        for (int j = 0; j < i; j++){
            if (score_record[j] == database->next->student->total_point){
                dup = 1;
            }
        }
        if (!dup) {
            score_record[i] = database->next->student->total_point;
            i++;
        }
        database = database->next;
    }

    qsort(&score_record, i, sizeof(int), compareNum);

    for (int j = 0; j < i; j++){
        database = first_node;
        while (database->next){
            int check = score_record[j];
            if (check == database->next->student->total_point){
                Student *curr = database->next->student;
                printf("%s %s %s %u %u %u %u %u %u %u\n", curr->id, curr->last_name, curr->first_name, curr->points[0], curr->points[1],curr->points[2], curr->points[3], curr->points[4], curr->points[5], curr->total_point);
            }
            database = database->next;
        }
    }
    return 1;
}

int save_file(struct data* database, char* file){
    FILE *f = fopen(file, "w");
	if (!f){
        printf("Error opening file\n");
		return 0;
	}

    struct data *first_node = database;
    //find the total number of student
    int total_stu = 0;
    while (database->next){
        total_stu++;
        database = database->next;
    }

    database = first_node;
    int score_record[total_stu];
    memset(score_record, 0, total_stu); //score of all student
    int i = 0;
    while (database->next){
        int dup = 0;
        for (int j = 0; j < i; j++){
            if (score_record[j] == database->next->student->total_point){
                dup = 1;
            }
        }
        if (!dup) {
            score_record[i] = database->next->student->total_point;
            i++;
        }
        database = database->next;
    }

    qsort(&score_record, i, sizeof(int), compareNum);

    for (int j = 0; j < i; j++){
        database = first_node;
        while (database->next){
            int check = score_record[j];
            if (check == database->next->student->total_point){
                Student *curr = database->next->student;
                fprintf(f, "%s %s %s %u %u %u %u %u %u %u\n", curr->id, curr->last_name, curr->first_name, curr->points[0], curr->points[1],curr->points[2], curr->points[3], curr->points[4], curr->points[5], curr->total_point);
            }
            database = database->next;
        }
    }
	fclose(f);
	return 1;
}

int load_file(struct data* database, char* file){
    FILE *f = fopen(file, "r");
    if (!f){
        printf("Error opening file\n");
		return 0;
    }

    freeAll(database);

    char buffer[1024];
    while (fgets(buffer, 1024, f) != NULL) {
        //allocate memory to add new student
        database->next = malloc(sizeof(struct data));
        if (database->next == NULL){
            free(database->next);
            printf("Error in memory\n");
            return 0;
        }
        database->next->student = malloc(sizeof(Student));
        if (database->next->student == NULL){
            free(database->next->student);
            printf("Error in memory\n");
            return 0;
        }
        database->next->student->first_name = (char*) malloc(1000);
        database->next->student->last_name = (char*) malloc(1000);

		sscanf(buffer, "%s %s %s %u %u %u %u %u %u %u\n", database->next->student->id, database->next->student->last_name, database->next->student->first_name, &database->next->student->points[0], &database->next->student->points[1], &database->next->student->points[2], &database->next->student->points[3], &database->next->student->points[4], &database->next->student->points[5], &database->next->student->total_point);
        database->next->next = NULL;
        database = database->next;
	}
    fclose(f);
	return 1;
}

int doCommand(struct data* database, char* buf){
  switch((int) buf[0]){
    case 'A': {
        char cmd = buf[0];
        char id[100];
        memset(id, '\0', sizeof(id));
        char name[1000];
        memset(name, '\0', sizeof(name));
        char surname[1000];
        memset(surname, '\0', 1000);

        int inputs = sscanf(buf, "%c %s %s %s", &cmd, id, surname, name);

        if (inputs != 4){
            printf("Invalid input.\n");
        }
        else if (strlen(id) > 6){
            printf("Student number can only be 6 digits.\n");
        }
        else if (add_student(database, id, surname, name)){
            printf("SUCCESS\n");
        }
        break;
    }
    case 'U':{
        char cmd = buf[0];
        char id[100];
        memset(id, '\0', sizeof(id));
        int round = 0;
        unsigned int pts = 0;

        int input = sscanf(buf, "%c %s %i %i", &cmd, id, &round, &pts);

        if (input != 4){
            printf("Invalid input.\n");
        }
        else if (update_points(database, id, round, pts)){
            printf("SUCCESS\n");
        }
        break;
    }
    case 'L':{
        if (print_data(database)){
            printf("SUCCESS\n");
        }
        break;
    }
    case 'W':{
        char cmd = buf[0];
        char file[1000];
        int in = sscanf(buf, "%c %s", &cmd, file);
        if (in != 2){ 
            printf("Invalid inputs.\n");
        }
        else if (save_file(database, file)){
            printf("SUCCESS\n");
        }
        break;
    }
    case 'O':{
        char cmd = buf[0];
        char file[1000];
        int inp = sscanf(buf, "%c %s", &cmd, file);
        if (inp != 2){ 
            printf("Invalid inputs.\n");
        }
        else if (load_file(database, file)){
            printf("SUCCESS\n");
        }
        break;
    }
    case 'Q':{
        printf("SUCCESS\n");
        return 0;
    }
    default:{
        printf("Invalid command %c\n", buf[0]);
        break;
    }
  }
  return 1;
}


int main(void) {
    struct data database;
    memset(&database, 0, sizeof(database));
    database.next = NULL;
    char buf[1000];
    int read = 1;
    while(read){
        fgets(buf, 1000, stdin);
        read = doCommand(&database, buf);
    }
    freeAll(&database);
}