
#include <iostream>

//Hero's state
class HeroState
{
public:
	virtual ~HeroState() {}
	virtual void handleInput(Hero& hero, Input input) {}
	virtual void update(Hero& hero) {}
};

class DuckingState : public HeroState
{
public:
    DuckingState() : chargeTime_(0)
    {}

    virtual void handleInput(Hero& hero, Input input) {
        if (input == RELEASE_DOWN) {
            //Changing state from ducking to standing 
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

//Delegation to the state
class Hero
{
public:
    virtual void handleInput(Input input) {
        state_->handleInput(*this, input);
    }

    virtual void update() {
        state_->update(*this);
    }

    //Other methods...
private:
    HeroState* state_;
};



/*Static state
class HeroineState
{
public:
    static StandingState standing;
    static DuckingState ducking;
    static JumpingState jumping;
    static DivingState diving;

    //Other code...
};

//Changing our state
if (input == PRESS_B)
{
    heroine.state_ = &HeroineState::jumping;
    heroine.setGraphics(IMAGE_JUMP);
}
*/



/*Instances of states
void Heroine::handleInput(Input input)
{
    //If state changes, we'll delete an old one, but only after it will end the work
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



/*Adding enter action
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

        //Calling enter action of state
        state_->enter(*this);
    }
}
*/