
bool orders[N_FLOORS][N_BUTTONS];

bool orders_orderExists(Order o){
	return orders[o.floor][o.button]; //mabye expand this to be more inclusive?
}

void orders_addOrder(Order o){
	orders[o.floor][o.button] = true;
}

void orders_clearOrders(int floor){ //assuming we allways clear all orders on a floor
	for (int button = 0; button < N_BUTTONS; button++){
		orders[floor][button] = false;
	}
}



void orders_init(){
	for(int floor = 0; floor < N_FLOORS; floor++){
		for(int button = 0; button < N_BUTTONS; button++){
			orders[floor][button] = false;
		}
	}
}