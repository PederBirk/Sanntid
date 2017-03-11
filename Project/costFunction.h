typedef struct{
	int cost;
	const char * ip;
} CostIp;

typedef struct{
	double timeOut;
	CostIp costs[N_ELEVATORS];
	int index;
	ButtonPress b;
	PendingCosts *next;
} PendingCosts;

void cost_handleCost(int cost, ButtonPress b, const char * ip);
void cost_newOrder(ButtonPress b);
void cost_init();