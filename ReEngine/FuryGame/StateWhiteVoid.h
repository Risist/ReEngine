#pragma once
#include <Re\ReEngine.h>

/// Main game state
/// Controlls all events within game like spawning characters
class StateWhiteVoid : public Game::State
{
public:

	/// overrided events
	virtual void onStart() override;
	virtual Game::State* onUpdate(sf::Time dt) override;
	virtual void onExit() override;


	/// initialize player controls
	void initKeys();

protected: /// spawn functions
	/// adds basic version of Zenon to world at provided position and rotation
	/// Zenon is low/middle income non agressive character usefull mainly in early game phase
	/// Flees from player and other edons
	Game::Actor* addZenon( const Vector2D& position, Angle rotation = Angle::zero);

	/// creates and adds to world player character at provided position and rotation
	Game::Actor* addPlayer(const Vector2D& position, Angle rotation = Angle::zero);

	/// creates and adds to world default bacground
	Game::Actor* addBackground(const Vector2D& position );

	/// creates and adds simple obstacle - for testing
	Game::Actor* addObstacle(const Vector2D& position, Angle rotation = Angle::zero);

	/// creates and adds simple obstacle - for testing
	Game::Actor* addBarrel(const Vector2D& position, Angle rotation = Angle::zero);

private:
	void controlBackgroundColor();
};