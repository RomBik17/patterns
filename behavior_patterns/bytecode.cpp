
#include <iostream>

//API
void setHealth(int wizard, int amount);
void setWisdom(int wizard, int amount);
void setAgility(int wizard, int amount);
void playSound(int soundId);
void spawnParticles(int particleType);

enum Instruction
{
	INST_SET_HEALTH = 0x00,
	INST_SET_WISDOM = 0x01,
	INST_SET_AGILITY = 0x02,
	INST_PLAY_SOUND = 0x03,
	INST_SPAWN_PARTICLES = 0x04
};

class VM
{
public:
	VM()
		: stackSize_(0)
	{}

	void interpret(char bytecode[], int size) {
		for (int i = 0; i < size; i++) {
			char instruction = bytecode[i];
			switch (instruction)
			{
			case INST_SET_HEALTH:
			{
				int amount = pop();
				int wizard = pop();
				setHealth(wizard, amount);
				break;
			}

			case INST_SET_WISDOM: {}
			case INST_SET_AGILITY: {}
			//Аналогично, как сверху...

			case INST_PLAY_SOUND:
				playSound(pop());
				break;

			case INST_SPAWN_PARTICLES:
				spawnParticles(pop());
				break;
			}
			case INST_LITERAL:
			{
				//Считываем следующий байт из байткода.
				int value = bytecode[++i];
				push(value);
				break;
			}
			case INST_GET_HEALTH:
			{
				int wizard = pop();
				push(getHealth(wizard));
				break;
			}
		}
	}
	//Other stuff...

private:
	void push(int value) {
		// Поверяем переполнение стека.
		assert(stackSize_ < MAX_STACK);
		stack_[stackSize_++] = value;
	}

	int pop() {
		// Проверяем что стек не пустой.
		assert(stackSize_ > 0);
		return stack_[--stackSize_];
	}
	static const int MAX_STACK = 128;
	int stackSize_;
	int stack_[MAX_STACK];
};