#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *accounts;
pthread_mutex_t *mutex;

void withdraw(char *account, int amount) {
  int accountNumber;
  sscanf(account, "A%d", &accountNumber);
  accountNumber--;
  pthread_mutex_lock(&mutex[accountNumber]);
  if (amount <= accounts[accountNumber]) {
    accounts[accountNumber] -= amount;
  }
  pthread_mutex_unlock(&mutex[accountNumber]);
}

void deposit(char *account, int amount) {
  int accountNumber;
  sscanf(account, "A%d", &accountNumber);
  accountNumber--;
  pthread_mutex_lock(&mutex[accountNumber]);
  accounts[accountNumber] += amount;
  pthread_mutex_unlock(&mutex[accountNumber]);
}

void *handleThread(void *arg) {
  char *line = (char *)arg;
  char method[20];
  char account[20];
  int amount;
  char *token = strtok(line, " ");
  token = strtok(NULL, " ");
  while (token != NULL) {
    strcpy(method, token);
    token = strtok(NULL, " ");
    strcpy(account, token);
    token = strtok(NULL, " ");
    amount = atoi(token);

    if (method[0] == 'd') {
      deposit(account, amount);
    } else if (method[0] == 'w') {
      withdraw(account, amount);
    } else {
      printf("ERROR: IMPROPER COMMAND:\n %s %s %d\n", method, account, amount);
    }
    token = strtok(NULL, " ");
  }
  // printf("Thread: %s\n", line);
  free(line);
  pthread_exit(NULL);
}

int main(void) {
  FILE *file;
  char line[10000];
  int numAccounts = 0;
  int numClients = 0;

  file = fopen("assignment_5_input.txt", "r");
  while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == 'A') {
      numAccounts++;
    }
    if (line[0] == 'C') {
      numClients++;
    }
  }
  fclose(file);

  accounts = (int *)malloc((numAccounts + 1) * sizeof(int));
  mutex = (pthread_mutex_t *)malloc(numAccounts * sizeof(pthread_mutex_t));
  pthread_t clientThreads[numClients];
  file = fopen("assignment_5_input.txt", "r");
  for (int i = 0; i < numAccounts; i++) {
    if (fgets(line, sizeof(line), file) != NULL) {
      char *token = strtok(line, " ");
      token = strtok(NULL, " ");
      token = strtok(NULL, " ");
      accounts[i] = atoi(token);
      pthread_mutex_init(&mutex[i], NULL);
    }
  }

  for (int i = 0; i < numClients; i++) {
    if (fgets(line, sizeof(line), file) != NULL) {

      char *lineCopy = strdup(line);

      pthread_create(&clientThreads[i], NULL, handleThread, (void *)lineCopy);
    }
  }

  fclose(file);
  for (int i = 0; i < numClients; ++i) {
    pthread_join(clientThreads[i], NULL);
  }
  printf("No. of Accounts: %d\n", numAccounts);
  printf("No. of Clients: %d\n", numClients);
  for (int i = 0; i < numAccounts; ++i) {
    printf("Account %d: %d\n", i + 1, accounts[i]);
		pthread_mutex_destroy(&mutex[i]);
  }

  return 0;

  // if transaction -> -bal, ignore transaction
}