#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// Custom signal handler to intercept interruptions
void handle_signal(int sig) {
    printf("\n[Signal Handler] Signal %d caught (e.g., Ctrl+C). Process continues...\n", sig);
}

// Helper function to check primality
int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

// Thread 1: Calculates the sum of the first N prime numbers
void* primeSumThread(void* input) {
    int targetCount = *((int*)input);
    int sum = 0, current = 2, primesFound = 0;

    printf("[Prime Thread] Computing sum of the first %d prime numbers...\n", targetCount);

    while (primesFound < targetCount) {
        if (isPrime(current)) {
            sum += current;
            primesFound++;
        }
        current++;
    }

    printf("[Prime Thread] Calculation complete. Sum = %d\n", sum);
    return NULL;
}

// Thread 2: Logs a message every 2 seconds for 100 seconds
void* logEvery2Sec(void* arg) {
    time_t begin = time(NULL);
    printf("[Logger A] Logging every 2 seconds...\n");

    while (difftime(time(NULL), begin) <= 100) {
        printf("[Logger A] Status update...\n");
        sleep(2);
    }

    printf("[Logger A] Logging ended.\n");
    return NULL;
}

// Thread 3: Logs a message every 3 seconds for 100 seconds
void* logEvery3Sec(void* arg) {
    time_t begin = time(NULL);
    printf("[Logger B] Logging every 3 seconds...\n");

    while (difftime(time(NULL), begin) <= 100) {
        printf("[Logger B] Heartbeat signal...\n");
        sleep(3);
    }

    printf("[Logger B] Logging ended.\n");
    return NULL;
}

int main() {
    // Setup signal handling for graceful ignore of Ctrl+C and kill
    struct sigaction action;
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);   // For Ctrl+C
    sigaction(SIGTERM, &action, NULL);  // For kill

    int numPrimes;
    printf("Enter number of primes to sum: ");
    scanf("%d", &numPrimes);

    pthread_t thread1, thread2, thread3;
    clock_t startClock = clock();

    printf("[Main Thread] Initializing threads...\n");

    pthread_create(&thread1, NULL, primeSumThread, &numPrimes);
    pthread_create(&thread2, NULL, logEvery2Sec, NULL);
    pthread_create(&thread3, NULL, logEvery3Sec, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    clock_t endClock = clock();
    double duration = (double)(endClock - startClock) / CLOCKS_PER_SEC;

    printf("[Main Thread] All operations finished.\n");
    printf("[Main Thread] Total execution time: %.2f seconds\n", duration);

    return 0;
}
