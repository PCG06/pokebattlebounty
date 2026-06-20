#include "global.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_effect.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "move_relearner.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "stat_editor.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#if P_STAT_EDITOR_ENABLE

//==========DEFINES==========//
struct StatEditorResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u8 mode;
    u8 monIconSpriteId;
    enum Species speciesID;
    u8 panel;
    u8 leftRow;
    u16 rightPanelColumn;
    u16 rightPanelRow;
    u16 rightPanelSelectedStat;
    u16 leftSelectorSpriteId;
    u16 rightSelectorSpriteId;
    u16 statEditingValue;
    u16 normalTotal;
    u16 evTotal;
    u16 ivTotal;
    u16 partyId;
    u16 panelInputMode;
};

#define PANEL_LEFT  0
#define PANEL_RIGHT 1

#define LEFT_ROW_NICKNAME 0
#define LEFT_ROW_ABILITY  1
#define LEFT_ROW_NATURE   2
#define LEFT_ROW_COUNT    3

#define PANEL_INPUT_SELECT 0
#define PANEL_INPUT_EDIT   1

#define RIGHT_PANEL_EVS 0
#define RIGHT_PANEL_IVS 1

#define EDIT_INPUT_INCREASE     0
#define EDIT_INPUT_MAX_INCREASE 1
#define EDIT_INPUT_DECREASE     2
#define EDIT_INPUT_MAX_DECREASE 3

#define MIN_STAT 0

#define CHECK_IF_STAT_CANT_INCREASE (((sStatEditorDataPtr->statEditingValue == ((sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS) ? (MAX_PER_STAT_EVS) : (MAX_PER_STAT_IVS))) \
                                     || ((sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS) && (sStatEditorDataPtr->evTotal == MAX_TOTAL_EVS))))
/*
Breakdown of CHECK_IF_STAT_CANT_INCREASE
TLDR: Stat can't increase if you're either: at the maximum amount a stat can have (for both EVs and IVs), or for EVs, if you already hit the max total of EVs

 | (sStatEditorDataPtr->statEditingValue == ((sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS) ? (MAX_PER_STAT_EVS) : (MAX_PER_STAT_IVS))
  \> This part checks if the current stat being raised is already at max, whether it's an EV or IV

 | (sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS)
  \> This part checks if you're currently editing an EV

 | (sStatEditorDataPtr->evTotal == MAX_TOTAL_EVS)
  \> This part checks if the Pokémon already has the max amount of evs

 | ((sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS) && (sStatEditorDataPtr->evTotal == MAX_TOTAL_EVS))
  \> Together, these two check if you're editing an EV and already at the maximum amount of EVs
*/

#define TAG_SELECTOR 30004

enum WindowIds
{
    WINDOW_1,
    WINDOW_2,
    WINDOW_3,
    WINDOW_4,
};

//==========EWRAM==========//
static EWRAM_DATA struct StatEditorResources *sStatEditorDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

//==========STATIC=DEFINES==========//
static void StatEditor_RunSetup(void);
static bool8 StatEditor_DoGfxSetup(void);
static bool8 StatEditor_InitBgs(void);
static void StatEditor_FadeAndBail(void);
static bool8 StatEditor_LoadGraphics(void);
static void StatEditor_InitWindows(void);
static void PrintTitleToWindowMainState(void);
static void Task_StatEditorWaitFadeIn(u8 taskId);
static void Task_StatEditorMain(u8 taskId);
static void CreateMonSprite(u32 dexNum);
static void PrintMonStats(void);
static void SelectorCallback(struct Sprite *sprite);
static struct Pokemon *GetCurrentPartyMon(void);
static u8 CreateSelectors(void);
static void DestroySelectors(void);

//==========CONST=DATA==========//
static const struct BgTemplate sStatEditorBgTemplates[] =
{
    {
        .bg = 0,    // windows, etc
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .priority = 1
    },
    {
        .bg = 1,    // this bg loads the UI tilemap
        .charBaseIndex = 3,
        .mapBaseIndex = 28,
        .priority = 2
    },
    {
        .bg = 2,    // this bg loads the UI tilemap
        .charBaseIndex = 0,
        .mapBaseIndex = 26,
        .priority = 0
    }
};

static const struct WindowTemplate sMenuWindowTemplates[] = 
{
    [WINDOW_1] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 1,   // position from left (per 8 pixels)
        .tilemapTop = 0,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 2,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
    },
    [WINDOW_2] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 11,   // position from left (per 8 pixels)
        .tilemapTop = 2,    // position from top (per 8 pixels)
        .width = 18,        // width (per 8 pixels)
        .height = 17,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1 + 70,     // tile start in VRAM
    },
    [WINDOW_3] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 1,   // position from left (per 8 pixels)
        .tilemapTop = 11,    // position from top (per 8 pixels)
        .width = 8,        // width (per 8 pixels)
        .height = 9,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1 + 70 + 306,     // tile start in VRAM
    },
    DUMMY_WIN_TEMPLATE
};

static const u32 sStatEditorBgTiles[]   = INCGFX_U32("graphics/stat_editor/background_tileset.png", ".4bpp.smol");
static const u32 sStatEditorBgTilemap[] = INCGFX_U32("graphics/stat_editor/background_tileset.bin", ".smolTM");
static const u16 sStatEditorBgPalette[] = INCGFX_U16("graphics/stat_editor/background_pal.pal", ".gbapal");
static const u16 sSelector_Pal[]        = INCGFX_U16("graphics/stat_editor/selector.png", ".gbapal");
static const u32 sSelector_Gfx[]        = INCGFX_U32("graphics/stat_editor/selector.png", ".4bpp.smol");
static const u8 sA_ButtonGfx[]          = INCGFX_U8("graphics/stat_editor/a_button.png", ".4bpp");
static const u8 sB_ButtonGfx[]          = INCGFX_U8("graphics/stat_editor/b_button.png", ".4bpp");
static const u8 sR_ButtonGfx[]          = INCGFX_U8("graphics/stat_editor/r_button.png", ".4bpp");
static const u8 sDPad_ButtonGfx[]       = INCGFX_U8("graphics/stat_editor/dpad_button.png", ".4bpp");

