
#include <iostream>

//-----------------------------------MONO_CLASS--------------------------------------------
//---------------------------------DO NOT DO THIS------------------------------------------
class Bjorn
{
public:
	Bjorn()
		: velocity_(0), x_(0), y_(0)
	{}

	void update(World& world, Graphics& graphics)
	{
		//Applying custom input to hero speed.
		switch (Controller::getJoystickDirection())
		{
		case DIR_LEFT:
			velocity_ -= WALK_ACCELERATION;
			break;

		case DIR_RIGHT:
			velocity_ += WALK_ACCELERATION;
			break;
		}

		//Change of position to speed.
		x_ += velocity_;
		world.resolveCollision(volume_, x_, y_, velocity_);

		//Rendering the corresponding sprite.
		Sprite* sprite = &spriteStand_;
		if (velocity_ < 0) {
			sprite = &spriteWalkLeft_;
		}
		else if (velocity_ > 0) {
			sprite = &spriteWalkRight_;
		}

		graphics.draw(*sprite, x_, y_);
	}

private:
	static const int WALK_ACCELERATION = 1;

	int velocity_;
	int x_, y_;

	Volume volume_;

	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
};
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------
//--------------------------------HOW TO DO IT WITH COMPONENT PATTERN----------------------------
class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void update(GameObject& bjorn) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
	virtual void update(GameObject& bjorn)
	{
		switch (Controller::getJoystickDirection())
		{
		case DIR_LEFT:
			bjorn.velocity -= WALK_ACCELERATION;
			break;

		case DIR_RIGHT:
			bjorn.velocity += WALK_ACCELERATION;
			break;
		}
	}

private:
	static const int WALK_ACCELERATION = 1;
};

class DemoInputComponent : public InputComponent
{
public:
	virtual void update(GameObject& bjorn)
	{
		//AI for auto controll for our Bjorn...
	}
};

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void update(GameObject& obj, World& world) = 0;
};

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void update(GameObject& obj, Graphics& graphics) = 0;
};

class BjornPhysicsComponent : public PhysicsComponent
{
public:
	virtual void update(GameObject& obj, World& world)
	{
		//Physics code...
	}
};

class BjornGraphicsComponent : public GraphicsComponent
{
public:
	virtual void update(GameObject& obj, Graphics& graphics)
	{
		//Graphics code...
	}
};

class GameObject
{
public:
	int velocity;
	int x, y;

	GameObject(InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics)
		: input_(input)
		, physics_(physics)
		, graphics_(graphics)
	{}

	void update(World& world, Graphics& graphics)
	{
		input_->update(*this);
		physics_->update(*this, world);
		graphics_->update(*this, graphics);
	}

private:
	InputComponent* input_;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;
};

GameObject* createBjorn()
{
	return new GameObject(
		new PlayerInputComponent(),
		new BjornPhysicsComponent(),
		new BjornGraphicsComponent()
	);
}
//---------------------------------END PATTERN------------------------------------------------
//--------------------------------------------------------------------------------------------