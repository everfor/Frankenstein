#pragma once

#include "audio_source.h"
#include "audio.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include <map>
#include <glm/glm.hpp>

class AudioEngine
{
	public:
		AudioEngine();
		virtual ~AudioEngine();
		void setAudioEnable(bool toggle) { audio_enabled = toggle; };
		bool audioEnabled() { return audio_enabled; };
		void addAudio(Audio* audio);
		// Audio to play in next loop
		void playAudio(Audio *audio, glm::vec3& source_pos, bool loop);
		// Play loop
		void play();
	private:
		bool audio_enabled;
		ALCdevice *device;
		ALCcontext *context;
		std::unique_ptr<AudioSource> background_source;
		std::unique_ptr<Audio> background;
		std::vector<std::unique_ptr<AudioSource>> audio_sources;
		std::vector<Audio*> audios;
};

