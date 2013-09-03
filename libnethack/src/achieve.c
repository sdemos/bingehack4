/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>

#include "hack.h"
#include "config.h"
#include "achieve.h"

static bool s

void
init_achievements(){
    int i;
    for (i = 0; i < sizeof(achievement_progress); i++) {
        achievement_progress[i] = 0;
        switch(i){
        case AID_DJINN_WISHES:
        case AID_KILL_GHOSTS:
        case AID_ASCEND_THRICE:
            achievement_max[i] = 3;
            break;
        case AID_RESURRECT_PLAYERS:
            achievement_max[i] = 4;
            break;
        case AID_GENOCIDES:
            achievement_max[i] = 5;
            break;
        case AID_KILL_DRAGONS:
            achievement_max[i] = 10;
        case AID_FALL_DOWN_STAIRS:
            achievement_max[i] = 20;
            break;
        case AID_KILL_GRID_BUGS:
            achievement_max[i] = 50;
            break;
        case AID_KILL_ORCS:
        case AID_KILL_UNDEAD:
            achievement_max[i] = 200;
            break;
        case AID_WALK_5K:
            achievement_max[i] = 5000;
            break;
        case AID_WALK_10K:
            achievement_max[i] = 10000;
            break;
        default:
            achievement_max[i] = 1;
            break;
        }
    }
}

int
award_achievement(int achievement_id) {
    return add_achievement_progress(achievement_id, get_achievement_max_progress(achievement_id));
}

int
add_achievement_progress(int achievement_id, int add_progress) {
    if (achievement_progress[achievement_id] >= achievement_max[achievement_id]) {
        return ACHIEVEMENT_PUSH_SUCCESS;
    } else {
        achievement_progress[achievement_id] += add_progress;
        if (achievement_progress[achievement_id] >= achievement_max[achievement_id]) {
            pline("You've earned some achievement! Yay!");
        }
    }
    return ACHIEVEMENT_PUSH_SUCCESS;
}

int
push_achievement_progress(int achievement_id, int add_progress) {
    return 0; // I don't actually know why this is here, it is just because of the old implementation of this. 
}

int
get_achievement_progress(int achievement_id) {
    return achievement_progress[achievement_id];
}

int
get_achievement_max_progress(int achievement_id) {
    return achievement_max[achievement_id];
}


