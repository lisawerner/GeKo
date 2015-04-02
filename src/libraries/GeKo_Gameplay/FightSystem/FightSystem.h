#pragma once

#include"GeKo_Gameplay/Object/Object.h"
#include"GeKo_Gameplay/Object/Geko.h"
#include"GeKo_Gameplay/Object/AI.h"


class FightSystem : public Subject<FightSystem, Quest_Event>
{
public:
	FightSystem();
	~FightSystem();

	void objectVSobject(Object* o1, Object* o2);

};