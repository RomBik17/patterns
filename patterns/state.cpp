
#include <iostream>

//состояние героя
class HeroState
{
public:
	virtual ~HeroState() {}
	virtual void handleInput(Hero& hero, Input input) {}
	virtual void update(Hero& hero) {}
};

//состояние погружения в воду
class DuckingState : public HeroState
{
public:
    DuckingState() : chargeTime_(0)
    {}

    virtual void handleInput(Hero& hero, Input input) {
        if (input == RELEASE_DOWN) {
            // Переход в состояние стояния...
            hero.setGraphics(IMAGE_STAND);
        }
    }

    virtual void update(Hero& hero) {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE) {
            hero.superBomb();
        }
    }

private:
    int chargeTime_;
};

//делегирование к состоянию
class Hero
{
public:
    virtual void handleInput(Input input) {
        state_->handleInput(*this, input);
    }

    virtual void update() {
        state_->update(*this);
    }

    // Другие методы...
private:
    HeroState* state_;
};



/*статическое состояние
class HeroineState
{
public:
    static StandingState standing;
    static DuckingState ducking;
    static JumpingState jumping;
    static DivingState diving;

    // Остальной код...
};

//изминение состояния
if (input == PRESS_B)
{
    heroine.state_ = &HeroineState::jumping;
    heroine.setGraphics(IMAGE_JUMP);
}
*/



/*экземпляры соостояний
void Heroine::handleInput(Input input)
{
    //если меняеться состояние, то мы удаляем старое, но только после того как оно закончиться
    HeroineState* state = state_->handleInput(*this, input);
    if (state != NULL) {
        delete state_;
        state_ = state;
    }
}

HeroineState* StandingState::handleInput(Heroine& heroine, Input input)
{
    //change state
    if (input == PRESS_DOWN) {
        // Other code...
        return new DuckingState();
    }

    // Stay in this state.
    return NULL;
}
*/



/*добавление входного действия
class StandingState : public HeroineState
{
public:
    virtual void enter(Heroine& heroine) {
        heroine.setGraphics(IMAGE_STAND);
    }

    // Other code...
};

void Heroine::handleInput(Input input)
{
    HeroineState* state = state_->handleInput(*this, input);
    if (state != NULL) {
        delete state_;
        state_ = state;

        // Вызов входного действия нового состояния.
        state_->enter(*this);
    }
}
*/