#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
void *fun1(void *receive); //declaring functions
void *fun2(void *receive);
void *fun3(void *receive);
pthread_mutex_t l; 			//declaring mutex variable
int shared=1;
struct resource
{
	int pen;
	int paper;
	int q_paper;
};
int turn=0;
int main()
{
	printf("Student 1 has pen\n");
	printf("Student 2 has paper\n");
	printf("Student 3 has question paper\n");
	pthread_mutex_init(&l, NULL); //initializing mutex locks
	pthread_t student1, student2,student3;	//declaring thread variable
	struct resource send;					//declaring object of resource
	while(turn<3)
	{
	   	if(turn==0)
		{
			send.paper=1;
			send.q_paper=1;
			turn++;
		}
			if(turn==1)
		{
			send.pen=1;
			send.q_paper=1;
			turn++;
	}
		if(turn==2)
	{
		send.paper=1;
		send.pen=1;
		turn++;
	}
	pthread_create(&student1, NULL, fun1, &send); //creation of thread
	pthread_create(&student2, NULL, fun2, &send);
	pthread_create(&student3, NULL, fun3, &send);
	pthread_join(student1, NULL);
	pthread_join(student2, NULL);				//joining threads
	pthread_join(student3,NULL);
	}	
}
void *fun1(void *receive)
{
    int x;
    int pen=1;
    struct resource *check=(struct resource *)receive;
   	if((check->paper==1)&&(check->q_paper==1))
    {
	    pthread_mutex_lock(&l);			//locking variable l
	    x=shared;
	    x++; 
	    printf("Teacher has given paper and question paper and I have pen\n");
	    sleep(5); 
	    shared=x; 
	    printf("student 1 completed assignment\n");
	    pthread_mutex_unlock(&l);					//unlocking variable
   
  	}
}
void *fun2(void *receive)
{
    int x;
    int paper =2;
    struct resource *check=(struct resource *)receive;
  	 if((check->pen==1)&&(check->q_paper==1))
   {
	    pthread_mutex_lock(&l);
	    x=shared;
	    x++;  
	    printf("Teacher has given pen and question paper and I have paper\n");
	    sleep(5); 				//making this thread sleep for 5 sec
	    shared=x; 
	    printf("student 2 completed assignment\n");
	    pthread_mutex_unlock(&l);
	}
     
}
void *fun3(void *receive)
{
    int x;
    int q_paper=3;
    struct resource *check=(struct resource *)receive;
   	if((check->paper==1)&&(check->pen==1))
   	{
	    pthread_mutex_lock(&l);
	    x=shared;
	    x++;  
	    printf("Teacher has given pen and paper and I have question paper\n");
	    sleep(5); 
	    shared=x; 
	    printf("student 3 completed assignment\n");
	    pthread_mutex_unlock(&l);
	}	
    
}
