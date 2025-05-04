#ifndef CONSTANTS_H
#define CONSTANTS_H

// enum Towards
// {
// 	Left,
// 	Right
// };

#define WINDOW_WIDTH sf::VideoMode::getDesktopMode().width 
#define WINDOW_HEIGHT sf::VideoMode::getDesktopMode().height
#define FPS 60
#define ABSOLUTE_RATE 100
#define CAPOO_POSITION_DELTATIME 1/6
#define INIT_SCALE 0.4
#define BUTTON_INIT_SCALE 0.8
#define BG_R 255
#define BG_G 255
#define BG_B 254
enum Direction
{
	Up,
	Down,
	Left,
	Right
};

enum EnumCapooInfo
{
	BODY,
	EFX_BOT,
	CAPOO_ACC_BOT,
	FACE,
	FACE_DECORATION,
	HAT,
	CLOTHES,
	BACK,
	RIGHT_HAND_ITEM,
	MOOD,
	CAPOO_ACC_BODY,
	CAPOO_ACC_TOP,
	EFX_TOP,
	EFX_APPEARS,
	TALK,
	FOOD,
	POO,
	TOTAL
};

enum class EnumCapooAction
{
    BODY, 
    BODY_LOOP, 
    FACE, 
    FACE_LOOP, 
    MOOD,
    MOOD_LOOP,
    EFFECTTOP,
    EFFECTTOP_LOOP,
    EFFECTBOT,
    EFFECTBOT_LOOP,
    TALK,
    TALK_LOOP,
    APPEAR,
    APPEAR_LOOP,
    FOOD,
    FOOD_LOOP,
    POO,
    POO_LOOP 
};

enum class EnumCapooActionNameKey
{
	idle_idle,
	idle_full,
	walk,
	run,
	wild,
	roll,
	air,
	fall,
	hit,
	pet,
	prone,
	catchUp,
	stackFog,
	stackDown,
	foodAppear,
	chew,
	enjoy,
	pooing,
	waitCleanPoo,
	pooRemoving,
	pooRemoveAfter,
	dizzy,
	summonAppear,
	recycle,
	merge,
	Count
};

enum class EnumCapooStatus
{
	idle,
	walk,
	run,
	wild,
	swoop,
	roll,
	drag,
	fall,
	slide,
	stack,
	pause,
	pet,
	appears,
	recyle,
	hungry,
	eat,
	dizzy,
	poo,
	cleanpoo
};


#endif