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
		ALuint getID() { return id; };
		// Factory
		static AudioResource* _get_resource(std::string& key);
		// Load all resources
		static void loadAll();
	private:
		AudioResource();
		ALuint id;
		static std::map<std::string, std::unique_ptr<AudioResource>> _resources;
};

