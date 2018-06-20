#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3
unsigned long tick(void)
{
  unsigned long d;
  __asm__ __volatile__ ("rdtsc" : "=A" (d) );
  return d;
}

typedef struct node
{
    int data;
    struct node* next;
} node;

typedef struct queue_s
{
    node* pin;
    node* pout;
} queue_s;

int dequeue (queue_s * queue)
{
    if (queue->pout == NULL)
    {
        return 0;
    }

    node* kill = queue->pout;
    queue->pout = queue->pout->next;
    if (queue->pout == NULL)
        queue->pin = NULL;

    free(kill);

    return 1;
}

int inqueue (queue_s * queue) // Типа push для очереди, добавляет последнего
{
    node* new = (node*) malloc(sizeof(node));

    if (new == NULL)
        return 0;

    new->data = 1;
    new->next = NULL;

    if (queue->pin == NULL)
    {
        queue->pin = new;
        queue->pin->next = NULL;
        queue->pout = new;
    }
    else
    {
        queue->pin->next = new;
        queue->pin = queue->pin->next;
    }

    return 1;
}


queue_s init_queue()
{
    queue_s queue;
    queue.pin = NULL;
    queue.pout = NULL;

    return queue;
}

int print (queue_s * queue)
{
    node* cursor = queue->pout;
    int i = 0;
    while (cursor != NULL)
    {
        //printf("%d", cursor->data);
        cursor = cursor->next;
        i++;
    }
    //if (i < 100)
        printf("%d\n", i);
    // else
    // {
    //     printf("100 \n");
    //     i = 100;
    // }
    return i;
}

int main(int argc, char const *argv[])
{
    while(1)
    {
        printf("------ List ------\n");
        printf("Start / exit (1 / 0): ");
        int a = getc(stdin);
        printf("\n");

        if (a == '1')
        {
            //double queuetime = getc(stdin);
            //scanf("Input edge of queue income: %lf", &queuetime);
            int sr = 0;
            int qt = 0;
            double time_p = 0;
            int time_o = 0;
            int times = 0;
            queue_s queue = init_queue();
            double time = 0;
            int result = 0;

            int tick_queue = rand() % 61;
            int tick_oa = rand() % 11;

            int flag = 0;
            unsigned long tb1, te1, tb2, te2, tb3, te3;
            int application = 0;
            tb1 = tick();
            while (result < 1000)
            {
                time++;
                if (tick_queue == 0)
                {
                    tb2 = tick();
                    inqueue(&queue);
                    te2 = tick();
                    application++;
                    tick_queue = rand() % 61;
                }
                else
                    tick_queue--;
                if (tick_oa == 0)
                {
                    tb3 = tick();
                    int l = dequeue(&queue);
                    te3 = tick();
                    if (l)
                    {
                        times++;
                        if (rand() % 11 > 2)
                            inqueue(&queue);
                        else
                        {
                            flag = 1;
                            result++;
                        }
                        tick_oa = rand() % 11;
                    }
                    else
                        time_p++;
                }
                else
                    tick_oa--;

                if (result % 100 == 0 && result != 0 && flag == 1)
                {
                    flag = 0;
                    printf("Tecushyaya dlina ocheredi = ");
                    sr = sr + print(&queue);
                    qt++;
                    printf("Srednyaya dlina ocheredi = %d\n", sr/qt);
                    //printf("Tecushyiy nomer zayavki = %d\n", application);
                }
                //print(&queue);
                //printf("\n");
            }
            te1 = tick();
            printf("\nIdeal time: 3100\n");
            printf("\nTime: %lf\n", time/10);
            printf("\nDifference between real and ideal time: %lf%%\n", (time/10-3100)/31);
            printf("\nTime of waiting: %lf\n", time_p/10);
            printf("\nNumber of trips: %d\n", times);
            printf("\nNumber of application %d\n", application);
            printf("\nTime inqueue = %lu\n", ((te2 - tb2) / N));
            printf("\ntime dequeue = %lu\n", ((te3 - tb3) / N));
        }
        else
        {
            break;
        }
        rewind(stdin);
    }
    return 0;
}