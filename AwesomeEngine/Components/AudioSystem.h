#pragma once
#include "Audio.h"
#include "Mix/System.h"
#include "Components/AudioComponent.h"

namespace AwesomeEngine
{
	class AudioSystem : Mix::System
	{
	public:
		AudioSystem();
		void SuspendAudio();
		void ResumeAudio();

		virtual void Update(float delta);

		std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	};
}

