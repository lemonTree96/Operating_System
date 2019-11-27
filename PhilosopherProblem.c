/**
* Toy Linux C implementation of Philosophers problem
* Author: Xzz
* Date: 2019-11-26
**/
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define Number_of_philosophers 5

pthread_mutex_t chopsticks[Number_of_philosophers];
pthread_t philosophers[Number_of_philosophers];
pthread_attr_t attributes[Number_of_philosophers];

void think(int philosopherNumber){
	int sleepTime=rand()%5+1;
	printf(" -- philosopher %d will think for %ds\r\n",philosopherNumber,sleepTime);
	sleep(sleepTime);
}

void pickup(int philosopherNumber){
	int right,left;
	right=((philosopherNumber+1)%Number_of_philosophers);
	left=((philosopherNumber+Number_of_philosophers-1)%Number_of_philosophers);
	if(philosopherNumber & 1){  //odd philosophers
		printf(" --W philosopher %d is waiting to pick up %d chopsticks\r\n",philosopherNumber,right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("     U-> philosopher %d picked up philosopher %d chopsticks ->right\r\n",philosopherNumber,right);
		printf(" --W philosopher %d is waiting to pick up %d chopsticks\r\n",philosopherNumber,left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("     U-> philosopher %d picked up philosopher %d chopsticks ->left\r\n",philosopherNumber,left);	
	}else{
		printf(" --W philosopher %d is waiting to pick up %d chopsticks\r\n",philosopherNumber,left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("     U-> philosopher %d picked up philosopher %d chopsticks ->left\r\n",philosopherNumber,left);
		printf(" --W philosopher %d is waiting to pick up %d chopsticks\r\n",philosopherNumber,right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("     U-> philosopher %d picked up philosopher %d chopsticks ->right\r\n",philosopherNumber,right);	
	}
}

void pickdown(int philosopherNumber){
	printf("    D->philosopher %d will put down him chopsticks\r\n",philosopherNumber);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber+1)%Number_of_philosophers]);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber+Number_of_philosophers)%Number_of_philosophers]);
}

void eat(int philosopherNumber){
	int eatTime=rand()%5+1;
	printf(" --E philosopher %d will eat for %ds\r\n",philosopherNumber,eatTime);
	sleep(eatTime);
}

void *philosopher(void *philosopherNumber){
	while(1){
		think(philosopherNumber);
		pickup(philosopherNumber);
		eat(philosopherNumber);
		pickdown(philosopherNumber);
	}
}
int main(){
	srand(time(NULL));
	int i=0;
	for(i=0;i<Number_of_philosophers;i++){
		pthread_mutex_init(&chopsticks[i],NULL);
	}
	for(i=0;i<Number_of_philosophers;i++){
		pthread_attr_init(&attributes[i]);
	}
	for(i=0;i<Number_of_philosophers;i++){
		pthread_create(&philosophers[i],&attributes[i],philosopher,(void *)(i));
	}
	for(i=0;i<Number_of_philosophers;i++){
		pthread_join(philosophers[i],NULL);
	}
	return 0;


}
