#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DIRECTIONS 4
#define TOTAL_CYCLE_TIME 120

typedef struct {
    double min_cost;
    int time_allocated;
} DPState;

void allocate_green_times(double exact_times[], int green_times[]) {
    DPState dp[DIRECTIONS + 1][TOTAL_CYCLE_TIME + 1];
    int remaining_time;

    for (int i = 0; i <= DIRECTIONS; i++) {
        for (int t = 0; t <= TOTAL_CYCLE_TIME; t++) {
            if (i == 0) {
                dp[i][t].min_cost = (t == 0) ? 0 : INFINITY;
            } else {
                dp[i][t].min_cost = INFINITY;
            }
            dp[i][t].time_allocated = -1;
        }
    }

    for (int i = 1; i <= DIRECTIONS; i++) {
        for (int t = 0; t <= TOTAL_CYCLE_TIME; t++) {
            for (int alloc = 0; alloc <= t; alloc++) {
                double cost = pow(alloc - exact_times[i-1], 2);
                double total_cost = dp[i-1][t-alloc].min_cost + cost;
                if (total_cost < dp[i][t].min_cost) {
                    dp[i][t].min_cost = total_cost;
                    dp[i][t].time_allocated = alloc;
                }
            }
        }
    }

    remaining_time = TOTAL_CYCLE_TIME;
    for (int i = DIRECTIONS; i >= 1; i--) {
        green_times[i-1] = dp[i][remaining_time].time_allocated;
        remaining_time -= green_times[i-1];
    }
}

void schedule_traffic(int queue_lengths[], int cycle_num, FILE *report_file, int save_to_file, int total_vehicles[], int *total_time) {
    char *lanes[DIRECTIONS] = {"North", "South", "East", "West"};
    int total_vehicles_in_cycle = 0;
    double exact_times[DIRECTIONS];
    int green_times[DIRECTIONS] = {0};

    printf("\n--- Traffic Cycle %d ---\n", cycle_num);
    if (save_to_file) fprintf(report_file, "\n--- Traffic Cycle %d ---\n", cycle_num);

    for (int i = 0; i < DIRECTIONS; i++) {
        total_vehicles_in_cycle += queue_lengths[i];
    }

    if (total_vehicles_in_cycle == 0) {
        for (int i = 0; i < DIRECTIONS; i++) {
            green_times[i] = 30;
        }
    } else {
        for (int i = 0; i < DIRECTIONS; i++) {
            exact_times[i] = (queue_lengths[i] * TOTAL_CYCLE_TIME * 1.0) / total_vehicles_in_cycle;
        }
        allocate_green_times(exact_times, green_times);
    }

    for (int i = 0; i < DIRECTIONS; i++) {
        printf("%s: %d seconds (Queue: %d)\n", lanes[i], green_times[i], queue_lengths[i]);
        if (save_to_file) {
            fprintf(report_file, "%s: %d seconds (Queue: %d)\n", lanes[i], green_times[i], queue_lengths[i]);
        }
        total_vehicles[i] += queue_lengths[i];
    }
    *total_time += TOTAL_CYCLE_TIME;
}

void calculate_average(int total_vehicles[], int total_time) {
    printf("\n--- Average Vehicles Per Minute ---\n");
    for (int i = 0; i < DIRECTIONS; i++) {
        double avg_per_min = (double)total_vehicles[i] / (total_time / 60.0);
        printf("%s: %.2f cars per minute\n", 
              (i == 0 ? "North" : (i == 1 ? "South" : (i == 2 ? "East" : "West"))), avg_per_min);
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

        printf("\nSave to file? (yes/no): ");
        scanf("%s", save_choice);
        if (strcmp(save_choice, "yes") == 0) {
            save_to_file = 1;
            report_file = fopen("traffic_report.txt", "w");
        }

        printf("\nInput type (dataset/manual): ");
        scanf("%s", choice);

        if (strcmp(choice, "dataset") == 0) {
            file = fopen("traffic_input.csv", "r");
            if (file == NULL) return 1;
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
        } 
        else if (strcmp(choice, "manual") == 0) {
            int num_cycles;
            printf("Number of traffic cycles: ");
            scanf("%d", &num_cycles);

            for (int c = 1; c <= num_cycles; c++) {
                printf("\nVehicle queue lengths for Cycle %d:\n", c);
                for (int i = 0; i < DIRECTIONS; i++) {
                    printf("%s: ", (i == 0 ? "North" : (i == 1 ? "South" : (i == 2 ? "East" : "West"))));
                    scanf("%d", &queue_lengths[i]);
                }
                schedule_traffic(queue_lengths, c, report_file, save_to_file, total_vehicles, &total_time);
            }
        }
        
        if (report_file != NULL) fclose(report_file);
        calculate_average(total_vehicles, total_time);
        printf("\nContinue? (yes/no): ");
        scanf("%s", again);
    } while (strcmp(again, "yes") == 0);
    printf("Program exited.\n");
    return 0;
}