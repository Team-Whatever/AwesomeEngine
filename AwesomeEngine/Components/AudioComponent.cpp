#include "AudioComponent.h"

namespace AwesomeEngine
{
	AudioComponent::AudioComponent(AudioSystem *givenAudSystem)
	{
		audSystem = givenAudSystem;		
	}

	void AudioComponent::LoadSound(std::string filepath)
	{
		//TODO: Make the filepath actually work
		//Must be a .wav file
		m_SoundEffectFile = std::make_unique<DirectX::SoundEffect>(audSystem->m_audEngine.get(), L"filepath");
		m_SoundEffect = m_SoundEffectFile->CreateInstance();
	}

	void AudioComponent::Play(bool isLooping)
	{
		m_SoundEffect->Play(isLooping);
	}

	void AudioComponent::Stop(bool stopImmediately)
	{
		m_SoundEffect->Stop(stopImmediately);
	}

	void AudioComponent::Resume()
	{
		m_SoundEffect->Resume();
	}

	void AudioComponent::Pause()
	{
		m_SoundEffect->Pause();
	}

	void AudioComponent::SetVolume(float volume)
	{
		soundVolume = volume;
		m_SoundEffect->SetVolume(soundVolume);
	}

}
