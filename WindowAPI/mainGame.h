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
//�÷��̾� ����
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
//�����
struct tagWorldMap
{
	RECT rc;
	image* map;
	float x, y;
	float width, height;
};
//��
struct tagRoom
{
	RECT rc;
	float x, y;
	float width, height;
};

//����
struct tagMob
{
	RECT rc;

	int width, height;
	float x, y;
	bool create;
};
//�÷��̾�
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
//���̾ ��ų
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
//���׿� ��ų
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
//���̽��� ��ų
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
//������� ��ų
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

	int _count;			//������ ���� ī��Ʈ
	int _index;			//������ �̹��� �ε���
	int _dashCount;
	int _dashIndex;
	int _dashWindCount;
	int _dashWindIndex;
	int _castCount;
	int _castIndex;
	int _castEffect1Conunt;			//������ ���� ī��Ʈ
	int _castEffrect1Index;			//������ �̹��� �ε���
	int _castEffect2Conunt;
	int _castEffrect2Index;

	bool pass;



public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//���̵���
	void playerIdle();
	//������
	void playerMove();
	//�뽬���
	void playerDash();
	//����ĳ���ø��
	void slamCasting();
	//�߻�ü ĳ���ø��
	void fireCasting();
	//Ű���� ���� ��ġ
	void keyboardDirection();
	//���콺 ���� ��ġ
	void MouseDirection();
	//����
	void playerAttack();
	//���� 8����
	void playerDirection();
	//Ŭ���� ���� ī��Ʈ �ʱ�ȭ
	void resetCounts();
	//��������Ʈ
	void playerAttackEffect();
	//ĳ��Ʈ ����Ʈ
	void playerCastffect();
	//���̾ ��ų
	void fireBall();
	//���׿� ��ų
	void meteoStrike();
	//���̽��� ��ų
	void iceQueen();
	//����̵���ų
	void tornado();

	

	//��ų�浹
	void skillCollision();


	mainGame() {}
	~mainGame() {}
};

