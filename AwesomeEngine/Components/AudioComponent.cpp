#include "AudioComponent.h"
#include "AudioSystem.h"

namespace AwesomeEngine
{
	AudioComponent::AudioComponent(AudioSystem *givenAudSystem)
	{
		audSystem = givenAudSystem; 
	}

	AudioComponent::AudioComponent(std::wstring audioFilePath)
		: m_EffectFilePath( audioFilePath )
	{
	}

	AudioComponent::AudioComponent(const AudioComponent& other)
	{
		m_EffectFilePath = other.m_EffectFilePath;
	}

	AudioComponent AudioComponent::operator=(const AudioComponent & other)
	{
		return AudioComponent(other);
	}

	void AudioComponent::LoadSound(std::wstring filepath)
	{
		//TODO: Make the filepath actually work
		//Must be a .wav file
		m_SoundEffectFile = std::make_unique<DirectX::SoundEffect>(audSystem->m_audEngine.get(), filepath.c_str()); 
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
