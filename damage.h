#ifndef __DAMAGE_H
#define __DAMAGE_H

/*
此函数计算一个怪物对勇士造成的伤害
参数说明：
h_atk: 勇士攻击
h_def: 勇士防御
h_mdef: 勇士魔防
m_hp: 怪物生命值
m_atk: 怪物攻击
m_def: 怪物防御
m_spe: 怪物特效
返回值：
一个整数，代表伤害值。
如果勇士无法对怪物造成伤害，返回999999999

怪物特效说明：
0: 无特效
1: 魔攻（怪物无视勇士的防御）
2: 坚固（怪物防御=勇士攻击-1）
3: 先攻（战斗前怪物首先攻击勇士一次）
4: 2连击（每回合怪物打勇士两次）
*/
int getDamage(int h_atk, int h_def, int h_mdef, int m_hp, int m_atk, int m_def, int m_spe);

int getDamage(const PlayerInfo& p, const Monster& m);

#endif