enum FontColors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};

static const u8 sMenuWindowFontColors[][3] =
{
    [FONT_BLACK] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]   = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

static const struct OamData sOamData_Selector =
{
    .size = SPRITE_SIZE(8x16),
    .shape = SPRITE_SHAPE(8x16),
    .priority = 0,
};

static const struct CompressedSpriteSheet sSpriteSheet_Selector =
{
    .data = sSelector_Gfx,
    .size = 8*16*4/2,
    .tag = TAG_SELECTOR,
};

static const struct SpritePalette sSpritePal_Selector =
{
    .data = sSelector_Pal,
    .tag = TAG_SELECTOR
};

static const union AnimCmd sSpriteAnim_Selector0[] =
{
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_END,
};

static const union AnimCmd *const sSpriteAnimTable_Selector[] =
{
    sSpriteAnim_Selector0,
};

static const struct SpriteTemplate sSpriteTemplate_Selector =
{
    .tileTag = TAG_SELECTOR,
    .paletteTag = TAG_SELECTOR,
    .oam = &sOamData_Selector,
    .anims = sSpriteAnimTable_Selector,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SelectorCallback
};

#define STAT_ROW_HEIGHT  16
#define SECOND_COLUMN    (8 * 4)
#define THIRD_COLUMN     (8 * 8)
#define STARTING_X       60
#define STARTING_Y       26

#define LEFT_PANEL_SELECTOR_WIDTH  68
#define RIGHT_PANEL_SELECTOR_WIDTH 28

#define LEFT_NICKNAME_Y  2
#define LEFT_ABILITY_Y   34
#define LEFT_NATURE_Y    50

#define WINDOW3_SCREEN_X 8
#define WINDOW3_SCREEN_Y 92

#define SELECTOR_LEFT_EDGE_X     (WINDOW3_SCREEN_X - 2)
#define SELECTOR_LEFT_NICKNAME_Y (WINDOW3_SCREEN_Y + LEFT_NICKNAME_Y + 4)
#define SELECTOR_LEFT_ABILITY_Y  (WINDOW3_SCREEN_Y + LEFT_ABILITY_Y + 4)
#define SELECTOR_LEFT_NATURE_Y   (WINDOW3_SCREEN_Y + LEFT_NATURE_Y + 4)

#define SELECTOR_RIGHT_EV_LEFT_EDGE_X  (STARTING_X + SECOND_COLUMN + 82)
#define SELECTOR_RIGHT_IV_LEFT_EDGE_X  (STARTING_X + THIRD_COLUMN + 82)
#define SELECTOR_RIGHT_BASE_Y          (STARTING_Y + 24)

#define MON_ICON_X (32 + 8)
#define MON_ICON_Y (32 + 24)

#define BUTTON_Y 4

struct StatPrintCoords
{
    u16 x;
    u16 y;
};

static const struct StatPrintCoords sStatPrintData[] =
{
    [MON_DATA_MAX_HP]    = {STARTING_X,                STARTING_Y},
    [MON_DATA_HP_EV]     = {STARTING_X + SECOND_COLUMN, STARTING_Y},
    [MON_DATA_HP_IV]     = {STARTING_X + THIRD_COLUMN,  STARTING_Y},

    [MON_DATA_ATK]       = {STARTING_X,                STARTING_Y + STAT_ROW_HEIGHT},
    [MON_DATA_ATK_EV]    = {STARTING_X + SECOND_COLUMN, STARTING_Y + STAT_ROW_HEIGHT},
    [MON_DATA_ATK_IV]    = {STARTING_X + THIRD_COLUMN,  STARTING_Y + STAT_ROW_HEIGHT},

    [MON_DATA_DEF]       = {STARTING_X,                STARTING_Y + (STAT_ROW_HEIGHT * 2)},
    [MON_DATA_DEF_EV]    = {STARTING_X + SECOND_COLUMN, STARTING_Y + (STAT_ROW_HEIGHT * 2)},
    [MON_DATA_DEF_IV]    = {STARTING_X + THIRD_COLUMN,  STARTING_Y + (STAT_ROW_HEIGHT * 2)},

    [MON_DATA_SPATK]     = {STARTING_X,                STARTING_Y + (STAT_ROW_HEIGHT * 3)},
    [MON_DATA_SPATK_EV]  = {STARTING_X + SECOND_COLUMN, STARTING_Y + (STAT_ROW_HEIGHT * 3)},
    [MON_DATA_SPATK_IV]  = {STARTING_X + THIRD_COLUMN,  STARTING_Y + (STAT_ROW_HEIGHT * 3)},

    [MON_DATA_SPDEF]     = {STARTING_X,                STARTING_Y + (STAT_ROW_HEIGHT * 4)},
    [MON_DATA_SPDEF_EV]  = {STARTING_X + SECOND_COLUMN, STARTING_Y + (STAT_ROW_HEIGHT * 4)},
    [MON_DATA_SPDEF_IV]  = {STARTING_X + THIRD_COLUMN,  STARTING_Y + (STAT_ROW_HEIGHT * 4)},

    [MON_DATA_SPEED]     = {STARTING_X,                STARTING_Y + (STAT_ROW_HEIGHT * 5)},
    [MON_DATA_SPEED_EV]  = {STARTING_X + SECOND_COLUMN, STARTING_Y + (STAT_ROW_HEIGHT * 5)},
    [MON_DATA_SPEED_IV]  = {STARTING_X + THIRD_COLUMN,  STARTING_Y + (STAT_ROW_HEIGHT * 5)},
};

static const u16 sStatsToPrintActual[] = {
    MON_DATA_MAX_HP, MON_DATA_ATK, MON_DATA_DEF, MON_DATA_SPEED, MON_DATA_SPATK, MON_DATA_SPDEF,
};

static const u16 sStatsToPrintEVs[] = {
    MON_DATA_HP_EV, MON_DATA_ATK_EV, MON_DATA_DEF_EV, MON_DATA_SPEED_EV, MON_DATA_SPATK_EV, MON_DATA_SPDEF_EV,
};

