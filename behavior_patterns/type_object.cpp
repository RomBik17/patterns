
#include <iostream>

class Breed
{
public:
	Breed(Breed* parent, int health, const char* attack)
		: health_(health)
		, attack_(attack)
	{
		//Inheritance of non-overridden attributes.
		if (parent != NULL) {
			if (health == 0)
				health_ = parent->getHealth();
			if (attack == NULL)
				attack_ = parent->getAttack();
		}
	}

	Monster* newMonster() { return new Monster(*this); }

	int getHealth() { return health_; }
	const char* getAttack() { return attack_; }

private:
	int health_; //Start health.
	const char* attack_;
};

class Monster
{
	friend class Breed;

public:
	const char* getAttack() {
		return breed_.getAttack();
	}

private:
	Monster(Breed& breed)
		: health_(breed.getHealth())
		, breed_(breed)
	{}

	int health_; //Temporary health.
	Breed& breed_;
};

/*if we want to read types from JSON
{
	"Troll": {
		"health": 25,
			"attack" : "The troll hits you!"
	},
		"Troll Archer" : {
			"parent": "Troll",
				"health" : 0,
				"attack" : "The troll archer fires an arrow!"
		},
			"Troll Wizard" : {
				"parent": "Troll",
					"health" : 0,
					"attack" : "The troll wizard casts a spell on you!"
			}
}*/
