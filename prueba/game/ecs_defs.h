#ifndef ECS_DEFS_H_
#define ECS_DEFS_H_

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class FighterCtrl;
class Image;
class DeAcceleration;
class Heart;
class ShowAtOppositeSide;
class Generations;
class DisableOnExit;
class Gun;
class FramedImage;
class Follow;
class State;
class GameCtrl;
class AsteroidsManager;
class CollisionsManager;

#define _CMPS_LIST_  \
	Transform,\
	FighterCtrl,\
	Image,\
	DeAcceleration, \
	Heart, \
	ShowAtOppositeSide, \
	Generations, \
	DisableOnExit, \
	Gun, \
	FramedImage, \
	Follow, \
	State, \
	GameCtrl, \
	AsteroidsManager, \
	CollisionsManager

// groups
struct Asteroid_grp;
struct Bullet_grp;
#define _GRPS_LIST_  Asteroid_grp, \
	Bullet_grp

// handlers
struct Player_hdlr;
struct Manager_hdlr;
#define _HDLRS_LIST_ Player_hdlr, \
	Manager_hdlr

#endif