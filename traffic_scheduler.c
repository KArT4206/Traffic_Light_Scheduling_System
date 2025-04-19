#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIRECTIONS 4
#define TOTAL_CYCLE_TIME 120

void schedule_traffic(int queue_lengths[], int cycle_num) {
    char *lanes[DIRECTIONS] = {"North", "South", "East", "West"};
    int total_vehicles = 0;

    for (int i = 0; i < DIRECTIONS; i++) {
        total_vehicles += queue_lengths[i];
    }

    printf("\n--- Traffic Cycle %d ---\n", cycle_num);

    if (total_vehicles == 0) {
        printf("No traffic detected. Assigning equal time (30 seconds) to each lane.\n");
        for (int i = 0; i < DIRECTIONS; i++) {
            printf("%s: 30 seconds\n", lanes[i]);
        }
    } else {
        for (int i = 0; i < DIRECTIONS; i++) {
            int green_time = (queue_lengths[i] * TOTAL_CYCLE_TIME) / total_vehicles;
            printf("%s: %d seconds (Queue: %d vehicles)\n", lanes[i], green_time, queue_lengths[i]);
        }
    }
}

int main() {
    char choice[10];
    char again[10];

    do {
        int queue_lengths[DIRECTIONS];
        int cycle = 1;
        FILE *file;
        char line[256];

        printf("\nChoose input type (type 'dataset' for file input or 'manual' for user input): ");
        scanf("%s", choice);

        if (strcmp(choice, "dataset") == 0) {
            file = fopen("traffic_input.csv", "r");
            if (file == NULL) {
                printf("Error: Cannot open file.\n");
                return 1;
            }

            fgets(line, sizeof(line), file); // Skip header

            while (fgets(line, sizeof(line), file)) {
                char *token = strtok(line, ",");
                for (int i = 0; i < DIRECTIONS; i++) {
                    if (token != NULL) {
                        queue_lengths[i] = atoi(token);
                        token = strtok(NULL, ",");
                    }
                }
                schedule_traffic(queue_lengths, cycle);
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
                schedule_traffic(queue_lengths, c);
            }

        } else {
            printf("Invalid input choice.\n");
        }

        printf("\nDo you want to continue? (yes/no): ");
        scanf("%s", again);

    } while (strcmp(again, "yes") == 0);

    printf("Program exited. Have a great day!\n");

    return 0;
}
