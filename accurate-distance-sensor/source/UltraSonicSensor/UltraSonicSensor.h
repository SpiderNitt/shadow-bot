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
    volatile float distance;

    enum {
        idle, measuring, waiting
    } status;
    volatile unsigned long timer2Overflows;

    void setPin (Pin pin, bool value);
    bool readPin (Pin pin);
    void setPinMode (Pin pin, PinMode mode);

    void wait(unsigned long us);
    
    void sendTriggerPulse();
    void updateDistance(float newDistance);

public:
    UltraSonicSensor (Pin trigger);

    void timer2CompAHandler();
    void echoPinRisingEdgeHadler();

    void start();
    void stop();
    float getDistance();

    void test();
};

#endif