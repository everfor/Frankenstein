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
		void setID(ALuint new_id) { id = new_id; };
		ALuint getID() { return id; };
		// Factory
		static AudioSourceResource* _get_resource();
		// Load all resources
		static void _load_all();
		// Delete all resources
		static void _delete_all();
	private:
		AudioSourceResource();
		ALuint id;
		static std::vector<std::unique_ptr<AudioSourceResource>> _resources;
};

