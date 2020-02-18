#pragma once

#include "../../packages/directxtk12_desktop_2015.2019.12.17.1/include/Audio.h"
#include "Mix/System.h"

namespace AwesomeEngine
{
	class AudioSystem : public Mix::System
	{
	public:
		AudioSystem(); 
		void SuspendAudio(); 
		void ResumeAudio();

		virtual void Update(float delta);

		std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	};
}

