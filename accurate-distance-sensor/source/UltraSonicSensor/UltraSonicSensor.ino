/*
    Tester code for UltraSonicSensor Class
 */
#include <avr/interrupt.h>
#include <avr/io.h>
#include "UltraSonicSensor.h"

//sensor at pin
UltraSonicSensor sensor = UltraSonicSensor(Pin('A', 1), Pin('B', 3));

int main() {
    sei(); //enable global interrupts
    sensor.start();

    while (1) {
        //display the distance
        int d = sensor.getDistance();
    }

    return 0;
}

ISR (TIMER2_COMPA_vect) {
    sensor.timer2OverflowHandler();
}

// echo pin interrupt