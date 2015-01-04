#pragma once

#include "audio_model.h"

#include <string>

#define WAV_HEADER			"RIFF"

class WavModel : public AudioModel
{
	public:
		WavModel(std::string& file_name);
		virtual ~WavModel() {};
		virtual void loadToAudio(AudioResource* audio) override;
};

