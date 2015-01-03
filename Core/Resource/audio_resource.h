#pragma once

#include "resource.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <memory>

class AudioResource : public Resource
{
	public:
		virtual ~AudioResource();
		void setData(char* new_data) { data.reset(new_data); };
		char* getData() { return data.get(); };
		void setSize(ALsizei new_size) { size = new_size; };
		ALsizei getSize() { return size; };
		void setID(ALuint new_id) { id = new_id; };
		ALuint getID() { return id; };
		void loadAudioData(char *data, ALuint format, ALuint size, ALuint sample_rate);
		// Factory
		static AudioResource* _get_resource(std::string& key);
		// Load all resources
		static void _load_all();
		// Delete all resources
		static void _delete_all();
	private:
		AudioResource();
		ALuint id;
		std::unique_ptr<char> data;
		ALsizei size;
		static std::map<std::string, std::unique_ptr<AudioResource>> _resources;
};

