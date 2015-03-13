/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/
/* Copyright (c) Stephen Demos, 2015.                             */
/* NetHack may be freely redistributed.  See license for details. */

#include "nhcurses.h"

static struct nh_objitems *legend_list;
static int legend_icount;

void
draw_legend(void)
{
//    if (!ui_flags.draw_legend)
//        return;

    werase(legend);

    mvwaddstr(legend, 0, 0, "This is my new window");

    wnoutrefresh(legend);
}

void
cleanup_legend(nh_bool dealloc)
{
    if (dealloc) {
        free(legend_list);
        legend_list = NULL;
    }
    delwin(legend);
    legend = NULL;
}
