#pragma once

enum class EOrderNum
{

	HUD = -15,
	PLAYER = -12,
	FRONTBACKGROUND = -10,
	OBSTACLE = -1,
	COLSTAGE = 1,
	STAGE,
	FOREBACKGROUND,
	BACKGROUND,
};

enum class ECheckDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

enum class EPlayerState
{
	IDLE,
	LOOKUP,
	BEND,
	WALK,
	RUN,
	JUMP,
	STAYUP,
	FALL,
	STICK,
	THROW
};

enum class EColorType
{
	NONE,
	MAGENTA,
	RED,
	GREEN,
	YELLOW
};

enum class EMonsterState
{
	IDLE,
	WALK,
	ATTACK,
	HURT
};