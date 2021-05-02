#include <stdio.h>
#include <string.h>

#include "binFileManager.h"
#include "binarioNaTela.h"


typedef struct {
    int id;
    char name[50];
    int age;
}USER;


USER *read_users_from_stdin(int total_users) {

    USER *users_set = malloc(total_users * sizeof(USER));

    for (int i = 0; i < total_users; i++) {
        scanf("%d", &users_set[i].id);
        scanf("%s", users_set[i].name);
        scanf("%d", &users_set[i].age);
    }

    return users_set;
}


void write_users_to_bin_file(FILE *stream, USER *user_set, int total_users) {

    for (int i = 0; i < total_users; i++) {
        USER current_user = user_set[i];
        write_int_to_bin_file(stream, &current_user.id);
        write_string_to_bin_file(stream, current_user.name, strlen(current_user.name) + 1);
        write_int_to_bin_file(stream, &current_user.age);
    }
}


int main(int argc, char *argv[]) {

    char bin_file_name[20];
    scanf("%s", bin_file_name);

    int total_users = 0;
    scanf("%d", &total_users);

    USER *users_set = read_users_from_stdin(total_users);

    FILE *bin_file_stream = fopen(bin_file_name, "wb");

    write_users_to_bin_file(bin_file_stream, users_set, total_users);

    fclose(bin_file_stream);

    free(users_set);

    binarioNaTela(bin_file_name);

    return 0;
}