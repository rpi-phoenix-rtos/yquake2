/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Refresh common initialization code
 *
 * =======================================================================
 */

#include "../ref_shared.h"

#define MAXPRINTMSG 4096

/*
 * this is only here so the functions in shared source files
 * (shared.c, rand.c, flash.c, mem.c/hunk.c) can link
 */
void
R_Printf(int level, const char* msg, ...)
{
	va_list argptr;
	va_start(argptr, msg);
	ri.Com_VPrintf(level, msg, argptr);
	va_end(argptr);
}

/*
 * Phoenix single-ELF port: the renderer is linked into the same binary as
 * the engine, so Sys_Error / Com_Printf / Com_DPrintf / Com_Error resolve
 * directly to the engine's real implementations. The .so-era forwarders
 * that used to live here (routing through ri.* because a separate ref_*.so
 * could not see the engine's symbols) are dropped to avoid multiple-
 * definition with the engine copies. R_Printf above still routes through
 * ri.Com_VPrintf, which is the renderer's public print entry point.
 */

/* shared variables */
refdef_t r_newrefdef;
viddef_t vid;
