#include "audio_engine.h"
#include "audio_resource.h"
#include "audio_source_resource.h"

#include <iostream>

AudioEngine::AudioEngine() :
			audio_enabled(false), source_cursor(0), total_sources(DEFAULT_SOURCES), resource_generated(false)
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

	setAudioEnable(true);

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

void AudioEngine::play()
{
	if (audioEnabled())
	{
		background_source.get()->play();

		for (int i = 0; i < audio_sources.size(); i++)
		{
			audio_sources[i].get()->play();
		}
	}
}

AudioSource* AudioEngine::getNextAvailableSource()
{
	unsigned int cursor = source_cursor;
	for (; source_cursor != cursor;)
	{
		AudioSource *source = audio_sources[source_cursor].get();
		source_cursor = (source_cursor + 1) % total_sources;

		// If the audio is not looping, then it is considered available
		if (source->shouldLoop() == AL_FALSE)
		{
			return source;
		}
	}

	// No available source found. return the first one
	source_cursor = 1;
	return audio_sources[0].get();
}

void AudioEngine::loadResource()
{
	if (audioEnabled())
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