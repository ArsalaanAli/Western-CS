#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
  char name[5];
  int arrivalTime;
  int burstTime;
  int turnaroundTime;
  int waitingTime;
};

int compareByArrival(const void *a, const void *b) {
  return ((struct Process *)a)->arrivalTime -
         ((struct Process *)b)->arrivalTime;
}

int compareByBurst(const void *a, const void *b) {
  return ((struct Process *)a)->burstTime - ((struct Process *)b)->burstTime;
}

void processTestCase(char *input) {
  struct Process processes[1000];
  int numProcesses = 0;

  char *token = strtok(input, " ");
  while (token != NULL) {
    strcpy(processes[numProcesses].name, token);
    token = strtok(NULL, " ");
    processes[numProcesses].arrivalTime = atoi(token);
    token = strtok(NULL, " ");
    processes[numProcesses].burstTime = atoi(token);
    token = strtok(NULL, " ");
    numProcesses++;
  }

  printf("Number of Processes: %d\n", numProcesses);

  printf("Process Scheduling Started\n");

  qsort(processes, numProcesses, sizeof(struct Process), compareByArrival);

  int currentTime = 0;
  int curProcess = 0;
  int progress = 0;
  int arrivedIndex = 0;
  int queue = 0;
  int totWait = 0;
  int totTurn = 0;

  while (curProcess != numProcesses) {
    printf("CPU Time %d:", currentTime);
    while (processes[arrivedIndex].arrivalTime <= currentTime &&
           arrivedIndex < numProcesses) {
      printf(" [%s arrived]", processes[arrivedIndex].name);
      arrivedIndex++;
      queue++;
    }
    if (queue == 0) {
      printf(" None\n");
      currentTime++;
      continue;
    }
    qsort(processes + (curProcess + 1), arrivedIndex - (curProcess + 1),
          sizeof(struct Process), compareByBurst);
    printf(" %s [%d/%d]\n", processes[curProcess].name, progress,
           processes[curProcess].burstTime);
    progress++;
    if (progress > processes[curProcess].burstTime) {
      int curTurn = currentTime - processes[curProcess].arrivalTime;
      int curWait = (currentTime - processes[curProcess].burstTime) -
                    processes[curProcess].arrivalTime;
      printf(
          "Process %s completed with Turnaround Time: %d, Waiting Time: %d\n",
          processes[curProcess].name, curTurn, curWait);
      totTurn += curTurn;
      totWait += curWait;
      curProcess++;
      queue--;
      progress = 0;
      if (queue) {
        printf("CPU Time %d: %s [%d/%d]\n", currentTime,
               processes[curProcess].name, progress,
               processes[curProcess].burstTime);
      }
      progress++;
    }
    currentTime++;
  }
  float avgTurn = (float)totTurn / numProcesses;
  float avgWait = (float)totWait / numProcesses;
  printf("Process scheduling completed with Avg Turnaround Time: %.2f, Avg "
         "Waiting Time: %.2f\n",
         avgTurn, avgWait);
}

int main() {
  FILE *file;

  file = fopen("sjf_input.txt", "r");

  if (file == NULL) {
    perror("Error opening the file");
    return 1;
  }

  char line[1000];
  int testCase = 1;

  while (fgets(line, sizeof(line), file) != NULL) {
    printf("Test case #%d: %s", testCase, line);
    processTestCase(line);
    printf("\n");
    testCase++;
  }

  fclose(file);

  return 0;
}
