#include "config.h"
#include "dataStructures.h"
#include "costFunction.h"
#include "network.h"
#include "main.h"
#include "timer.h"
#include "orders.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

PendingCosts * first;

void cost_newOrder(ButtonPress b){
	PendingCosts *p = malloc(sizeof(PendingCosts));
	p->timeOut = timer_getTime() + COST_TIMEOUT;
	(p->costs[0]).cost = orders_calculateCost(b);
	(p->costs[0]).ip = 0;
	p->index = 1;
	p->b = b;
	p->next = first;
	first = p
}


void cost_handleCost(int cost, ButtonPress b, const char * ip){
	PendingCosts *p = first;
	while(p != NULL){
		if(p->b == b){
			p->costs[p->index].cost = cost; //Probably want a semaphore or something here
			p->costs[p->index].ip = ip;
			p->index++;
		}
		p = p->next;
	}
}

void *checkCostTimeout(){
	while(true){
		double currentTime = timer_getTime(); //assume time remains constant through running of function, even though it might not :s
		PendingCosts *p = first;
		while(p != NULL){
			if(p->timeOut < currentTime){
				int lowestCost = p->costs[0].cost;
				char * returnIp = 0;
				for(int i = 1; i < N_ELEVATORS; i++){
					if(p->costs[i].cost < lowestCost){
						lowestCost = p->costs[i].cost;
						returnIp = p->costs[i].ip;
					}
				}
				if(returnIp != 0){
					network_sendDelegateOrder(p->b, returnIp);
					clearPendingCosts(p->b);
				}
				else{
					main_handleOrder(p->b, LOCAL);
					clearPendingCosts(p->b);
				}
			}
		}
		usleep(CHECK_FOR_COST_TIMEOUT_INTERVAL * 1000);
	}
}

void clearPendingCosts(ButtonPress b){
	PendingCosts *p = first;
	PendingCosts *prev = NULL;
	while(p != NULL){
		if(p->b == b){
			if(prev == NULL){
				first = NULL;
				free(p);
			}
			else{
				prev->next = p->next;
				free(p);
			}
			break;
		}
		prev = p;
		p = p->next;
	}
}

void cost_init(){
	first = NULL;
	pthread_t checkCostTimeoutThread;
	pthread_create(&checkCostTimeoutThread, NULL, checkCostTimeout, NULL);
}