static const u16 sStatsToPrintIVs[] = {
    MON_DATA_HP_IV, MON_DATA_ATK_IV, MON_DATA_DEF_IV, MON_DATA_SPEED_IV, MON_DATA_SPATK_IV, MON_DATA_SPDEF_IV,
};

static const u8 sGenderColors[2][3] =
{
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_BLUE, TEXT_COLOR_BLUE},
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED,  TEXT_COLOR_RED}
};

static const u8 sText_MenuTitle[]             = _("Stat Editor");
static const u8 sText_MenuHP[]                = _("HP");
static const u8 sText_MenuAttack[]            = _("Attack");
static const u8 sText_MenuSpAttack[]          = _("Sp. Atk");
static const u8 sText_MenuDefense[]           = _("Defense");
static const u8 sText_MenuSpDefense[]         = _("Sp. Def");
static const u8 sText_MenuSpeed[]             = _("Speed");
static const u8 sText_MenuTotal[]             = _("Total");
static const u8 sText_MenuStat[]              = _("Stat");
static const u8 sText_MenuReal[]              = _("Real");
static const u8 sText_MenuEV[]                = _("EVs");
static const u8 sText_MenuIV[]                = _("IVs");
static const u8 sText_MonLevel[]              = _("Lv.{CLEAR 1}{STR_VAR_1}");
static const u8 sText_MenuLRButtonText[]      = _("Cycle Party");
static const u8 sText_MenuBButtonText[]       = _("Back");
static const u8 sText_MenuDPadChangeStat[]    = _("Change Stat");
static const u8 sText_MenuDPadChangeAbility[] = _("Change Ability");
static const u8 sText_MenuDPadChangeNature[]  = _("Change Nature");
static const u8 sText_MenuAButtonText[]       = _("Save");

// Begin Generic UI Initialization Code

void Task_OpenStatEditorFromStartMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        StatEditor_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

void StatEditor_Init(MainCallback callback)
{
    if ((sStatEditorDataPtr = AllocZeroed(sizeof(struct StatEditorResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sStatEditorDataPtr->gfxLoadState          = 0;
    sStatEditorDataPtr->savedCallback         = callback;
    sStatEditorDataPtr->leftSelectorSpriteId  = 0xFF;
    sStatEditorDataPtr->rightSelectorSpriteId = 0xFF;
    sStatEditorDataPtr->partyId               = gSpecialVar_0x8004;
    sStatEditorDataPtr->panel                 = PANEL_LEFT;
    sStatEditorDataPtr->leftRow               = LEFT_ROW_NICKNAME;
    sStatEditorDataPtr->rightPanelColumn      = RIGHT_PANEL_EVS;
    sStatEditorDataPtr->rightPanelRow         = 0;

    SetMainCallback2(StatEditor_RunSetup);
}

static void StatEditor_RunSetup(void)
{
    while (TRUE)
    {
        if (StatEditor_DoGfxSetup() == TRUE)
            break;
    }
}

static void StatEditor_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void StatEditor_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 StatEditor_DoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        SetVBlankHBlankCallbacksToNull();
        ResetVramOamAndBgCntRegs();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (StatEditor_InitBgs())
        {
            sStatEditorDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            StatEditor_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (StatEditor_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        sStatEditorDataPtr->speciesID = GetMonData(GetCurrentPartyMon(), MON_DATA_SPECIES_OR_EGG);
        FreeMonIconPalettes();
        LoadMonIconPalettes();
        LoadCompressedSpriteSheet(&sSpriteSheet_Selector);
        LoadSpritePalette(&sSpritePal_Selector);
        CreateMonSprite(sStatEditorDataPtr->speciesID);
        gMain.state++;
        break;
    case 5:
        StatEditor_InitWindows();
        PrintTitleToWindowMainState();
        sStatEditorDataPtr->panelInputMode = PANEL_INPUT_SELECT;
        PrintMonStats();
        CreateSelectors();
        gMain.state++;
        break;
    case 6:
        CreateTask(Task_StatEditorWaitFadeIn, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(StatEditor_VBlankCB);
        SetMainCallback2(StatEditor_MainCB);
        return TRUE;
    }
    return FALSE;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void StatEditor_FreeResources(void)
{
    DestroySelectors();
    FreeResourcesAndDestroySprite(&gSprites[sStatEditorDataPtr->monIconSpriteId], sStatEditorDataPtr->monIconSpriteId);
    try_free(sStatEditorDataPtr);
    try_free(sBg1TilemapBuffer);
    FreeAllWindowBuffers();
}

static void Task_StatEditorWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sStatEditorDataPtr->savedCallback);
        StatEditor_FreeResources();
        DestroyTask(taskId);
    }
}

static void StatEditor_FadeAndBail(void)
{
    gLastViewedMonIndex = sStatEditorDataPtr->partyId;
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_StatEditorWaitFadeAndBail, 0);
    SetVBlankCallback(StatEditor_VBlankCB);
    SetMainCallback2(StatEditor_MainCB);
}

static bool8 StatEditor_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);

    if (sBg1TilemapBuffer == NULL)
        return FALSE;

    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sStatEditorBgTemplates, NELEMS(sStatEditorBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 StatEditor_LoadGraphics(void)
{
    switch (sStatEditorDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sStatEditorBgTiles, 0, 0, 0);
        sStatEditorDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sStatEditorBgTilemap, sBg1TilemapBuffer);
            sStatEditorDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(sStatEditorBgPalette, 0, 32);
        sStatEditorDataPtr->gfxLoadState++;
        break;
    default:
        sStatEditorDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void StatEditor_InitWindows(void)
{
    InitWindows(sMenuWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    FillWindowPixelBuffer(WINDOW_1, 0);
    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);
    ScheduleBgCopyTilemapToVram(2);
}

static void Task_StatEditorWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_StatEditorMain;
}

static void Task_StatEditorTurnOff(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sStatEditorDataPtr->savedCallback);
        StatEditor_FreeResources();
        DestroyTask(taskId);
    }
}

