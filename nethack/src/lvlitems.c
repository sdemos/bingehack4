/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/
/* Copyright (c) Daniel Thaler, 2011.                             */
/* NetHack may be freely redistributed.  See license for details. */

#include "nhcurses.h"


static struct nh_objitems *lvlitems_list;
static int lvlitems_icount;


void
draw_lvlitems(void)
{
    if (!ui_flags.draw_lvlitems)
        return;

    mvwaddstr(lvlitems, 0, 0, "This is my new window");

    wnoutrefresh(lvlitems);
}

void
cleanup_lvlitems(nh_bool dealloc)
{
}
