// para compilar: gcc prodcons_1_thread_varcond.c -o prodcons_1_thread_varcond -lpthread
// para executar: prodcons_1_thread_varcond
//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_PRODUCED 17
#define MAX_QUEUE 7

pthread_cond_t cond_queue_empty, cond_queue_full;
pthread_mutex_t item_queue_cond_lock;

int queue[MAX_QUEUE], item_available=0, produced=0, consumed=0;

/* other data structures here */

int create_item(void) {

	return(rand()%1000);

} //fim  create_item()

void insert_into_queue(int item) {

	
	queue[item_available++] = item;
	produced++;
	printf("producing item:%d, value:%d, queued:%d \n", produced, item, item_available); 
	return;

} // fim insert_into_queue()

int extract_from_queue() {

	consumed++;
	printf("cosuming item:%d, value:%d, queued:%d \n", consumed, queue[item_available-1], item_available-1); 
	
	return(queue[--item_available]);

} // fim extract_from_queue()

void process_item(int my_item) {
	static int printed=0;

	printf("Printed:%d, value:%d, queued:%d \n", printed++, my_item, item_available);

	return;

} // fim_process_item()

void *producer(void) {
	int item;
	while (produced < MAX_PRODUCED ) {
		item = create_item();
		pthread_mutex_lock(&item_queue_cond_lock);
		while (item_available == MAX_QUEUE)
			pthread_cond_wait(&cond_queue_empty, &item_queue_cond_lock);
		insert_into_queue(item);
        pthread_cond_signal(&cond_queue_full);
        pthread_mutex_unlock(&item_queue_cond_lock);
	}
	pthread_exit(0);
} // fim producer
void *consumer(void) {
	int my_item = 0;
	while (consumed < MAX_PRODUCED) {
		pthread_mutex_lock(&item_queue_cond_lock);
        	while (item_available == 0)
        		pthread_cond_wait(&cond_queue_full, &item_queue_cond_lock);
        	my_item = extract_from_queue();
        	pthread_cond_signal(&cond_queue_empty);
        	pthread_mutex_unlock(&item_queue_cond_lock);
        	process_item(my_item);
	}
	pthread_exit(0);
} // fim_consumer


int main(void) {
	pthread_t prod_handle, cons_handle;

	/* declarations and initializations */
    	item_available = 0;

    	pthread_cond_init(&cond_queue_empty, NULL);
    	pthread_cond_init(&cond_queue_full, NULL);
    	pthread_mutex_init(&item_queue_cond_lock, NULL);
    	/* create and join producer and consumer threads */

	if (pthread_create(&prod_handle, 0, (void *) producer, (void *) 0) != 0) { 
		printf("Error creating thread producer! Exiting! \n");
		exit(0);
	}
	if (pthread_create(&cons_handle, 0, (void *) consumer, (void *) 0) != 0) { 
		printf("Error creating thread consumer! Exiting! \n");
		exit(0);
	}

	pthread_join(prod_handle, 0);
	pthread_join(cons_handle, 0);

	exit(0);	
} // main()