//
//       Stat Editor Code
//  End of UI setup code, beginning of stat editor specific code
//
static struct Pokemon *GetCurrentPartyMon(void)
{
    return &gParties[B_TRAINER_PLAYER][sStatEditorDataPtr->partyId];
}

static void CreateMonSprite(u32 dexNum)
{
    u32 personality = GetMonData(GetCurrentPartyMon(), MON_DATA_PERSONALITY);
    sStatEditorDataPtr->monIconSpriteId = CreateMonPicSprite_Affine(dexNum, 0, personality, TRUE, MON_ICON_X, MON_ICON_Y, 0, TAG_NONE);
    gSprites[sStatEditorDataPtr->monIconSpriteId].oam.priority = 0;
}

static u8 CreateSelectors(void)
{
    if (sStatEditorDataPtr->leftSelectorSpriteId == 0xFF)
        sStatEditorDataPtr->leftSelectorSpriteId = CreateSprite(&sSpriteTemplate_Selector, SELECTOR_LEFT_EDGE_X, SELECTOR_LEFT_NICKNAME_Y, 0);

    if (sStatEditorDataPtr->rightSelectorSpriteId == 0xFF)
        sStatEditorDataPtr->rightSelectorSpriteId = CreateSprite(&sSpriteTemplate_Selector, SELECTOR_LEFT_EDGE_X + LEFT_PANEL_SELECTOR_WIDTH, SELECTOR_LEFT_NICKNAME_Y, 0);

    gSprites[sStatEditorDataPtr->leftSelectorSpriteId].invisible = FALSE;
    gSprites[sStatEditorDataPtr->rightSelectorSpriteId].invisible = FALSE;

    // Flip sprite for right side cursor
    gSprites[sStatEditorDataPtr->rightSelectorSpriteId].hFlip = TRUE;

    StartSpriteAnim(&gSprites[sStatEditorDataPtr->leftSelectorSpriteId], 0);
    StartSpriteAnim(&gSprites[sStatEditorDataPtr->rightSelectorSpriteId], 0);
    return sStatEditorDataPtr->leftSelectorSpriteId;
}

static void DestroySelectors(void)
{
    if (sStatEditorDataPtr->leftSelectorSpriteId != 0xFF)
        DestroySprite(&gSprites[sStatEditorDataPtr->leftSelectorSpriteId]);
    if (sStatEditorDataPtr->rightSelectorSpriteId != 0xFF)
        DestroySprite(&gSprites[sStatEditorDataPtr->rightSelectorSpriteId]);
    sStatEditorDataPtr->leftSelectorSpriteId = 0xFF;
    sStatEditorDataPtr->rightSelectorSpriteId = 0xFF;
}

static void PrintTitleToWindowMainState(void)
{
    FillWindowPixelBuffer(WINDOW_1, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 1, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuTitle);
    BlitBitmapToWindow(WINDOW_1, sR_ButtonGfx, 75, BUTTON_Y, 24, 8);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 102, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuLRButtonText);
    BlitBitmapToWindow(WINDOW_1, sB_ButtonGfx, 196, BUTTON_Y, 8, 8);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 208, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuBButtonText);
    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);
}

void GetDPadText(void)
{
    if (sStatEditorDataPtr->panel == PANEL_LEFT)
    {
        if (sStatEditorDataPtr->leftRow == LEFT_ROW_ABILITY)
        {
            BlitBitmapToWindow(WINDOW_1, sDPad_ButtonGfx, 75, BUTTON_Y, 24, 8);
            AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 102, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuDPadChangeAbility);
        }
        else if (sStatEditorDataPtr->leftRow == LEFT_ROW_NATURE)
        {
            BlitBitmapToWindow(WINDOW_1, sDPad_ButtonGfx, 75, BUTTON_Y, 24, 8);
            AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 102, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuDPadChangeNature);
        }
    }
    else if (sStatEditorDataPtr->panel == PANEL_RIGHT)
    {
        BlitBitmapToWindow(WINDOW_1, sDPad_ButtonGfx, 75, BUTTON_Y, 24, 8);
        AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 102, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuDPadChangeStat);
    }
}

static void PrintTitleToWindowEditState(void)
{
    FillWindowPixelBuffer(WINDOW_1, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 1, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuTitle);
    GetDPadText();
    BlitBitmapToWindow(WINDOW_1, sA_ButtonGfx, 186, BUTTON_Y, 8, 8);
    BlitBitmapToWindow(WINDOW_1, sB_ButtonGfx, 196, BUTTON_Y, 8, 8);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 208, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuAButtonText);
    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);
}

