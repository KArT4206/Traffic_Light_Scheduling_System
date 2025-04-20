#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIRECTIONS 4
#define TOTAL_CYCLE_TIME 120

void schedule_traffic(int queue_lengths[], int cycle_num, FILE *report_file, int save_to_file, int total_vehicles[], int *total_time) {
    char *lanes[DIRECTIONS] = {"North", "South", "East", "West"};
    int total_vehicles_in_cycle = 0;

    printf("\n--- Traffic Cycle %d ---\n", cycle_num);
    if (save_to_file) fprintf(report_file, "\n--- Traffic Cycle %d ---\n", cycle_num);

    for (int i = 0; i < DIRECTIONS; i++) {
        total_vehicles_in_cycle += queue_lengths[i];
    }

    if (total_vehicles_in_cycle == 0) {
        printf("No traffic detected. Assigning equal time (30 seconds) to each lane.\n");
        if (save_to_file) fprintf(report_file, "No traffic detected. Assigning equal time (30 seconds) to each lane.\n");

        for (int i = 0; i < DIRECTIONS; i++) {
            printf("%s: 30 seconds\n", lanes[i]);
            if (save_to_file) fprintf(report_file, "%s: 30 seconds\n", lanes[i]);
        }
    } else {
        for (int i = 0; i < DIRECTIONS; i++) {
            int green_time = (queue_lengths[i] * TOTAL_CYCLE_TIME) / total_vehicles_in_cycle;
            printf("%s: %d seconds (Queue: %d vehicles)\n", lanes[i], green_time, queue_lengths[i]);
            if (save_to_file) {
                fprintf(report_file, "%s: %d seconds (Queue: %d vehicles)\n", lanes[i], green_time, queue_lengths[i]);
            }

            total_vehicles[i] += queue_lengths[i];
        }
    }

    *total_time += TOTAL_CYCLE_TIME;
}

void calculate_average(int total_vehicles[], int total_time) {
    printf("\n--- Average Vehicles Per Minute ---\n");
    for (int i = 0; i < DIRECTIONS; i++) {
        double avg_per_min = (double)total_vehicles[i] / (total_time / 60.0);
        printf("%s: %.2f cars per minute\n", (i == 0 ? "North" : (i == 1 ? "South" : (i == 2 ? "East" : "West"))), avg_per_min);
    }
}

int main() {
    char choice[10];
    char again[10];

    do {
        int queue_lengths[DIRECTIONS];
        int cycle = 1;
        FILE *file;
        FILE *report_file = NULL;
        char line[256];
        char save_choice[10];
        int save_to_file = 0;
        int total_vehicles[DIRECTIONS] = {0};
        int total_time = 0;

        printf("\nDo you want to save the traffic cycles to a text file? (yes/no): ");
        scanf("%s", save_choice);
        if (strcmp(save_choice, "yes") == 0) {
            save_to_file = 1;
            report_file = fopen("traffic_report.txt", "w");
            if (report_file == NULL) {
                printf("Error creating report file.\n");
                return 1;
            }
        }

        printf("\nChoose input type (type 'dataset' for file input or 'manual' for user input): ");
        scanf("%s", choice);

        if (strcmp(choice, "dataset") == 0) {
            file = fopen("traffic_input.csv", "r");
            if (file == NULL) {
                printf("Error: Cannot open file.\n");
                return 1;
            }

            fgets(line, sizeof(line), file);

            while (fgets(line, sizeof(line), file)) {
                char *token = strtok(line, ",");
                for (int i = 0; i < DIRECTIONS; i++) {
                    if (token != NULL) {
                        queue_lengths[i] = atoi(token);
                        token = strtok(NULL, ",");
                    }
                }

                schedule_traffic(queue_lengths, cycle, report_file, save_to_file, total_vehicles, &total_time);
                cycle++;
            }

            fclose(file);

        } else if (strcmp(choice, "manual") == 0) {
            char *lanes[DIRECTIONS] = {"North", "South", "East", "West"};
            int num_cycles;

            printf("Enter the number of traffic cycles: ");
            scanf("%d", &num_cycles);

            for (int c = 1; c <= num_cycles; c++) {
                printf("\nEnter vehicle queue lengths for Cycle %d:\n", c);
                for (int i = 0; i < DIRECTIONS; i++) {
                    printf("%s: ", lanes[i]);
                    scanf("%d", &queue_lengths[i]);
                }

                schedule_traffic(queue_lengths, c, report_file, save_to_file, total_vehicles, &total_time);
            }

        } else {
            printf("Invalid input choice.\n");
        }

        if (report_file != NULL) fclose(report_file);

        calculate_average(total_vehicles, total_time);

        printf("\nDo you want to continue? (yes/no): ");
        scanf("%s", again);

    } while (strcmp(again, "yes") == 0);

    printf("Program exited. Have a great day!\n");

    return 0;
}
