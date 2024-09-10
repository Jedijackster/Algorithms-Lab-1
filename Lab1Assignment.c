// Name: Jack Yohn
// ID: 1002056627
// Compile command: gcc -o Lab1Assignment Lab1Assignment.c

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *index;  // Holds indices of counters
    int *count;  // Holds counts of counters
    int size;    // Current number of counters
} CounterSystem;

void initSystem(CounterSystem *system, int n) {
    system->index = (int *)malloc(n * sizeof(int));
    system->count = (int *)malloc(n * sizeof(int));
    system->size = n;
    for (int i = 0; i < n; i++) {
        system->index[i] = i;
        system->count[i] = 0;
    }
}


int binarySearch(int *arr, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void addCounter(CounterSystem *system, int index) {
    if (index >= 0 && index < system->size) {
        system->count[index]++;
    }
}

void subtractCounter(CounterSystem *system, int index) {
    if (index >= 0 && index < system->size) {
        system->count[index]--;
    }
}

void printByIndex(CounterSystem *system) {
    printf("Printing By Index: \n");
    printf("Index:   Count:\n");
    for (int i = 0; i < system->size; i++) {
        printf(" %d         %d\n", system->index[i], system->count[i]);
    }
}

void printByCount(CounterSystem *system) {
    int *tempIndex = (int *)malloc(system->size * sizeof(int));
    int *tempCount = (int *)malloc(system->size * sizeof(int));
    
    for (int i = 0; i < system->size; i++) {
        tempIndex[i] = system->index[i];
        tempCount[i] = system->count[i];
    }
    
    // Simple bubble sort for demonstration; can be replaced with more efficient sort.
    for (int i = 0; i < system->size - 1; i++) {
        for (int j = i + 1; j < system->size; j++) {
            if (tempCount[i] > tempCount[j]) {
                int temp = tempCount[i];
                tempCount[i] = tempCount[j];
                tempCount[j] = temp;

                temp = tempIndex[i];
                tempIndex[i] = tempIndex[j];
                tempIndex[j] = temp;
            }
        }
    }

    printf("Printing By Count: \n");
    printf("Index:   Count:\n");
    for (int i = 0; i < system->size; i++) {
        printf(" %d         %d\n", tempIndex[i], tempCount[i]);
    }

    free(tempIndex);
    free(tempCount);
}

int countInRange(CounterSystem *system, int lower, int upper) {
    int count = 0;
    for (int i = 0; i < system->size; i++) {
        if (system->count[i] >= lower && system->count[i] <= upper) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    CounterSystem system;
    initSystem(&system, n);

    int operation, i, j;
    while (scanf("%d", &operation) != EOF) {
        switch (operation) {
            case 0:
                free(system.index);
                free(system.count);
                return 0;
            case 1:
                printByIndex(&system);
                printf("-----------------\n");
                break;
            case 2:
                printByCount(&system);
                printf("-----------------\n");
                break;
            case 3:
                scanf("%d", &i);
                addCounter(&system, i);
                break;
            case 4:
                scanf("%d", &i);
                subtractCounter(&system, i);
                break;
            case 5:
                scanf("%d %d", &i, &j);
                printf("%d counters valued between %d and %d\n",countInRange(&system, i, j), i, j);
                break;
            default:
                fprintf(stderr, "Unknown operation\n");
                break;
        }
    }

    free(system.index);
    free(system.count);
    return 0;
}
