// gcc -o threadpool threadpool.c -pthread
// ./threadpool

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 스레드 수와 작업 수 정의
#define NUM_THREADS 3
#define NUM_TASKS 10

// 작업을 나타내는 구조체
typedef struct {
    void (*function)(int);  // 작업 함수 포인터
    int arg;                // 작업 함수에 전달할 인자
} Task;

// 전역 변수로 작업 큐와 작업 개수 선언
Task task_queue[NUM_TASKS];
int task_count = 0;

// 뮤텍스와 조건 변수 초기화
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

// 작업자 스레드 함수
void* worker(void* arg) {
    while (1) {
        Task task;
        
        // 뮤텍스 잠금
        pthread_mutex_lock(&mutex);
        
        // 작업이 없으면 대기
        while (task_count == 0) {
            pthread_cond_wait(&condition, &mutex);
        }
        
        // 작업 큐에서 작업 가져오기
        task = task_queue[--task_count];
        
        // 뮤텍스 해제
        pthread_mutex_unlock(&mutex);
        
        // 작업 실행
        task.function(task.arg);
    }
    return NULL;
}

// 작업을 큐에 추가하는 함수
void add_task(void (*function)(int), int arg) {
    // 뮤텍스 잠금
    pthread_mutex_lock(&mutex);
    
    // 작업 큐에 새 작업 추가
    task_queue[task_count].function = function;
    task_queue[task_count].arg = arg;
    task_count++;
    
    // 대기 중인 스레드에게 신호 보내기
    pthread_cond_signal(&condition);
    
    // 뮤텍스 해제
    pthread_mutex_unlock(&mutex);
}

// 실제 작업을 수행하는 함수
void task_function(int arg) {
    printf("작업 %d 처리 중\n", arg);
    sleep(1);  // 작업을 시뮬레이션하기 위한 1초 대기
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
    // (실제 상황에서는 더 정교한 방법으로 완료를 확인해야 함)
    sleep(NUM_TASKS);
    
    return 0;
}