static void PrintMonStats(void)
{
    u32 currentStat;
    u8 text[2];

    struct Pokemon *mon = GetCurrentPartyMon();
    u32 nature = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
    u32 abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM);
    enum Ability ability = gSpeciesInfo[sStatEditorDataPtr->speciesID].abilities[abilityNum];
    u32 level = GetMonData(mon, MON_DATA_LEVEL);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY);
    u32 gender = GetGenderFromSpeciesAndPersonality(sStatEditorDataPtr->speciesID, personality);

    FillWindowPixelBuffer(WINDOW_2, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WINDOW_3, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    sStatEditorDataPtr->normalTotal = 0;
    sStatEditorDataPtr->evTotal = 0;
    sStatEditorDataPtr->ivTotal = 0;

    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 18, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuStat);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, STARTING_X, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuReal);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, STARTING_X + SECOND_COLUMN + 4, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuEV);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, STARTING_X + THIRD_COLUMN + 5, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuIV);

    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 24, STARTING_Y + (STAT_ROW_HEIGHT * 0), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuHP);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 12, STARTING_Y + (STAT_ROW_HEIGHT * 1), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuAttack);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 12, STARTING_Y + (STAT_ROW_HEIGHT * 2), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuDefense);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 10, STARTING_Y + (STAT_ROW_HEIGHT * 3), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuSpAttack);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 12, STARTING_Y + (STAT_ROW_HEIGHT * 4), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuSpDefense);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 16, STARTING_Y + (STAT_ROW_HEIGHT * 5), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuSpeed);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 16, STARTING_Y + (STAT_ROW_HEIGHT * 6), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuTotal);

    // Print Mon Stats
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        currentStat = GetMonData(mon, sStatsToPrintActual[i]);
        sStatEditorDataPtr->normalTotal += currentStat;
        ConvertIntToDecimalStringN(gStringVar2, currentStat, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, sStatPrintData[sStatsToPrintActual[i]].x, sStatPrintData[sStatsToPrintActual[i]].y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);
    }

    // EVs
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        currentStat = GetMonData(mon, sStatsToPrintEVs[i]);
        sStatEditorDataPtr->evTotal += currentStat;
        ConvertIntToDecimalStringN(gStringVar2, currentStat, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, sStatPrintData[sStatsToPrintEVs[i]].x, sStatPrintData[sStatsToPrintEVs[i]].y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);
    }

    // IVs
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        currentStat = GetMonData(mon, sStatsToPrintIVs[i]);
        sStatEditorDataPtr->ivTotal += currentStat;
        ConvertIntToDecimalStringN(gStringVar2, currentStat, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, sStatPrintData[sStatsToPrintIVs[i]].x, sStatPrintData[sStatsToPrintIVs[i]].y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);
    }

    // Totals row
    ConvertIntToDecimalStringN(gStringVar2, sStatEditorDataPtr->normalTotal, STR_CONV_MODE_RIGHT_ALIGN, 4);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, STARTING_X - 6, STARTING_Y + (STAT_ROW_HEIGHT * 6), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    ConvertIntToDecimalStringN(gStringVar2, sStatEditorDataPtr->evTotal, STR_CONV_MODE_RIGHT_ALIGN, 3);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, STARTING_X + SECOND_COLUMN, STARTING_Y + (STAT_ROW_HEIGHT * 6), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    ConvertIntToDecimalStringN(gStringVar2, sStatEditorDataPtr->ivTotal, STR_CONV_MODE_RIGHT_ALIGN, 3);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, STARTING_X + THIRD_COLUMN, STARTING_Y + (STAT_ROW_HEIGHT * 6), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    // Print ability / nature / name / level / gender
    GetMonNickname(mon, gStringVar2);
    AddTextPrinterParameterized4(WINDOW_3, FONT_NARROW, 2, LEFT_NICKNAME_Y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    ConvertIntToDecimalStringN(gStringVar1, level, STR_CONV_MODE_RIGHT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar2, sText_MonLevel);
    AddTextPrinterParameterized4(WINDOW_3, FONT_SMALL_NARROW, 2, 18, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, gStringVar2);

    StringCopy(text, gText_MaleSymbol);
    if (gender != MON_GENDERLESS)
    {
        if (gender == MON_FEMALE)
            StringCopy(text, gText_FemaleSymbol);

        AddTextPrinterParameterized4(WINDOW_3, FONT_NORMAL, 41 + 8, 19, 0, 0, sGenderColors[(gender == MON_FEMALE)], TEXT_SKIP_DRAW, text);
    }

    StringCopy(gStringVar2, gAbilitiesInfo[ability].name);
    AddTextPrinterParameterized4(WINDOW_3, FONT_SMALL_NARROW, 2, LEFT_ABILITY_Y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    StringCopy(gStringVar2, gNaturesInfo[nature].name);
    AddTextPrinterParameterized4(WINDOW_3, FONT_SMALL_NARROW, 2, LEFT_NATURE_Y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    PutWindowTilemap(WINDOW_3);
    CopyWindowToVram(WINDOW_3, 3);
    PutWindowTilemap(WINDOW_2);
    CopyWindowToVram(WINDOW_2, 3);
}

struct SpriteCoords
{
    u8 x;
    u8 y;
};

static void SelectorCallback(struct Sprite *sprite)
{
    static const struct SpriteCoords sRightPanelCoords[6][2] = {
        {{SELECTOR_RIGHT_EV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 0)}, {SELECTOR_RIGHT_IV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 0)}},
        {{SELECTOR_RIGHT_EV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 1)}, {SELECTOR_RIGHT_IV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 1)}},
        {{SELECTOR_RIGHT_EV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 2)}, {SELECTOR_RIGHT_IV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 2)}},
        {{SELECTOR_RIGHT_EV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 3)}, {SELECTOR_RIGHT_IV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 3)}},
        {{SELECTOR_RIGHT_EV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 4)}, {SELECTOR_RIGHT_IV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 4)}},
        {{SELECTOR_RIGHT_EV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 5)}, {SELECTOR_RIGHT_IV_LEFT_EDGE_X, SELECTOR_RIGHT_BASE_Y + (STAT_ROW_HEIGHT * 5)}},
    };

    static const u8 sLeftPanelY[LEFT_ROW_COUNT] = {
        [LEFT_ROW_NICKNAME] = SELECTOR_LEFT_NICKNAME_Y,
        [LEFT_ROW_ABILITY]  = SELECTOR_LEFT_ABILITY_Y,
        [LEFT_ROW_NATURE]   = SELECTOR_LEFT_NATURE_Y,
    };

    bool32 isLeft = (sprite == &gSprites[sStatEditorDataPtr->leftSelectorSpriteId]);
    u32 leftEdgeX;
    u32 y;
    bool32 shouldInvis = FALSE;

    if (sStatEditorDataPtr->panel == PANEL_LEFT)
    {
        leftEdgeX = SELECTOR_LEFT_EDGE_X;
        y = sLeftPanelY[sStatEditorDataPtr->leftRow];
        sprite->x = isLeft ? leftEdgeX : (leftEdgeX + LEFT_PANEL_SELECTOR_WIDTH);
        sprite->y = y;
    }
    else
    {
        sStatEditorDataPtr->rightPanelSelectedStat = sStatEditorDataPtr->rightPanelColumn + (sStatEditorDataPtr->rightPanelRow * 2);
        leftEdgeX = sRightPanelCoords[sStatEditorDataPtr->rightPanelRow][sStatEditorDataPtr->rightPanelColumn].x;
        y = sRightPanelCoords[sStatEditorDataPtr->rightPanelRow][sStatEditorDataPtr->rightPanelColumn].y;
        sprite->x = isLeft ? leftEdgeX : (leftEdgeX + RIGHT_PANEL_SELECTOR_WIDTH);
        sprite->y = y;

        // Don't show cursor on left when stat is empty, on right when stat is maxed
        if (sStatEditorDataPtr->panelInputMode == PANEL_INPUT_EDIT)
        {
            if (isLeft && sStatEditorDataPtr->statEditingValue == MIN_STAT)
                shouldInvis = TRUE;
            else if (!isLeft && CHECK_IF_STAT_CANT_INCREASE)
                shouldInvis = TRUE;
        }
    }

    if (sStatEditorDataPtr->panelInputMode == PANEL_INPUT_EDIT)
    {
        if (sprite->data[0] == 32)
            sprite->invisible = TRUE;
        if (sprite->data[0] >= 48)
        {
            sprite->invisible = shouldInvis;
            sprite->data[0] = 0;
        }
        sprite->data[0]++;
    }
    else
    {
        sprite->invisible = FALSE;
        sprite->data[0] = 0;
    }
}

