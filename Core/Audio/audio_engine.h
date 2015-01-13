#pragma once

#include "audio_source.h"
#include "audio.h"
#include "camera.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include <map>
#include <glm/glm.hpp>

#define DEFAULT_SOURCES			32

class AudioEngine
{
	public:
		AudioEngine();
		virtual ~AudioEngine();
		Camera* getListener() { return listener; };
		void setListener(Camera *new_cam) { listener = new_cam; };
		bool audioInitialized() { return audio_initialized; };
		void setBackgroundAudio(const std::string& file_name);
		void setBackgroundAudio(Audio* back_audio);
		// Audio to play in next loop
		void playAudio(Audio *audio, glm::vec3& source_pos, bool loop);
		// Play loop
		void play(float delta);
		// Load all resources
		void loadResource();
		// Delete all resources
		void deleteResource();
	private:
		AudioSource* getNextAvailableSource();
		bool audio_initialized;
		ALCdevice *device;
		ALCcontext *context;
		Camera *listener;
		std::unique_ptr<AudioSource> background_source;
		std::unique_ptr<Audio> background;
		std::vector<std::unique_ptr<AudioSource>> audio_sources;
		unsigned int source_cursor;
		unsigned int total_sources;
		bool resource_generated;
};

