#include "audio_source.h"


AudioSource::AudioSource(bool back, ALboolean loop) :
			is_background(back), should_play(false), should_loop(loop), pos(glm::vec3()), timer(0.0f), is_playing(false), audio(NULL)
{
	resource = AudioSourceResource::_get_resource();
}

AudioSource::~AudioSource()
{
}

void AudioSource::play(float delta)
{
	if (shouldPlay() && audio != NULL)
	{
		// Set Buffer
		alSourcei(resource->getID(), AL_BUFFER, audio->getResource()->getID());
		// Looping
		alSourcei(resource->getID(), AL_LOOPING, shouldLoop());
		// If not background music, set position
		if (!isBackground())
		{
			alSource3f(resource->getID(), AL_POSITION, pos.x, pos.y, pos.z);
		}

		// Play
		alSourcePlay(resource->getID());
		should_play = false;
		is_playing = true;
	}
	else
	{
		if (is_playing & !shouldLoop())
		{
			timer += delta;

			if (timer > audio->getResource()->getDuration())
			{
				resetTimer();
			}
		}
	}
}