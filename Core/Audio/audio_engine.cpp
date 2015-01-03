#include "audio_engine.h"

#include <iostream>

AudioEngine::AudioEngine() :
	audio_enabled(false)
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

	setAudioEnable(true);
}

AudioEngine::~AudioEngine()
{
	if (context != NULL)
	{
		alcDestroyContext(context);
	}

	if (device != NULL)
	{
		alcCloseDevice(device);
	}
}

void AudioEngine::addAudio(Audio* audio)
{
	audios.push_back(audio);
}

void AudioEngine::playAudio(Audio *audio, glm::vec3& source_pos, bool loop)
{
	// TODO
}

void AudioEngine::play()
{
	background_source.get()->play();

	for (int i = 0; i < audio_sources.size(); i++)
	{
		audio_sources[i].get()->play();
	}
}