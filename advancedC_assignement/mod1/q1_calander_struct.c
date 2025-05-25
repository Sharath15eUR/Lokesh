#include <stdio.h>
#include <string.h>

#define MAX_TASKS 3
#define MAX_TASK_LENGTH 100
#define DAYS_IN_WEEK 7


typedef enum {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
} WeekDay;

typedef struct {
    char tasks[MAX_TASKS][MAX_TASK_LENGTH];
    int task_count;
} Day;

int strcmp_ignore_case(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        if (c1 != c2)
            return c1 - c2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int get_weekday_index(const char* input) {
    if (strcmp_ignore_case(input, "Monday") == 0) return MONDAY;
    if (strcmp_ignore_case(input, "Tuesday") == 0) return TUESDAY;
    if (strcmp_ignore_case(input, "Wednesday") == 0) return WEDNESDAY;
    if (strcmp_ignore_case(input, "Thursday") == 0) return THURSDAY;
    if (strcmp_ignore_case(input, "Friday") == 0) return FRIDAY;
    if (strcmp_ignore_case(input, "Saturday") == 0) return SATURDAY;
    if (strcmp_ignore_case(input, "Sunday") == 0) return SUNDAY;
    return -1;
}


void initialize_week(Day week[]) {
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        week[i].task_count = 0;
    }
}


void input_tasks(Day week[]) {
    char day_input[20];
    printf("Enter day name: ");
    scanf("%s", day_input);

    int day_index = get_weekday_index(day_input);
    if (day_index == -1) {
        printf("Invalid day name\n");
        return;
    }

    Day* current_day = &week[day_index];
    int remaining = MAX_TASKS - current_day->task_count;

    if (remaining == 0) {
        printf("Task limit reached for that day.\n");
        return;
    }

    printf("more %d task can be added\n", remaining);

    for (int i = 0; i < remaining; i++) {
        char buffer[MAX_TASK_LENGTH];
        printf("Enter task %d or done to stop: ", current_day->task_count + 1);
        scanf(" %[^\n]", buffer);  
        if (strcmp_ignore_case(buffer, "done") == 0)
            break;

        strcpy(current_day->tasks[current_day->task_count], buffer);
        current_day->task_count++;
    }
}


void display_tasks(Day week[]) {
    const char* day_names[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    printf("\n--- Weekly Tasks ---\n");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s:\n", day_names[i]);  // Display the name of the day
        if (week[i].task_count == 0) {
            printf("  No tasks\n");
        } else {
            for (int j = 0; j < week[i].task_count; j++) {
                printf("  - %s\n", week[i].tasks[j]);
            }
        }
    }
}

int main() {
    Day week[DAYS_IN_WEEK];
    int choice;

    initialize_week(week);

    do {
        printf("\nMenu:\n");
        printf("1.Add tasks to a day\n");
        printf("2.Display all tasks\n");
        printf("3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                input_tasks(week);
                break;
            case 2:
                display_tasks(week);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
