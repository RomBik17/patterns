
#include <iostream>

class Monster
{
public:
	virtual ~Monster() {}
	virtual Monster* clone() = 0;

	// Другие вещи...
};

class Ghost : public Monster
{
public:
	Ghost(int health, int speed)
		: health_(health),
		speed_(speed)
	{}

	virtual Monster* clone() {
		return new Ghost(health_, speed_);
	}

private:
	int health_;
	int speed_;
};

//без шаблонов
class Spawner
{
public:
	Spawner(Monster* prototype)
		: prototype_(prototype)
	{}

	Monster* spawnMonster() {
		return prototype_->clone();
	}

private:
	Monster* prototype_;
};



//через шаблоны
class Spawner
{
public:
	virtual ~Spawner() {}
	virtual Monster* spawnMonster() = 0;
};

template <class T>
class SpawnerFor : public Spawner
{
public:
	virtual Monster* spawnMonster() { return new T(); }
};