static void Task_DelayedSpriteLoad(u8 taskId) // wait 4 frames after changing the mon you're editing so there are no palette problems
{
    if (gTasks[taskId].data[11] >= 4)
    {
        CreateMonSprite(sStatEditorDataPtr->speciesID);
        PrintMonStats();
        gTasks[taskId].func = Task_StatEditorMain;
    }
    else
    {
        gTasks[taskId].data[11]++;
    }
}

static void ReloadNewPokemon(u8 taskId)
{
    gSprites[sStatEditorDataPtr->monIconSpriteId].invisible = TRUE;
    FreeResourcesAndDestroySprite(&gSprites[sStatEditorDataPtr->monIconSpriteId], sStatEditorDataPtr->monIconSpriteId);
    sStatEditorDataPtr->speciesID = GetMonData(GetCurrentPartyMon(), MON_DATA_SPECIES_OR_EGG);
    gSpecialVar_0x8004 = sStatEditorDataPtr->partyId;
    gTasks[taskId].func = Task_DelayedSpriteLoad;
    gTasks[taskId].data[11] = 0;
}

static u32 GetValidAbilitySlots(enum Species species, u8 outSlots[])
{
    u32 count = 0;
    enum Ability ab0 = GetSpeciesAbility(species, 0);
    enum Ability ab1 = GetSpeciesAbility(species, 1);
    enum Ability ab2 = GetSpeciesAbility(species, 2);

    outSlots[count++] = 0;

    if (ab1 != ABILITY_NONE && ab1 != ab0)
        outSlots[count++] = 1;

    if (ab2 != ABILITY_NONE && ab2 != ab0)
        outSlots[count++] = 2;

    return count;
}

static bool32 HasOnlyOneAbility(enum Species species)
{
    u8 outSlots[NUM_ABILITY_SLOTS];

    return GetValidAbilitySlots(species, outSlots) == 1;
}

static void CB2_ReturnToSummaryScreenFromNamingScreen(void)
{
    ShowPokemonSummaryScreen(SUMMARY_MODE_STAT_EDITOR, gParties[B_TRAINER_PLAYER], gSpecialVar_0x8004, gPartiesCount[B_TRAINER_PLAYER] - 1, gInitialSummaryScreenCallback);
}

static void CB2_ReturnToStatEditorFromNamingScreen(void)
{
    SetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar2); // partyId gets overwritten to 0.
    if (P_PARTY_MENU_STAT_EDITOR)
        StatEditor_Init(CB2_ReturnToPartyMenuFromSummaryScreen);
    else if (P_SUMMARY_SCREEN_STAT_EDITOR)
        StatEditor_Init(CB2_ReturnToSummaryScreenFromNamingScreen);
}

static void CB2_StatEditorChangePokemonNickname(void)
{
    ChangePokemonNicknameWithCallback(CB2_ReturnToStatEditorFromNamingScreen);
}

static void HandleLeftPanelNextValue(void)
{
    struct Pokemon *mon = GetCurrentPartyMon();
    u32 val;

    switch (sStatEditorDataPtr->leftRow)
    {
    case LEFT_ROW_NICKNAME:
        break;

    case LEFT_ROW_ABILITY:
    {
        u8 slots[NUM_ABILITY_SLOTS];
        u32 count = GetValidAbilitySlots(sStatEditorDataPtr->speciesID, slots);

        if (count <= 1)
            return;

        u32 current = GetMonData(mon, MON_DATA_ABILITY_NUM);
        u32 pos = 0;

        for (u32 i = 0; i < count; i++)
        {
            if (slots[i] == current)
            {
                pos = i;
                break;
            }
        }

        val = slots[(pos + 1) % count];
        SetMonData(mon, MON_DATA_ABILITY_NUM, &val);
        PrintMonStats();
        break;
    }

    case LEFT_ROW_NATURE:
        val = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
        val = (val + 1) % NUM_NATURES;
        SetMonData(mon, MON_DATA_HIDDEN_NATURE, &val);
        CalculateMonStats(mon);
        PrintMonStats();
        break;
    }
}

static void HandleLeftPanelPreviousValue(void)
{
    struct Pokemon *mon = GetCurrentPartyMon();
    u32 val;

    switch (sStatEditorDataPtr->leftRow)
    {
    case LEFT_ROW_NICKNAME:
        break;

    case LEFT_ROW_ABILITY:
    {
        u8 slots[NUM_ABILITY_SLOTS];
        u32 count = GetValidAbilitySlots(sStatEditorDataPtr->speciesID, slots);

        if (count <= 1)
            return;

        u32 current = GetMonData(mon, MON_DATA_ABILITY_NUM);
        u32 pos = 0;

        for (u32 i = 0; i < count; i++)
        {
            if (slots[i] == current)
            {
                pos = i;
                break;
            }
        }

        val = slots[(pos == 0) ? (count - 1) : (pos - 1)];
        SetMonData(mon, MON_DATA_ABILITY_NUM, &val);
        PrintMonStats();
        break;
    }

    case LEFT_ROW_NATURE:
        val = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
        val = (val == 0) ? (NUM_NATURES - 1) : (val - 1);
        SetMonData(mon, MON_DATA_HIDDEN_NATURE, &val);
        CalculateMonStats(mon);
        PrintMonStats();
        break;
    }
}

