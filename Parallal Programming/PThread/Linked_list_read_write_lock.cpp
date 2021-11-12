#include <bits/stdc++.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int thread_count;
long n;
long long total_operation, op_per_thread, search_percent, insert_percent, delete_percent;
pthread_rwlock_t rwlock;

struct list_node_s
{
    int data;
    struct list_node_s *next;
} * head_p;

int search_op(int value, struct list_node_s *head_p);
int insert_op(int value, struct list_node_s **head_p);
int delete_op(int value, struct list_node_s **head_p);
void create_list(int n);
void print();

void *thread_run(void *rank)
{
    long my_rank = (long)rank;
    long long _search = op_per_thread * search_percent / 100LL;
    long long _insert = op_per_thread * insert_percent / 100LL;
    long long _delete = op_per_thread * delete_percent / 100LL;

    while (_search--)
    {
        pthread_rwlock_rdlock(&rwlock);
        search_op(rand() % total_operation, head_p);
        pthread_rwlock_unlock(&rwlock);
    }
    while (_insert--)
    {
        pthread_rwlock_wrlock(&rwlock);
        insert_op(rand() % total_operation, &head_p);
        pthread_rwlock_unlock(&rwlock);
    }
    while (_delete--)
    {
        pthread_rwlock_wrlock(&rwlock);
        delete_op(rand() % total_operation, &head_p);
        pthread_rwlock_unlock(&rwlock);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    create_list(1000);
    search_percent = 80;
    insert_percent = 10;
    delete_percent = 10;

    pthread_rwlock_init(&rwlock, NULL);

    long thread;
    pthread_t *thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
    total_operation = strtol(argv[2], NULL, 10);
    op_per_thread = total_operation / thread_count;

    thread_handles = (pthread_t *)malloc(thread_count * sizeof(pthread_t));
    clock_t begin = clock();

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, thread_run, (void *)thread);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time: %.8lf\n", time_spent * 1000.0);

    pthread_rwlock_destroy(&rwlock);
    free(thread_handles);
    return 0;
}

int search_op(int value, struct list_node_s *head_p)
{
    struct list_node_s *current_p = head_p;

    while (current_p != NULL && current_p->data < value)
        current_p = current_p->next;

    if (current_p == NULL || current_p->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int insert_op(int value, struct list_node_s **head_p)
{
    struct list_node_s *curr_p = *head_p;
    struct list_node_s *pred_p = NULL;
    struct list_node_s *temp_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = (struct list_node_s *)malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;

        if (pred_p == NULL)
            *head_p = temp_p;
        else
            pred_p->next = temp_p;

        return 1;
    }
    else
        return 0;
}

int delete_op(int value, struct list_node_s **head_p)
{
    struct list_node_s *curr_p = *head_p;
    struct list_node_s *pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value)
    {
        if (pred_p == NULL)
        {
            *head_p = curr_p->next;
            free(curr_p);
        }
        else
        {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    }
    else
        return 0;
}

void create_list(int n)
{
    int cn = 0;
    while (n--)
    {
        insert_op(cn += 3, &head_p);
    }
}

void print()
{
    struct list_node_s *tmp = head_p;
    while (tmp != NULL)
    {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    puts("");
}