#ifndef ULTRASONIC_SENSOR
#define ULTRASONIC_SENSOR


struct Pin {
    int pin;
    char port;
    Pin(char, int);
    Pin();
};

enum PinMode {
    input, output
};

class UltraSonicSensor {
private:
    Pin echoPin, triggerPin;
    volatile int distance;
    enum {
        idle, measuring
    } status;
    volatile int timer2Overflows;

    void setPin (Pin pin, bool value);
    bool readPin (Pin pin);
    void setPinMode (Pin pin, PinMode mode);

    void wait(int us);
    
    void sendTriggerPulse();

public:
    UltraSonicSensor (Pin trigger, Pin echo);

    void timer2OverflowHandler();
    void echoPinRisingEdgeHadler();

    void start();
    void stop();
    int getDistance();
};

#endif