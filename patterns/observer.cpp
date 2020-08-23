
#include <iostream>

class Observer
{
public:
    virtual ~Observer() {}
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

//Achievement for falling from a bridge as an example
class Achievements : public Observer
{
public:
    virtual void onNotify(const Entity& entity, Event event) {
        switch (event) {
        case EVENT_ENTITY_FELL:
            if (entity.isHero() && heroIsOnBridge_) {
                unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
            }
            break;

            //Processing of other events and updating heroIsOnBridge_...
        }
    }

private:
    void unlock(Achievement achievement) {
        //Unlock achievement if it was locked...
    }

    bool heroIsOnBridge_;
};

class Subject
{
public:
    void addObserver(Observer* observer) {
        //Adding in array
    }

    void removeObserver(Observer* observer) {
        //Remove from array...
    }

    //Other code...

protected:
    void notify(const Entity& entity, Event event) {
        for (int i = 0; i < numObservers_; i++) {
            observers_[i]->onNotify(entity, event);
        }
    }

private:
    Observer* observers_[MAX_OBSERVERS];
    int numObservers_;
};

//Call example
void Physics::updateBody(PhysicsBody& body)
{
    bool wasOnSurface = body.isOnSurface();
    body.accelerate(GRAVITY);
    body.update();

    if (wasOnSurface && !body.isOnSurface()) {
        notify(body, EVENT_START_FALL);
    }
}