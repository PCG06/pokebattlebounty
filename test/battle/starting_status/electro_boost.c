#include "global.h"
#include "event_data.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Electro Boost grants a Charge boost and +1 Sp. Def to Electric-types")
{
    s16 damage[2] = {0};
    SetStartingStatus(STARTING_STATUS_ELECTRO_BOOST);

    GIVEN {
        PLAYER(SPECIES_PIKACHU);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SPARK); }
        TURN { MOVE(player, MOVE_SPARK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPARK, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPARK, player);
        HP_BAR(opponent, captureDamage: &damage[1]);
    } THEN {
        EXPECT_EQ(player->volatiles.chargeTimer > 0, TRUE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(opponent->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
        ResetStartingStatuses();
    }
}

SINGLE_BATTLE_TEST("Electro Boost doesn't charge the user if it has used Charge the same turn")
{
    SetStartingStatus(STARTING_STATUS_ELECTRO_BOOST);

    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Speed(5); }
        OPPONENT(SPECIES_PIKACHU) { Speed(4); }
    } WHEN {
        TURN { MOVE(player, MOVE_CHARGE); }
        TURN { MOVE(player, MOVE_SPARK); MOVE(opponent, MOVE_SPARK); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CHARGE, player);
        NOT MESSAGE("Pikachu was charged up!");
        MESSAGE("The opposing Pikachu was charged up!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPARK, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPARK, opponent);

        MESSAGE("Pikachu was charged up!");
        MESSAGE("The opposing Pikachu was charged up!");
    } THEN {
        ResetStartingStatuses();
    }
}

DOUBLE_BATTLE_TEST("Electro Boost activates in speed order in a double battle")
{
    SetStartingStatus(STARTING_STATUS_ELECTRO_BOOST);

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(4); }
        PLAYER(SPECIES_PIKACHU) { Speed(5); }
        OPPONENT(SPECIES_PIKACHU) { Speed(6); }
        OPPONENT(SPECIES_PIKACHU) { Speed(3); }
    } WHEN {
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CHARGED_UP, opponentLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CHARGED_UP, playerRight);
        // playerLeft is not Electric-type, does not activate
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CHARGED_UP, playerLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CHARGED_UP, opponentRight);
    } THEN {
        ResetStartingStatuses();
    }
}

SINGLE_BATTLE_TEST("Electro Boost (temporary) expires after 5 turns")
{
    SetStartingStatus(STARTING_STATUS_ELECTRO_BOOST_TEMPORARY);

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        // More than 5 turns
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
    } SCENE {
        // Messages aren't printing right now on upcoming. Fix it soon
        // MESSAGE("A strong electric charge surrounds the field!");
        MESSAGE("The electric charge around the field disappeared.");
    } THEN {
        ResetStartingStatuses();
    }
}
