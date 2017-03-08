#include "dataStructures.h"
#include "elev.h"
#include "buttons.h"
#include "orders.h"
#include "fsm.h"
#include <stdio.h>


void main_handleOrder(ButtonPress b){
	OrderState state;
	if(b.button == BUTTON_COMMAND){
		state = LOCAL;
	}
	else{
		state = LOCAL;
	}
	elev_set_button_lamp(b.button, b.floor, true);
	if(orders_addOrder(b, state) && state == GLOBAL){
		//ask for cost  from other systems
	}
}

void main_clearOrders(int floor){
	orders_clearOrders(floor);
	for (int button = 0; button < N_BUTTONS; button++){
		elev_set_button_lamp(button, floor, false);
	}
}

int main(){
	elev_init();
	fsm_init(true);
	orders_init();
	buttons_init(); //Order matters here: Make sure buttons is last
	printf("init over\n");
	while (true){
		//aint doin shiet;
		if(elev_get_stop_signal()){
			break;
		}
	}
}