#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//이곳에서 초기화를 한다
	//월드맵 생성
	_worldMap.width = 1000;
	_worldMap.height = 1000;
	_worldMap.x = _worldMap.y = 500;
	_worldMap.rc = RectMakeCenter(_worldMap.x, _worldMap.y, _worldMap.width, _worldMap.height);
	_worldMap.map = IMAGEMANAGER->addImage("map","map/map_1600x1000.bmp", 1600, 1000);

	pass = false;
	//월드맵 안에 방생성
	for (int i = 0; i < ROOM_MAX; i++)
	{
		_room[i].width = RND->range(50, 60);
		_room[i].height = RND->range(50, 60);
		while (1)
		{
			_room[i].rc = RectMake(RND->range(0, 300), RND->range(0, 300), _room[i].width, _room[i].height);
			if (i == 0)
			{
				pass = true;
			}

			for (int j = 0; j < i; j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_room[i].rc, &_room[j].rc))
				{
					break;
				}

				if (j == i - 1)
				{
					pass = true;
				}
			}

			if (pass == true)
			{
				pass = false;
				break;
			}
		}
	}

	//ui 초기화

	//체력바
	_ui.hpbarImage = IMAGEMANAGER->addImage("hpbar","ui/hpbar_250x40.bmp", 250, 40, true, RGB (255,0,255));
	//체력
	_ui.hpImage = IMAGEMANAGER->addImage("hp", "ui/hp_250x40.bmp", 250, 40, true, RGB(255, 0, 255));
	//스킬창
	for (int i = 0; i < SKILLWINDOW; i++)
	{
		_ui.skillWindowImage[i] = IMAGEMANAGER->addImage("skillWindow", "ui/skillwindow_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	}
	//움직임키
	for (int i = 0; i < FUNCTIONKEY; i++)
	{
		_ui.functionKeyWindowImage[i] = IMAGEMANAGER->addImage("functionKeyWindow", "ui/skillwindow_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	}
	//파이어볼 스킬창
	_ui.fireBallWindowImage = IMAGEMANAGER->addImage("fireBallWindow", "ui/fireball_window_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	//아이스퀸 스킬창
	_ui.iceQueenWindowImage = IMAGEMANAGER->addImage("iceQueenWindow", "ui/iceQueen_window_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	//메테오 스킬창
	_ui.meteoStrikeWindowImage = IMAGEMANAGER->addImage("meteoStrikeWindow", "ui/meteo_window_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	//토네이도 스킬창
	_ui.tornadoWindowImage = IMAGEMANAGER->addImage("tornadoWindow", "ui/tornado_window_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	//어택 창
	_ui.attackWindowImage = IMAGEMANAGER->addImage("attackWindow", "ui/attack_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	//대쉬 창
	_ui.dashWindowImage = IMAGEMANAGER->addImage("dashWindow", "ui/Dash_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	//펑션키
	_ui.functionKeyMclickImage = IMAGEMANAGER->addImage("mClick", "ui/Mclick_16x32.bmp", 32, 16, true, RGB(255, 0, 255));
	_ui.functionKeyQImage = IMAGEMANAGER->addImage("Q", "ui/Q_16x16.bmp", 16, 16, true, RGB(255, 0, 255));
	_ui.functionKeyEImage = IMAGEMANAGER->addImage("E", "ui/E_16x16.bmp", 16, 16, true, RGB(255, 0, 255));
	_ui.functionKeyRImage = IMAGEMANAGER->addImage("R", "ui/R_16x16.bmp", 16, 16, true, RGB(255, 0, 255));
	_ui.functionKeyTImage = IMAGEMANAGER->addImage("T", "ui/T_16x16.bmp", 16, 16, true, RGB(255, 0, 255));
	_ui.functionKeyShiftImage = IMAGEMANAGER->addImage("Shift", "ui/Shift_16x16.bmp", 16, 16, true, RGB(255, 0, 255));

	//플레이어 초기화
	_player.direction = BOTTOM;
	_player.idle = IDLE;
	_player.crossHair = { _ptMouse.x-25, _ptMouse.y-25 };
	_player.x = 500.f;
	_player.y = 500.f;
	_player.width = 112;
	_player.height = 132;
	_player.rangeX = _player.x;
	_player.rangeY = _player.y;
	_player.moveSpeed = 4.0f;
	_player.dashSpeed = 15.0f;
	_player.attack = false;
	_player.walk = false;
	_player.dash = false;
	_player.slamCast = false;
	_player.fireCast = false;

	_count = _index = _castCount = _castIndex = _dashCount = _dashCount = _dashWindCount = _dashWindCount = _castEffect1Conunt = _castEffrect1Index = _castEffect2Conunt = _castEffrect2Index = 0;
	effect1Conunt = 0;
	effrect1Index = 0;
	effect2Conunt = 0;
	effrect2Index = 0;
	effect3Conunt = 0;
	effrect3Index = 0;
	effectDiagonal1Conunt = 0;
	effrectDiagonal1Index = 0;
	effectDiagonal2Conunt = 0;
	effrectDiagonal2Index = 0;
	effectDiagonal3Conunt = 0;
	effrectDiagonal3Index = 0;



	//이미지 매니져 사용시
	//_pumpkin = IMAGEMANAGER->addFrameImage("호박", "호박.bmp", 400.f, 400.f, 800, 264, 8, 2);
	//IMAGEMANAGER->addFrameImage("호박", "호박.bmp", 400.f, 400.f, 800, 264, 8, 2);

	//플레이어 렉트
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
	//크로스헤어 이미지
	_player.crossHairImage = IMAGEMANAGER->addImage("크로스헤어", "crosshair/crosshair_50x50.bmp", 50, 50,true,RGB(255,0,255));
	//그림자 이미지
	_player.shadowImage = IMAGEMANAGER->addImage("shadow", "player/shadow/shadow_112x61.bmp", 56, 31, true, RGB(255, 0, 255));
	//아이들이미지
	_player.idleImage = IMAGEMANAGER->addFrameImage("idle", "player/idle/playerIdle_1x4_112x528.bmp", (float)_player.rc.left, (float)_player.rc.top, 112, 528, 1, 4);
	//워크이미지
	_player.walkImage = IMAGEMANAGER->addFrameImage("walk", "player/walk/playerWalk_10x4_1120x496.bmp", (float)_player.rc.left, (float)_player.rc.top, 1120, 496, 10, 4);
	//대쉬 이미지
	_player.dashImage = IMAGEMANAGER->addFrameImage("dash", "player/dash/dash_1620_720_9_4_1.bmp", (float)_player.rc.left, (float)_player.rc.top, 1620, 720, 9, 4);
	//대쉬 바람 이미지
	_player.dashWindImage = IMAGEMANAGER->addFrameImage("dashWind", "player/dash/dashWind_1350x105_5.bmp", (float)_player.rc.left, (float)_player.rc.top, 1350, 105, 5, 1);
	//대쉬 쉐도우 이미지
	_player.dashShadow1Image = IMAGEMANAGER->addFrameImage("dashShadow", "player/dash/dashShadow1_1620_720_9_4.bmp", (float)_player.rc.left, (float)_player.rc.top, 1620, 720, 9, 4);
	_player.dashShadow2Image = IMAGEMANAGER->addFrameImage("dashShadow2", "player/dash/dashShadow2_1620_720_9_4.bmp", (float)_player.rc.left, (float)_player.rc.top, 1620, 720, 9, 4);
	//서클 캐스트 이펙트
	_player.CastingCircleEffectImage = IMAGEMANAGER->addFrameImage("CastingCircleEffectImage", "effect/CastingCircleEffect/CastingCircleEffect_5120x128_20.bmp", 5120, 128, 20, 1);
	//에어 캐스트 이펙트
	_player.AirSpinnerBurstImage = IMAGEMANAGER->addFrameImage("AirSpinnerBurst", "effect/castEffect/AirSpinnerBurst/AirSpinnerBurst_1792x150_7.bmp", 1792, 150, 7, 1);
	//슬램다운캐스팅이미지
	_player.WizardGroundSlamDown = IMAGEMANAGER->addFrameImage("WizardGroundSlamDown", "player/casting/slam/WizardGroundSlamDown0_1972x385_10_2.bmp", (float)_player.rc.left, (float)_player.rc.top, 1972, 385, 10, 2);
	//공격1이미지
	_player.attack1Image = IMAGEMANAGER->addFrameImage("attack1","player/attack1/playerAttack1_9x4_1224x624.bmp", (float)_player.rc.left, (float)_player.rc.top, 1224, 624, 9, 4);
	//공격2이미지
	_player.attack2Image = IMAGEMANAGER->addFrameImage("attack2", "player/Attack2/playerAttack2_8x4_1216x592.bmp", (float)_player.rc.left, (float)_player.rc.top, 1216, 592, 8, 4);
	//공격3이미지
	_player.attack3Image = IMAGEMANAGER->addFrameImage("attack3", "player/Attack3/playerAttack3_9x4_1260x608.bmp", (float)_player.rc.left, (float)_player.rc.top, 1260, 608, 9, 4);
	//공격이펙트1이미지
	_player.attackEffect1Image = IMAGEMANAGER->addFrameImage("attackEffect1", "effect/attackEffect/attackEffect1_1008x576.bmp", (float)_player.rc.left, (float)_player.rc.top, 1008, 576, 7, 4);	
	//공격이펙트2이미지
	_player.attackEffect2Image = IMAGEMANAGER->addFrameImage("attackEffect2", "effect/attackEffect/attackEffect2_1008x576.bmp", (float)_player.rc.left, (float)_player.rc.top, 1008, 576, 7, 4);
	//공격이펙트3이미지
	_player.attackEffect3Image = IMAGEMANAGER->addFrameImage("attackEffect3", "effect/attackEffect/attackEffect3_1152_576.bmp", (float)_player.rc.left, (float)_player.rc.top, 1152, 576, 8, 4);
	//공격이펙트 대각1이미지
	_player.attackEffectDiagonal1Image = IMAGEMANAGER->addFrameImage("attackEffectDiagonal1", "effect/attackEffect/attackEffect1_대각_1008x576.bmp", (float)_player.rc.left, (float)_player.rc.top, 1008, 576, 7, 4);
	//공격이펙트 대각1이미지
	_player.attackEffectDiagonal2Image = IMAGEMANAGER->addFrameImage("attackEffectDiagonal2", "effect/attackEffect/attackEffect2_대각_1008x576.bmp", (float)_player.rc.left, (float)_player.rc.top, 1008, 576, 7, 4);
	//공격이펙트 대각3이미지
	_player.attackEffectDiagonal3Image = IMAGEMANAGER->addFrameImage("attackEffectDiagonal3", "effect/attackEffect/attackEffect3_대각_1152_576.bmp", (float)_player.rc.left, (float)_player.rc.top, 1152, 576, 8, 4);


	//파이어볼
	_fireBall.fireBallImage = IMAGEMANAGER->addFrameImage("fireBall", "skill/fireBall/fireball_744x992.bmp", (float)_player.x, (float)_player.y, 744, 992, 6, 8);
	_fireBall.fireBallExplosion1Image = IMAGEMANAGER->addFrameImage("explosion1", "skill/fireBall/fireSkill1_1206x175_9x1.bmp", (float)_fireBall.x, (float)_fireBall.y, 1206, 175, 9, 1);
	_fireBall.fireBallExplosion2Image = IMAGEMANAGER->addFrameImage("explosion2", "skill/fireBall/fireSkill2_1251x174_9x1.bmp", (float)_fireBall.x, (float)_fireBall.y, 1251, 174, 9, 1);

	_fireBall.x = _player.x-77;
	_fireBall.y = _player.y-77;
	_fireBall.width = 124;
	_fireBall.height = 124;
	_fireBall.angle = 0.0f;
	_fireBall.speed = 8.0f;	
	_fireBall.skillCount = _fireBall.skillIndex = 0;
	_fireBall.ExplosionCount = _fireBall.ExplosionIndex = 0;
	_fireBall.coolDownTime = 0;
	_fireBall.isFire = false;
	_fireBall.isExplosion = false;
	//메테오
	_meteoStrike.meteoStrikeImage = IMAGEMANAGER->addFrameImage("_meteoStrike", "skill/meteoStrike/MeteorStrike_1800x410_1.bmp", (float)_meteoStrike.x, (float)_meteoStrike.y, 1800, 410, 6, 1);
	//_meteoStrike.meteoStrikeImage = IMAGEMANAGER->addFrameImage("_meteoStrike", "skill/meteoStrike/1464x548_4.bmp", (float)_meteoStrike.x, (float)_meteoStrike.y, 1464, 548, 4, 1);
	_meteoStrike.meteoStrikeExplosionImage = IMAGEMANAGER->addFrameImage("_meteoStrikeExplosion", "skill/meteoStrike/FireExplosion2_2800x386_2.bmp", (float)_meteoStrike.range.x, (float)_meteoStrike.range.y, 2800, 386, 7, 1);

	_meteoStrike.x = 1000.f;
	_meteoStrike.y = -500.f;
	_meteoStrike.width = 300;
	_meteoStrike.height = 400;
	_meteoStrike.angle = 0.0f;
	_meteoStrike.speed = 8.0f;
	_meteoStrike.skillCount = _meteoStrike.skillIndex = 0;
	_meteoStrike.ExplosionCount = _meteoStrike.ExplosionIndex= 0;		
	_meteoStrike.coolDownTime = 0;	
	_meteoStrike.isFire = false;
	_meteoStrike.isExplosion = false;

	//아이스퀸
	_iceQueen.iceQueenImage = IMAGEMANAGER->addFrameImage("iceQueen","skill/iceQueen/IceQueen_1200x220_1.bmp", (float)_iceQueen.x, (float)_iceQueen.y, 900, 165, 10, 1);
	_iceQueen.x = _player.x - 77;
	_iceQueen.y = _player.y - 77;
	_iceQueen.width = 90;
	_iceQueen.height = 165;
	_iceQueen.angle = 0.0f;
	_iceQueen.speed = 0.0f;
	_iceQueen.skillCount = 0;
	_iceQueen.skillIndex = 0;
	_iceQueen.renderCount = _iceQueen.renderCount2 = 0;
	_iceQueen.coolDownTime = 0;	
	_iceQueen.isFire = false;
	_iceQueen.isIce = false;

	//토네이도
	_tornado.tornadoImage = IMAGEMANAGER->addFrameImage("tornado","skill/tornado/Tornado_3600x232_1.bmp", (float)_tornado.x, (float)_tornado.y, 3600, 232, 12, 1);
	_tornado.x = _player.x;
	_tornado.y = _player.y;
	_tornado.width = 300;
	_tornado.height = 232;
	_tornado.skillCount = _tornado.skillIndex = 0;
	_tornado.coolDownTime = 0;
	_tornado.isFire = false;
	

	





	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다
	
	//이미지 매니져 사용시 매니져가 알아서 해제 해주니까
	//safe_delete() 사용할 필요 없다
}


//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//월드맵
	//_worldMap.rc = RectMakeCenter(_worldMap.x, _worldMap.y, _worldMap.width, _worldMap.height);
	//플레이어 렉트 업데이트
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
	//마우스 좌표 업데이트
	_player.crossHair = { _ptMouse.x - 25, _ptMouse.y - 25 };
	//발사체 속도

	//공격 마우스 키
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_player.slamCast && !_player.dash)
	{
		//클릭시 카운트 초기화
		this->resetCounts();
		this->MouseDirection();
		_player.idle = ATTACK1;	
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//_player.idle = IDLE;
	}
	//움직임 키
	if (KEYMANAGER->isStayKeyDown('S') && !_player.slamCast && !_player.dash)
	{		
		//_worldMap.y -= _player.moveSpeed;
		_player.y += _player.moveSpeed;
		_player.direction = BOTTOM;
		_player.idle = WALK;
		_player.walk = true;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_player.idle = IDLE;
		_player.walk = false;
	}
	if (KEYMANAGER->isStayKeyDown('W') && !_player.slamCast && !_player.dash)
	{
		//_worldMap.y += _player.moveSpeed;
		_player.y -= _player.moveSpeed;
		_player.direction = TOP;
		_player.idle = WALK;
		_player.walk = true;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_player.idle = IDLE;
		_player.walk = false;
	}
	if (KEYMANAGER->isStayKeyDown('D') && !_player.slamCast && !_player.dash)
	{
		//_worldMap.x -= _player.moveSpeed;
		_player.x += _player.moveSpeed;
		_player.direction = RIGHT;
		_player.idle = WALK;
		_player.walk = true;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_player.idle = IDLE;
		_player.walk = false;
	}
	if (KEYMANAGER->isStayKeyDown('A') && !_player.slamCast && !_player.dash)
	{
		//_worldMap.x += _player.moveSpeed;
		_player.x -= _player.moveSpeed;
		_player.direction = LEFT;
		_player.idle = WALK;
		_player.walk = true;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_player.idle = IDLE;
		_player.walk = false;
	}
	//대쉬
	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT)&& !_player.dash)
	{
		_player.dashSpeed = 22.0f;
		_player.dash = true;
		_player.idle = DASH;
		_dashCount = _dashIndex = _dashWindCount = _dashWindIndex = 0;
		//위치저장
		_player.dashX = _player.x;
		_player.dashY = _player.y;
	}
	//파이어볼 스킬 // 마우스 방향 지정
	if (KEYMANAGER->isOnceKeyDown('Q') && !_fireBall.isFire)
	{
		//마우스 방향에 따라 위치값 찾기
		this->MouseDirection();
		//캐스팅
		_player.fireCast = true;
		_fireBall.skillCount = _fireBall.skillIndex = 0;
		//발사
		_fireBall.isFire = true;
		//방향 저장
		_fireBall.x = _player.x;
		_fireBall.y = _player.y;
		_fireBall.direction = _player.direction;
		//각도 저장
		_fireBall.angle = getAngle(_player.x, _player.y, _ptMouse.x, _ptMouse.y);
	}
	//메테오 스킬
	if (KEYMANAGER->isOnceKeyDown('R') && !_meteoStrike.isFire)
	{
		_player.slamCast = true;
		_meteoStrike.x = _player.crossHair.x + 400;
		_meteoStrike.y = -200.f;
		_meteoStrike.skillCount = _meteoStrike.skillIndex = 0;
		//발사
		_meteoStrike.isFire = true;
		//방향 저장
		//_meteoStrike.x = _player.x;
		//_meteoStrike.y = _player.y;
		//위치저장
		_meteoStrike.range.x = _ptMouse.x;
		_meteoStrike.range.y = _ptMouse.y;
		//각도 저장
		_meteoStrike.angle = getAngle(_meteoStrike.x, _meteoStrike.y, _ptMouse.x, _ptMouse.y);
	}
	//아이스퀸 스킬
	if (KEYMANAGER->isOnceKeyDown('E') && !_iceQueen.isFire)
	{
		_player.slamCast = true;
		_iceQueen.skillCount = _iceQueen.skillIndex = _iceQueen.renderCount = 0;
		//발사
		_iceQueen.isFire = true;
		//방향 저장
		_iceQueen.x = _player.x;
		_iceQueen.y = _player.y;
		_iceQueen.direction = _player.direction;
		//각도 저장
		_iceQueen.angle = getAngle(_player.x, _player.y, _ptMouse.x, _ptMouse.y);
	}
	//토네이도 스킬
	if (KEYMANAGER->isOnceKeyDown('T') && !_tornado.isFire)
	{
		_player.slamCast = true;
		_tornado.skillCount = _tornado.skillIndex = 0;
		//발사
		_tornado.isFire = true;
		//방향 저장
		_tornado.x = _player.x;
		_tornado.y = _player.y;
	}

	//아이들모션
	this->playerIdle();
	//무브모션
	this->playerMove();
	//대쉬모션
	this->playerDash();
	//슬램캐스팅 모션
	this->slamCasting();
	//발사체 캐스팅모션
	this->fireCasting();
	//공격모션
	this->playerAttack();
	//키보드 방향 위치
	this->keyboardDirection();
	//마우스 방향 위치
	this->playerDirection();
	//공격이펙트
	this->playerAttackEffect();
	//캐스트 이펙트
	this->playerCastffect();
	//스킬
	this->fireBall();
	this->iceQueen();
	this->meteoStrike();
	this->tornado();
	//스킬 충돌
	this->skillCollision();
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void mainGame::render(HDC hdc)
{
	//백버퍼 가져오기 (이건 렌더에 두기)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	//PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다

	Rectangle(memDC, _worldMap.rc);

	_worldMap.map->render(memDC, _worldMap.rc.left, _worldMap.rc.top);
	for (int i = 0; i < ROOM_MAX; i++)
	{
	//	Rectangle(memDC, _room[i].rc);
	}

	//테스트
	//char str[128];
	//wsprintf(str, "방향:%d", _player.direction);
	//TextOut(memDC, 800, 10, str, strlen(str));
	//char str1[128];
	//wsprintf(str1, "x:%d y:%d", _ptMouse.x , _ptMouse.y);
	//TextOut(memDC, 800, 30, str1, strlen(str1));
	//char str2[128];
	//wsprintf(str2, "플레이어 x:%d 플레이어 y:%d", _player.dashX, _player.dashY);
	//TextOut(memDC, 800, 50, str2, strlen(str2));
		
	
	//플레이어 움직임
	//Rectangle(memDC, _player.rc);
	//그림자
	_player.shadowImage->render(memDC, _player.x-27, _player.y+45);
	//슬램 캐스팅 이펙트
	if (_player.slamCast)
	{
		_player.AirSpinnerBurstImage->frameRender(memDC, _player.x-130, _player.y-20);
	}	
	//서클 캐스팅 이펙트
	if (_player.slamCast)
	{
		_player.CastingCircleEffectImage->frameRender(memDC, _player.x-130, _player.y);
	}
	//아이들
	if (_player.idle == IDLE && !_player.slamCast && !_player.fireCast && !_player.dash)
	{
		_player.idleImage->frameRender(memDC, _player.rc.left, _player.rc.top);
	}
	//무브
	if (_player.idle == WALK && !_player.attack && !_player.fireCast && !_player.dash)
	{
		_player.walkImage->frameRender(memDC, _player.rc.left, _player.rc.top);
	}
	//대쉬
	if (_player.dash && !_player.attack && !_player.fireCast)
	{
		_player.dashWindImage->frameRender(memDC, _player.dashX-136, _player.dashY);				//대쉬바람
		_player.dashShadow2Image->frameRender(memDC, _player.rc.left - 34, _player.rc.top - 14);	//대쉬그림자2
		_player.dashShadow1Image->frameRender(memDC, _player.rc.left - 34, _player.rc.top - 14);	//대쉬그림자1
		_player.dashImage->frameRender(memDC, _player.rc.left-34, _player.rc.top-14);				//대쉬
	}
	//슬램다운캐스팅
	if (_player.slamCast && !_player.attack && !_player.walk)
	{
		_player.WizardGroundSlamDown->frameRender(memDC, _player.rc.left-40, _player.rc.top-20);
	}

	//발사체캐스팅
	if (_player.fireCast && !_player.attack)
	{
		_player.attack3Image->frameRender(memDC, _player.rc.left - 10, _player.rc.top - 15);
	}
	//공격1
	if (_player.idle == ATTACK1)
	{
		_player.attack1Image->frameRender(memDC, _player.rc.left - 10, _player.rc.top - 15);

		if (_player.direction == BOTTOM || _player.direction == TOP || _player.direction == LEFT || _player.direction == RIGHT)
		{
			_player.attackEffect1Image->frameRender(memDC, _player.rangeX, _player.rangeY);
		}
		else
		{
			_player.attackEffectDiagonal1Image->frameRender(memDC, _player.rangeX, _player.rangeY);
		}		
	}
	//공격2
	if (_player.idle == ATTACK2)
	{
		_player.attack2Image->frameRender(memDC, _player.rc.left - 10, _player.rc.top - 15);

		if (_player.direction == BOTTOM || _player.direction == TOP || _player.direction == LEFT || _player.direction == RIGHT)
		{
			_player.attackEffect2Image->frameRender(memDC, _player.rangeX, _player.rangeY);
		}
		else
		{
			_player.attackEffectDiagonal2Image->frameRender(memDC, _player.rangeX, _player.rangeY);
		}		
	}
	//공격3
	if (_player.idle == ATTACK3)
	{
		_player.attack3Image->frameRender(memDC, _player.rc.left - 10, _player.rc.top - 15);

		if (_player.direction == BOTTOM || _player.direction == TOP || _player.direction == LEFT || _player.direction == RIGHT)
		{
			_player.attackEffect3Image->frameRender(memDC, _player.rangeX, _player.rangeY);
		}
		else
		{
			_player.attackEffectDiagonal3Image->frameRender(memDC, _player.rangeX, _player.rangeY);
		}		
	}

	//발사선
	//LineMake(memDC, _player.x, _player.y, _ptMouse.x, _ptMouse.y);

	//파이어볼 렌더
	if (_fireBall.isFire)
	{
		//Rectangle(memDC, _fireBall.rc);
		_fireBall.fireBallImage->frameRender(memDC, _fireBall.rc.left, _fireBall.rc.top);
	}
	//파이어볼 폭발 렌더
	if (_fireBall.isExplosion)
	{			
		_fireBall.fireBallExplosion1Image->frameRender(memDC, _fireBall.rc.left, _fireBall.rc.top);
		_fireBall.fireBallExplosion2Image->frameRender(memDC, _fireBall.rc.left, _fireBall.rc.top);

	}
	//메테오 렌더
	if (_meteoStrike.isFire)
	{
		//Rectangle(memDC, _meteoStrike.rc);
		_meteoStrike.meteoStrikeImage->frameRender(memDC, _meteoStrike.rc.left, _meteoStrike.rc.top);
	}
	//메테오 폭발 렌더
	if (_meteoStrike.isExplosion)
	{		
		_meteoStrike.meteoStrikeExplosionImage->frameRender(memDC, _meteoStrike.range.x-200, _meteoStrike.range.y-270);
	}
	//아이스퀸 렌더
	if (_iceQueen.isFire)
	{		
		for (int i = 0; i < ICEQUEENMAX; i++)
		{
			//Rectangle(memDC, _iceQueen.rc[i]);
			//Rectangle(memDC, _iceQueen.rc2);
			_iceQueen.iceQueenImage->frameRender(memDC, _iceQueen.rc[i].left, _iceQueen.rc[i].top);
			//_iceQueen.iceQueenImage->frameRender(memDC, _iceQueen.rc2.left, _iceQueen.rc2.top);
		}		
	}
	//토네이도 렌더
	if (_tornado.isFire)
	{
		//Rectangle(memDC, _tornado.rc);
		_tornado.tornadoImage->frameRender(memDC, _tornado.rc.left, _tornado.rc.top);
	}

	//ui 렌더
	//체력
	_ui.hpImage->render(memDC, 20, 30);
	//체력바
	_ui.hpbarImage->render(memDC, 20, 30);
	//1스킬 파이어볼
	_ui.fireBallWindowImage->render(memDC, 30, 920);
	//2스킬 아이스퀸
	_ui.iceQueenWindowImage->render(memDC, 90, 920);
	//3스킬 메테오
	_ui.meteoStrikeWindowImage->render(memDC, 150, 920);
	//4스킬 토네이도
	_ui.tornadoWindowImage->render(memDC, 210, 920);

	//대쉬 창
	_ui.dashWindowImage->render(memDC, 500, 920);
	//어택 창
	_ui.attackWindowImage->render(memDC, 560, 920);
	//스킬바
	for (int i = 0; i < SKILLWINDOW; i++)
	{
		_ui.skillWindowImage[i]->render(memDC, 30 + (i * 60), 920 );
	}
	//쉬프트 마우스 클릭 창
	for (int i = 0; i < FUNCTIONKEY; i++)
	{
		_ui.functionKeyWindowImage[i]->render(memDC, 500 + (i * 60), 920);
	}
	//펑션키	이미지
	_ui.functionKeyMclickImage->render(memDC, 578, 900, 0, 0, 16, 16);	//왼클릭
	_ui.functionKeyMclickImage->render(memDC, 638, 900, 16, 0, 16, 16);	//우클릭
	_ui.functionKeyQImage->render(memDC, 48, 900);
	_ui.functionKeyEImage->render(memDC, 108, 900);
	_ui.functionKeyRImage->render(memDC, 168, 900);
	_ui.functionKeyTImage->render(memDC, 228, 900);
	_ui.functionKeyShiftImage->render(memDC, 518, 900);




	
	//크로스헤어
	_player.crossHairImage->render(memDC, _player.crossHair.x, _player.crossHair.y);
	//호박 프레임 이미지 렌더
	//이미지변수로 사용할때
	//_pumpkin->frameRender(memDC, _pumpkin->getX(), _pumpkin->getY());
	//이미지매니져에서 바로 렌더
	//IMAGEMANAGER->frameRender("호박", memDC, _pumpkin->getX(), _pumpkin->getY());
	//IMAGEMANAGER->findImage("호박")->frameRender(memDC, _pumpkin->getX(), _pumpkin->getY());

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(hdc);
}
//아이들 모션
void mainGame::playerIdle()
{
	
	if (!_player.walk && _player.direction == BOTTOM && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(0);
	}
	if (!_player.walk && _player.direction == TOP && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(1);
	}
	if (!_player.walk && _player.direction == RIGHT && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(2);
	}
	if (!_player.walk && _player.direction == RIGHTTOP && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(2);
	}
	if (!_player.walk && _player.direction == RIGHTBOTTOM && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(2);
	}
	if (!_player.walk && _player.direction == LEFT && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(3);
	}
	if (!_player.walk && _player.direction == LEFTTOP && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(3);
	}
	if (!_player.walk && _player.direction == LEFTBOTTOM && _player.idle == IDLE)
	{
		_player.idleImage->setFrameY(3);
	}
}
//움직임 모션
void mainGame::playerMove()
{	
	//위
	if (_player.walk && _player.direction == TOP)
	{		
		_count++;		
		_player.walkImage->setFrameY(1);
		if (_count % MOVE_CUT_SPEED == 0)
		{
			_index++;
			if (_index > 10)
			{
				_index = 0;
			}
			_player.walkImage->setFrameX(_index);
		}
	}
	//아래
	if (_player.walk && _player.direction == BOTTOM)
	{
		_count++;
		_player.walkImage->setFrameY(0);
		if (_count % MOVE_CUT_SPEED == 0)
		{
			_index++;
			if (_index > 10)
			{
				_index = 0;
			}
			_player.walkImage->setFrameX(_index);
		}
	}
	//오른쪽
	if (_player.walk && _player.direction == RIGHT)
	{
		_count++;
		_player.walkImage->setFrameY(2);
		if (_count % MOVE_CUT_SPEED == 0)
		{
			_index++;
			if (_index > 10)
			{
				_index = 0;
			}
			_player.walkImage->setFrameX(_index);
		}
	}
	//왼쪽
	if (_player.walk && _player.direction == LEFT)
	{
		_count++;
		_player.walkImage->setFrameY(3);
		if (_count % MOVE_CUT_SPEED == 0)
		{
			_index++;
			if (_index > 10)
			{
				_index = 0;
			}
			_player.walkImage->setFrameX(_index);
		}
	}
}
//대쉬모션
void mainGame::playerDash()
{	
	if (_player.dash)
	{			

		//바람
		_dashWindCount++;
		_player.dashWindImage->setFrameY(0);
		if (_dashWindCount % 8 == 0)
		{
			_dashWindIndex++;
			if (_dashWindIndex > 4)
			{
				_dashWindIndex = 0;

			}
			_player.dashWindImage->setFrameX(_dashWindIndex);
		}
		//방향
		if (_player.direction == LEFT)
		{
			_player.dashSpeed--;
			_player.x -= _player.dashSpeed;			
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == LEFTTOP)
		{
			_player.dashSpeed--;
			_player.x -= _player.dashSpeed;
			_player.y -= _player.dashSpeed;
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == LEFTBOTTOM)
		{
			_player.dashSpeed--;
			_player.x -= _player.dashSpeed;
			_player.y += _player.dashSpeed;
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == TOP)
		{
			_player.dashSpeed--;
			_player.y -= _player.dashSpeed;
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == BOTTOM)
		{
			_player.dashSpeed--;
			_player.y += _player.dashSpeed;
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == RIGHTTOP)
		{
			_player.dashSpeed--;
			_player.x += _player.dashSpeed;
			_player.y -= _player.dashSpeed;
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == RIGHT)
		{
			_player.dashSpeed--;
			_player.x += _player.dashSpeed;		
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}
		else if (_player.direction == RIGHTBOTTOM)
		{
			_player.dashSpeed--;
			_player.x += _player.dashSpeed;
			_player.y += _player.dashSpeed;
			if (_player.dashSpeed <= 0)
			{
				_player.dashSpeed = 0;
			}
		}

		//이미지
		//바텀
		if (_player.direction == BOTTOM)
		{
			_dashCount++;
			_player.dashImage->setFrameY(0);
			_player.dashShadow1Image->setFrameY(0);
			_player.dashShadow2Image->setFrameY(0);
			if (_dashCount % 4 == 0)
			{
				_dashIndex++;
				if (_dashIndex > 8)
				{
					_dashIndex = 0;
					_player.dash = false;
					_player.idle = IDLE;
				}
				_player.dashImage->setFrameX(_dashIndex);
				_player.dashShadow1Image->setFrameX(_dashIndex-1);
				_player.dashShadow2Image->setFrameX(_dashIndex-2);
			}
		}
		//탑
		if (_player.direction == TOP)
		{
			_dashCount++;
			_player.dashImage->setFrameY(1);
			_player.dashShadow1Image->setFrameY(1);
			_player.dashShadow2Image->setFrameY(1);
			if (_dashCount % 4 == 0)
			{
				_dashIndex++;
				if (_dashIndex > 8)
				{
					_dashIndex = 0;
					_player.dash = false;
					_player.idle = IDLE;
				}
				_player.dashImage->setFrameX(_dashIndex);
				_player.dashShadow1Image->setFrameX(_dashIndex-1);
				_player.dashShadow2Image->setFrameX(_dashIndex-2);
			}
		}
		//라이트
		if (_player.direction == RIGHTTOP || _player.direction == RIGHT || _player.direction == RIGHTBOTTOM)
		{
			_dashCount++;
			_player.dashImage->setFrameY(2);
			_player.dashShadow1Image->setFrameY(2);
			_player.dashShadow2Image->setFrameY(2);

			if (_dashCount % 4 == 0)
			{
				_dashIndex++;
				if (_dashIndex > 8)
				{
					_dashIndex = 0;
					_player.dash = false;
					_player.idle = IDLE;
				}
				_player.dashImage->setFrameX(_dashIndex);
				_player.dashShadow1Image->setFrameX(_dashIndex-1);
				_player.dashShadow2Image->setFrameX(_dashIndex-2);
			}
		}
		//레프트
		if (_player.direction == LEFTTOP || _player.direction == LEFT || _player.direction == LEFTBOTTOM)
		{
			_dashCount++;
			_player.dashImage->setFrameY(3);
			_player.dashShadow1Image->setFrameY(3);
			_player.dashShadow2Image->setFrameY(3);
			if (_dashCount % 4 == 0)
			{
				_dashIndex++;
				if (_dashIndex > 8)
				{
					_dashIndex = 0;		
					_player.dash = false;
					_player.idle = IDLE;
				}
				_player.dashImage->setFrameX(_dashIndex);
				_player.dashShadow1Image->setFrameX(_dashIndex-1);
				_player.dashShadow2Image->setFrameX(_dashIndex-2);
			}
		}

	}
}
//슬램 캐스팅 모션
void mainGame::slamCasting()
{
	if (_player.slamCast)
	{
		_player.walk = false;
		if (_player.direction == LEFTTOP || _player.direction == TOP || _player.direction == RIGHTTOP)
		{
			_castCount++;
			_player.WizardGroundSlamDown->setFrameY(1);
			if (_castCount % 5 == 0)
			{
				_castIndex++;
				if (_castIndex > 10)
				{
					_castIndex = 0;
					_player.slamCast = false;
				}
				_player.WizardGroundSlamDown->setFrameX(_castIndex);
			}
		}

		else
		{
			_castCount++;
			_player.WizardGroundSlamDown->setFrameY(0);
			if (_castCount % 5 == 0)
			{
				_castIndex++;
				if (_castIndex > 10)
				{
					_castIndex = 0;
					_player.slamCast = false;
				}
				_player.WizardGroundSlamDown->setFrameX(_castIndex);
			}
		}
	}
}
//발사체 캐스팅모션
void mainGame::fireCasting()
{
	_player.walk = false;
	if (_player.fireCast)
	{
		if (_player.direction == BOTTOM)
		{
			_count++;
			_player.attack3Image->setFrameY(0);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.direction = BOTTOM;
					_player.fireCast = false;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
		if (_player.direction == TOP)
		{
			_count++;
			_player.attack3Image->setFrameY(1);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.direction = TOP;
					_player.fireCast = false;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
		if (_player.direction == RIGHT || _player.direction == RIGHTTOP || _player.direction == RIGHTBOTTOM)
		{
			_count++;
			_player.attack3Image->setFrameY(2);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.direction = RIGHT;
					_player.fireCast = false;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
		if (_player.direction == LEFT || _player.direction == LEFTTOP || _player.direction == LEFTBOTTOM)
		{
			_count++;
			_player.attack3Image->setFrameY(3);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.direction = LEFT;
					_player.fireCast = false;
					
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
	}
}
//키보드 방향 위치
void mainGame::keyboardDirection()
{
	//LEFTTOP
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W'))
	{
		_player.direction = LEFTTOP;
	}
	//RIGHTOP
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W'))
	{
		_player.direction = RIGHTTOP;
	}
	//LEFTBOTTOM
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S'))
	{
		_player.direction = LEFTBOTTOM;
	}
	//RIGHTBOTTOM
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	{
		_player.direction = RIGHTBOTTOM;
	}
}
//마우스 클릭 방향 위치
void mainGame::MouseDirection()
{
	//BOTTOM
	if (_player.crossHair.y >= _player.rc.top)
	{
		_player.direction = BOTTOM;
	}
	//TOP
	if (_player.crossHair.y <= _player.rc.bottom)
	{
		_player.direction = TOP;
	}
	//RIGHT
	if (_player.crossHair.x >= _player.rc.right)
	{
		_player.direction = RIGHT;
	}
	//LEFT
	if (_player.crossHair.x <= _player.rc.left)
	{
		_player.direction = LEFT;
	}

	//LEFTTOP
	if (_player.crossHair.x < _player.rc.left && _player.crossHair.y < _player.rc.top)
	{
		_player.direction = LEFTTOP;
	}
	//LEFTBOTTOM
	if (_player.crossHair.x < _player.rc.left && _player.crossHair.y > _player.rc.bottom)
	{
		_player.direction = LEFTBOTTOM;
	}
	//RIGHTTOP
	if (_player.crossHair.x > _player.rc.right && _player.crossHair.y < _player.rc.top)
	{
		_player.direction = RIGHTTOP;
	}
	//RIGHTBOTOOM
	if (_player.crossHair.x > _player.rc.right && _player.crossHair.y > _player.rc.bottom)
	{
		_player.direction = RIGHTBOTTOM;
	}
}
//공격 콤보
void mainGame::playerAttack()
{
	//공격1
	if (_player.idle == ATTACK1)
	{
		if (_player.direction == BOTTOM)
		{
			_count++;			
			_player.attack1Image->setFrameY(0);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = ATTACK2;
				}
				_player.attack1Image->setFrameX(_index);
			}
		}
		if (_player.direction == TOP)
		{
			_count++;
			_player.attack1Image->setFrameY(1);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;				
				if (_index > 8)
				{
					_index = 0;
					_player.idle = ATTACK2;
				}
				_player.attack1Image->setFrameX(_index);
			}
		}
		if (_player.direction == RIGHT || _player.direction == RIGHTTOP || _player.direction == RIGHTBOTTOM)
		{
			_count++;
			_player.attack1Image->setFrameY(2);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = ATTACK2;
				}
				_player.attack1Image->setFrameX(_index);
			}
		}
		if (_player.direction == LEFT || _player.direction == LEFTTOP || _player.direction == LEFTBOTTOM)
		{
			_count++;
			_player.attack1Image->setFrameY(3);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = ATTACK2;
				}
				_player.attack1Image->setFrameX(_index);
			}
		}
	}

	//공격2
	if (_player.idle == ATTACK2)
	{
		if (_player.direction == BOTTOM)
		{
			_count++;
			_player.attack2Image->setFrameY(0);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 7)
				{
					_index = 0;
					_player.idle = ATTACK3;
				}
				_player.attack2Image->setFrameX(_index);
			}
		}
		if (_player.direction == TOP)
		{
			_count++;
			_player.attack2Image->setFrameY(1);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 7)
				{
					_index = 0;
					_player.idle = ATTACK3;
				}
				_player.attack2Image->setFrameX(_index);
			}
		}
		if (_player.direction == RIGHT || _player.direction == RIGHTTOP || _player.direction == RIGHTBOTTOM)
		{
			_count++;
			_player.attack2Image->setFrameY(2);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 7)
				{
					_index = 0;
					_player.idle = ATTACK3;
				}
				_player.attack2Image->setFrameX(_index);
			}
		}
		if (_player.direction == LEFT || _player.direction == LEFTTOP || _player.direction == LEFTBOTTOM)
		{
			_count++;
			_player.attack2Image->setFrameY(3);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 7)
				{
					_index = 0;
					_player.idle = ATTACK3;
				}
				_player.attack2Image->setFrameX(_index);
			}
		}
	}

	//공격3
	if (_player.idle == ATTACK3)
	{
		if (_player.direction == BOTTOM)
		{
			_count++;
			_player.attack3Image->setFrameY(0);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = IDLE;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
		if (_player.direction == TOP)
		{
			_count++;
			_player.attack3Image->setFrameY(1);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = IDLE;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
		if (_player.direction == RIGHT || _player.direction == RIGHTTOP || _player.direction == RIGHTBOTTOM)
		{
			_count++;
			_player.attack3Image->setFrameY(2);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = IDLE;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
		if (_player.direction == LEFT || _player.direction == LEFTTOP || _player.direction == LEFTBOTTOM)
		{
			_count++;
			_player.attack3Image->setFrameY(3);
			if (_count % ATTACK_CUT_SPEED == 0)
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
					_player.idle = IDLE;
				}
				_player.attack3Image->setFrameX(_index);
			}
		}
	}
}
//공격 8방향
void mainGame::playerDirection()
{
	if (_player.direction == BOTTOM)
	{
		_player.rangeX = _player.x - 77;
		_player.rangeY = _player.y;
	}
	else if (_player.direction == TOP)
	{
		_player.rangeX = _player.x - 77;
		_player.rangeY = _player.y - 144;
	}
	else if (_player.direction == RIGHT)
	{
		_player.rangeX = _player.x;
		_player.rangeY = _player.y - 77;
	}
	else if (_player.direction == LEFT)
	{
		//이미지 가로크기만큼 줄임
		_player.rangeX = _player.x - 144;
		_player.rangeY = _player.y - 77;
	}
	else if (_player.direction == LEFTTOP)
	{
		//이미지 가로크기만큼 줄임
		_player.rangeX = _player.x - 144;
		_player.rangeY = _player.y - 144;
	}
	else if (_player.direction == RIGHTTOP)
	{
		//이미지 가로크기만큼 줄임
		_player.rangeX = _player.x;
		_player.rangeY = _player.y - 144;
	}
	else if (_player.direction == RIGHTBOTTOM)
	{
		//이미지 가로크기만큼 줄임
		_player.rangeX = _player.x;
		_player.rangeY = _player.y;
	}
	else if (_player.direction == LEFTBOTTOM)
	{
		//이미지 가로크기만큼 줄임
		_player.rangeX = _player.x - 144;
		_player.rangeY = _player.y;
	}
}
//클릭시 공격 카운트 초기화
void mainGame::resetCounts()
{
	_count = _index = 0;
	effect1Conunt = 0;
	effrect1Index = 0;
	effect2Conunt = 0;
	effrect2Index = 0;
	effect3Conunt = 0;
	effrect3Index = 0;

	effectDiagonal1Conunt = 0;
	effrectDiagonal1Index = 0;
	effectDiagonal2Conunt = 0;
	effrectDiagonal2Index = 0;
	effectDiagonal3Conunt = 0;
	effrectDiagonal3Index = 0;
}
//공격이펙트
void mainGame::playerAttackEffect()
{
	if (_player.idle == ATTACK1)
	{
		if (_player.direction == BOTTOM)
		{
			effect1Conunt++;
			_player.attackEffect1Image->setFrameY(0);
			if (effect1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect1Index++;
				if (effrect1Index > 6)
				{
					effrect1Index = 0;
				}
				_player.attackEffect1Image->setFrameX(effrect1Index);
			}
		}

		else if (_player.direction == TOP)
		{
			effect1Conunt++;
			_player.attackEffect1Image->setFrameY(1);
			if (effect1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect1Index++;
				if (effrect1Index > 6)
				{
					effrect1Index = 0;
				}
				_player.attackEffect1Image->setFrameX(effrect1Index);
			}
		}

		else if (_player.direction == RIGHT)
		{
			effect1Conunt++;
			_player.attackEffect1Image->setFrameY(2);
			if (effect1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect1Index++;
				if (effrect1Index > 6)
				{
					effrect1Index = 0;
				}
				_player.attackEffect1Image->setFrameX(effrect1Index);
			}
		}

		else if (_player.direction == LEFT)
		{
			effect1Conunt++;
			_player.attackEffect1Image->setFrameY(3);
			if (effect1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect1Index++;
				if (effrect1Index > 6)
				{
					effrect1Index = 0;
				}
				_player.attackEffect1Image->setFrameX(effrect1Index);
			}
		}

		else if (_player.direction == LEFTTOP)
		{
			effectDiagonal1Conunt++;
			_player.attackEffectDiagonal1Image->setFrameY(0);
			if (effectDiagonal1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal1Index++;
				if (effrectDiagonal1Index > 6)
				{
					effrectDiagonal1Index = 0;
				}
				_player.attackEffectDiagonal1Image->setFrameX(effrectDiagonal1Index);
			}
		}

		else if (_player.direction == RIGHTTOP)
		{
			effectDiagonal1Conunt++;
			_player.attackEffectDiagonal1Image->setFrameY(1);
			if (effectDiagonal1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal1Index++;
				if (effrectDiagonal1Index > 6)
				{
					effrectDiagonal1Index = 0;
				}
				_player.attackEffectDiagonal1Image->setFrameX(effrectDiagonal1Index);
			}
		}

		else if (_player.direction == LEFTBOTTOM)
		{
			effectDiagonal1Conunt++;
			_player.attackEffectDiagonal1Image->setFrameY(2);
			if (effectDiagonal1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal1Index++;
				if (effrectDiagonal1Index > 6)
				{
					effrectDiagonal1Index = 0;
				}
				_player.attackEffectDiagonal1Image->setFrameX(effrectDiagonal1Index);
			}
		}

		else if (_player.direction == RIGHTBOTTOM)
		{
			effectDiagonal1Conunt++;
			_player.attackEffectDiagonal1Image->setFrameY(3);
			if (effectDiagonal1Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal1Index++;
				if (effrectDiagonal1Index > 6)
				{
					effrectDiagonal1Index = 0;
				}
				_player.attackEffectDiagonal1Image->setFrameX(effrectDiagonal1Index);
			}
		}
	}


	


	//공격2이펙트
	if (_player.idle == ATTACK2)
	{
		if (_player.direction == BOTTOM)
		{
			effect2Conunt++;
			_player.attackEffect2Image->setFrameY(0);
			if (effect2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect2Index++;
				if (effrect2Index > 6)
				{
					effrect2Index = 0;
				}
				_player.attackEffect2Image->setFrameX(effrect2Index);
			}
		}

		else if (_player.direction == TOP)
		{
			effect2Conunt++;
			_player.attackEffect2Image->setFrameY(1);
			if (effect2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect2Index++;
				if (effrect2Index > 6)
				{
					effrect2Index = 0;
				}
				_player.attackEffect2Image->setFrameX(effrect2Index);
			}
		}
		else if (_player.direction == RIGHT)
		{
			effect2Conunt++;
			_player.attackEffect2Image->setFrameY(2);
			if (effect2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect2Index++;
				if (effrect2Index > 6)
				{
					effrect2Index = 0;
				}
				_player.attackEffect2Image->setFrameX(effrect2Index);
			}
		}

		else if (_player.direction == LEFT)
		{
			effect2Conunt++;
			_player.attackEffect2Image->setFrameY(3);
			if (effect2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect2Index++;
				if (effrect2Index > 6)
				{
					effrect2Index = 0;
				}
				_player.attackEffect2Image->setFrameX(effrect2Index);
			}
		}

		else if (_player.direction == LEFTTOP)
		{
			effectDiagonal2Conunt++;
			_player.attackEffectDiagonal2Image->setFrameY(0);
			if (effectDiagonal2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal2Index++;
				if (effrectDiagonal2Index > 6)
				{
					effrectDiagonal2Index = 0;
				}
				_player.attackEffectDiagonal2Image->setFrameX(effrectDiagonal2Index);
			}
		}

		else if (_player.direction == RIGHTTOP)
		{
			effectDiagonal2Conunt++;
			_player.attackEffectDiagonal2Image->setFrameY(1);
			if (effectDiagonal2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal2Index++;
				if (effrectDiagonal2Index > 6)
				{
					effrectDiagonal2Index = 0;
				}
				_player.attackEffectDiagonal2Image->setFrameX(effrectDiagonal2Index);
			}
		}

		else if (_player.direction == LEFTBOTTOM)
		{
			effectDiagonal2Conunt++;
			_player.attackEffectDiagonal2Image->setFrameY(2);
			if (effectDiagonal2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal2Index++;
				if (effrectDiagonal2Index > 6)
				{
					effrectDiagonal2Index = 0;
				}
				_player.attackEffectDiagonal2Image->setFrameX(effrectDiagonal2Index);
			}
		}

		else if (_player.direction == RIGHTBOTTOM)
		{
			effectDiagonal2Conunt++;
			_player.attackEffectDiagonal2Image->setFrameY(3);
			if (effectDiagonal2Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal2Index++;
				if (effrectDiagonal2Index > 6)
				{
					effrectDiagonal2Index = 0;
				}
				_player.attackEffectDiagonal2Image->setFrameX(effrectDiagonal2Index);
			}
		}
	}



	//공격3이펙트
	if (_player.idle == ATTACK3)
	{
		if (_player.direction == BOTTOM)
		{
			effect3Conunt++;
			_player.attackEffect3Image->setFrameY(0);
			if (effect3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect3Index++;
				if (effrect3Index > 7)
				{
					effrect3Index = 0;
				}
				_player.attackEffect3Image->setFrameX(effrect3Index);
			}
		}

		if (_player.direction == TOP)
		{
			effect3Conunt++;
			_player.attackEffect3Image->setFrameY(1);
			if (effect3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect3Index++;
				if (effrect3Index > 7)
				{
					effrect3Index = 0;
				}
				_player.attackEffect3Image->setFrameX(effrect3Index);
			}
		}

		if (_player.direction == RIGHT)
		{
			effect3Conunt++;
			_player.attackEffect3Image->setFrameY(2);
			if (effect3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect3Index++;
				if (effrect3Index > 7)
				{
					effrect3Index = 0;
				}
				_player.attackEffect3Image->setFrameX(effrect3Index);
			}
		}

		if (_player.direction == LEFT)
		{
			effect3Conunt++;
			_player.attackEffect3Image->setFrameY(3);
			if (effect3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrect3Index++;
				if (effrect3Index > 7)
				{
					effrect3Index = 0;
				}
				_player.attackEffect3Image->setFrameX(effrect3Index);
			}
		}

		else if (_player.direction == LEFTTOP)
		{
			effectDiagonal3Conunt++;
			_player.attackEffectDiagonal3Image->setFrameY(0);
			if (effectDiagonal3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal3Index++;
				if (effrectDiagonal3Index > 7)
				{
					effrectDiagonal3Index = 0;
				}
				_player.attackEffectDiagonal3Image->setFrameX(effrectDiagonal3Index);
			}
		}

		else if (_player.direction == RIGHTTOP)
		{
			effectDiagonal3Conunt++;
			_player.attackEffectDiagonal3Image->setFrameY(1);
			if (effectDiagonal3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal3Index++;
				if (effrectDiagonal3Index > 7)
				{
					effrectDiagonal3Index = 0;
				}
				_player.attackEffectDiagonal3Image->setFrameX(effrectDiagonal3Index);
			}
		}

		else if (_player.direction == LEFTBOTTOM)
		{
			effectDiagonal3Conunt++;
			_player.attackEffectDiagonal3Image->setFrameY(2);
			if (effectDiagonal3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal3Index++;
				if (effrectDiagonal3Index > 7)
				{
					effrectDiagonal3Index = 0;
				}
				_player.attackEffectDiagonal3Image->setFrameX(effrectDiagonal3Index);
			}
		}

		else if (_player.direction == RIGHTBOTTOM)
		{
			effectDiagonal3Conunt++;
			_player.attackEffectDiagonal3Image->setFrameY(3);
			if (effectDiagonal3Conunt % ATTACKEFFECT_CUT_SPEED == 0)
			{
				effrectDiagonal3Index++;
				if (effrectDiagonal3Index > 7)
				{
					effrectDiagonal3Index = 0;
				}
				_player.attackEffectDiagonal3Image->setFrameX(effrectDiagonal3Index);
			}
		}
	}


}
//캐스트 이펙트
void mainGame::playerCastffect()
{	//바람이펙트
	if (_player.slamCast)
	{
		_castEffect1Conunt++;
		_player.AirSpinnerBurstImage->setFrameY(0);
		if (_castEffect1Conunt % CASTEFFECT_CUT_SPEED == 0)
		{
			_castEffrect1Index++;
			if (_castEffrect1Index > 6)
			{
				_castEffrect1Index = 0;
			}
			_player.AirSpinnerBurstImage->setFrameX(_castEffrect1Index);
		}
	}
	//서클이펙트
	if (_player.slamCast)
	{
		_castEffect2Conunt++;
		_player.CastingCircleEffectImage->setFrameY(0);
		if (_castEffect2Conunt % 3 == 0)
		{
			_castEffrect2Index++;
			if (_castEffrect2Index > 19)
			{
				_castEffrect2Index = 0;
			}
			_player.CastingCircleEffectImage->setFrameX(_castEffrect2Index);
		}
	}
}
//파이어볼 스킬
void mainGame::fireBall()
{
	if (_fireBall.isFire)
	{
		//BOTTOM
		if (_fireBall.direction == BOTTOM)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x, _fireBall.y + _fireBall.height, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(0);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//TOP
		else if (_fireBall.direction == TOP)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x, _fireBall.y - _fireBall.height, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(1);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//RIGHT
		else if (_fireBall.direction == RIGHT)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x + _fireBall.width, _fireBall.y, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle) * _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(2);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//LEFT
		else if (_fireBall.direction == LEFT)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x - _fireBall.width, _fireBall.y, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(3);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//LEFTTOP
		else if (_fireBall.direction == LEFTTOP)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x - _fireBall.width, _fireBall.y - _fireBall.height, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(4);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//RIGHTTOP
		else if (_fireBall.direction == RIGHTTOP)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x + _fireBall.width, _fireBall.y - _fireBall.height, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(5);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//RIGHTBOTTOM
		else if (_fireBall.direction == RIGHTBOTTOM)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x + _fireBall.width, _fireBall.y + _fireBall.height, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(6);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
		//LEFTBOTTOM
		else if (_fireBall.direction == LEFTBOTTOM)
		{
			_fireBall.rc = RectMakeCenter(_fireBall.x - _fireBall.width, _fireBall.y + _fireBall.height, _fireBall.width, _fireBall.height);

			_fireBall.x += cos(_fireBall.angle) * _fireBall.speed;
			_fireBall.y += -sin(_fireBall.angle)* _fireBall.speed;
			_fireBall.skillCount++;
			_fireBall.fireBallImage->setFrameY(7);
			if (_fireBall.skillCount % 4 == 0)
			{
				_fireBall.skillIndex++;
				if (_fireBall.skillIndex > 5)
				{
					_fireBall.skillIndex = 0;
				}
				_fireBall.fireBallImage->setFrameX(_fireBall.skillIndex);
			}
		}
	}

	//폭발
	if (_fireBall.isExplosion)
	{		
		_fireBall.ExplosionCount++;
		_fireBall.fireBallExplosion1Image->setFrameY(0);
		_fireBall.fireBallExplosion2Image->setFrameY(0);
		if (_fireBall.ExplosionCount % 4 == 0)
		{
			_fireBall.ExplosionIndex++;
			if (_fireBall.ExplosionIndex > 8)
			{
				_fireBall.ExplosionIndex = 0;
				_fireBall.isExplosion = false;
			}
			_fireBall.fireBallExplosion1Image->setFrameX(_fireBall.ExplosionIndex);
			_fireBall.fireBallExplosion2Image->setFrameX(_fireBall.ExplosionIndex);
		}
		
	}
}
//메테오 스킬
void mainGame::meteoStrike()
{
	//메테오 발사
	if (_meteoStrike.isFire)
	{
		_meteoStrike.rc = RectMakeCenter(_meteoStrike.x, _meteoStrike.y, _meteoStrike.width, _meteoStrike.height);

		_meteoStrike.x += cos(_meteoStrike.angle) * _meteoStrike.speed;
		_meteoStrike.y += -sin(_meteoStrike.angle) * _meteoStrike.speed;
		_meteoStrike.skillCount++;
		_meteoStrike.meteoStrikeImage->setFrameY(0);
		if (_meteoStrike.skillCount % 8 == 0)
		{
			_meteoStrike.skillIndex++;
			if (_meteoStrike.skillIndex > 5)
			{
				_meteoStrike.skillIndex = 0;
			}
			_meteoStrike.meteoStrikeImage->setFrameX(_meteoStrike.skillIndex);
		}
	}
	
	//메테오 폭발
	if (_meteoStrike.isExplosion)
	{		
		_meteoStrike.ExplosionCount++;
		_meteoStrike.meteoStrikeExplosionImage->setFrameY(0);		
		if (_meteoStrike.ExplosionCount % 6 == 0)
		{			
			_meteoStrike.ExplosionIndex++;
			if (_meteoStrike.ExplosionIndex > 6)
			{				
				_meteoStrike.ExplosionIndex = 0;	
				_meteoStrike.isExplosion = false;
			}
			_meteoStrike.meteoStrikeExplosionImage->setFrameX(_meteoStrike.ExplosionIndex);	
		}
	}
}
//아이스퀸 스킬
void mainGame::iceQueen()
{
	if (_iceQueen.isFire)
	{
	
		for (int i = 0; i < ICEQUEENMAX; i++)
		{
			_iceQueen.rc[i] = RectMakeCenter(_iceQueen.x + (cos(_iceQueen.angle)*i*50), _iceQueen.y + (-sin(_iceQueen.angle)*i*50), _iceQueen.width, _iceQueen.height);
			//_iceQueen.rc2 = RectMakeCenter(_iceQueen.x + cos(_iceQueen.angle) * i*10, _iceQueen.y + -sin(_iceQueen.angle) * 150, _iceQueen.width, _iceQueen.height);
		}	

		//_iceQueen.x += cos(_iceQueen.angle) * _iceQueen.speed;
		//_iceQueen.y += -sin(_iceQueen.angle) * _iceQueen.speed;
		_iceQueen.skillCount++;
		_iceQueen.iceQueenImage->setFrameY(0);
		if (_iceQueen.skillCount % 6 == 0)
		{
			_iceQueen.skillIndex++;
			if (_iceQueen.skillIndex > 9)
			{
				_iceQueen.skillIndex = 0;
				_iceQueen.isFire = false;
			}
			_iceQueen.iceQueenImage->setFrameX(_iceQueen.skillIndex);
		}		
	}
}
//토네이도스킬
void mainGame::tornado()
{
	if (_tornado.isFire)
	{
		_tornado.rc = RectMakeCenter(_tornado.x, _tornado.y-30, _tornado.width, _tornado.height);		

		_tornado.skillCount++;
		_tornado.tornadoImage->setFrameY(0);
		if (_tornado.skillCount % 6 == 0)
		{
			_tornado.skillIndex++;			
			if (_tornado.skillIndex > 11)
			{
				_tornado.skillIndex = 0;
				_tornado.isFire = false;
			}
			_tornado.tornadoImage->setFrameX(_tornado.skillIndex);
		}
	}
}
//스킬 충돌
void mainGame::skillCollision()
{
	//파이어볼 충돌
	if (_fireBall.isFire)
	{
		//왼쪽 충돌
		if (_fireBall.rc.left < 0)
		{
			_fireBall.isFire = false;
			_fireBall.isExplosion = true;
		}
		//오른쪽 충돌
		else if (_fireBall.rc.right > WINSIZEX)
		{
			_fireBall.isFire = false;
			_fireBall.isExplosion = true;
		}
		//탑 충돌
		else if (_fireBall.rc.top < 0)
		{
			_fireBall.isFire = false;
			_fireBall.isExplosion = true;
		}
		//바텀 윈도우
		else if (_fireBall.rc.bottom > WINSIZEY)
		{
			_fireBall.isFire = false;
			_fireBall.isExplosion = true;
		}
	}

	//아이스퀸 벽 충돌 ( 테스트땜에 일단 빼놈)
	//if (_iceQueen.isFire)
	//{
	//	for (int i = 0; i < ICEQUEENMAX; i++)
	//	{
	//		//왼쪽 충돌
	//		if (_iceQueen.rc[i].left < 0)
	//		{
	//			_iceQueen.isFire = false;
	//		}
	//		//오른쪽 충돌
	//		else if (_iceQueen.rc[i].right > WINSIZEX)
	//		{
	//			_iceQueen.isFire = false;
	//		}
	//		//탑 충돌
	//		else if (_iceQueen.rc[i].top < 0)
	//		{
	//			_iceQueen.isFire = false;
	//		}
	//		//바텀 윈도우
	//		else if (_iceQueen.rc[i].bottom > WINSIZEY)
	//		{
	//			_iceQueen.isFire = false;
	//		}
	//	}
	//}

	//메테오 충돌
	if (_meteoStrike.isFire == true && _meteoStrike.rc.bottom >= _meteoStrike.range.y+50)
	{
		_meteoStrike.isFire = false;
		_meteoStrike.isExplosion = true;
	}
}
