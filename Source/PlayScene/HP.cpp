#include "HP.h"
#include <assert.h>

namespace {
	const VECTOR2 LEFT_TOP = { 20, 20 };
	const int IMAGE_WIDTH = 400;
	const int IMAGE_HEIGHT = 43;
	const float DAMAGE_TIME = 1.5f;
}

HP::HP(int hp)
{
	addHp_ = 0;
	hp_ = hp;
	maxHp_ = hp;

	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	hBarFrameImage_ = LoadGraph("data/image/hpBarFrame.png");
	assert(hBarFrameImage_ > 0);
	hBarGreenImage_ = LoadGraph("data/image/hpBarGreen.png");
	assert(hBarGreenImage_ > 0);
	hBarRedImage_ = LoadGraph("data/image/hpBarRed.png");
	assert(hBarRedImage_ > 0);

	damageTimer_ = 0.0f;
	hpRaitio_ = 0.0f;
	state_ = HP_STATE::HP_NORMAL;
}

HP::~HP()
{
}

void HP::Update()
{
	switch (state_)
	{
	case HP_STATE::HP_NORMAL:
		break;
	case HP_STATE::HP_HEAL:
		state_ = HP_STATE::HP_NORMAL;
		break;
	case HP_STATE::HP_DAMAGE:
		damageTimer_ -= Time::DeltaTime();
		if (damageTimer_ <= 0.0f)
		{
			addHp_ = 0;
			hpRaitio_ = 0.0f;
			state_ = HP_STATE::HP_NORMAL;
		}
		break;
	}
}

void HP::Draw()
{
	float raitio = (float)hp_ / (float)maxHp_;
	DrawGraph((int)LEFT_TOP.x, (int)LEFT_TOP.y, hBarFrameImage_, TRUE);

	switch (state_)
	{
	case HP_STATE::HP_NORMAL:
	case HP_STATE::HP_HEAL:
		DrawRectGraph((int)LEFT_TOP.x, (int)LEFT_TOP.y, 0, 0, (int)(IMAGE_WIDTH * raitio), IMAGE_HEIGHT, hBarRedImage_, TRUE);
		break;
	case HP_STATE::HP_DAMAGE:
		DrawRectGraph((int)LEFT_TOP.x, (int)LEFT_TOP.y, 0, 0, (int)(IMAGE_WIDTH * (raitio + hpRaitio_ * timeRaitio_)), IMAGE_HEIGHT, hBarRedImage_, TRUE);
		break;
	}
	DrawRectGraph((int)LEFT_TOP.x, (int)LEFT_TOP.y, 0, 0, (int)(IMAGE_WIDTH * raitio), IMAGE_HEIGHT, hBarGreenImage_, TRUE);
}

void HP::AddHP(int addHp)
{
	addHp_ = std::abs(addHp);
	hpRaitio_ = (float)std::abs(addHp_) / (float)maxHp_ + hpRaitio_ * timeRaitio_;
	hp_ += addHp_;
	if (hp_ > maxHp_) // Å‘å’l‚æ‚è‘å‚«‚­‚È‚Á‚Ä‚¢‚½ê‡
	{
		hp_ = maxHp_;
	}
	if (addHp_ > 0)
	{
		state_ = HP_STATE::HP_HEAL;
	}
	else if (addHp < 0)
	{
		state_ = HP_STATE::HP_DAMAGE;
		damageTimer_ = DAMAGE_TIME;
	}
}
