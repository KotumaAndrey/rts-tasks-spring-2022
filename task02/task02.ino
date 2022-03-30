#include <TaskManagerIO.h>

class LightDiode : public Executable {
private:
    int state;
public:
    const int pin;
    const unsigned long interval;
    LightDiode(int pin, long interval) : pin(pin), interval(interval), state(LOW) {}
    void exec() {
        this->state = (this->state == LOW) ? HIGH : LOW;
        digitalWrite(this->pin, this->state);
    }
};

#define diodesCount 5
LightDiode* diodes[diodesCount] = {
    new LightDiode(11, 133),
    new LightDiode(10, 128),
    new LightDiode(9, 25),
    new LightDiode(6, 10),
    new LightDiode(5, 140),
};

void setup() {
    for(int i = 0; i < diodesCount; i++) {
        taskManager.scheduleFixedRate(diodes[i]->interval, diodes[i]);
    }
}

void loop() {
    taskManager.runLoop();
}
