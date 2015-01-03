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
