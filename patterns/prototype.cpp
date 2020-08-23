
#include <iostream>

class Monster
{
public:
	virtual ~Monster() {}
	virtual Monster* clone() = 0;

	//Other code...
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

//Without templates
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



//With templates
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