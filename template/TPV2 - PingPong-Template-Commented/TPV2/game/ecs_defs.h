// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
struct Image;
struct PaddleCtrlKeys;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	PaddleCtrlKeys

// groups
struct Paddle;
#define _GRPS_LIST_ Paddle

// handlers
struct Ball;
struct LeftPaddle;
struct RightPaddle;
#define _HDLRS_LIST_ \
	Ball, \
	LeftPaddle, \
	RightPaddle

// systems
class BallSystem;
class PaddlesSystem;
class RenderSystem;
class CollisionSystem;
class GameManagerSystem;
class NetworkSystem;

#define _SYS_LIST_ \
		BallSystem, \
		PaddlesSystem, \
		RenderSystem, \
		CollisionSystem, \
		GameManagerSystem,\
		NetworkSystem