static void Task_LeftPanelEditMode(u8 taskId)
{
    if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        gTasks[taskId].func = Task_StatEditorMain;
        PlaySE(SE_SELECT);
        sStatEditorDataPtr->panelInputMode = PANEL_INPUT_SELECT;
        PrintTitleToWindowMainState();
        return;
    }

    switch (sStatEditorDataPtr->leftRow)
    {
    case LEFT_ROW_NICKNAME:
        PlaySE(SE_SELECT);
        sStatEditorDataPtr->savedCallback = CB2_StatEditorChangePokemonNickname;
        gSpecialVar_0x8004 = sStatEditorDataPtr->partyId;
        Task_StatEditorTurnOff(taskId);
        break;

    case LEFT_ROW_ABILITY:
    case LEFT_ROW_NATURE:
        if (JOY_NEW(DPAD_RIGHT))
        {
            PlaySE(SE_SELECT);
            HandleLeftPanelNextValue();
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            PlaySE(SE_SELECT);
            HandleLeftPanelPreviousValue();
        }
        break;
    }
}

static const u16 sSelectedStatToStatEnum[] = {
    MON_DATA_HP_EV,    MON_DATA_HP_IV,
    MON_DATA_ATK_EV,   MON_DATA_ATK_IV,
    MON_DATA_DEF_EV,   MON_DATA_DEF_IV,
    MON_DATA_SPATK_EV, MON_DATA_SPATK_IV,
    MON_DATA_SPDEF_EV, MON_DATA_SPDEF_IV,
    MON_DATA_SPEED_EV, MON_DATA_SPEED_IV,
};

static void ApplyRightPanelStatChange(void)
{
    struct Pokemon *mon = GetCurrentPartyMon();
    u32 currentStatEnum = sSelectedStatToStatEnum[sStatEditorDataPtr->rightPanelSelectedStat];
    s32 amountHPLost = 0;
    u32 currentHP    = 0;

    if (currentStatEnum == MON_DATA_HP_EV || currentStatEnum == MON_DATA_HP_IV)
    {
        u32 oldMaxHP = GetMonData(mon, MON_DATA_MAX_HP);
        currentHP    = GetMonData(mon, MON_DATA_HP);
        amountHPLost = oldMaxHP - currentHP;
    }

    SetMonData(mon, currentStatEnum, &(sStatEditorDataPtr->statEditingValue));
    CalculateMonStats(mon);

    if ((amountHPLost > 0) && (currentHP != 0))
    {
        s32 diff = GetMonData(mon, MON_DATA_MAX_HP) - amountHPLost;
        if (diff < 0)
            diff = 0;
        SetMonData(mon, MON_DATA_HP, &diff);
    }

    PrintMonStats();
}

static void HandleRightPanelEditInput(u32 input)
{
    if ((input <= EDIT_INPUT_MAX_INCREASE) && CHECK_IF_STAT_CANT_INCREASE)
        return;

    if ((input >= EDIT_INPUT_DECREASE) && (sStatEditorDataPtr->statEditingValue == MIN_STAT))
        return;

    switch (input)
    {
    case EDIT_INPUT_INCREASE:
        if (!CHECK_IF_STAT_CANT_INCREASE)
            sStatEditorDataPtr->statEditingValue++;
        break;
    case EDIT_INPUT_MAX_INCREASE:
        if (sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS)
        {
            u32 remaining = MAX_TOTAL_EVS - sStatEditorDataPtr->evTotal;
            sStatEditorDataPtr->statEditingValue += (remaining < MAX_PER_STAT_EVS) ? remaining : MAX_PER_STAT_EVS;
            if (sStatEditorDataPtr->statEditingValue > MAX_PER_STAT_EVS)
                sStatEditorDataPtr->statEditingValue = MAX_PER_STAT_EVS;
        }
        else
        {
            sStatEditorDataPtr->statEditingValue = MAX_PER_STAT_IVS;
        }
        break;
    case EDIT_INPUT_DECREASE:
        if (sStatEditorDataPtr->statEditingValue != MIN_STAT)
            sStatEditorDataPtr->statEditingValue--;
        break;
    case EDIT_INPUT_MAX_DECREASE:
        sStatEditorDataPtr->statEditingValue = MIN_STAT;
        break;
    }

    ApplyRightPanelStatChange();
}

static void Task_RightPanelEditMode(u8 taskId)
{
    if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        gTasks[taskId].func = Task_StatEditorMain;
        PlaySE(SE_SELECT);
        sStatEditorDataPtr->panelInputMode = PANEL_INPUT_SELECT;
        PrintTitleToWindowMainState();
        return;
    }

    if (JOY_NEW(DPAD_LEFT))
        HandleRightPanelEditInput(EDIT_INPUT_DECREASE);
    else if (JOY_NEW(DPAD_RIGHT))
        HandleRightPanelEditInput(EDIT_INPUT_INCREASE);
    else if (JOY_NEW(DPAD_UP) || JOY_NEW(R_BUTTON))
        HandleRightPanelEditInput(EDIT_INPUT_MAX_INCREASE);
    else if (JOY_NEW(DPAD_DOWN) || JOY_NEW(L_BUTTON))
        HandleRightPanelEditInput(EDIT_INPUT_MAX_DECREASE);
}

