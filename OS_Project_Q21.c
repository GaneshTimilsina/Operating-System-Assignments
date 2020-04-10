//question no. 21

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

void * cat_fun();
void * mouse_fun();


int NumBowls[15],num=0 ,arr[15];
int NumCats=0,NumMice=0;
sem_t numberOfCats,numberOfMice;
pthread_t th1,th2,th3,th4,th5;
pthread_mutex_t mutex, cat_utex, mouse_mutex;

int main()
{   int num=5,x;
	int cat_sem = sem_init(&numberOfCats,0,5); //Value 0 indicates that the semaphore is to be shared between the threads of process.
	int mouse_sem = sem_init(&numberOfMice,0,5); //Value 0 indicates that the semaphore is to be shared between the threads of process.

	if(cat_sem!=0)//returns 0 (Zero) on initilizing semaphore successfully
	{
		printf("Error in initilizing Cat Semaphore");
	}
	if(mouse_sem!=0)
        {
                printf("Error in initilizing Mouse  Semaphore");
        }
	printf("\n\n==================================================================");
	printf("\nRules:\n");
	printf("1. Cats and mice should never be eating at the same time.\n");
	printf("2. Neither cats nor mice should starve.");
 	printf("\n==================================================================");


	pthread_create(&th1,NULL,cat_fun,NULL);// pthread_create is using for Creating a thread
	sleep(7);
	pthread_create(&th2,NULL,cat_fun,NULL);
	sleep(3);
	pthread_create(&th3,NULL,cat_fun,NULL);
	sleep(6);
	pthread_create(&th4,NULL,cat_fun,NULL);
	pthread_create(&th5,NULL,mouse_fun,NULL);


	pthread_join(th1,NULL); // pthread_join used to join with a terminated thread!!
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	pthread_join(th5,NULL);
	pthread_join(th4,NULL);
}

void * mouse_fun()
{
	NumMice=NumMice+1;
        arr[NumMice]=NumMice;
        int count=NumMice;

        sem_wait(&numberOfMice);
        if(NumMice==1)
        {
        	pthread_mutex_lock(&mouse_mutex);
        }
        printf("\n\nMouse %d Is Eating \n",NumMice);
        printf("Mouse %d Is Sleeping \n",NumMice);
        sleep(5);
        if(count!=arr[count])
        {
                return NULL;
        }
        printf("Mouse %d Woke Up And Starts Eating \n",NumMice);
        sleep(5);

        printf("Mouse %d Has Executed\n",NumMice);

        pthread_mutex_unlock(&mouse_mutex);
}

void * cat_fun()
{
        pthread_mutex_lock(&mutex);
        NumCats=NumCats+1;
        num=num+1;
        printf("\n\nCat%d Has Started It's Execution \n",NumCats);
        printf("Cat %d Is Now Sleeping \n",NumCats);
        sleep(5);

        printf("Cat %d Woke Up \n",NumCats);
        while(NumMice>0)
        {
        sem_destroy(&numberOfMice);
        printf("Mouse %d Is Dead \n",NumMice);
        arr[NumMice]=-1;
        NumMice=NumMice-1;
        }
        printf("Cat %d Is Now Sleeping Again\n",NumCats);
        sleep(5);

        printf("\n\nCat %d Woke Up And Starts Eating\n",NumCats);
        NumBowls[num]=num;
        printf("CAT %d Has Finished It's Execution \n",NumCats);
        pthread_mutex_unlock(&mutex);
}
