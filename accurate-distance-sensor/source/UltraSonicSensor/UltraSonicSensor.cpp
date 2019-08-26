#include "UltraSonicSensor.h"
#include <avr/io.h>

void UltraSonicSensor::setPin(Pin pin, bool value) {
    switch (pin.port) {
        case 'B':
            if (value)
                PORTB |= (1 << pin.pin);
            else 
                PORTB &= !(1 << pin.pin);

            break;
            
        case 'C':
            if (value)
                PORTC |= (1 << pin.pin);
            else 
                PORTC &= !(1 << pin.pin);

            break;
            
        case 'D':
            if (value)
                PORTD |= (1 << pin.pin);
            else 
                PORTD &= !(1 << pin.pin);

            break;
    }
}

bool UltraSonicSensor::readPin(Pin pin) {
    switch (pin.port) {
        case 'B':
            return PINB & (1 << pin.pin);
        case 'C':
            return PINC & (1 << pin.pin);
        case 'D':
            return PIND & (1 << pin.pin);
    }
}

void UltraSonicSensor::setPinMode(Pin pin, PinMode mode) {
    switch (pin.port) {
        case 'B':
            if (mode) 
                DDRB |= (1 << pin.pin);
            else 
                DDRB &= !(1 << pin.pin);

        case 'C':
            if (mode) 
                DDRC |= (1 << pin.pin);
            else 
                DDRC &= !(1 << pin.pin);

        case 'D':
            if (mode) 
                DDRD |= (1 << pin.pin);
            else 
                DDRD &= !(1 << pin.pin);
    }
}

UltraSonicSensor::UltraSonicSensor(Pin trigger, Pin echo) {
    triggerPin = trigger;
    echoPin = echo;

    setPinMode(triggerPin, output);
    setPinMode(echoPin, input);

    distance = 0;
    status = idle;
    timer2Overflows = 0;
}

void UltraSonicSensor::wait(int us) {
    TCCR2A = (1 << WGM21);
    OCR2A = us * 2;
    TCCR2B = (1 << CS21);
    TIMSK2 &= !(1 << OCIE2A);
    while (!(TIFR2 & (1 << OCF2A)));
    TCCR2B = 0;
}

void UltraSonicSensor::sendTriggerPulse() {
    setPin(triggerPin, false);
    wait (10);
    setPin(triggerPin, true);
    wait (50);
    setPin(triggerPin, false);

    status = measuring;
    timer2Overflows = 0;

    //start counting
    TCCR2A = (1 << WGM21);
    TIMSK2 |= (1 << OCIE2A);
    OCR2A = 100 * 2;
    TCCR2B = (1 << CS21);
}

void UltraSonicSensor::timer2OverflowHandler() {
    if (status == measuring)
        timer2Overflows ++;
}

void UltraSonicSensor::echoPinRisingEdgeHadler() {
    if (status == measuring) {
        int time = timer2Overflows * 100 + TCNT1 / 2;
        distance = time * 34 / 100; //approx distance
        
        sendTriggerPulse();
    }
}

int UltraSonicSensor::getDistance() {
    return distance;
}

Pin::Pin() {
    port = 'D';
    pin = 0;
}

Pin::Pin(char Port, int Pin) {
    pin = Pin;
    port = Port;
}

void UltraSonicSensor::start() {
    sendTriggerPulse();
}

void UltraSonicSensor::stop() {
    TCCR2B = 0;
    status = idle;
}