static void Task_StatEditorMain(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        gLastViewedMonIndex = sStatEditorDataPtr->partyId;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_StatEditorTurnOff;
        return;
    }

    if (JOY_NEW(L_BUTTON))
    {
        u32 partyId = sStatEditorDataPtr->partyId;
        sStatEditorDataPtr->partyId = (partyId == 0) ? (gPartiesCount[B_TRAINER_PLAYER] - 1) : (partyId - 1);
        PlaySE(SE_SELECT);
        ReloadNewPokemon(taskId);
        return;
    }

    if (JOY_NEW(R_BUTTON))
    {
        u32 partyId = sStatEditorDataPtr->partyId;
        sStatEditorDataPtr->partyId = (partyId == gPartiesCount[B_TRAINER_PLAYER] - 1) ? 0 : (partyId + 1);
        PlaySE(SE_SELECT);
        ReloadNewPokemon(taskId);
        return;
    }

    if (JOY_NEW(START_BUTTON))
    {
        PlaySE(SE_SELECT);
        gRelearnMode = RELEARN_MODE_STAT_EDITOR;
        sStatEditorDataPtr->savedCallback = CB2_InitLearnMove;
        gSpecialVar_0x8004 = sStatEditorDataPtr->partyId;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_StatEditorTurnOff;
        return;
    }

    if (sStatEditorDataPtr->panel == PANEL_LEFT)
    {
        if (JOY_NEW(DPAD_UP))
        {
            PlaySE(SE_SELECT);
            sStatEditorDataPtr->leftRow = (sStatEditorDataPtr->leftRow == 0) ? (LEFT_ROW_COUNT - 1) : (sStatEditorDataPtr->leftRow - 1);
            PrintMonStats();
            return;
        }

        if (JOY_NEW(DPAD_DOWN))
        {
            PlaySE(SE_SELECT);
            sStatEditorDataPtr->leftRow = (sStatEditorDataPtr->leftRow + 1) % LEFT_ROW_COUNT;
            PrintMonStats();
            return;
        }

        if (JOY_NEW(DPAD_LEFT))
        {
            PlaySE(SE_SELECT);
            sStatEditorDataPtr->panel = PANEL_RIGHT;
            sStatEditorDataPtr->rightPanelColumn = RIGHT_PANEL_IVS;
            sStatEditorDataPtr->rightPanelRow = 0;
            PrintMonStats();
            return;
        }

        if (JOY_NEW(DPAD_RIGHT))
        {
            PlaySE(SE_SELECT);
            sStatEditorDataPtr->panel = PANEL_RIGHT;
            sStatEditorDataPtr->rightPanelColumn = RIGHT_PANEL_EVS;
            sStatEditorDataPtr->rightPanelRow = 0;
            PrintMonStats();
            return;
        }

        if (JOY_NEW(A_BUTTON))
        {
            if (sStatEditorDataPtr->leftRow == LEFT_ROW_ABILITY
             && HasOnlyOneAbility(sStatEditorDataPtr->speciesID) == TRUE)
            {
                PlaySE(SE_FAILURE);
                sStatEditorDataPtr->panelInputMode = PANEL_INPUT_SELECT;
                return;
            }

            PlaySE(SE_SELECT);
            sStatEditorDataPtr->panelInputMode = PANEL_INPUT_EDIT;
            gSprites[sStatEditorDataPtr->leftSelectorSpriteId].data[0] = 32;
            gSprites[sStatEditorDataPtr->rightSelectorSpriteId].data[0] = 32;
            PrintTitleToWindowEditState();
            gTasks[taskId].func = Task_LeftPanelEditMode;
            return;
        }
    }
    else if (sStatEditorDataPtr->panel == PANEL_RIGHT)
    {
        if (JOY_NEW(A_BUTTON))
        {
            sStatEditorDataPtr->rightPanelSelectedStat = sStatEditorDataPtr->rightPanelColumn + (sStatEditorDataPtr->rightPanelRow * 2);
            sStatEditorDataPtr->statEditingValue = GetMonData(GetCurrentPartyMon(), sSelectedStatToStatEnum[sStatEditorDataPtr->rightPanelSelectedStat]);

            if (sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS
             && sStatEditorDataPtr->statEditingValue == MIN_STAT
             && sStatEditorDataPtr->evTotal == MAX_TOTAL_EVS)
            {
                PlaySE(SE_FAILURE);
                sStatEditorDataPtr->panelInputMode = PANEL_INPUT_SELECT;
                return;
            }

            PlaySE(SE_SELECT);
            sStatEditorDataPtr->panelInputMode = PANEL_INPUT_EDIT;
            gSprites[sStatEditorDataPtr->leftSelectorSpriteId].data[0] = 32;
            gSprites[sStatEditorDataPtr->rightSelectorSpriteId].data[0] = 32;
            PrintTitleToWindowEditState();
            gTasks[taskId].func = Task_RightPanelEditMode;
            return;
        }

        if (JOY_NEW(DPAD_UP))
        {
            PlaySE(SE_SELECT);
            sStatEditorDataPtr->rightPanelRow = (sStatEditorDataPtr->rightPanelRow == 0) ? 5 : (sStatEditorDataPtr->rightPanelRow - 1);
            return;
        }

        if (JOY_NEW(DPAD_DOWN))
        {
            PlaySE(SE_SELECT);
            sStatEditorDataPtr->rightPanelRow = (sStatEditorDataPtr->rightPanelRow == 5) ? 0 : (sStatEditorDataPtr->rightPanelRow + 1);
            return;
        }

        if (JOY_NEW(DPAD_LEFT))
        {
            PlaySE(SE_SELECT);
            if (sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_IVS)
                sStatEditorDataPtr->rightPanelColumn = RIGHT_PANEL_EVS;
            else
            {
                sStatEditorDataPtr->panel = PANEL_LEFT;
                sStatEditorDataPtr->leftRow = LEFT_ROW_NICKNAME;
            }
            PrintMonStats();
            return;
        }

        if (JOY_NEW(DPAD_RIGHT))
        {
            PlaySE(SE_SELECT);
            if (sStatEditorDataPtr->rightPanelColumn == RIGHT_PANEL_EVS)
                sStatEditorDataPtr->rightPanelColumn = RIGHT_PANEL_IVS;
            else
            {
                sStatEditorDataPtr->panel = PANEL_LEFT;
                sStatEditorDataPtr->leftRow = LEFT_ROW_NICKNAME;
            }
            PrintMonStats();
            return;
        }
    }
}

#endif // P_STAT_EDITOR_ENABLE
