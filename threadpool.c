// gcc -o threadpool threadpool.c -pthread
// ./threadpool

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_TASKS 10

typedef struct {
    void (*function)(int);
    int arg;
} Task;

Task task_queue[NUM_TASKS];
int task_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void* worker(void* arg) {
    while (1) {
        Task task;
        
        pthread_mutex_lock(&mutex);
        while (task_count == 0) {
            pthread_cond_wait(&condition, &mutex);
        }
        
        task = task_queue[--task_count];
        pthread_mutex_unlock(&mutex);
        
        task.function(task.arg);
    }
    return NULL;
}

void add_task(void (*function)(int), int arg) {
    pthread_mutex_lock(&mutex);
    
    task_queue[task_count].function = function;
    task_queue[task_count].arg = arg;
    task_count++;
    
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
}

void task_function(int arg) {
    printf("Task %d is being processed\n", arg);
    sleep(1);  // 작업을 시뮬레이션하기 위한 대기
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // 작업자 스레드 생성
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }
    
    // 작업 추가
    for (int i = 0; i < NUM_TASKS; i++) {
        add_task(task_function, i);
    }
    
    // 모든 작업이 완료될 때까지 대기
    sleep(NUM_TASKS);
    
    return 0;
}