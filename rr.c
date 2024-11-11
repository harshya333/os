#include <stdio.h>
#define MAX_PROCESSES 10
int main() {
    int n, i, quantum;
    int burst_time[MAX_PROCESSES], remaining_time[MAX_PROCESSES];
    int process_order[MAX_PROCESSES], waiting_time[MAX_PROCESSES] = {0}, turnaround_time[MAX_PROCESSES] = {0};
    int arrival_time[MAX_PROCESSES];
    int current_time = 0;
    int complete = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
       
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
      
    }
    printf("Enter the arrival time for each process:\n");
    for (i = 0; i < n; i++) {
      
        scanf("%d", &arrival_time[i]);
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    while (complete < n) {
        int found_process = 0; // Flag to check if any process is executed in this cycle
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && arrival_time[i] <= current_time) {
                found_process = 1; // We have found a process to execute
                if (remaining_time[i] > quantum) {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    current_time += remaining_time[i];
                    waiting_time[i] = current_time - burst_time[i] - arrival_time[i]; // Calculate waiting time
                    if (waiting_time[i] < 0) {
                        waiting_time[i] = 0; // Ensure waiting time is not negative
                    }
                    turnaround_time[i] = waiting_time[i] + burst_time[i]; // Calculate turnaround time
                    remaining_time[i] = 0; // Mark process as completed
                    complete++;
                }
            }
        }
        if (!found_process) {
            current_time++;
        }
    }
    double avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", process_order[i], burst_time[i],
               arrival_time[i], waiting_time[i], turnaround_time[i]);
    }
  avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}
