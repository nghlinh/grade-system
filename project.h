#ifndef _PROJECT__H_
#define _PROJECT__H_

typedef struct{
    char id[7];
    char* first_name;
    char* last_name;
    int points[6];
    int total_point;
}Student;


struct data{
    Student *student;
    struct data* next;
};

int add_student(struct data *database, char* id, char* surname, char* name);
int update_points(struct data *database, char* id, int round, int pts);
int print_data(struct data *database);
int save_file(struct data* database, char* file);
int load_file(struct data* database, char* file);

#endif //! _PROJECT__H_