
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

		// Если ничего не передано, то ничего и не делаем.
		return NULL;
	}

	// Методы для привязки команд...

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



//отмена действий
class MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(Unit* unit, int x, int y)
		: unit_(unit), xBefore_(0), yBefore_(0),
		x_(x), y_(y)
	{}

	virtual void execute() {
		// Запоминаем позицию юнита перед ходом
		// чтобы потом ее восстановить.
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
	// Выбираем юнит...
	Unit* unit = getSelectedUnit();

	if (isPressed(BUTTON_UP)) {
		// Перемещаем юнит на единицу вверх.
		int destY = unit->y() — 1;
		return new MoveUnitCommand(unit, unit->x(), destY);
	}

	if (isPressed(BUTTON_DOWN)) {
		// Перемещаем юнит на единицу вниз.
		int destY = unit->y() + 1;
		return new MoveUnitCommand(unit, unit->x(), destY);
	}

	// Другие шаги...

	return NULL;
}