/*
    Tester code for UltraSonicSensor Class
 */
#include <avr/interrupt.h>
#include <avr/io.h>
#include "UltraSonicSensor.h"

//sensor at pin
UltraSonicSensor sensor = UltraSonicSensor(Pin('D', 0));

int main() {
    sei(); //enable global interrupts
    Serial.begin(9600);
    Serial.print("Hello\n");
    sensor.start();

    while (1) {
        //display the distance
        unsigned long d = sensor.getDistance();
        Serial.print(d);
        Serial.print('\n');
    }

    return 0;
}

ISR (TIMER2_COMPA_vect) {
    sensor.timer2CompAHandler();
}

ISR (INT0_vect) {
    sensor.echoPinRisingEdgeHadler();
}