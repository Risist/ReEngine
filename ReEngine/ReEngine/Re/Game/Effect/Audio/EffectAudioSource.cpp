#include <Re\Game\Effect\Audio\EffectAudioSource.h>
#include <Re\Game\GameActor.h>

namespace Effect
{
	////////////////// Source

	AudioSource::~AudioSource()
	{
		for (auto it : sounds)
			delete it;
		for (auto it : musics)
			delete it;
	}
	bool AudioSource::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}
	void AudioSource::onUpdate(sf::Time dt)
	{
		for (auto& it : sounds)
			it->setPosition(getActor()->getPosition().x, getActor()->getPosition().y, 0);

		for (auto& it : musics)
			it->setPosition(getActor()->getPosition().x, getActor()->getPosition().y, 0);
	}

	/*void AudioSource::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);

		{
			auto it = sounds.begin();
			do
			{
				saver.save<string>	("audioType",	"sound");
				saver.save<float>	("volume",		(*it)->getVolume(),			100.f);
				saver.save<float>	("attenuation", (*it)->getAttenuation(),	1.f);
				saver.save<float>	("minDistance", (*it)->getMinDistance(),	100.f);
				saver.save<float>	("pitch",		(*it)->getPitch(),			1.f);
				saver.save<bool>	("loop",		(*it)->getLoop(),			false);

				/// todo save sound id
			}
			while (saver.nextLine(file), it != sounds.end());
		}

		{
			auto it = musics.begin();
			do
			{
				saver.save<string>	("audioType",	"music");
				saver.save<float>	("volume",		(*it)->getVolume(),			100.f);
				saver.save<float>	("attenuation", (*it)->getAttenuation(),	1.f);
				saver.save<float>	("minDistance", (*it)->getMinDistance(),	100.f);
				saver.save<float>	("pitch",		(*it)->getPitch(),			1.f);
				saver.save<bool>	("loop",		(*it)->getLoop(),			false);
				/// todo save path

			} while (saver.nextLine(file), it != musics.end());
		}


		saver.setEndLine();
	}

	void AudioSource::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			std::string audioType = loader.load<string>("audioType", "sound");
			
			float32 volume		= loader.load<float32>	("volume", 100.f);
			float32 attenuation = loader.load<float32>	("attenuation", 1.f);
			float32 minDistance = loader.load<float32>	("minDistance", 100.f);
			bool loop			= loader.load<bool>		("loop", false);
			float32 pitch		= loader.load<float32>	("pitch", 1.f);

			if (audioType == "sound")
			{
				addSound(loader.load<ResId>("soundId", 0), volume, attenuation, minDistance, loop, pitch);
			}
			else if (audioType == "music")
			{
				std::string musicPath = loader.load<string>("musicPath", "_undefined");
				if(musicPath == "_undefined")
					addMusic(loader.load<ResId>("musicPathId", 0), volume, attenuation, minDistance, loop, pitch);
				else
					addMusic(musicPath, volume, attenuation, minDistance, loop, pitch);
			}
		}
	}*/

	///////////////////// Listener

	bool Effect::AudioListener::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}

	void AudioListener::onUpdate(sf::Time dt)
	{
		sf::Listener::setPosition(getActor()->getPosition().x, getActor()->getPosition().y, 0);
	}
	/*void AudioListener::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
		saver.save<float32>("globalVolume", sf::Listener::getGlobalVolume());
		saver.save<float32>("directionX", sf::Listener::getDirection().x);
		saver.save<float32>("directionY", sf::Listener::getDirection().y);
	}
	void AudioListener::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		setGlobalVolume(loader.load<float32>("globalVolume", 100.f));
		setDirection({
			loader.load<float32>("directionX", 0.f),
			loader.load<float32>("directionY", 0.f)
		});
	}*/
}
