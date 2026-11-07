#ifndef GUARD_CONSTANTS_QUESTS_H
#define GUARD_CONSTANTS_QUESTS_H

// Main Quests defines
enum
{
    QUEST_1,
    QUEST_2,
    QUEST_3,
    QUEST_4,
    QUEST_5,
    QUEST_6,
    QUEST_7,
    QUEST_8,
    QUEST_9,
    QUEST_10,
    QUEST_11,
    QUEST_12,
    QUEST_13,
    QUEST_14,
    QUEST_15,
    QUEST_16,
    QUEST_17,
    QUEST_18,
    QUEST_19,
    QUEST_20,
    QUEST_21,
    QUEST_22,
    QUEST_23,
    QUEST_24,
    QUEST_25,
    QUEST_26,
    QUEST_27,
    QUEST_28,
    QUEST_29,
    QUEST_30,
    QUEST_COUNT,
};

// Side Quests defines
enum
{
    // Sub Quests of Main Quest 1
    SUB_QUEST_1,
    SUB_QUEST_2,
    SUB_QUEST_3,
    SUB_QUEST_4,
    SUB_QUEST_5,
    SUB_QUEST_6,
    SUB_QUEST_7,
    SUB_QUEST_8,
    SUB_QUEST_9,
    SUB_QUEST_10,

    // Sub Quests of Main Quest 2
    SUB_QUEST_11,
    SUB_QUEST_12,
    SUB_QUEST_13,
    SUB_QUEST_14,
    SUB_QUEST_15,
    SUB_QUEST_16,
    SUB_QUEST_17,
    SUB_QUEST_18,
    SUB_QUEST_19,
    SUB_QUEST_20,
    SUB_QUEST_21,
    SUB_QUEST_22,
    SUB_QUEST_23,
    SUB_QUEST_24,
    SUB_QUEST_25,
    SUB_QUEST_26,
    SUB_QUEST_27,
    SUB_QUEST_28,
    SUB_QUEST_29,
    SUB_QUEST_30,

    // Total sub quests
    SUB_QUEST_COUNT
};

#define QUEST_1_SUB_COUNT SUB_QUEST_10 + 1
#define QUEST_2_SUB_COUNT SUB_QUEST_30 - SUB_QUEST_10

#define NUM_MAIN_QUESTS (u32) QUEST_COUNT
#define NUM_SUB_QUESTS  (u32) SUB_QUEST_COUNT

#define QUEST_ARRAY_COUNT max(NUM_SUB_QUESTS, NUM_MAIN_QUESTS)

enum QuestSort
{
    SORT_DEFAULT,
    SORT_INACTIVE,
    SORT_ACTIVE,
    SORT_REWARD,
    SORT_DONE,

    SORT_DEFAULT_AZ = 10,
    SORT_INACTIVE_AZ,
    SORT_ACTIVE_AZ,
    SORT_REWARD_AZ,
    SORT_DONE_AZ,

    SORT_SUBQUEST = 100,
};

enum QuestModes
{
    INCREMENT = 1,
    ALPHA, 
    SUB,
};

enum QuestSpriteTypes
{
    OBJECT = 1,
    ITEM,
    PKMN,
};

enum QuestCases
{
	FLAG_GET_UNLOCKED,    // check if quest is unlocked
	FLAG_GET_INACTIVE,    // check if quest is unlocked but has no other state
	FLAG_GET_ACTIVE,      // check if quest is active
	FLAG_GET_REWARD,      // check if quest is ready for reward
	FLAG_GET_COMPLETED,   // check if quest is completed
	FLAG_GET_FAVORITE,    // check if quest is favorited
	FLAG_SET_UNLOCKED,    // mark quest as unlocked
	FLAG_SET_INACTIVE,    // mark quest as inactive
	FLAG_SET_ACTIVE,      // mark quest as active
	FLAG_SET_REWARD,      // mark quest ready for reward
	FLAG_SET_COMPLETED,   // mark completed quest
	FLAG_SET_FAVORITE,    // mark quest as a favorite
	FLAG_REMOVE_INACTIVE, // remove inactive flag from quest
	FLAG_REMOVE_ACTIVE,   // remove active flag from quest
	FLAG_REMOVE_REWARD,   // remove reward flag from quest
	FLAG_REMOVE_FAVORITE, // remove favorite flag from quest
};

// Quest Menu scripting command params
enum QuestScrCmdParams
{
    QUEST_MENU_OPEN,              // opens the quest menu (questId = 0)
    QUEST_MENU_UNLOCK_QUEST,      // questId = QUEST_X (0-indexed)
    QUEST_MENU_SET_ACTIVE,        // questId = QUEST_X (0-indexed)
    QUEST_MENU_SET_REWARD,        // questId = QUEST_X (0-indexed)
    QUEST_MENU_COMPLETE_QUEST,    // questId = QUEST_X (0-indexed)
    QUEST_MENU_CHECK_UNLOCKED,    // checks if questId has been unlocked. Returns result to gSpecialVar_Result
    QUEST_MENU_CHECK_INACTIVE,    // check if a questID is inactive. Returns result to gSpecialVar_Result
    QUEST_MENU_CHECK_ACTIVE,      // checks if questId has been unlocked. Returns result to gSpecialVar_Result
    QUEST_MENU_CHECK_REWARD,      // checks if questId is in Reward state. Returns result to gSpecialVar_Result
    QUEST_MENU_CHECK_COMPLETE,    // checks if questId has been completed. Returns result to gSpecialVar_Result
    QUEST_MENU_BUFFER_QUEST_NAME, // buffers a quest name to gStringVar1
};

#endif // GUARD_CONSTANTS_QUESTS_H
