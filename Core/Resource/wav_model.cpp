#include "wav_model.h"
#include "exceptions.h"
#include "utils.h"

#include <fstream>

WavModel::WavModel(std::string& file_name)
{
	char buffer[4];
	std::ifstream in(file_name.c_str(), std::ios::binary);

	if (in.is_open())
	{
		// Decoding wav file
		in.read(buffer, 4);	// RIFF
		// Bunch of stuff we dont care
		in.read(buffer, 4);
		in.read(buffer, 4);	// WAVE
		in.read(buffer, 4); // fmt
		in.read(buffer, 4); // 16
		in.read(buffer, 2); // 1

		// channel
		in.read(buffer, 2);
		int channel = _char_to_int(buffer, 2);

		// Sample Rate
		in.read(buffer, 4);
		setSampleRate(_char_to_int(buffer, 4));

		in.read(buffer, 4);
		in.read(buffer, 2);

		// Bit per sample
		in.read(buffer, 2);
		int bps = _char_to_int(buffer, 2);

		in.read(buffer, 4);

		// data
		in.read(buffer, 4);
		setSize(_char_to_int(buffer, 4));

		initializeData(getSize());
		char *data = getData();
		in.read(data, getSize());

		// Set format
		if (channel == 1)
		{
			if (bps == 1)
			{
				setFormat(AL_FORMAT_MONO8);
			}
			else
			{
				setFormat(AL_FORMAT_MONO16);
			}
		}
		else
		{
			if (bps == 1)
			{
				setFormat(AL_FORMAT_STEREO8);
			}
			else
			{
				setFormat(AL_FORMAT_STEREO16);
			}
		}
	}
	else
	{
		throw ResourceException("Cannot open file " + file_name);
	}
}

void WavModel::loadToAudio(AudioResource *resource)
{
	resource->loadAudioData(getData(), getFormat(), getSize(), getSampleRate());
}