#pragma once

#include "resource.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <memory>

class AudioSourceResource : public Resource
{
	public:
		virtual ~AudioSourceResource();
		ALuint getID() { return id; };
		// Factory
		static AudioSourceResource* _get_resource();
		// Load all resources
		static void loadAll();
	private:
		AudioSourceResource();
		ALuint id;
		static std::vector<std::unique_ptr<AudioSourceResource>> _resources;
};

