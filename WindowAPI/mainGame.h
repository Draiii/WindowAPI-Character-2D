#pragma once
#include "gameNode.h"
#define PI 3.141592f 
#define MOVE_CUT_SPEED 4
#define ATTACK_CUT_SPEED 3
#define ATTACKEFFECT_CUT_SPEED 4
#define CASTEFFECT_CUT_SPEED 8
#define FIREBALLMAX 5
#define ICEQUEENMAX 20
#define SKILLWINDOW 6
#define FUNCTIONKEY 3
#define ROOM_MAX 10
enum idle
{
	IDLE,
	WALK,
	DASH,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	CAST
};
//플레이어 방향
enum direction
{
	BOTTOM,
	TOP,
	RIGHT,
	LEFT,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTTOP,
	RIGHTBOTTOM
};
//월드맵
struct tagWorldMap
{
	RECT rc;
	image* map;
	float x, y;
	float width, height;
};
//방
struct tagRoom
{
	RECT rc;
	float x, y;
	float width, height;
};

//몬스터
struct tagMob
{
	RECT rc;

	int width, height;
	float x, y;
	bool create;
};
//플레이어
struct tagPlayer
{
	RECT rc;
	POINT crossHair;
	image* crossHairImage;
	image* idleImage;
	image* shadowImage;
	image* walkImage;
	image* dashImage;
	image* dashWindImage;
	image* dashShadow1Image;
	image* dashShadow2Image;
	image* WizardGroundSlamDown;
	image* AirSpinnerBurstImage;
	image* CastingCircleEffectImage;
	image* attack1Image;
	image* attack2Image;
	image* attack3Image;
	image* attackEffect1Image;
	image* attackEffectDiagonal1Image;
	image* attackEffect2Image;
	image* attackEffectDiagonal2Image;
	image* attackEffect3Image;
	image* attackEffectDiagonal3Image;

	int width, height;
	int idle;
	int direction;
	float moveSpeed;
	float dashSpeed;	
	float x, y;
	float dashX, dashY;
	float angle;
	float rangeX;
	float rangeY;
	bool walk;
	bool dash;
	bool attack;
	bool slamCast;
	bool fireCast;
};
//UI
struct tagUI
{
	image* hpbarImage;
	image* hpImage;
	image* skillWindowImage[SKILLWINDOW];
	image* functionKeyWindowImage[FUNCTIONKEY];
	image* fireBallWindowImage;
	image* meteoStrikeWindowImage;
	image* iceQueenWindowImage;
	image* tornadoWindowImage;

	image* dashWindowImage;
	image* attackWindowImage;


	image* functionKeyMclickImage;
	image* functionKeyQImage;
	image* functionKeyEImage;
	image* functionKeyRImage;
	image* functionKeyTImage;
	image* functionKeyShiftImage;
};
//파이어볼 스킬
struct tagFireballSkill
{
	RECT rc;
	image* fireBallImage;
	image* fireBallExplosion1Image;
	image* fireBallExplosion2Image;
	float x, y;
	float width, height;
	float angle;
	float speed;
	int skillCount;
	int skillIndex;
	int ExplosionCount;
	int ExplosionIndex;
	int coolDownTime;
	int direction;
	bool isFire;
	bool isExplosion;
};
//메테오 스킬
struct tagMeteoStrikeSkill
{
	RECT rc;
	RECT ExplosionRc;
	image* meteoStrikeImage;
	image* meteoStrikeExplosionImage;
	float x, y;
	float width, height;
	float angle;
	float speed;
	int skillCount;
	int skillIndex;
	int ExplosionCount;
	int ExplosionIndex;
	int coolDownTime;
	POINT range;
	bool isFire;
	bool isExplosion;
};
//아이스퀸 스킬
struct tagIceQueenSkill
{
	RECT rc[ICEQUEENMAX];	
	image* iceQueenImage;
	float x, y;
	float width, height;
	float angle;
	float speed;
	int renderCount;
	int renderCount2;
	int skillCount;
	int skillIndex;
	int coolDownTime;
	int direction;
	bool isFire;
	bool isIce;
};
//토네이토 스킬
struct tagTornadoSkill
{
	RECT rc;
	image* tornadoImage;
	float x, y;
	float width, height;
	int skillCount;
	int skillIndex;
	int coolDownTime;
	bool isFire;

};

class mainGame : public gameNode
{
private:
	int effect1Conunt;
	int effrect1Index;
	int effect2Conunt;
	int effrect2Index;
	int effect3Conunt;
	int effrect3Index;

	int effectDiagonal1Conunt;
	int effrectDiagonal1Index;
	int effectDiagonal2Conunt;
	int effrectDiagonal2Index;
	int effectDiagonal3Conunt;
	int effrectDiagonal3Index;
	
	tagWorldMap _worldMap;
	tagRoom _room[ROOM_MAX];
	tagPlayer _player;
	tagUI _ui;
	tagFireballSkill _fireBall;
	tagMeteoStrikeSkill _meteoStrike;
	tagIceQueenSkill _iceQueen;
	tagTornadoSkill _tornado;

	int _count;			//프레임 돌릴 카운트
	int _index;			//프레임 이미지 인덱스
	int _dashCount;
	int _dashIndex;
	int _dashWindCount;
	int _dashWindIndex;
	int _castCount;
	int _castIndex;
	int _castEffect1Conunt;			//프레임 돌릴 카운트
	int _castEffrect1Index;			//프레임 이미지 인덱스
	int _castEffect2Conunt;
	int _castEffrect2Index;

	bool pass;



public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//아이들모션
	void playerIdle();
	//무브모션
	void playerMove();
	//대쉬모션
	void playerDash();
	//슬램캐스팅모션
	void slamCasting();
	//발사체 캐스팅모션
	void fireCasting();
	//키보드 방향 위치
	void keyboardDirection();
	//마우스 방향 위치
	void MouseDirection();
	//공격
	void playerAttack();
	//공격 8방향
	void playerDirection();
	//클릭시 공격 카운트 초기화
	void resetCounts();
	//공격이펙트
	void playerAttackEffect();
	//캐스트 이펙트
	void playerCastffect();
	//파이어볼 스킬
	void fireBall();
	//메테오 스킬
	void meteoStrike();
	//아이스퀸 스킬
	void iceQueen();
	//토네이도스킬
	void tornado();

	

	//스킬충돌
	void skillCollision();


	mainGame() {}
	~mainGame() {}
};

