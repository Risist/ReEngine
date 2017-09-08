#pragma once
#include <Re\Game\Effect\EffectBase.h>
#include <Re\Graphics\ResourceManager.h>

namespace Effect
{
	/* 
	efect which plays sounds and music from the actor position
	@parent Game::Actor only
	*/
	class AudioSource final: public Base
	{
		SERIALISATION_NAME(AudioSource)
	public:
		~AudioSource();


		virtual bool canBeParent(Base * potentialParent) const override;
		virtual void onUpdate(sf::Time dt) override;

		AudioSource* addSound(ResId soundId, float volume = 100.f, float attenuation = 1.f, float minDistance = 100.f, bool loop = false, float pitch = 1.f)
		{
			sounds.push_back(new sf::Sound(soundInst[soundId]) );
			sounds.back()->setRelativeToListener(true);
			sounds.back()->setLoop(loop);
			sounds.back()->setVolume(loop);
			sounds.back()->setAttenuation(loop);
			sounds.back()->setMinDistance(loop);
			sounds.back()->setPitch(loop);
			return this;
		}
		AudioSource* addMusic(ResId musicPathId, float volume = 100.f, float attenuation = 1.f, float minDistance = 100.f, bool loop = false, float pitch = 1.f)
		{
			musics.push_back(new sf::Music);
			musics.back()->openFromFile(pathInst[musicPathId]);
			musics.back()->setRelativeToListener(true);

			musics.back()->setLoop(loop);
			musics.back()->setVolume(loop);
			musics.back()->setAttenuation(loop);
			musics.back()->setMinDistance(loop);
			musics.back()->setPitch(loop);
			return this;
		}
		AudioSource* addMusic(const string& path, float volume = 100.f, float attenuation = 1.f, float minDistance = 100.f, bool loop = false, float pitch = 1.f)
		{
			musics.push_back(new sf::Music);
			musics.back()->openFromFile(path);
			musics.back()->setRelativeToListener(true);
			
			musics.back()->setLoop(loop);
			musics.back()->setVolume(loop);
			musics.back()->setAttenuation(loop);
			musics.back()->setMinDistance(loop);
			musics.back()->setPitch(loop);
			return this;
		}


		vector<sf::Sound*> sounds;
		vector<sf::Music*> musics;
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)override;*/
	};

	/* 
	updates position of sound listener to Game::Actor
	@parent Game::Actor only
	*/
	class AudioListener final: public Base
	{
		SERIALISATION_NAME(AudioListener)
	public:

		virtual bool canBeParent(Base * potentialParent) const override;
		virtual void onUpdate(sf::Time dt) override;


		AudioListener* setDirection(const Vector2D& s)
		{
			sf::Listener::setDirection(s.x, s.y, 0);
			return this;
		}
		AudioListener* setGlobalVolume(float s = 100.f)
		{
			sf::Listener::setGlobalVolume(s);
			return this;
		}

	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)override;*/
	};

}