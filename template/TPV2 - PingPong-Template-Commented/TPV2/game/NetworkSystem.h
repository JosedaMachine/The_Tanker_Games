// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>
#include <array>

#include "../ecs/System.h"
#include "netwrok_messages.h"

class Vector2D;

class NetworkSystem: public System {
public:
	NetworkSystem(const char *host, Uint16 port, std::string playerName);
	virtual ~NetworkSystem();
	void init() override;
	void update() override;

	inline Uint8 getId() {
		return id_;
	}

	inline bool isMaster() {
		return isMaster_;
	}

	inline bool isGameReady() {
		return isGameReday_;
	}

	void sendPaddlePosition(Vector2D pos);
	void sendStartGameRequest();
	void sendStateChanged(Uint8 state, Uint8 left_score, Uint8 right_score);
	void sendBallInfo(Vector2D pos, Vector2D vel);

	auto& getNames() {
		return names_;
	}

	void switchId() {
		if (isMaster_ && !isGameReday_) {
			id_ = 1 - id_;
			std::swap(names_[0], names_[1]);
		}
	}

private:
	const char *host_;
	Uint16 port_;
	bool isMaster_;
	bool isGameReday_;
	Uint8 id_;
	UDPsocket conn_;
	UDPpacket *p_;
	NetworkMessage *m_;
	IPaddress otherPlayerAddress_;
	std::string localPlayerName_;
	std::string remotePlayerName_;
	std::array<std::string, 2> names_;
	Uint32 lastTimeActive_;
};

