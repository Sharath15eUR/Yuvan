#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Check whether a number is prime
int isPrime(int number) {
    if (number < 2) return 0;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

// Thread to compute the sum of the first N prime numbers
void* computePrimeSum(void* arg) {
    int limit = *((int*)arg);
    int count = 0, candidate = 2, total = 0;

    while (count < limit) {
        if (isPrime(candidate)) {
            total += candidate;
            count++;
        }
        candidate++;
    }

    printf("[Prime Sum Thread] Total of first %d primes: %d\n", limit, total);
    return NULL;
}

// Thread that prints a message every 2 seconds for 100 seconds
void* loggerThread1(void* arg) {
    time_t begin = time(NULL);
    while (difftime(time(NULL), begin) <= 100) {
        printf("[Logger 1] Message from Logger 1\n");
        sleep(2);
    }
    return NULL;
}

// Thread that prints a message every 3 seconds for 100 seconds
void* loggerThread2(void* arg) {
    time_t begin = time(NULL);
    while (difftime(time(NULL), begin) <= 100) {
        printf("[Logger 2] Message from Logger 2\n");
        sleep(3);
    }
    return NULL;
}

int main() {
    int n;
    printf("Enter the number of prime numbers to add: ");
    scanf("%d", &n);

    pthread_t primeThread, logThread1, logThread2;

    // Launch threads
    pthread_create(&primeThread, NULL, computePrimeSum, &n);
    pthread_create(&logThread1, NULL, loggerThread1, NULL);
    pthread_create(&logThread2, NULL, loggerThread2, NULL);

    // Wait for all threads to complete
    pthread_join(primeThread, NULL);
    pthread_join(logThread1, NULL);
    pthread_join(logThread2, NULL);

    printf("All threads have finished execution.\n");
    return 0;
}
