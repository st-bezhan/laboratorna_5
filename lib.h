//
// Created by Stanislav Bezhan on 16.12.2024.
//

#ifndef LIB_H
#define LIB_H

struct FileData {
    double start_value;
    double end_value;
    unsigned int points;
    double step;
    char group_name[100];
    char student_name[200];
};

struct FileData read_starting_file();
void read_binary_file(const char *filename);
void write_table(struct FileData data);

#endif //LIB_H
