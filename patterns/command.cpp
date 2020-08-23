
#include <iostream>

class Command
{
public:
	virtual ~Command() {}

	virtual void execute(GameActor& actor) = 0;
	virtual void undo	(GameActor& actor) = 0;
};

class JumpCommand : public Command
{
public:
	virtual void execute(GameActor& actor) {
		actor.jump();
	}
};

class InputHandler
{
public:
	Command* handleInput()
	{
		if (isPressed(BUTTON_X)) return buttonX_;
		if (isPressed(BUTTON_Y)) return buttonY_;
		if (isPressed(BUTTON_A)) return buttonA_;
		if (isPressed(BUTTON_B)) return buttonB_;

		//If mothing is transfered, we don't do anything
		return NULL;
	}

	//Methods for binding commands...

private:
	Command* buttonX_;
	Command* buttonY_;
	Command* buttonA_;
	Command* buttonB_;
};

void example()
{
	//...
	Command* command = inputHandler.handleInput();
	if (command)
	{
		command->execute(actor);
	}
}



//Cancellation of actions
class MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(Unit* unit, int x, int y)
		: unit_(unit), xBefore_(0), yBefore_(0),
		x_(x), y_(y)
	{}

	virtual void execute() {
		//Remember unit's position before the move
		//To restore it later
		xBefore_ = unit_->x();
		yBefore_ = unit_->y();

		unit_->moveTo(x_, y_);
	}

	virtual void undo() {
		unit_->moveTo(xBefore_, yBefore_);
	}

private:
	Unit* unit_;
	int xBefore_, yBefore_;
	int x_, y_;
};

Command* handleInput()
{
	//Choose unit...
	Unit* unit = getSelectedUnit();

	if (isPressed(BUTTON_UP)) {
		//Moving unit by 1 up
		int destY = unit->y() — 1;
		return new MoveUnitCommand(unit, unit->x(), destY);
	}

	if (isPressed(BUTTON_DOWN)) {
		//Moving unit by 1 down
		int destY = unit->y() + 1;
		return new MoveUnitCommand(unit, unit->x(), destY);
	}

	//Other code...

	return NULL;
}