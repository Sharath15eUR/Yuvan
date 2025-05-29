#include <stdio.h>
#include <string.h>

#define DAYS_IN_WEEK 7
#define MAX_TASKS_PER_DAY 3
#define TASK_DESCRIPTION_LENGTH 100

typedef struct {
    char nameOfDay[10];
    char taskList[MAX_TASKS_PER_DAY][TASK_DESCRIPTION_LENGTH];
    int numberOfTasks;
} WeekDay;

int main() {
    WeekDay schedule[DAYS_IN_WEEK] = {
        {"Monday"}, {"Tuesday"}, {"Wednesday"}, {"Thursday"},
        {"Friday"}, {"Saturday"}, {"Sunday"}
    };

    char inputDay[10];
    char taskInput[TASK_DESCRIPTION_LENGTH];

    while (1) {
        printf("Enter the day (or type 'exit' to quit): ");
        scanf("%s", inputDay);

        if (strcasecmp(inputDay, "exit") == 0)
            break;

        int dayIndex = -1;
        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            if (strcasecmp(inputDay, schedule[i].nameOfDay) == 0) {
                dayIndex = i;
                break;
            }
        }

        if (dayIndex == -1) {
            printf("Day not recognized. Please try again.\n");
            continue;
        }

        if (schedule[dayIndex].numberOfTasks >= MAX_TASKS_PER_DAY) {
            printf("Maximum number of tasks reached for %s.\n", schedule[dayIndex].nameOfDay);
            continue;
        }

        getchar(); // consume leftover newline character
        printf("Enter the task description: ");
        fgets(taskInput, TASK_DESCRIPTION_LENGTH, stdin);
        taskInput[strcspn(taskInput, "\n")] = '\0'; // remove newline

        strcpy(schedule[dayIndex].taskList[schedule[dayIndex].numberOfTasks], taskInput);
        schedule[dayIndex].numberOfTasks++;
    }

    printf("\n--- Weekly Task Overview ---\n");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s:\n", schedule[i].nameOfDay);
        if (schedule[i].numberOfTasks == 0) {
            printf("  No tasks scheduled\n");
        } else {
            for (int j = 0; j < schedule[i].numberOfTasks; j++) {
                printf("  %d. %s\n", j + 1, schedule[i].taskList[j]);
            }
        }
    }

    return 0;
}
