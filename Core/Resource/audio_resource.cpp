#include "audio_resource.h"
#include "resource_manager.h"

std::map<std::string, std::unique_ptr<AudioResource>> AudioResource::_resources;

AudioResource::AudioResource()
{
	increaseRefCout();
}

AudioResource::~AudioResource()
{
}

void AudioResource::loadAudioData(char *data, ALuint format, ALuint size, ALuint sample_rate)
{
	setData(data);
	setSize(size);
	
	alBufferData(getID(), format, getData(), getSize(), sample_rate);
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

void AudioResource::_load_all()
{
	ALuint *ids = (ALuint*)malloc(AudioResource::_resources.size() * sizeof(ALuint));
	alGenBuffers(AudioResource::_resources.size(), ids);

	int index = 0;
	for (std::map<std::string, std::unique_ptr<AudioResource>>::iterator it = AudioResource::_resources.begin();
		it != AudioResource::_resources.end();
		it++)
	{
		it->second.get()->setID(ids[index++]);

		ResourceManager::loadAudio(it->first, it->second.get());
	}

	free(ids);
}

void AudioResource::_delete_all()
{
	ALuint *ids = (ALuint*)malloc(AudioResource::_resources.size() * sizeof(ALuint));

	int index = 0;
	for (std::map<std::string, std::unique_ptr<AudioResource>>::iterator it = AudioResource::_resources.begin();
		it != AudioResource::_resources.end();
		it++)
	{
		ids[index++] = it->second.get()->getID();
	}

	alDeleteBuffers(AudioResource::_resources.size(), ids);

	free(ids);

	AudioResource::_resources.clear();
}