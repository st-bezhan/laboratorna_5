#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FileData {
    double start_value;
    double end_value;
    unsigned int points;
    double step;
    char group_name[100];
    char student_name[200];
};

struct FileData read_starting_file() {
    FILE *file = fopen("..//file.txt", "r");
    if (file == NULL) {
        printf("\nUnable to open the file");
        exit(1);
    }
    double start_value, end_value, step;
    unsigned int points;
    char group_code[100], name[100], surname[100], full_name[200] = "";
    fscanf(file, "%lf", &start_value);
    fscanf(file, "%lf", &end_value);
    fscanf(file, "%u", &points);
    fscanf(file, "%lf", &step);
    fscanf(file, "%s", &group_code);
    fscanf(file, "%s", &name);
    fscanf(file, "%s", &surname);
    fclose(file);

    struct FileData data = {
        .start_value = start_value,
        .end_value = end_value,
        .points = points,
        .step = step,
    };

    snprintf(full_name, sizeof(full_name), "%s %s", name, surname);
    strcpy(data.group_name, group_code);
    strcpy(data.student_name, full_name);

    return data;
}
void read_binary_file(const char *filename) {
    FILE *binary_file = fopen(filename, "rb");

    if (binary_file == NULL) {
        printf("Unable to open binary file.\n");
        exit(1);
    }

    unsigned int points;
    fread(&points, sizeof(points), 1, binary_file);
    printf("Number of points: %u\n", points);

    double *values = (double *)malloc(2 * points * sizeof(double));
    if (values == NULL) {
        printf("Memory allocation failed.\n");
        fclose(binary_file);
        exit(1);
    }

    for (unsigned int i = 0; i <= points; i++) {
        double x, fX;
        fread(&x, sizeof(double), 1, binary_file);
        fread(&fX, sizeof(double), 1, binary_file);
        printf("N: %u: X: %.3lf, f(X): %.3lf\n", i, x, fX);
    }

    free(values);
    fclose(binary_file);
}

void write_table(struct FileData data) {
    FILE *created_file = fopen("..//new_file.txt", "w");
    FILE *binary_file = fopen("..//binary.bin", "wb");

    if (created_file == NULL || binary_file == NULL) {
        printf("\nUnable to create new file.");
        exit(1);
    }
    fwrite(&data.points, sizeof(data.points), 1, binary_file);
    fputs("******************************************************", created_file);
    fprintf(created_file, "\n|%5s|%20s|%25s|", "N", "X", "F(X)");
    fputs("\n******************************************************", created_file);
    fputs("\n+-----+--------------------+-------------------------+", created_file);

    double current_x = data.start_value;
    unsigned int current_step = 0;

    while (current_step <= data.points) {
        double fX = pow(current_x, 4) - 5 * pow(current_x, 3) - 0.25 * pow(current_x, 2) + 2;
        fprintf(created_file,"\n|%5d|%20.3lf|%25.3lf|", current_step, current_x, fX);
        fputs("\n+-----+--------------------+-------------------------+",created_file);
        fwrite(&current_x, sizeof(double), 1, binary_file);
        fwrite(&fX, sizeof(double), 1, binary_file);
        current_step++;
        current_x += data.step;
    }

    fprintf(created_file, "\n%s", data.group_name);
    fprintf(created_file, "\n%s", data.student_name);
    fclose(created_file);
    fclose(binary_file);
}

int main(void) {
    struct FileData data = read_starting_file();
    write_table(data);
    read_binary_file("..//binary.bin");
    return 0;

}
