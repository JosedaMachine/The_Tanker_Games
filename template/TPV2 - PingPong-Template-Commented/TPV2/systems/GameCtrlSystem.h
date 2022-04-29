#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"

enum class GameState { NEWGAME, PAUSED, RUNNING, GAMEOVER };

class GameCtrlSystem : public System {
public:
	GameCtrlSystem();

	virtual ~GameCtrlSystem();

	// - a este método se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();

	// - a este método se le va a llamar cuando no haya más asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();

	// - devuelve el estado del juego.
	GameState getGameState();

	// - Cambia el estado del juego
	void setState(GameState state);

	// - inicializar el estado del juego si es necesario, etc.
	void init() override;

	// - si el juego está parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la práctica 1, etc.
	void update() override;

	// - Devuelve si el jugador ha ganado
	bool& hasWon();

	// - Setea si el jugador ha ganado
	void setWin(bool t);

	// - Devuelve la textura de los mensajes
	Texture* getMessageTexture();

private:
	bool hasWon_;
	GameState state_;
	Texture* message;

};