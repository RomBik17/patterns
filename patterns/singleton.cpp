
#include <iostream>

class Singleton {
public:
    //delete copy operator
    Singleton(const Singleton&) = delete;
    Singleton& operator =(const Singleton&) = delete;

    static Singleton& instance()
    {
        static Singleton result;
        return result;
    }

    const unsigned& width()
    {
        return mScreenWidth;
    }

    const unsigned& height()
    {
        return mScreenHeight;
    }

    void load()
    {
        mScreenWidth = 1920;
        mScreenHeight = 1080;
    }

private:
    //hide constructor
    Singleton() = default;

    unsigned mScreenWidth{ 0 };
    unsigned mScreenHeight{ 0 };
};

int SingletonRun()
{
    Singleton::instance().load();

    std::cout << Singleton::instance().height() << std::endl;
    std::cout << Singleton::instance().width() << std::endl;

    return 0;
}