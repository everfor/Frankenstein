#include "audio_engine.h"
#include "audio_resource.h"
#include "audio_source_resource.h"

#include <iostream>

AudioEngine::AudioEngine() :
				audio_initialized(false), source_cursor(0), total_sources(DEFAULT_SOURCES), resource_generated(false), listener(NULL)
{
	device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		std::cerr << "Unable to open audio device. Audio engine will not be running." << std::endl;
		return;
	}

	context = alcCreateContext(device, NULL);
	if (context == NULL)
	{
		std::cerr << "Unable to create audio context. Audio engine will not be running." << std::endl;
		return;
	}

	alcMakeContextCurrent(context);

	audio_initialized = true;

	// Bakcground audio source
	background_source = std::unique_ptr<AudioSource>(new AudioSource(true, AL_TRUE));

	// Other sources
	audio_sources.reserve(total_sources);
	for (int i = 0; i < total_sources; i++)
	{
		audio_sources.push_back(std::unique_ptr<AudioSource>(new AudioSource()));
	}
}

AudioEngine::~AudioEngine()
{
	deleteResource();

	if (context != NULL)
	{
		alcDestroyContext(context);
	}

	if (device != NULL)
	{
		alcCloseDevice(device);
	}
}

void AudioEngine::setBackgroundAudio(const std::string& file_name)
{
	setBackgroundAudio(new Audio(file_name));
}

void AudioEngine::setBackgroundAudio(Audio* back_audio)
{
	background.reset(back_audio);
	background_source.get()->setAudio(background.get());
}

void AudioEngine::playAudio(Audio *audio, glm::vec3& source_pos, bool loop)
{
	AudioSource *source = getNextAvailableSource();
	source->setAudio(audio);
	source->setPosition(source_pos);
	source->setLoop(loop ? AL_TRUE : AL_FALSE);
}

void AudioEngine::play(float delta)
{
	if (audioInitialized())
	{
		// Set listener
		if (getListener() != NULL)
		{
			glm::vec3 pos = getListener()->getTransform()->getTransformedTranslation();
			glm::vec3 forward = getListener()->getTransform()->getTransformedForward();

			float f[6] = { forward.x, forward.y, forward.z, 0.0f, 1.0f, 0.0f };

			alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
			alListenerfv(AL_ORIENTATION, f);
		}

		background_source.get()->play(delta);

		for (int i = 0; i < audio_sources.size(); i++)
		{
			audio_sources[i].get()->play(delta);
		}
	}
}

AudioSource* AudioEngine::getNextAvailableSource()
{
	unsigned int current_cursor = source_cursor;
	do
	{
		AudioSource *source = audio_sources[source_cursor].get();
		source_cursor = (source_cursor + 1) % total_sources;

		if (!source->isPlaying())
		{
			return source;
		}
	} while (source_cursor != current_cursor);

	// No available source found. return the first one
	source_cursor = 1;
	return audio_sources[0].get();
}

void AudioEngine::loadResource()
{
	if (audioInitialized())
	{
		AudioSourceResource::_load_all();
		AudioResource::_load_all();
		
		resource_generated = true;
	}
}

void AudioEngine::deleteResource()
{
	if (resource_generated)
	{
		AudioSourceResource::_delete_all();
		AudioResource::_delete_all();
	}
}