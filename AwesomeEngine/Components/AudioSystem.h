#pragma once
#include "Audio.h"

namespace AwesomeEngine
{
	class AudioSystem
	{
	public:
		AudioSystem();
		void SuspendAudio();
		void ResumeAudio();

		std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	};
}

