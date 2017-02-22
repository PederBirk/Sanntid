#include "buttons.h"
#include "dataStructures.h"

void main_handleOrder(Order o){
	if(orders_orderExists(o)){
		elev_set_button_lamp(o.button, o.floor, true);
		return;
	}
	if(o.button == BUTTON_COMMAND){
		orders_addOrder(o);
	}
	else{
		//In future: do network thing with cost and whatnot
		orders_addOrder(o);
	}
}



int main(){
	elev_init();
	buttons_init();
	while true{
		//aint doin shiet;
	}
}