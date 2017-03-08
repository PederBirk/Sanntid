#pragma once

bool orders_orderOnFloor(int floor);
bool orders_addOrder(ButtonPress b, OrderState state);
void orders_clearOrders(int floor);
void orders_init();
bool shouldStop(MotorDir dir, int floor);
MotorDir orders_getDirection;