#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/quests.h"

static const u8 sText_Caught[] = _("Caught");
static const u8 sText_Found[] = _("Found");

///////////////////////////////////////////////////////////////////////////////
////////////////////////BEGIN QUEST CUSTOMIZATION//////////////////////////////

// Declaration of side quest structures. Edits to quests are made here.
const struct MainQuest gMainQuests[QUEST_COUNT] =
{
    [QUEST_1] =
    {
        .name = COMPOUND_STRING("Side Quest 1"),
        .desc = COMPOUND_STRING("Description 1"),
        .donedesc = COMPOUND_STRING("Completed Quest 1"),
        .map = COMPOUND_STRING("Map 1"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = gSubQuests1,
        .numSubquests = QUEST_1_SUB_COUNT
    },
    [QUEST_2] =
    {
        .name = COMPOUND_STRING("Side Quest 2"),
        .desc = COMPOUND_STRING("Description 2"),
        .donedesc = COMPOUND_STRING("Completed Quest 2"),
        .map = COMPOUND_STRING("Map 2"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = gSubQuests2,
        .numSubquests = QUEST_2_SUB_COUNT
    },
    [QUEST_3] =
    {
        .name = COMPOUND_STRING("Side Quest 3"),
        .desc = COMPOUND_STRING("Description 3"),
        .donedesc = COMPOUND_STRING("Completed Quest 3"),
        .map = COMPOUND_STRING("Map 3"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_4] =
    {
        .name = COMPOUND_STRING("Side Quest 4"),
        .desc = COMPOUND_STRING("Description 4"),
        .donedesc = COMPOUND_STRING("Completed Quest 4"),
        .map = COMPOUND_STRING("Map 4"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_5] =
    {
        .name = COMPOUND_STRING("Side Quest 5"),
        .desc = COMPOUND_STRING("Description 5"),
        .donedesc = COMPOUND_STRING("Completed Quest 5"),
        .map = COMPOUND_STRING("Map 5"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_6] =
    {
        .name = COMPOUND_STRING("Side Quest 6"),
        .desc = COMPOUND_STRING("Description 6"),
        .donedesc = COMPOUND_STRING("Completed Quest 6"),
        .map = COMPOUND_STRING("Map 6"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_7] =
    {
        .name = COMPOUND_STRING("Side Quest 7"),
        .desc = COMPOUND_STRING("Description 7"),
        .donedesc = COMPOUND_STRING("Completed Quest 7"),
        .map = COMPOUND_STRING("Map 7"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_8] =
    {
        .name = COMPOUND_STRING("Side Quest 8"),
        .desc = COMPOUND_STRING("Description 8"),
        .donedesc = COMPOUND_STRING("Completed Quest 8"),
        .map = COMPOUND_STRING("Map 8"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_9] =
    {
        .name = COMPOUND_STRING("Side Quest 9"),
        .desc = COMPOUND_STRING("Description 9"),
        .donedesc = COMPOUND_STRING("Completed Quest 9"),
        .map = COMPOUND_STRING("Map 9"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_10] =
    {
        .name = COMPOUND_STRING("Side Quest 10"),
        .desc = COMPOUND_STRING("Description 10"),
        .donedesc = COMPOUND_STRING("Completed Quest 10"),
        .map = COMPOUND_STRING("Map 10"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_11] =
    {
        .name = COMPOUND_STRING("Side Quest 11"),
        .desc = COMPOUND_STRING("Description 11"),
        .donedesc = COMPOUND_STRING("Completed Quest 11"),
        .map = COMPOUND_STRING("Map 11"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_12] =
    {
        .name = COMPOUND_STRING("Side Quest 12"),
        .desc = COMPOUND_STRING("Description 12"),
        .donedesc = COMPOUND_STRING("Completed Quest 12"),
        .map = COMPOUND_STRING("Map 12"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_13] =
    {
        .name = COMPOUND_STRING("Side Quest 13"),
        .desc = COMPOUND_STRING("Description 13"),
        .donedesc = COMPOUND_STRING("Completed Quest 13"),
        .map = COMPOUND_STRING("Map 13"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_14] =
    {
        .name = COMPOUND_STRING("Side Quest 14"),
        .desc = COMPOUND_STRING("Description 14"),
        .donedesc = COMPOUND_STRING("Completed Quest 14"),
        .map = COMPOUND_STRING("Map 14"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_15] =
    {
        .name = COMPOUND_STRING("Side Quest 15"),
        .desc = COMPOUND_STRING("Description 15"),
        .donedesc = COMPOUND_STRING("Completed Quest 15"),
        .map = COMPOUND_STRING("Map 15"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_16] =
    {
        .name = COMPOUND_STRING("Side Quest 16"),
        .desc = COMPOUND_STRING("Description 16"),
        .donedesc = COMPOUND_STRING("Completed Quest 16"),
        .map = COMPOUND_STRING("Map 16"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_17] =
    {
        .name = COMPOUND_STRING("Side Quest 17"),
        .desc = COMPOUND_STRING("Description 17"),
        .donedesc = COMPOUND_STRING("Completed Quest 17"),
        .map = COMPOUND_STRING("Map 17"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_18] =
    {
        .name = COMPOUND_STRING("Side Quest 18"),
        .desc = COMPOUND_STRING("Description 18"),
        .donedesc = COMPOUND_STRING("Completed Quest 18"),
        .map = COMPOUND_STRING("Map 18"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_19] =
    {
        .name = COMPOUND_STRING("Side Quest 19"),
        .desc = COMPOUND_STRING("Description 19"),
        .donedesc = COMPOUND_STRING("Completed Quest 19"),
        .map = COMPOUND_STRING("Map 19"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_20] =
    {
        .name = COMPOUND_STRING("Side Quest 20"),
        .desc = COMPOUND_STRING("Description 20"),
        .donedesc = COMPOUND_STRING("Completed Quest 20"),
        .map = COMPOUND_STRING("Map 20"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_21] =
    {
        .name = COMPOUND_STRING("Side Quest 21"),
        .desc = COMPOUND_STRING("Description 21"),
        .donedesc = COMPOUND_STRING("Completed Quest 21"),
        .map = COMPOUND_STRING("Map 21"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_22] =
    {
        .name = COMPOUND_STRING("Side Quest 22"),
        .desc = COMPOUND_STRING("Description 22"),
        .donedesc = COMPOUND_STRING("Completed Quest 22"),
        .map = COMPOUND_STRING("Map 22"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_23] =
    {
        .name = COMPOUND_STRING("Side Quest 23"),
        .desc = COMPOUND_STRING("Description 23"),
        .donedesc = COMPOUND_STRING("Completed Quest 23"),
        .map = COMPOUND_STRING("Map 23"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_24] =
    {
        .name = COMPOUND_STRING("Side Quest 24"),
        .desc = COMPOUND_STRING("Description 24"),
        .donedesc = COMPOUND_STRING("Completed Quest 24"),
        .map = COMPOUND_STRING("Map 24"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_25] =
    {
        .name = COMPOUND_STRING("Side Quest 25"),
        .desc = COMPOUND_STRING("Description 25"),
        .donedesc = COMPOUND_STRING("Completed Quest 25"),
        .map = COMPOUND_STRING("Map 25"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_26] =
    {
        .name = COMPOUND_STRING("Side Quest 26"),
        .desc = COMPOUND_STRING("Description 26"),
        .donedesc = COMPOUND_STRING("Completed Quest 26"),
        .map = COMPOUND_STRING("Map 26"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_27] =
    {
        .name = COMPOUND_STRING("Side Quest 27"),
        .desc = COMPOUND_STRING("Description 27"),
        .donedesc = COMPOUND_STRING("Completed Quest 27"),
        .map = COMPOUND_STRING("Map 27"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_28] =
    {
        .name = COMPOUND_STRING("Side Quest 28"),
        .desc = COMPOUND_STRING("Description 28"),
        .donedesc = COMPOUND_STRING("Completed Quest 28"),
        .map = COMPOUND_STRING("Map 28"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_29] =
    {
        .name = COMPOUND_STRING("Side Quest 29"),
        .desc = COMPOUND_STRING("Description 29"),
        .donedesc = COMPOUND_STRING("Completed Quest 29"),
        .map = COMPOUND_STRING("Map 29"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
    [QUEST_30] =
    {
        .name = COMPOUND_STRING("Side Quest 30"),
        .desc = COMPOUND_STRING("Description 30"),
        .donedesc = COMPOUND_STRING("Completed Quest 30"),
        .map = COMPOUND_STRING("Map 30"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = NULL,
        .numSubquests = 0
    },
};
////////////////////////END QUEST CUSTOMIZATION////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//////////////////////BEGIN SUBQUEST CUSTOMIZATION/////////////////////////////

// Declaration of subquest structures. Edits to subquests are made here.
const struct SubQuest gSubQuests1[QUEST_1_SUB_COUNT] =
{
    {
        .id = SUB_QUEST_1,
        .name = COMPOUND_STRING("Quest 1 Part 1"),
        .desc = COMPOUND_STRING("Description Sub 1"),
        .map = COMPOUND_STRING("Map 1"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_2,
        .name = COMPOUND_STRING("Quest 1 Part 2"),
        .desc = COMPOUND_STRING("Description Sub 2"),
        .map = COMPOUND_STRING("Map 2"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_3,
        .name = COMPOUND_STRING("Quest 1 Part 3"),
        .desc = COMPOUND_STRING("Description Sub 3"),
        .map = COMPOUND_STRING("Map 3"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_4,
        .name = COMPOUND_STRING("Quest 1 Part 4"),
        .desc = COMPOUND_STRING("Description Sub 4"),
        .map = COMPOUND_STRING("Map 4"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_5,
        .name = COMPOUND_STRING("Quest 1 Part 5"),
        .desc = COMPOUND_STRING("Description Sub 5"),
        .map = COMPOUND_STRING("Map 5"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_6,
        .name = COMPOUND_STRING("Quest 1 Part 6"),
        .desc = COMPOUND_STRING("Description Sub 6"),
        .map = COMPOUND_STRING("Map 6"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_7,
        .name = COMPOUND_STRING("Quest 1 Part 7"),
        .desc = COMPOUND_STRING("Description Sub 7"),
        .map = COMPOUND_STRING("Map 7"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_8,
        .name = COMPOUND_STRING("Quest 1 Part 8"),
        .desc = COMPOUND_STRING("Description Sub 8"),
        .map = COMPOUND_STRING("Map 8"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_9,
        .name = COMPOUND_STRING("Quest 1 Part 9"),
        .desc = COMPOUND_STRING("Description Sub 9"),
        .map = COMPOUND_STRING("Map 9"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_10,
        .name = COMPOUND_STRING("Quest 1 Part 10"),
        .desc = COMPOUND_STRING("Description Sub 10"),
        .map = COMPOUND_STRING("Map 10"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },
};

const struct SubQuest gSubQuests2[QUEST_2_SUB_COUNT] =
{
    {
        .id = SUB_QUEST_11,
        .name = COMPOUND_STRING("Quest 2 Part 1"),
        .desc = COMPOUND_STRING("Description Sub 1"),
        .map = COMPOUND_STRING("Map 1"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_12,
        .name = COMPOUND_STRING("Quest 2 Part 2"),
        .desc = COMPOUND_STRING("Description Sub 2"),
        .map = COMPOUND_STRING("Map 2"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_13,
        .name = COMPOUND_STRING("Quest 2 Part 3"),
        .desc = COMPOUND_STRING("Description Sub 3"),
        .map = COMPOUND_STRING("Map 3"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_14,
        .name = COMPOUND_STRING("Quest 2 Part 4"),
        .desc = COMPOUND_STRING("Description Sub 4"),
        .map = COMPOUND_STRING("Map 4"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_15,
        .name = COMPOUND_STRING("Quest 2 Part 5"),
        .desc = COMPOUND_STRING("Description Sub 5"),
        .map = COMPOUND_STRING("Map 5"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_16,
        .name = COMPOUND_STRING("Quest 2 Part 6"),
        .desc = COMPOUND_STRING("Description Sub 6"),
        .map = COMPOUND_STRING("Map 6"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_17,
        .name = COMPOUND_STRING("Quest 2 Part 7"),
        .desc = COMPOUND_STRING("Description Sub 7"),
        .map = COMPOUND_STRING("Map 7"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_18,
        .name = COMPOUND_STRING("Quest 2 Part 8"),
        .desc = COMPOUND_STRING("Description Sub 8"),
        .map = COMPOUND_STRING("Map 8"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_19,
        .name = COMPOUND_STRING("Quest 2 Part 9"),
        .desc = COMPOUND_STRING("Description Sub 9"),
        .map = COMPOUND_STRING("Map 9"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_20,
        .name = COMPOUND_STRING("Quest 2 Part 10"),
        .desc = COMPOUND_STRING("Description Sub 10"),
        .map = COMPOUND_STRING("Map 10"),
        .sprite = SPECIES_HO_OH,
        .spritetype = PKMN,
        .type = sText_Caught
    },

    {
        .id = SUB_QUEST_21,
        .name = COMPOUND_STRING("Quest 2 Part 11"),
        .desc = COMPOUND_STRING("Description Sub 11"),
        .map = COMPOUND_STRING("Map 11"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_22,
        .name = COMPOUND_STRING("Quest 2 Part 12"),
        .desc = COMPOUND_STRING("Description Sub 12"),
        .map = COMPOUND_STRING("Map 12"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_23,
        .name = COMPOUND_STRING("Quest 2 Part 13"),
        .desc = COMPOUND_STRING("Description Sub 13"),
        .map = COMPOUND_STRING("Map 13"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_24,
        .name = COMPOUND_STRING("Quest 2 Part 14"),
        .desc = COMPOUND_STRING("Description Sub 14"),
        .map = COMPOUND_STRING("Map 14"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_25,
        .name = COMPOUND_STRING("Quest 2 Part 15"),
        .desc = COMPOUND_STRING("Description Sub 15"),
        .map = COMPOUND_STRING("Map 15"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_26,
        .name = COMPOUND_STRING("Quest 2 Part 16"),
        .desc = COMPOUND_STRING("Description Sub 16"),
        .map = COMPOUND_STRING("Map 16"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_27,
        .name = COMPOUND_STRING("Quest 2 Part 17"),
        .desc = COMPOUND_STRING("Description Sub 17"),
        .map = COMPOUND_STRING("Map 17"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_28,
        .name = COMPOUND_STRING("Quest 2 Part 18"),
        .desc = COMPOUND_STRING("Description Sub 18"),
        .map = COMPOUND_STRING("Map 18"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_29,
        .name = COMPOUND_STRING("Quest 2 Part 19"),
        .desc = COMPOUND_STRING("Description Sub 19"),
        .map = COMPOUND_STRING("Map 19"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },

    {
        .id = SUB_QUEST_30,
        .name = COMPOUND_STRING("Quest 2 Part 20"),
        .desc = COMPOUND_STRING("Description Sub 20"),
        .map = COMPOUND_STRING("Map 20"),
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Found
    },
};

////////////////////////END SUBQUEST CUSTOMIZATION/////////////////////////////
///////////////////////////////////////////////////////////////////////////////
