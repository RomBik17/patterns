
#include <iostream>

class Observer
{
public:
    virtual ~Observer() {}
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

//очивка по падению с моста как пример
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

            // Обработка остальных событий и обновление heroIsOnBridge_...
        }
    }

private:
    void unlock(Achievement achievement) {
        // Разблокирование если не было разблокировано раньше...
    }

    bool heroIsOnBridge_;
};

class Subject
{
public:
    void addObserver(Observer* observer) {
        // Добавление в массив...
    }

    void removeObserver(Observer* observer) {
        // Удаление из массива...
    }

    // Другие вещи...

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

//пример вызова
void Physics::updateBody(PhysicsBody& body)
{
    bool wasOnSurface = body.isOnSurface();
    body.accelerate(GRAVITY);
    body.update();

    if (wasOnSurface && !body.isOnSurface()) {
        notify(body, EVENT_START_FALL);
    }
}