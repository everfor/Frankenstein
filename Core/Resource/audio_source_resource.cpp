#include "audio_source_resource.h"

std::vector<std::unique_ptr<AudioSourceResource>> AudioSourceResource::_resources;

AudioSourceResource::AudioSourceResource()
{
	increaseRefCout();
}

AudioSourceResource::~AudioSourceResource()
{
}

AudioSourceResource* AudioSourceResource::_get_resource()
{
	AudioSourceResource::_resources.push_back(std::unique_ptr<AudioSourceResource>(new AudioSourceResource()));
	return AudioSourceResource::_resources.back().get();
}

void AudioSourceResource::_load_all()
{
	ALuint* ids = (ALuint*)malloc(AudioSourceResource::_resources.size() * sizeof(ALuint));

	// Generate sources
	alGenSources(AudioSourceResource::_resources.size(), ids);
	for (int i = 0; i < AudioSourceResource::_resources.size(); i++)
	{
		AudioSourceResource::_resources[i].get()->setID(ids[i]);
	}

	free(ids);
}

void AudioSourceResource::_delete_all()
{
	ALuint* ids = (ALuint*)malloc(AudioSourceResource::_resources.size() * sizeof(ALuint));

	for (int i = 0; i < AudioSourceResource::_resources.size(); i++)
	{
		ids[i] = AudioSourceResource::_resources[i].get()->getID();
	}

	alDeleteSources(AudioSourceResource::_resources.size(), ids);

	free(ids);

	AudioSourceResource::_resources.clear();
}