#include "dataStructures.h"
#include "elev.h"
#include "buttons.h"
#include "orders.h"
#include "fsm.h"


void main_handleOrder(ButtonPress b){
	OrderState state;
	if(b.button == BUTTON_COMMAND){
		state = LOCAL;
	}
	else{
		state = GLOBAL;
	}
	if(orders_addOrder(b, state) && state == GLOBAL){
		//ask for cost from other systems
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
	fsm_init(false);
	orders_init();
	buttons_init(); //Order matters here: Make sure buttons is last
	while (true){
		//aint doin shiet;
	}
}