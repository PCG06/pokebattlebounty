/*
* Event moves distributed on Pokémon (both, legal and illegal!)
* Link: https://www.smogon.com/forums/threads/event-move-legalities.3650291/
*/

static const u16 sNoneEventLearnset[] =
{
    MOVE_UNAVAILABLE
};

#if P_FAMILY_BULBASAUR
static const u16 sBulbasaurEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_LEAF_STORM,
    MOVE_UNAVAILABLE
};

static const u16 sIvysaurEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_LEAF_STORM,
    MOVE_UNAVAILABLE
};

static const u16 sVenusaurEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_LEAF_STORM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_BULBASAUR

#if P_FAMILY_CHARMANDER
static const u16 sCharizardEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_HOLD_HANDS,
    MOVE_ANCIENT_POWER,
    // Custom
    MOVE_RAGING_FURY,
    MOVE_SEARING_SHOT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CHARMANDER

#if P_FAMILY_SQUIRTLE
static const u16 sBlastoiseEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_FOLLOW_ME,
    MOVE_AURA_SPHERE,
    MOVE_FAKE_OUT,
    MOVE_MUDDY_WATER,
    MOVE_WATER_SPOUT,
    MOVE_ZAP_CANNON,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SQUIRTLE

#if P_FAMILY_PIKACHU
static const u16 sPikachuEventLearnset[] =
{
    MOVE_ENDEAVOR,
    MOVE_EXTREME_SPEED,
    MOVE_SURF,
    MOVE_YAWN,
    MOVE_ENCORE,
    MOVE_FAKE_OUT,
    MOVE_NASTY_PLOT,
    MOVE_SING,
    MOVE_UNAVAILABLE
};

