
#include <iostream>

class Superpower
{
public:
    virtual ~Superpower() {}

protected:
    //sandbox methood
    virtual void activate() = 0;

    void move(double x, double y, double z) {
        //Code...
    }

    void playSound(SoundId sound, double volume) {
        //Code...
    }

    void spawnParticles(ParticleType type, int count) {
        //Code...
    }

    double getHeroX() {
        //Code...
    }

    double getHeroY() {
        //Code...
    }

    double getHeroZ() {
        //Code...
    }

    //Other...
};

class SkyLaunch : public Superpower
{
protected:
    virtual void activate() {
        //Jump
        if (getHeroZ() == 0) {
            //We are on the ground, so we can jump
            playSound(SOUND_SPROING, 1.0f);
            spawnParticles(PARTICLE_DUST, 10);
            move(0, 0, 20);
        }
        else if (getHeroZ() < 10.0f) {
            //Low above the ground, so we can do a double jump
            playSound(SOUND_SWOOP, 1.0f);
            move(0, 0, getHeroZ() — 20);
        }
        else {
            //We are in the air and can tackle
            playSound(SOUND_DIVE, 0.7f);
            spawnParticles(PARTICLE_SPARKLES, 1);
            move(0, 0, -getHeroZ());
        }
    }
};