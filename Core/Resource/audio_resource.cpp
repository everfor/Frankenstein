#include "audio_resource.h"

std::map<std::string, std::unique_ptr<AudioResource>> AudioResource::_resources;

AudioResource::AudioResource()
{
	increaseRefCout();
}

AudioResource::~AudioResource()
{
}

AudioResource* AudioResource::_get_resource(std::string& key)
{
	if (AudioResource::_resources.find(key) != AudioResource::_resources.end())
	{
		AudioResource::_resources.at(key).get()->increaseRefCout();
		return AudioResource::_resources.at(key).get();
	}
	AudioResource::_resources.insert(std::pair<std::string, std::unique_ptr<AudioResource>>(key, std::unique_ptr<AudioResource>(new AudioResource())));
	return AudioResource::_resources.at(key).get();
}

void AudioResource::loadAll()
{
	// TODO
}
