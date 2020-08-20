
#include <iostream>
#include <memory>
#include <vector>

class IHelmet
{
public:
	virtual void draw() = 0;
};

class HeavyHelmet : public IHelmet
{
public:
	void draw() override 
	{ 
		std::cout << "Heavy Helmet" << std::endl; 
	}
};

class LightHelmet : public IHelmet
{
public:
	void draw() override 
	{ 
		std::cout << "Light Helmet" << std::endl; 
	}
};

class IHelmetFactory
{
public:
	virtual std::unique_ptr<IHelmet> makeHelmet() = 0;
};

class HeavyHelmetFactory : public IHelmetFactory
{
public:
	std::unique_ptr<IHelmet> makeHelmet() override 
	{ 
		return std::unique_ptr<HeavyHelmet>(); 
	}
};

class LightHelmetFactory : public IHelmetFactory
{
public:
	std::unique_ptr<IHelmet> makeHelmet() override
	{
		return std::unique_ptr<LightHelmet>();
	}
};

int example()
{
	int i = rand();
	std::vector<std::unique_ptr<IHelmet>> helmets;
	switch (i%2)
	{
	case 0:
	{
		LightHelmetFactory factory;
		helmets.push_back(factory.makeHelmet());
		break;
	}
	case 1:
	{
		HeavyHelmetFactory factory;
		helmets.push_back(factory.makeHelmet());
		break;
	}
	default:
		break;
	}
	for (auto& helmet : helmets)
	{
		helmet->draw();
	}
	return 0;
}