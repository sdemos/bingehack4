/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/
/* Copyright (c) Stephen Demos, 2015.                             */
/* NetHack may be freely redistributed.  See license for details. */

#include "nhcurses.h"

static struct nh_dbuf_entry *legend_list;
static int legend_icount;

void
draw_legend(void)
{
    if (!ui_flags.draw_legend)
        return;

    werase(legend);

    const struct nh_drawing_info *di = nh_get_drawing_info();
 
    wattron(legend, A_UNDERLINE);
    mvwaddstr(legend, 0, 0, "Legend:");
    wattroff(legend, A_UNDERLINE);

    // print out things that are on the screen here
    int i;
    for (i = 0; i < legend_icount; i++) {
        mvwaddstr(legend, i+1, 0, di->objects[legend_list[i].obj].symname);
    }
    //char buf[16];
    //sprintf(buf, "%i %i", legend_list->obj, legend_icount);
    //mvwaddstr(legend, 1, 0, buf);

    wnoutrefresh(legend);
}

void
curses_update_legend(struct nh_dbuf_entry * items, int icount)
{
    legend_list = items;
    legend_icount = icount;
    draw_legend();
}

void
cleanup_legend(nh_bool dealloc)
{
    delwin(legend);
    legend = NULL;
}
