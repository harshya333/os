#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to sort an array
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("Child process (PID: %d) started.\n", getpid());
        sleep(5); // Sleep to demonstrate orphan state if parent terminates first
        printf("Child process after parent is terminated (Orphan state) if parent ends early.\n");
        printf("Sorted array (by child): ");
        bubbleSort(arr, n);
        printArray(arr, n);
        printf("Child process (PID: %d) ends.\n", getpid());
    } 
    else if (pid > 0) { // Parent process
        printf("Parent process (PID: %d) started.\n", getpid());
        bubbleSort(arr, n);
        printf("Sorted array (by parent): ");
        printArray(arr, n);
        wait(NULL); // Waiting for child process to complete
        printf("Parent process ends.\n");
        // After wait, child process goes to zombie state briefly before full termination
    } 
    else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
