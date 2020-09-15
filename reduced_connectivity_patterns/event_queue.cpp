
#include <iostream>

class Audio
{
public:
	static void playSound(SoundId id, int volume)
	{
		for (int i = head_; i != tail_;
			i = (i + 1) % MAX_PENDING) {
			if (pending_[i].id == id) {
				//Using the larger of the two.
				pending_[i].volume = max(volume, pending_[i].volume);

				//Do not have to add.
				return;
			}
		}

		assert((tail_ + 1) % MAX_PENDING != head_);

		//Adding to the end.
		pending_[tail_].id = id;
		pending_[tail_].volume = volume;
		tail_ = (tail_ + 1) % MAX_PENDING;
	}

	static void update() 
	{
		//If there are no requests in the queue, we do nothing.
		if (head_ == tail_) return;

		ResourceId resource = loadSound(pending_[head_].id);
		int channel = findOpenChannel();
		if (channel == -1) return;
		startSound(resource, channel, pending_[head_].volume);

		head_ = (head_ + 1) % MAX_PENDING;
	}

	static void init() 
	{
		head_ = 0;
		tail_ = 0;
	}

	//Other Code...
private:
	static int head_;
	static int tail_;

	static const int MAX_PENDING = 16;

	static PlayMessage pending_[MAX_PENDING];
	static int numPending_;
};

class Menu
{
public:
	void onSelect(int index) {
		Audio::playSound(SOUND_BLOOP, VOL_MAX);
		//Other Code...
	}
};

struct PlayMessage
{
	SoundId id;
	int volume;
};