static const u16 sRaichuEventLearnset[] =
{
    MOVE_ENDEAVOR,
    MOVE_EXTREME_SPEED,
    MOVE_SURF,
    MOVE_YAWN,
    MOVE_ENCORE,
    MOVE_FAKE_OUT,
    MOVE_NASTY_PLOT,
    MOVE_SING,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_PIKACHU

#if P_FAMILY_NIDORAN
static const u16 sNidoqueenEventLearnset[] =
{
    MOVE_SUCKER_PUNCH,
    MOVE_HORN_DRILL,
    MOVE_LOVELY_KISS,
    MOVE_MOONLIGHT,
    MOVE_COUNTER,
    MOVE_UNAVAILABLE
};

static const u16 sNidokingEventLearnset[] =
{
    MOVE_LOVELY_KISS,
    MOVE_MORNING_SUN,
    MOVE_COUNTER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_NIDORAN

#if P_FAMILY_POLIWAG
static const u16 sPoliwrathEventLearnset[] =
{
    MOVE_LOVELY_KISS,
    MOVE_BELLY_DRUM,
    MOVE_UNAVAILABLE
};

#if P_GEN_2_CROSS_EVOS
static const u16 sPolitoedEventLearnset[] =
{
    MOVE_LOVELY_KISS,
    MOVE_BELLY_DRUM,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_POLIWAG

#if P_FAMILY_ODDISH
static const u16 sVileplumeEventLearnset[] =
{
    MOVE_LEECH_SEED,
    MOVE_AFTER_YOU,
    MOVE_STRENGTH_SAP,
    MOVE_MOONBLAST,
    MOVE_UNAVAILABLE
};

static const u16 sBellossomEventLearnset[] =
{
    MOVE_LEECH_SEED,
    MOVE_AFTER_YOU,
    MOVE_STRENGTH_SAP,
    MOVE_MOONBLAST,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ODDISH

#if P_FAMILY_PSYDUCK
static const u16 sGolduckEventLearnset[] =
{
    MOVE_PETAL_DANCE,
    MOVE_CROSS_CHOP,
    MOVE_HYPNOSIS,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_PSYDUCK

#if P_FAMILY_MACHOP
static const u16 sMachampEventLearnset[] =
{
    MOVE_BULLET_PUNCH,
    MOVE_HEAVY_SLAM,
    // CUstom
    MOVE_MACH_PUNCH,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MACHOP

#if P_FAMILY_TENTACOOL
static const u16 sTentacruelEventLearnset[] =
{
    MOVE_AURORA_BEAM,
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_TENTACOOL

#if P_FAMILY_GEODUDE
static const u16 sGolemEventLearnset[] =
{
    MOVE_AUTOTOMIZE,
    MOVE_WIDE_GUARD,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GEODUDE

#if P_FAMILY_SLOWPOKE
static const u16 sSlowbroEventLearnset[] =
{
    MOVE_BELLY_DRUM,
    MOVE_BLOCK,
    MOVE_UNAVAILABLE
};

#if P_GEN_2_CROSS_EVOS
static const u16 sSlowkingEventLearnset[] =
{
    MOVE_BELLY_DRUM,
    MOVE_BLOCK,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_SLOWPOKE

#if P_FAMILY_MAGNEMITE
static const u16 sMagnezoneEventLearnset[] =
{
    MOVE_ELECTROWEB,
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MAGNEMITE

#if P_FAMILY_DODUO
static const u16 sDodrioEventLearnset[] =
{
    MOVE_QUICK_ATTACK,
    MOVE_SUPERSONIC,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DODUO

#if P_FAMILY_SEEL
static const u16 sDewgongEventLearnset[] =
{
    MOVE_ENCORE,
    MOVE_IRON_TAIL,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SEEL

#if P_FAMILY_GRIMER
static const u16 sMukEventLearnset[] =
{
    MOVE_CURSE,
    MOVE_SHADOW_SNEAK,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GRIMER

#if P_FAMILY_SHELLDER
static const u16 sCloysterEventLearnset[] =
{
    MOVE_BUBBLE_BEAM,
    MOVE_TWINEEDLE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SHELLDER

#if P_FAMILY_GASTLY
static const u16 sGastlyEventLearnset[] =
{
    MOVE_SLUDGE_WAVE,
    MOVE_CLEAR_SMOG,
    MOVE_DISABLE,
    MOVE_HAZE,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};
static const u16 sHaunterEventLearnset[] =
{
    MOVE_SLUDGE_WAVE,
    MOVE_CLEAR_SMOG,
    MOVE_DISABLE,
    MOVE_HAZE,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};

static const u16 sGengarEventLearnset[] =
{
    MOVE_SLUDGE_WAVE,
    MOVE_CLEAR_SMOG,
    MOVE_DISABLE,
    MOVE_HAZE,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GASTLY

#if P_FAMILY_ONIX
static const u16 sSteelixEventLearnset[] =
{
    MOVE_BLOCK,
    MOVE_DEFENSE_CURL,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ONIX

#if P_FAMILY_DROWZEE
static const u16 sHypnoEventLearnset[] =
{
    MOVE_BELLY_DRUM,
    MOVE_WISH,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DROWZEE

#if P_FAMILY_KRABBY
static const u16 sKinglerEventLearnset[] =
{
    MOVE_AGILITY,
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_KRABBY

#if P_FAMILY_EXEGGCUTE
static const u16 sExeggutorEventLearnset[] =
{
    MOVE_ANCIENT_POWER,
    MOVE_SYNTHESIS,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_EXEGGCUTE

#if P_FAMILY_HITMONS
static const u16 sHitmonchanEventLearnset[] =
{
    // Custom
    MOVE_METEOR_MASH,
    MOVE_SHADOW_PUNCH,
    MOVE_UNAVAILABLE
};

static const u16 sHitmonleeEventLearnset[] =
{
    // Custom
    MOVE_THUNDEROUS_KICK,
    MOVE_TRIPLE_AXEL,
    MOVE_TROP_KICK,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HITMONS

#if P_FAMILY_CUBONE
static const u16 sMarowakEventLearnset[] =
{
    MOVE_BELLY_DRUM,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CUBONE

#if P_FAMILY_LICKITUNG
static const u16 sLickilickyEventLearnset[] =
{
    MOVE_HEAL_BELL,
    MOVE_WISH,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_LICKITUNG

#if P_FAMILY_CHANSEY
static const u16 sChanseyEventLearnset[] =
{
    MOVE_WISH,
    MOVE_AROMATHERAPY,
    // Custom
    MOVE_WISH,
    MOVE_UNAVAILABLE
};

static const u16 sBlisseyEventLearnset[] =
{
    MOVE_WISH,
    MOVE_AROMATHERAPY,
    // Custom
    MOVE_WISH,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CHANSEY

#if P_FAMILY_TANGELA
static const u16 sTangrowthEventLearnset[] =
{
    MOVE_LEECH_SEED,
    MOVE_REFLECT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_TANGELA

#if P_FAMILY_KANGASKHAN
static const u16 sKangaskhanEventLearnset[] =
{
    MOVE_WISH,
    MOVE_YAWN,
    // Custom
    MOVE_CLOSE_COMBAT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_KANGASKHAN

#if P_FAMILY_HORSEA
static const u16 sKingdraEventLearnset[] =
{
    MOVE_HAZE,
    // Custom
    MOVE_SNIPE_SHOT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HORSEA

#if P_FAMILY_GOLDEEN
static const u16 sSeakingEventLearnset[] =
{
    MOVE_SWORDS_DANCE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GOLDEEN

#if P_FAMILY_STARYU
static const u16 sStarmieEventLearnset[] =
{
    MOVE_AURORA_BEAM,
    MOVE_MINIMIZE,
    // Custom
    MOVE_AQUA_STEP,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_STARYU

#if P_FAMILY_MR_MIME
#if P_GALARIAN_FORMS
static const u16 sMrRimeEventLearnset[] =
{
    MOVE_FAKE_OUT,
    MOVE_TICKLE,
    MOVE_UNAVAILABLE
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_MR_MIME

#if P_FAMILY_SCYTHER
static const u16 sScizorEventLearnset[] =
{
    MOVE_BUG_BITE,
    MOVE_COUNTER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SCYTHER

#if P_FAMILY_PINSIR
static const u16 sPinsirEventLearnset[] =
{
    MOVE_QUICK_ATTACK,
    MOVE_SUPERPOWER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_PINSIR

#if P_FAMILY_TAUROS
static const u16 sTaurosEventLearnset[] =
{
    MOVE_DOUBLE_EDGE,
    MOVE_IRON_TAIL,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_TAUROS

#if P_FAMILY_MAGIKARP
static const u16 sGyaradosEventLearnset[] =
{
    MOVE_BOUNCE,
    MOVE_REVERSAL,
    // Custom
    // MOVE_DRAGON_ASCENT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MAGIKARP

#if P_FAMILY_LAPRAS
static const u16 sLaprasEventLearnset[] =
{
    MOVE_CURSE,
    MOVE_FISSURE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_LAPRAS

#if P_FAMILY_EEVEE
static const u16 sEeveeEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_GROWTH,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};

static const u16 sVaporeonEventLearnset[] =
{
    MOVE_AURORA_BEAM,
    MOVE_CELEBRATE,
    MOVE_GROWTH,
    MOVE_HAZE,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};

static const u16 sJolteonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_DOUBLE_KICK,
    MOVE_GROWTH,
    MOVE_PIN_MISSILE,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};

static const u16 sFlareonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_COVET,
    MOVE_GROWTH,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};

#if P_GEN_2_CROSS_EVOS
static const u16 sEspeonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_GROWTH,
    MOVE_HEAL_BELL,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};

static const u16 sUmbreonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_COVET,
    MOVE_GROWTH,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_2_CROSS_EVOS

#if P_GEN_4_CROSS_EVOS
static const u16 sLeafeonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_CHARM,
    MOVE_COVET,
    MOVE_GROWTH,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};

static const u16 sGlaceonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_CHARM,
    MOVE_COVET,
    MOVE_GROWTH,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_4_CROSS_EVOS

#if P_GEN_6_CROSS_EVOS
static const u16 sSylveonEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_CHARM,
    MOVE_COVET,
    MOVE_GROWTH,
    MOVE_STORED_POWER,
    MOVE_YAWN,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_6_CROSS_EVOS
#endif //P_FAMILY_EEVEE

#if P_FAMILY_PORYGON
#if P_GEN_4_CROSS_EVOS
static const u16 sPorygonZEventLearnset[] =
{
    MOVE_TRICK,
    MOVE_ZAP_CANNON,
    // Custom
    MOVE_AURA_SPHERE,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_PORYGON

#if P_FAMILY_OMANYTE
static const u16 sOmastarEventLearnset[] =
{
    MOVE_AURORA_BEAM,
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_OMANYTE

#if P_FAMILY_KABUTO
static const u16 sKabutopsEventLearnset[] =
{
    MOVE_AURORA_BEAM,
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_KABUTO

#if P_FAMILY_AERODACTYL
static const u16 sAerodactylEventLearnset[] =
{
    MOVE_AQUA_TAIL,
    MOVE_ROOST,
    // Custom
    MOVE_BRAVE_BIRD,
    MOVE_HEAD_SMASH,
    MOVE_WILD_CHARGE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_AERODACTYL

#if P_FAMILY_SNORLAX
static const u16 sSnorlaxEventLearnset[] =
{
    MOVE_LOVELY_KISS,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SNORLAX

#if P_FAMILY_ARTICUNO
static const u16 sArticunoEventLearnset[] =
{
    MOVE_HEAL_BELL,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ARTICUNO

#if P_FAMILY_ZAPDOS
static const u16 sZapdosEventLearnset[] =
{
    MOVE_BATON_PASS,
    MOVE_EXTRASENSORY,
    MOVE_METAL_SOUND,
    MOVE_REFLECT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ZAPDOS

#if P_FAMILY_MOLTRES
static const u16 sMoltresEventLearnset[] =
{
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MOLTRES

#if P_FAMILY_DRATINI
static const u16 sDragoniteEventLearnset[] =
{
    MOVE_EXTREME_SPEED,
    MOVE_WATER_PULSE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DRATINI

#if P_FAMILY_MEWTWO
static const u16 sMewtwoEventLearnset[] =
{
    MOVE_HEAL_PULSE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MEWTWO

#if P_FAMILY_MEW
static const u16 sMewEventLearnset[] =
{
    MOVE_AMNESIA,
    MOVE_HYPNOSIS,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MEW

#if P_FAMILY_CHIKORITA
static const u16 sMeganiumEventLearnset[] =
{
    MOVE_PETAL_DANCE,
    MOVE_SWORDS_DANCE,
    MOVE_LEECH_SEED,
    // Custom
    MOVE_DRAINING_KISS,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CHIKORITA

#if P_FAMILY_CYNDAQUIL
static const u16 sTyphlosionEventLearnset[] =
{
    MOVE_DOUBLE_EDGE,
    MOVE_FURY_SWIPES,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CYNDAQUIL

#if P_FAMILY_TOTODILE
static const u16 sFeraligatrEventLearnset[] =
{
    MOVE_SUBMISSION,
    MOVE_CRUNCH,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_TOTODILE

#if P_FAMILY_SENTRET
static const u16 sFurretEventLearnset[] =
{
    MOVE_ASSIST,
    MOVE_SLASH,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SENTRET

#if P_FAMILY_HOOTHOOT
static const u16 sNoctowlEventLearnset[] =
{
    MOVE_HYPNOSIS,
    MOVE_NIGHT_SHADE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HOOTHOOT

#if P_FAMILY_LEDYBA
static const u16 sLedianEventLearnset[] =
{
    MOVE_ENCORE,
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_LEDYBA

#if P_FAMILY_SPINARAK
static const u16 sAriadosEventLearnset[] =
{
    MOVE_BATON_PASS,
    MOVE_PURSUIT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SPINARAK

#if P_FAMILY_CHINCHOU
static const u16 sLanturnEventLearnset[] =
{
    MOVE_AMNESIA,
    MOVE_SCREECH,
    // Custom
    MOVE_PARABOLIC_CHARGE,
    MOVE_SPARKLING_ARIA,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CHINCHOU

#if P_FAMILY_TOGEPI
static const u16 sTogekissEventLearnset[] =
{
    MOVE_EXTRASENSORY,
    MOVE_PRESENT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_TOGEPI

#if P_FAMILY_NATU
static const u16 sXatuEventLearnset[] =
{
    MOVE_HAZE,
    MOVE_QUICK_ATTACK,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_NATU

#if P_FAMILY_MAREEP
static const u16 sAmpharosEventLearnset[] =
{
    MOVE_AGILITY,
    MOVE_BODY_SLAM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MAREEP

#if P_FAMILY_MARILL
static const u16 sAzumarillEventLearnset[] =
{
    MOVE_HYDRO_PUMP,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MARILL

#if P_FAMILY_SUDOWOODO
static const u16 sSudowoodoEventLearnset[] =
{
    MOVE_DEFENSE_CURL,
    MOVE_SELF_DESTRUCT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SUDOWOODO

#if P_FAMILY_HOPPIP
static const u16 sJumpluffEventLearnset[] =
{
    MOVE_AMNESIA,
    MOVE_ENCORE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HOPPIP

#if P_FAMILY_AIPOM
static const u16 sAmbipomEventLearnset[] =
{
    MOVE_COUNTER,
    MOVE_DOUBLE_SLAP,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_AIPOM

#if P_FAMILY_SUNKERN
static const u16 sSunfloraEventLearnset[] =
{
    MOVE_ENCORE,
    MOVE_INGRAIN,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SUNKERN

#if P_FAMILY_YANMA
static const u16 sYanmegaEventLearnset[] =
{
    MOVE_WHIRLWIND,
    MOVE_REVERSAL,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_YANMA

#if P_FAMILY_WOOPER
static const u16 sQuagsireEventLearnset[] =
{
    MOVE_BELLY_DRUM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_WOOPER

#if P_FAMILY_MURKROW
static const u16 sHonchkrowEventLearnset[] =
{
    MOVE_BRAVE_BIRD,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MURKROW

#if P_FAMILY_MISDREAVUS
static const u16 sMismagiusEventLearnset[] =
{
    MOVE_HYPNOSIS,
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MISDREAVUS

#if P_FAMILY_UNOWN
static const u16 sUnownEventLearnset[] =
{
    MOVE_HIDDEN_POWER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_UNOWN

#if P_FAMILY_WOBBUFFET
static const u16 sWobbuffetEventLearnset[] =
{
    MOVE_COUNTER,
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_WOBBUFFET

#if P_FAMILY_GIRAFARIG
static const u16 sGirafarigEventLearnset[] =
{
    MOVE_AMNESIA,
    MOVE_BEAT_UP,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GIRAFARIG

#if P_FAMILY_PINECO
static const u16 sForretressEventLearnset[] =
{
    MOVE_FLAIL,
    MOVE_REFLECT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_PINECO

#if P_FAMILY_DUNSPARCE
static const u16 sDunsparceEventLearnset[] =
{
    MOVE_BITE,
    MOVE_HEADBUTT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DUNSPARCE

#if P_FAMILY_GLIGAR
static const u16 sGliscorEventLearnset[] =
{
    MOVE_BATON_PASS,
    MOVE_COUNTER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GLIGAR

#if P_FAMILY_SNUBBULL
static const u16 sGranbullEventLearnset[] =
{
    MOVE_HEAL_BELL,
    MOVE_PRESENT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SNUBBULL

#if P_FAMILY_QWILFISH
static const u16 sQwilfishEventLearnset[] =
{
    MOVE_ASTONISH,
    MOVE_BUBBLE_BEAM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_QWILFISH

#if P_FAMILY_SHUCKLE
static const u16 sShuckleEventLearnset[] =
{
    MOVE_HELPING_HAND,
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SHUCKLE

#if P_FAMILY_HERACROSS
static const u16 sHeracrossEventLearnset[] =
{
    MOVE_BIDE,
    MOVE_FALSE_SWIPE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HERACROSS

#if P_FAMILY_SNEASEL
static const u16 sWeavileEventLearnset[] =
{
    MOVE_BITE,
    MOVE_COUNTER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SNEASEL

#if P_FAMILY_TEDDIURSA
static const u16 sUrsaringEventLearnset[] =
{
    MOVE_CRUNCH,
    MOVE_TAKE_DOWN,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_TEDDIURSA

#if P_FAMILY_SLUGMA
static const u16 sMagcargoEventLearnset[] =
{
    MOVE_HEAT_WAVE,
    MOVE_SMOKESCREEN,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SLUGMA

#if P_FAMILY_SWINUB
static const u16 sPiloswineEventLearnset[] =
{
    MOVE_ANCIENT_POWER,
    MOVE_ICICLE_SPEAR,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SWINUB

#if P_FAMILY_CORSOLA
static const u16 sCorsolaEventLearnset[] =
{
    MOVE_AMNESIA,
    MOVE_BARRIER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CORSOLA

#if P_FAMILY_REMORAID
static const u16 sOctilleryEventLearnset[] =
{
    MOVE_AURORA_BEAM,
    MOVE_OCTAZOOKA,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_REMORAID

#if P_FAMILY_DELIBIRD
static const u16 sDelibirdEventLearnset[] =
{
    MOVE_SPIKES,
    MOVE_RAPID_SPIN,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DELIBIRD

#if P_FAMILY_MANTINE
static const u16 sMantineEventLearnset[] =
{
    MOVE_AMNESIA,
    MOVE_TWISTER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MANTINE

#if P_FAMILY_SKARMORY
static const u16 sSkarmoryEventLearnset[] =
{
    MOVE_CURSE,
    MOVE_WHIRLWIND,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SKARMORY

#if P_FAMILY_PHANPY
static const u16 sDonphanEventLearnset[] =
{
    MOVE_ENCORE,
    MOVE_BODY_SLAM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_PHANPY

#if P_FAMILY_STANTLER
static const u16 sStantlerEventLearnset[] =
{
    MOVE_BITE,
    MOVE_DISABLE,
    MOVE_UNAVAILABLE
};

#if P_GEN_8_CROSS_EVOS
static const u16 sWyrdeerEventLearnset[] =
{
    MOVE_BITE,
    MOVE_DISABLE,
    MOVE_UNAVAILABLE
};
#endif //P_GEN_8_CROSS_EVOS
#endif //P_FAMILY_STANTLER

#if P_FAMILY_RAIKOU
static const u16 sRaikouEventLearnset[] =
{
    MOVE_AURA_SPHERE,
    MOVE_EXTREME_SPEED,
    MOVE_WEATHER_BALL,
    MOVE_DETECT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_RAIKOU

#if P_FAMILY_ENTEI
static const u16 sEnteiEventLearnset[] =
{
    MOVE_EXTREME_SPEED,
    MOVE_HOWL,
    MOVE_FLARE_BLITZ,
    MOVE_CURSE,
    MOVE_DETECT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ENTEI

#if P_FAMILY_SUICUNE
static const u16 sSuicuneEventLearnset[] =
{
    MOVE_EXTREME_SPEED,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SUICUNE

#if P_FAMILY_LARVITAR
static const u16 sTyranitarEventLearnset[] =
{
    MOVE_ANCIENT_POWER,
    MOVE_DRAGON_DANCE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_LARVITAR

#if P_FAMILY_LUGIA
static const u16 sLugiaEventLearnset[] =
{
    MOVE_AEROBLAST,
    MOVE_PSYCHIC,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_LUGIA

#if P_FAMILY_HO_OH
static const u16 sHoOhEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_CURSE,
    MOVE_DETECT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HO_OH

#if P_FAMILY_CELEBI
static const u16 sCelebiEventLearnset[] =
{
    MOVE_NASTY_PLOT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CELEBI

#if P_FAMILY_CARVANHA
static const u16 sSharpedoEventLearnset[] =
{
    // Custom
    MOVE_FISHIOUS_REND,
    MOVE_JAW_LOCK,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CARVANHA

#if P_FAMILY_CACNEA
static const u16 sCacturneEventLearnset[] =
{
    MOVE_ENCORE,
    MOVE_NASTY_PLOT,
    MOVE_SWITCHEROO,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_CACNEA

#if P_FAMILY_RAYQUAZA
static const u16 sRayquazaEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_V_CREATE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_RAYQUAZA

#if P_FAMILY_DEOXYS
static const u16 sDeoxysEventLearnset[] =
{
    MOVE_METEOR_MASH,
    MOVE_NASTY_PLOT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DEOXYS

#if P_FAMILY_JIRACHI
static const u16 sJirachiEventLearnset[] =
{
    MOVE_DRACO_METEOR,
    MOVE_FOLLOW_ME,
    MOVE_HAPPY_HOUR,
    MOVE_HEART_STAMP,
    MOVE_MOONBLAST,
    MOVE_PLAY_ROUGH,
    MOVE_BODY_SLAM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_JIRACHI

#if P_FAMILY_GIBLE
static const u16 sGarchompEventLearnset[] =
{
    // Custom
    MOVE_DRAGON_DANCE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GIBLE

#if P_FAMILY_HEATRAN
static const u16 sHeatranEventLearnset[] =
{
    MOVE_ERUPTION,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_HEATRAN

#if P_FAMILY_DARKRAI
static const u16 sDarkraiEventLearnset[] =
{
    MOVE_SPACIAL_REND,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DARKRAI

#if P_FAMILY_SHAYMIN
static const u16 sShayminLandEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_UNAVAILABLE
};

static const u16 sShayminSkyEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_SHAYMIN

#if P_FAMILY_ARCEUS
static const u16 sArceusEventLearnset[] =
{
    MOVE_SHADOW_FORCE,
    MOVE_SPACIAL_REND,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ARCEUS

#if P_FAMILY_VICTINI
static const u16 sVictiniEventLearnset[] =
{
    MOVE_BLUE_FLARE,
    MOVE_BOLT_STRIKE,
    MOVE_CELEBRATE,
    MOVE_FUSION_BOLT,
    MOVE_FUSION_FLARE,
    MOVE_GLACIATE,
    MOVE_V_CREATE,
    // Custom
    MOVE_PSYCHIC_FANGS,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_VICTINI

#if P_FAMILY_ZORUA
static const u16 sZoroarkEventLearnset[] =
{
    MOVE_SLUDGE_BOMB,
    MOVE_DETECT,
    MOVE_FAKE_TEARS,
    MOVE_MEMENTO,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ZORUA

#if P_FAMILY_DEINO
static const u16 sHydreigonEventLearnset[] =
{
    // Custom
    MOVE_FICKLE_BEAM,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_DEINO

#if P_FAMILY_RESHIRAM
static const u16 sReshiramEventLearnset[] =
{
    // Custom
    MOVE_EARTH_POWER,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_RESHIRAM

#if P_FAMILY_ZEKROM
static const u16 sZekromEventLearnset[] =
{
    MOVE_HAZE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_ZEKROM

#if P_FAMILY_MELOETTA
static const u16 sMeloettaEventLearnset[] =
{
    MOVE_CELEBRATE,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_MELOETTA

#if P_FAMILY_GENESECT
static const u16 sGenesectEventLearnset[] =
{
    MOVE_BLAZE_KICK,
    MOVE_EXTREME_SPEED,
    MOVE_SHIFT_GEAR,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_GENESECT

#if P_FAMILY_FROAKIE
static const u16 sGreninjaEventLearnset[] =
{
    MOVE_HAPPY_HOUR,
    MOVE_TOXIC_SPIKES,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_FROAKIE

#if P_FAMILY_LITTEN
static const u16 sIncineroarEventLearnset[] =
{
    // Custom
    MOVE_ENTRAINMENT,
    MOVE_UNAVAILABLE
};
#endif //P_FAMILY_LITTEN
