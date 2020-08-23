
#include <iostream>

class Terrain
{
public:
    Terrain(int movementCost,
        bool isWater,
        Texture texture)
        : movementCost_(movementCost),
        isWater_(isWater),
        texture_(texture)
    {}

    int getMovementCost() const { return movementCost_; }
    bool isWater() const { return isWater_; }
    const Texture& getTexture() const { return texture_; }

private:
    int movementCost_;
    bool isWater_;
    Texture texture_;
};

class World
{
private:
	Terrain* tiles_[WIDTH][HEIGHT];

	//Other code...
};