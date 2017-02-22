#include <pthread.h>
#include "elev.h"
#include "main.h"
#include "dataStructures.h"

bool previousButtonStates[N_FLOORS][N_BUTTONS]; //Mabye check zero-indexing here?

void *buttonListener(){
	while true{
		for(int floor = 0; floor < N_FLOORS; floor++){
			for(int button = 0; button < N_BUTTONS; button++){
				Order o;
				o.floor = floor;
				o.button = button;
				main_handleOrder(o)
			}
		}
		//Sleep for a little while, 50ms or so mabye?
	}
}

bool readButton(int floor, elev_button_type_t button){ //Only returns true when button goes from unpressed to pressed
	if(elev_get_button_signal(button, floor) != previousButtonStates[floor][button]){
		previousButtonStates[floor][button] = elev_get_button_signal(button, floor);
		if(previousButtonStates[floor][button]){
			return true;
		}
	}
}

void buttons_init(){
	for(int floor = 0; floor < N_FLOORS; floor++){
		for(int button = 0; button < N_BUTTONS; button++){
			previousButtonStates[floor][button] = false;
		}
	}
	pthread_t buttonListenerThread;
	pthread_create(&buttonListenerThread, NULL, buttonListener, NULL);
}