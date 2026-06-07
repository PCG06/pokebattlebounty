#ifndef GUARD_QUESTS_H
#define GUARD_QUESTS_H

#include "constants/quests.h"

struct SubQuest
{
    const u8 id;
	const u8 *name;
	const u8 *desc;
	const u8 *map;
	const u16 sprite;
    const u8 spritetype;
    const u8 *type;
}; 

struct MainQuest
{
	const u8 *name;
	const u8 *desc;
	const u8 *donedesc;
	const u8 *map;
	const u16 sprite;
    const u8 spritetype;
	const struct SubQuest *subquests;
	const u8 numSubquests;
};

extern const struct MainQuest gMainQuests[];
extern const struct SubQuest gSubQuests1[];
extern const struct SubQuest gSubQuests2[];

// functions
void QuestMenu_Init(u8 a0, MainCallback callback);
u8 QuestMenu_GetSetSubquestState(u8 quest, u8 caseId, u8 childQuest);
u8 QuestMenu_GetSetQuestState(u8 quest, u8 caseId);
void Task_QuestMenu_OpenFromStartMenu(u8);
void QuestMenu_CopyQuestName(u8 *dst, u8 questId);
void QuestMenu_CopySubquestName(u8 *dst, u8 parentId, u8 childId);
void QuestMenu_ResetMenuSaveData(void);

#endif // GUARD_QUESTS_H
