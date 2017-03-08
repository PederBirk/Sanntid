#include <pthread.h>
#include "elev.h"
#include "main.h"
#include "dataStructures.h"
#include <unistd.h>
#define BUTTONS_LISTENER_INTERVAL 50

static bool previousButtonStates[N_FLOORS][N_BUTTONS];

void *buttonListener(){
	while(true){
		for(int floor = 0; floor < N_FLOORS; floor++){
			for(int button = 0; button < N_BUTTONS; button++){
				if(readButton(floor, button)){
					ButtonPress b;
					b.floor = floor;
					b.button = button;
					main_handleOrder(b);
				}
			}
		}
		usleep(BUTTONS_LISTENER_INTERVAL * 1000);
	}
}

bool readButton(int floor, ButtonType button){ //Only returns true when button goes from unpressed to pressed
	if(elev_get_button_signal(button, floor) != previousButtonStates[floor][button]){
		previousButtonStates[floor][button] = elev_get_button_signal(button, floor);
		return previousButtonStates[floor][button];
	}
	return false;
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