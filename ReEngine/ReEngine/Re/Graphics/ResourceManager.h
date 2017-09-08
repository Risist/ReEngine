#pragma once
#include <Re\Common\utility.h>
#include <string>
#include <unordered_map>

using namespace sf;
using namespace std;

using ResId = uint16;


/// class which contains game resources
class ResourceManager : public Res::ISerialisable
{
public:
	ResourceManager();

	/// list of loaded textures
	std::unordered_map< ResId, Texture> atlases;
	
	/// struct to hold data about texture instance placed in atlas
	struct TextureInstance
	{
		ResId atlasId;
		Texture* getTexture() const;
		void setSprite(sf::Sprite& inSp)
		{
			inSp.setTexture(*getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void setConvexShape(sf::ConvexShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void setCircleShape(sf::CircleShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void setRectShape(sf::RectangleShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}

 		sf::IntRect bounds;
	};
	std::unordered_map<ResId, TextureInstance> textures;


	std::unordered_map< ResId, Font> fonts;
	std::unordered_map< ResId, SoundBuffer> sounds;
	/// to faster load scripts many times in a row
	/// save script in memory, so disc operations is not needed
	std::unordered_map< ResId, string> cashedScript;
	/// for resources which can not be preloaded save paths to use in game
	std::unordered_map< ResId, string> paths;

	//////// physics
	/// cashed body definitions to allow easier creation of rigidbodies
	std::unordered_map< ResId, b2BodyDef> bodyDefs;
	/// cashed fixture definitions to allow easier creation of fixtures
	std::unordered_map< ResId, b2FixtureDef> fixtureDefs;

	/// cashed shapes definitions to allow easier creation of shapes
	std::unordered_map< ResId, b2CircleShape> circleShapes;
	std::unordered_map< ResId, b2PolygonShape> polygonShapes;
	std::unordered_map< ResId, b2ChainShape> chainShapes;

	void createTexture(Texture& ts, const std::string& path);
	string createTranscription(const std::string& path);

	/// set color which shoud be treated as transparent
	static inline void setClTransparent(const Color& s)
	{
		clTransparent = s;
	}
	/// get color which shoud be treated as transparent
	static inline const Color& getClTransparent()
	{
		return clTransparent;
	}

private:
	static Image im;
	static Color clTransparent;

protected:
	virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
	virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
};
extern ResourceManager res;



/// defines for easier usage
#define atlasInst res.atlases
#define tsInst res.textures
#define fontInst res.fonts
#define soundInst res.sounds
#define scriptInst res.cashedScript
#define pathInst res.paths

#define bodyDefInst res.bodyDefs
#define fixtureInst res.fixtureDefs
#define circleShapeInst res.circleShapes
#define polygonShapeInst res.polygonShapes
#define chainShapeInst res.chainShapes


