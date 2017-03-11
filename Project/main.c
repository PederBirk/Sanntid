#include "dataStructures.h"
#include "elev.h"
#include "config.h"
#include "buttons.h"
#include "orders.h"
#include "fsm.h"
#include "costFunction.h"
#include "network.h"
#include <stdio.h>

const char *ips[N_ELEVATORS - 1] = {"129.241.187.154"};

void main_shareOrder(ButtonPress b){
	cost_newOrder(b);
	for(int i = 0; i < N_ELEVATORS - 1; i++){
		network_sendRequestCost(b, ips[i]);
	}
}

void main_handleOrder(ButtonPress b, OrderState state){
	if(b.button == BUTTON_COMMAND){
		elev_set_button_lamp(b.button, b.floor, true);
		orders_addOrder(b, LOCAL);
		return;
	}
	if(state == NONE){
		elev_set_button_lamp(b.button, b.floor, true);
		if(orders_addOrder(b, GLOBAL)){
			main_shareOrder(b);
		}
		return;
	}
	orders_addOrder(b, state);
}

void main_clearOrders(int floor, bool broadCast){
	orders_clearOrders(floor);
	if(broadCast){
		network_sendClearFloor(floor);
	}
	for (int button = 0; button < N_BUTTONS; button++){
		elev_set_button_lamp(button, floor, false);
	}
}

int main(){
	elev_init();
	fsm_init(true);
	orders_init();
	cost_init();
	network_init();
	buttons_init(); //Order matters here: Make sure buttons is last
	printf("init over\n");
	while (true){
		//aint doin shiet;
		if(elev_get_stop_signal()){
			printf("Stop button pressed, stopping program\n");
			break;
		}
	}
}
