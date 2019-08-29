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

UltraSonicSensor::UltraSonicSensor(Pin trigger) {
    triggerPin = trigger;
    echoPin = Pin('C', 2);

    setPinMode(triggerPin, output);
    setPinMode(echoPin, input);

    distance = 0;
    status = idle;
    timer2Overflows = 0;
}

void UltraSonicSensor::wait(unsigned long us) {
    status = waiting;
    TCCR2A = (1 << WGM21);
    TCNT2 = 0;
    OCR2A = us * 2;
    TIMSK2 = 0;
    TCCR2B = (1 << CS21); //prescalar: 8
    while (!(TIFR2 & (1 << OCF2A)));
    TCCR2B = 0;
}

void UltraSonicSensor::sendTriggerPulse() {
    setPin(triggerPin, false);
    wait (2);
    setPin(triggerPin, true);
    wait (10);
    setPin(triggerPin, false);

    timer2Overflows = 0;

    //start counting
    TCCR2A = (1 << WGM21);
    TIMSK2 = (1 << OCIE2A);
    OCR2A = 100 * 2;
    TCNT2 = 0;

    //set interrupt to rising edge
    EICRA = (1 << ISC00) | (1 << ISC01);
}

void UltraSonicSensor::timer2CompAHandler() {
    if (status == measuring)
        timer2Overflows ++;
}

void UltraSonicSensor::echoPinRisingEdgeHadler() {
    if (status == waiting) {
        status = measuring;
        
        //start measuring
        TCCR2B = (1 << CS21);

        //change the interrupt to falling edge
        EICRA = (1 << ISC01);
    }
    else if (status == measuring) {
        unsigned long time = timer2Overflows * 100l + TCNT2 / 2;
        float d = time / 58.0f; //approx 
        updateDistance(d);
        
        sendTriggerPulse();
    }
}

float UltraSonicSensor::getDistance() {
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
    EIMSK = (1 << INT0);
    sendTriggerPulse();
}

void UltraSonicSensor::stop() {
    TCCR2B = 0;
    status = idle;
}

void UltraSonicSensor::test() {
    Pin testPin = Pin('B', 5);
    setPinMode(testPin, output);
    setPin(testPin, false);
}

void UltraSonicSensor::updateDistance(float newDistance) {
    // update distance
    distance = newDistance;
}