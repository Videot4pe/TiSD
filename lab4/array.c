#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_ELEM 100
#define N 3
unsigned long tick(void)
{
  unsigned long d;
  __asm__ __volatile__ ("rdtsc" : "=A" (d) );
  return d;
}

typedef struct queue_m
{
    int data[MAX_ELEM];
    int pin;
    int pout;
    int full;
} queue_m;


int dequeue (queue_m * queue)
{
    if (!(queue->full) && queue->pout == queue->pin)
    {
        return 0;
    }

    queue->full = 0;

    queue->data[queue->pout] = 0;
    queue->pout = (queue->pout + 1) % MAX_ELEM;

    return 1;
}

int inqueue (queue_m * queue)
{
    if (queue->full)
    {
        return 0;
    }

    if ((queue->pin + 1) % MAX_ELEM == queue->pout)
    {
        queue->full = 1;
    }

    queue->data[queue->pin] = 1;
    queue->pin = (queue->pin + 1) % MAX_ELEM;

    return 1;
}

queue_m init_queue()
{
    queue_m queue;
    for (int i = 0; i < MAX_ELEM; ++i)
        queue.data[i] = 0;
    queue.pin = 0;
    queue.pout = 0;
    queue.full = 0;

    return queue;
}

int print (queue_m * queue)
{
    int max = 0;
	for (int i = 0; i < MAX_ELEM; ++i)
        if (queue->data[i] == 1)
            max++;
    //if (max < 100)
    //{
    	printf("%d\n", max);
    	return max;
	// }
 //    else
 //    }
 //    	printf("100\n");
 //    	return 100;
 //    }
}

int main(int argc, char const *argv[])
{
    while(1)
    {
        printf("------ Array ------\n");
        printf("Start / exit (1 / 0): ");
        int a = getc(stdin);
        printf("\n");

        if (a == '1')
        {
        	int sr = 0;
	        int qt = 0;
	        double time_p = 0;
	        int time_o = 0;
	        int times = 0;
        	queue_m queue = init_queue();
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