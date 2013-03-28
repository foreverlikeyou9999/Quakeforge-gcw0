/*
	keys.c

	(description)

	Copyright (C) 1996-1997  Id Software, Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "QF/cbuf.h"
#include "QF/cmd.h"
#include "QF/console.h"
#include "QF/csqc.h"
#include "QF/cvar.h"
#include "QF/keys.h"
#include "QF/screen.h"
#include "QF/sys.h"
#include "QF/zone.h"
#include "QF/gib.h"

#include "compat.h"
#include "old_keys.h"

#define U __attribute__ ((used))
static U void (*const key_progs_init)(struct progs_s *) = Key_Progs_Init;
#undef U

/*  key up events are sent even if in console mode */

static keydest_t    key_dest = key_console;
static keytarget_t  key_targets[key_last];
VISIBLE knum_t      key_togglemenu = QFK_ESCAPE;
VISIBLE knum_t      key_toggleconsole = QFK_BACKQUOTE;

#define KEYDEST_CALLBACK_CHUNK 16
static keydest_callback_t **keydest_callbacks;
static int num_keydest_callbacks;
static int max_keydest_callbacks;

VISIBLE int			keydown[QFK_LAST];

static int  keyhelp;
static cbuf_t *cbuf;

static const char *keydest_names[] = {
	"key_unfocused",
	"key_game",
	"key_demo",
	"key_console",
	"key_message",
	"key_menu",

	"key_last"
};


typedef struct {
	const char *name;
	imt_t	imtnum;
} imtname_t;

typedef struct {
	const char *name;
	knum_t	keynum;
} keyname_t;

keyname_t   keynames[] = {
	{ "K_UNKNOWN",		QFK_UNKNOWN },
	{ "K_FIRST",		QFK_FIRST },
	{ "K_BACKSPACE",	QFK_BACKSPACE },
	{ "K_TAB",			QFK_TAB },
	{ "K_CLEAR",		QFK_CLEAR },
	{ "K_RETURN",		QFK_RETURN },
	{ "K_PAUSE",		QFK_PAUSE },
	{ "K_ESCAPE",		QFK_ESCAPE },
	{ "K_SPACE",		QFK_SPACE },
	{ "K_EXCLAIM",		QFK_EXCLAIM },
	{ "K_QUOTEDBL",		QFK_QUOTEDBL },
	{ "K_HASH",			QFK_HASH },
	{ "K_DOLLAR",		QFK_DOLLAR },
	{ "K_PERCENT",		QFK_PERCENT },
	{ "K_AMPERSAND",	QFK_AMPERSAND },
	{ "K_QUOTE",		QFK_QUOTE },
	{ "K_LEFTPAREN",	QFK_LEFTPAREN },
	{ "K_RIGHTPAREN",	QFK_RIGHTPAREN },
	{ "K_ASTERISK",		QFK_ASTERISK },
	{ "K_PLUS",			QFK_PLUS },
	{ "K_COMMA",		QFK_COMMA },
	{ "K_MINUS",		QFK_MINUS },
	{ "K_PERIOD",		QFK_PERIOD },
	{ "K_SLASH",		QFK_SLASH },
	{ "K_0",			QFK_0 },
	{ "K_1",			QFK_1 },
	{ "K_2",			QFK_2 },
	{ "K_3",			QFK_3 },
	{ "K_4",			QFK_4 },
	{ "K_5",			QFK_5 },
	{ "K_6",			QFK_6 },
	{ "K_7",			QFK_7 },
	{ "K_8",			QFK_8 },
	{ "K_9",			QFK_9 },
	{ "K_COLON",		QFK_COLON },
	{ "K_SEMICOLON",	QFK_SEMICOLON },
	{ "K_LESS",			QFK_LESS },
	{ "K_EQUALS",		QFK_EQUALS },
	{ "K_GREATER",		QFK_GREATER },
	{ "K_QUESTION",		QFK_QUESTION },
	{ "K_AT",			QFK_AT },
	{ "K_LEFTBRACKET",	QFK_LEFTBRACKET },
	{ "K_BACKSLASH",	QFK_BACKSLASH },
	{ "K_RIGHTBRACKET",	QFK_RIGHTBRACKET },
	{ "K_CARET",		QFK_CARET },
	{ "K_UNDERSCORE",	QFK_UNDERSCORE },
	{ "K_BACKQUOTE",	QFK_BACKQUOTE },
	{ "K_a",			QFK_a },
	{ "K_b",			QFK_b },
	{ "K_c",			QFK_c },
	{ "K_d",			QFK_d },
	{ "K_e",			QFK_e },
	{ "K_f",			QFK_f },
	{ "K_g",			QFK_g },
	{ "K_h",			QFK_h },
	{ "K_i",			QFK_i },
	{ "K_j",			QFK_j },
	{ "K_k",			QFK_k },
	{ "K_l",			QFK_l },
	{ "K_m",			QFK_m },
	{ "K_n",			QFK_n },
	{ "K_o",			QFK_o },
	{ "K_p",			QFK_p },
	{ "K_q",			QFK_q },
	{ "K_r",			QFK_r },
	{ "K_s",			QFK_s },
	{ "K_t",			QFK_t },
	{ "K_u",			QFK_u },
	{ "K_v",			QFK_v },
	{ "K_w",			QFK_w },
	{ "K_x",			QFK_x },
	{ "K_y",			QFK_y },
	{ "K_z",			QFK_z },
	{ "K_BRACELEFT",	QFK_BRACELEFT },
	{ "K_BAR",			QFK_BAR },
	{ "K_BRACERIGHT",	QFK_BRACERIGHT },
	{ "K_ASCIITILDE",	QFK_ASCIITILDE },
	{ "K_DELETE",		QFK_DELETE },
	{ "K_WORLD_0",		QFK_WORLD_0 },
	{ "K_WORLD_1",		QFK_WORLD_1 },
	{ "K_WORLD_2",		QFK_WORLD_2 },
	{ "K_WORLD_3",		QFK_WORLD_3 },
	{ "K_WORLD_4",		QFK_WORLD_4 },
	{ "K_WORLD_5",		QFK_WORLD_5 },
	{ "K_WORLD_6",		QFK_WORLD_6 },
	{ "K_WORLD_7",		QFK_WORLD_7 },
	{ "K_WORLD_8",		QFK_WORLD_8 },
	{ "K_WORLD_9",		QFK_WORLD_9 },
	{ "K_WORLD_10",		QFK_WORLD_10 },
	{ "K_WORLD_11",		QFK_WORLD_11 },
	{ "K_WORLD_12",		QFK_WORLD_12 },
	{ "K_WORLD_13",		QFK_WORLD_13 },
	{ "K_WORLD_14",		QFK_WORLD_14 },
	{ "K_WORLD_15",		QFK_WORLD_15 },
	{ "K_WORLD_16",		QFK_WORLD_16 },
	{ "K_WORLD_17",		QFK_WORLD_17 },
	{ "K_WORLD_18",		QFK_WORLD_18 },
	{ "K_WORLD_19",		QFK_WORLD_19 },
	{ "K_WORLD_20",		QFK_WORLD_20 },
	{ "K_WORLD_21",		QFK_WORLD_21 },
	{ "K_WORLD_22",		QFK_WORLD_22 },
	{ "K_WORLD_23",		QFK_WORLD_23 },
	{ "K_WORLD_24",		QFK_WORLD_24 },
	{ "K_WORLD_25",		QFK_WORLD_25 },
	{ "K_WORLD_26",		QFK_WORLD_26 },
	{ "K_WORLD_27",		QFK_WORLD_27 },
	{ "K_WORLD_28",		QFK_WORLD_28 },
	{ "K_WORLD_29",		QFK_WORLD_29 },
	{ "K_WORLD_30",		QFK_WORLD_30 },
	{ "K_WORLD_31",		QFK_WORLD_31 },
	{ "K_WORLD_32",		QFK_WORLD_32 },
	{ "K_WORLD_33",		QFK_WORLD_33 },
	{ "K_WORLD_34",		QFK_WORLD_34 },
	{ "K_WORLD_35",		QFK_WORLD_35 },
	{ "K_WORLD_36",		QFK_WORLD_36 },
	{ "K_WORLD_37",		QFK_WORLD_37 },
	{ "K_WORLD_38",		QFK_WORLD_38 },
	{ "K_WORLD_39",		QFK_WORLD_39 },
	{ "K_WORLD_40",		QFK_WORLD_40 },
	{ "K_WORLD_41",		QFK_WORLD_41 },
	{ "K_WORLD_42",		QFK_WORLD_42 },
	{ "K_WORLD_43",		QFK_WORLD_43 },
	{ "K_WORLD_44",		QFK_WORLD_44 },
	{ "K_WORLD_45",		QFK_WORLD_45 },
	{ "K_WORLD_46",		QFK_WORLD_46 },
	{ "K_WORLD_47",		QFK_WORLD_47 },
	{ "K_WORLD_48",		QFK_WORLD_48 },
	{ "K_WORLD_49",		QFK_WORLD_49 },
	{ "K_WORLD_50",		QFK_WORLD_50 },
	{ "K_WORLD_51",		QFK_WORLD_51 },
	{ "K_WORLD_52",		QFK_WORLD_52 },
	{ "K_WORLD_53",		QFK_WORLD_53 },
	{ "K_WORLD_54",		QFK_WORLD_54 },
	{ "K_WORLD_55",		QFK_WORLD_55 },
	{ "K_WORLD_56",		QFK_WORLD_56 },
	{ "K_WORLD_57",		QFK_WORLD_57 },
	{ "K_WORLD_58",		QFK_WORLD_58 },
	{ "K_WORLD_59",		QFK_WORLD_59 },
	{ "K_WORLD_60",		QFK_WORLD_60 },
	{ "K_WORLD_61",		QFK_WORLD_61 },
	{ "K_WORLD_62",		QFK_WORLD_62 },
	{ "K_WORLD_63",		QFK_WORLD_63 },
	{ "K_WORLD_64",		QFK_WORLD_64 },
	{ "K_WORLD_65",		QFK_WORLD_65 },
	{ "K_WORLD_66",		QFK_WORLD_66 },
	{ "K_WORLD_67",		QFK_WORLD_67 },
	{ "K_WORLD_68",		QFK_WORLD_68 },
	{ "K_WORLD_69",		QFK_WORLD_69 },
	{ "K_WORLD_70",		QFK_WORLD_70 },
	{ "K_WORLD_71",		QFK_WORLD_71 },
	{ "K_WORLD_72",		QFK_WORLD_72 },
	{ "K_WORLD_73",		QFK_WORLD_73 },
	{ "K_WORLD_74",		QFK_WORLD_74 },
	{ "K_WORLD_75",		QFK_WORLD_75 },
	{ "K_WORLD_76",		QFK_WORLD_76 },
	{ "K_WORLD_77",		QFK_WORLD_77 },
	{ "K_WORLD_78",		QFK_WORLD_78 },
	{ "K_WORLD_79",		QFK_WORLD_79 },
	{ "K_WORLD_80",		QFK_WORLD_80 },
	{ "K_WORLD_81",		QFK_WORLD_81 },
	{ "K_WORLD_82",		QFK_WORLD_82 },
	{ "K_WORLD_83",		QFK_WORLD_83 },
	{ "K_WORLD_84",		QFK_WORLD_84 },
	{ "K_WORLD_85",		QFK_WORLD_85 },
	{ "K_WORLD_86",		QFK_WORLD_86 },
	{ "K_WORLD_87",		QFK_WORLD_87 },
	{ "K_WORLD_88",		QFK_WORLD_88 },
	{ "K_WORLD_89",		QFK_WORLD_89 },
	{ "K_WORLD_90",		QFK_WORLD_90 },
	{ "K_WORLD_91",		QFK_WORLD_91 },
	{ "K_WORLD_92",		QFK_WORLD_92 },
	{ "K_WORLD_93",		QFK_WORLD_93 },
	{ "K_WORLD_94",		QFK_WORLD_94 },
	{ "K_WORLD_95",		QFK_WORLD_95 },
	{ "K_KP0",			QFK_KP0 },
	{ "K_KP1",			QFK_KP1 },
	{ "K_KP2",			QFK_KP2 },
	{ "K_KP3",			QFK_KP3 },
	{ "K_KP4",			QFK_KP4 },
	{ "K_KP5",			QFK_KP5 },
	{ "K_KP6",			QFK_KP6 },
	{ "K_KP7",			QFK_KP7 },
	{ "K_KP8",			QFK_KP8 },
	{ "K_KP9",			QFK_KP9 },
	{ "K_KP_PERIOD",	QFK_KP_PERIOD },
	{ "K_KP_DIVIDE",	QFK_KP_DIVIDE },
	{ "K_KP_MULTIPLY",	QFK_KP_MULTIPLY },
	{ "K_KP_MINUS",		QFK_KP_MINUS },
	{ "K_KP_PLUS",		QFK_KP_PLUS },
	{ "K_KP_ENTER",		QFK_KP_ENTER },
	{ "K_KP_EQUALS",	QFK_KP_EQUALS },
	{ "K_UP",			QFK_UP },
	{ "K_DOWN",			QFK_DOWN },
	{ "K_RIGHT",		QFK_RIGHT },
	{ "K_LEFT",			QFK_LEFT },
	{ "K_INSERT",		QFK_INSERT },
	{ "K_HOME",			QFK_HOME },
	{ "K_END",			QFK_END },
	{ "K_PAGEUP",		QFK_PAGEUP },
	{ "K_PAGEDOWN",		QFK_PAGEDOWN },
	{ "K_F1",			QFK_F1 },
	{ "K_F2",			QFK_F2 },
	{ "K_F3",			QFK_F3 },
	{ "K_F4",			QFK_F4 },
	{ "K_F5",			QFK_F5 },
	{ "K_F6",			QFK_F6 },
	{ "K_F7",			QFK_F7 },
	{ "K_F8",			QFK_F8 },
	{ "K_F9",			QFK_F9 },
	{ "K_F10",			QFK_F10 },
	{ "K_F11",			QFK_F11 },
	{ "K_F12",			QFK_F12 },
	{ "K_F13",			QFK_F13 },
	{ "K_F14",			QFK_F14 },
	{ "K_F15",			QFK_F15 },
	{ "K_NUMLOCK",		QFK_NUMLOCK },
	{ "K_CAPSLOCK",		QFK_CAPSLOCK },
	{ "K_SCROLLOCK",	QFK_SCROLLOCK },
	{ "K_RSHIFT",		QFK_RSHIFT },
	{ "K_LSHIFT",		QFK_LSHIFT },
	{ "K_RCTRL",		QFK_RCTRL },
	{ "K_LCTRL",		QFK_LCTRL },
	{ "K_RALT",			QFK_RALT },
	{ "K_LALT",			QFK_LALT },
	{ "K_RMETA",		QFK_RMETA },
	{ "K_LMETA",		QFK_LMETA },
	{ "K_LSUPER",		QFK_LSUPER },
	{ "K_RSUPER",		QFK_RSUPER },
	{ "K_MODE",			QFK_MODE },
	{ "K_COMPOSE",		QFK_COMPOSE },
	{ "K_HELP",			QFK_HELP },
	{ "K_PRINT",		QFK_PRINT },
	{ "K_SYSREQ",		QFK_SYSREQ },
	{ "K_BREAK",		QFK_BREAK },
	{ "K_MENU",			QFK_MENU },
	{ "K_POWER",		QFK_POWER },
	{ "K_EURO",			QFK_EURO },

	{ "K_KANJI", 		QFK_KANJI },
	{ "K_MUHENKAN", 	QFK_MUHENKAN },
	{ "K_HENKAN", 		QFK_HENKAN },
	{ "K_ROMAJI", 		QFK_ROMAJI },
	{ "K_HIRAGANA", 	QFK_HIRAGANA },
	{ "K_KATAKANA", 	QFK_KATAKANA },
	{ "K_HIRAGANA_KATAKANA",	QFK_HIRAGANA_KATAKANA },
	{ "K_ZENKAKU", 		QFK_ZENKAKU },
	{ "K_HANKAKU", 		QFK_HANKAKU },
	{ "K_ZENKAKU_HANKAKU",	QFK_ZENKAKU_HANKAKU },
	{ "K_TOUROKU", 		QFK_TOUROKU },
	{ "K_MASSYO", 		QFK_MASSYO },
	{ "K_KANA_LOCK", 	QFK_KANA_LOCK },
	{ "K_KANA_SHIFT", 	QFK_KANA_SHIFT },
	{ "K_EISU_SHIFT", 	QFK_EISU_SHIFT },
	{ "K_EISU_TOGGLE", 	QFK_EISU_TOGGLE },
	{ "K_KANJI_BANGOU", QFK_KANJI_BANGOU },
	{ "K_ZEN_KOHO", 	QFK_ZEN_KOHO },
	{ "K_MAE_KOHO", 	QFK_MAE_KOHO },

	{ "K_HOMEPAGE",		QFK_HOMEPAGE },
	{ "K_SEARCH",		QFK_SEARCH },
	{ "K_MAIL",			QFK_MAIL },
	{ "K_FAVORITES",	QFK_FAVORITES },
	{ "K_AUDIOMUTE",	QFK_AUDIOMUTE },
	{ "K_AUDIOLOWERVOLUME",	QFK_AUDIOLOWERVOLUME },
	{ "K_AUDIORAISEVOLUME",	QFK_AUDIORAISEVOLUME },
	{ "K_AUDIOPLAY",		QFK_AUDIOPLAY },
	{ "K_CALCULATOR",	QFK_CALCULATOR },
	{ "K_UNDO",			QFK_UNDO },
	{ "K_REDO",			QFK_REDO },
	{ "K_NEW",			QFK_NEW },
	{ "K_RELOAD",		QFK_RELOAD },
	{ "K_OPEN",			QFK_OPEN },
	{ "K_CLOSE",		QFK_CLOSE },
	{ "K_REPLY",		QFK_REPLY },
	{ "K_MAILFORWARD",	QFK_MAILFORWARD },
	{ "K_SEND",			QFK_SEND },
	{ "K_SAVE",			QFK_SAVE },
	{ "K_BACK",			QFK_BACK },
	{ "K_FORWARD",		QFK_FORWARD },

	{ "M_BUTTON1",		QFM_BUTTON1 },
	{ "M_BUTTON2",		QFM_BUTTON2 },
	{ "M_BUTTON3",		QFM_BUTTON3 },
	{ "M_WHEEL_UP",		QFM_WHEEL_UP },
	{ "M_WHEEL_DOWN",	QFM_WHEEL_DOWN },
	{ "M_BUTTON6",		QFM_BUTTON6 },
	{ "M_BUTTON7",		QFM_BUTTON7 },
	{ "M_BUTTON8",		QFM_BUTTON8 },
	{ "M_BUTTON9",		QFM_BUTTON9 },
	{ "M_BUTTON10",		QFM_BUTTON10 },
	{ "M_BUTTON11",		QFM_BUTTON11 },
	{ "M_BUTTON12",		QFM_BUTTON12 },
	{ "M_BUTTON13",		QFM_BUTTON13 },
	{ "M_BUTTON14",		QFM_BUTTON14 },
	{ "M_BUTTON15",		QFM_BUTTON15 },
	{ "M_BUTTON16",		QFM_BUTTON16 },
	{ "M_BUTTON17",		QFM_BUTTON17 },
	{ "M_BUTTON18",		QFM_BUTTON18 },
	{ "M_BUTTON19",		QFM_BUTTON19 },
	{ "M_BUTTON20",		QFM_BUTTON20 },
	{ "M_BUTTON21",		QFM_BUTTON21 },
	{ "M_BUTTON22",		QFM_BUTTON22 },
	{ "M_BUTTON23",		QFM_BUTTON23 },
	{ "M_BUTTON24",		QFM_BUTTON24 },
	{ "M_BUTTON25",		QFM_BUTTON25 },
	{ "M_BUTTON26",		QFM_BUTTON26 },
	{ "M_BUTTON27",		QFM_BUTTON27 },
	{ "M_BUTTON28",		QFM_BUTTON28 },
	{ "M_BUTTON29",		QFM_BUTTON29 },
	{ "M_BUTTON30",		QFM_BUTTON30 },
	{ "M_BUTTON31",		QFM_BUTTON31 },
	{ "M_BUTTON32",		QFM_BUTTON32 },

	{ "J_BUTTON1",		QFJ_BUTTON1 },
	{ "J_BUTTON2",		QFJ_BUTTON2 },
	{ "J_BUTTON3",		QFJ_BUTTON3 },
	{ "J_BUTTON4",		QFJ_BUTTON4 },
	{ "J_BUTTON5",		QFJ_BUTTON5 },
	{ "J_BUTTON6",		QFJ_BUTTON6 },
	{ "J_BUTTON7",		QFJ_BUTTON7 },
	{ "J_BUTTON8",		QFJ_BUTTON8 },
	{ "J_BUTTON9",		QFJ_BUTTON9 },
	{ "J_BUTTON10",		QFJ_BUTTON10 },
	{ "J_BUTTON11",		QFJ_BUTTON11 },
	{ "J_BUTTON12",		QFJ_BUTTON12 },
	{ "J_BUTTON13",		QFJ_BUTTON13 },
	{ "J_BUTTON14",		QFJ_BUTTON14 },
	{ "J_BUTTON15",		QFJ_BUTTON15 },
	{ "J_BUTTON16",		QFJ_BUTTON16 },
	{ "J_BUTTON17",		QFJ_BUTTON17 },
	{ "J_BUTTON18",		QFJ_BUTTON18 },
	{ "J_BUTTON19",		QFJ_BUTTON19 },
	{ "J_BUTTON20",		QFJ_BUTTON20 },
	{ "J_BUTTON21",		QFJ_BUTTON21 },
	{ "J_BUTTON22",		QFJ_BUTTON22 },
	{ "J_BUTTON23",		QFJ_BUTTON23 },
	{ "J_BUTTON24",		QFJ_BUTTON24 },
	{ "J_BUTTON25",		QFJ_BUTTON25 },
	{ "J_BUTTON26",		QFJ_BUTTON26 },
	{ "J_BUTTON27",		QFJ_BUTTON27 },
	{ "J_BUTTON28",		QFJ_BUTTON28 },
	{ "J_BUTTON29",		QFJ_BUTTON29 },
	{ "J_BUTTON30",		QFJ_BUTTON30 },
	{ "J_BUTTON31",		QFJ_BUTTON31 },
	{ "J_BUTTON32",		QFJ_BUTTON32 },

	{NULL, 0}
};

static imt_t *
key_target_find_imt (keytarget_t *kt, const char *imt_name)
{
	imt_t      *imt;
	for (imt = kt->imts; imt; imt = imt->next) {
		if (!strcasecmp (imt->name, imt_name)) {
			return imt;
		}
	}
	return 0;
}

VISIBLE imt_t *
Key_FindIMT (const char *imt_name)
{
	keydest_t   kd;
	imt_t      *imt = 0;

	for (kd = key_unfocused; !imt && kd < key_last; kd++) {
		imt = key_target_find_imt (&key_targets[kd], imt_name);
	}
	return imt;
}

void
Key_CreateIMT (keydest_t kd, const char *imt_name, const char *chain_imt_name)
{
	imt_t      *imt;
	imt_t      *chain_imt = 0;
	keytarget_t *kt = &key_targets[kd];

	imt = Key_FindIMT (imt_name);
	if (imt) {
		Sys_Printf ("imt error: imt %s already exists\n", imt_name);
		return;
	}
	if (chain_imt_name) {
		chain_imt = Key_FindIMT (chain_imt_name);
		if (!chain_imt) {
			Sys_Printf ("imt error: chain imt %s does not exist\n",
						chain_imt_name);
			return;
		}
		imt = key_target_find_imt (kt, chain_imt_name);
		if (!imt) {
			Sys_Printf ("imt error: chain imt %s not on target key "
						"destination\n", chain_imt_name);
			return;
		}
	}
	imt = calloc (1, sizeof (imt_t));
	imt->name = strdup (imt_name);
	imt->chain = chain_imt;
	imt->next = kt->imts;
	kt->imts = imt;
	if (!kt->active) {
		kt->active = imt;
	}
}

VISIBLE void
Key_SetBinding (imt_t *imt, knum_t keynum, const char *binding)
{
	if (keynum == (knum_t) -1)
		return;

	if (imt->bindings[keynum].str) {
		free (imt->bindings[keynum].str);
		imt->bindings[keynum].str = NULL;
	}
	if (binding) {
		imt->bindings[keynum].str = strdup(binding);
	}
}

static void
Key_CallDestCallbacks (keydest_t kd)
{
	int         i;

	for (i = 0; i < num_keydest_callbacks; i++)
		keydest_callbacks[i] (kd);
}

static void
process_binding (knum_t key, const char *kb)
{
	char        cmd[1024];

	if (kb[0] == '+') {
		if (keydown[key])
			snprintf (cmd, sizeof (cmd), "%s %d\n", kb, key);
		else
			snprintf (cmd, sizeof (cmd), "-%s %d\n", kb + 1, key);
	} else {
		if (!keydown[key])
			return;
		snprintf (cmd, sizeof (cmd), "%s\n", kb);
	}
	Cbuf_AddText (cbuf, cmd);
}

/*
  Key_Game

  Game key handling.
*/
static qboolean
Key_Game (knum_t key, short unicode)
{
	const char *kb;
	imt_t      *imt = key_targets[key_dest].active;

	while (imt) {
		kb = imt->bindings[key].str;
		if (kb) {
			if (keydown[key] <= 1)
				process_binding (key, kb);
			return true;
		}
		imt = imt->chain;
	}
	return false;
/*
	Sys_DPrintf("kb %p, key_target %d, key_dest %d, key %d\n", kb,
				key_target, key_dest, key);
*/
}

/*
  Key_Console

  Interactive line editing and console scrollback
*/
static void
Key_Console (knum_t key, short unicode)
{
	// escape is un-bindable
	if (keydown[key] == 1 && key && Key_Game (key, unicode))
		return;

	Con_KeyEvent (key, unicode, keydown[key]);
}

//============================================================================

/*
  Key_StringToKeynum

  Returns a key number to be used to index keybindings[] by looking at
  the given string.  Single ascii characters return themselves, while
  the QFK_* names are matched up.
*/
static int
Key_StringToKeynum (const char *str)
{
	keyname_t  *kn;

	if (!str || !str[0])
		return -1;

	for (kn = keynames; kn->name; kn++) {
		if (!strcasecmp (str, kn->name))
			return kn->keynum;
	}
	return -1;
}

/*
  Key_KeynumToString

  Returns a string (a QFK_* name) for the given keynum.
  FIXME: handle quote special (general escape sequence?)
*/
VISIBLE const char *
Key_KeynumToString (knum_t keynum)
{
	keyname_t  *kn;

	if (keynum == (knum_t) -1)
		return "<KEY NOT FOUND>";

	for (kn = keynames; kn->name; kn++)
		if (keynum == kn->keynum)
			return kn->name;

	return "<UNKNOWN KEYNUM>";
}

static void
Key_In_Unbind (const char *imt_name, const char *key_name)
{
	imt_t      *imt;
	int         key;

	imt = Key_FindIMT (imt_name);
	if (!imt) {
		Sys_Printf ("\"%s\" isn't a valid imt\n", imt_name);
		return;
	}

	key = Key_StringToKeynum (key_name);
	if (key == -1) {
		Sys_Printf ("\"%s\" isn't a valid key\n", key_name);
		return;
	}

	Key_SetBinding (imt, key, NULL);
}

static void
Key_In_Unbind_f (void)
{
	if (Cmd_Argc () != 3) {
		Sys_Printf ("in_unbind <imt> <key> : remove commands from a key\n");
		return;
	}
	Key_In_Unbind (Cmd_Argv (1), Cmd_Argv (2));
}

static void
Key_Unbindall_f (void)
{
	keydest_t   kd;
	imt_t      *imt;
	int         i;

	for (kd = key_unfocused; kd < key_last; kd++) {
		for (imt = key_targets[kd].imts; imt; imt = imt->next) {
			for (i = 0; i < QFK_LAST; i++) {
				Key_SetBinding (imt, i, 0);
			}
		}
	}
}

static void
Key_In_Clear (void)
{
	int         err = 0;
	imt_t      *imt;
	int         i, j;

	if (Cmd_Argc () == 1) {
		Sys_Printf ("in_clear <imt> ...\n");
		return;
	}
	for (i = 1; i < Cmd_Argc (); i++) {
		if (!Key_FindIMT (Cmd_Argv (i))) {
			Sys_Printf ("\"%s\" isn't a valid imt\n", Cmd_Argv (i));
			err = 1;
		}
	}
	if (err)
		return;
	for (i = 1; i < Cmd_Argc (); i++) {
		imt = Key_FindIMT (Cmd_Argv (i));
		for (j = 0; j < QFK_LAST; j++)
			Key_SetBinding (imt, j, NULL);
	}
}

static void
Key_IMT_Create_f (void)
{
	const char *keydest;
	const char *imt_name;
	const char *chain_imt_name = 0;
	keydest_t   kd;

	if (Cmd_Argc () < 3 || Cmd_Argc () > 4) {
		Sys_Printf ("see help imt_create\n");
		return;
	}
	keydest = Cmd_Argv (1);
	imt_name = Cmd_Argv (2);
	if (Cmd_Argc () == 4) {
		chain_imt_name = Cmd_Argv (3);
	}
	for (kd = key_game; kd < key_last; kd++) {
		if (!strcasecmp (keydest_names[kd], keydest)) {
			break;
		}
	}
	if (kd == key_last) {
		Sys_Printf ("imt error: invalid keydest: %s\n", keydest);
		return;
	}
	Key_CreateIMT (kd, imt_name, chain_imt_name);
}

static void
Key_IMT_Drop_All_f (void)
{
	keydest_t   kd;
	imt_t       *imt;

	for (kd = key_unfocused; kd < key_last; kd++) {
		while (key_targets[kd].imts) {
			imt = key_targets[kd].imts;
			key_targets[kd].imts = imt->next;
			free ((char *) imt->name);
			free (imt);
		}
		key_targets[kd].active = 0;
	}
}

static void
Key_In_Bind (const char *imt_name, const char *key_name, const char *cmd)
{
	imt_t      *imt;
	int         key;

	imt = Key_FindIMT (imt_name);
	if (!imt) {
		Sys_Printf ("\"%s\" isn't a valid imt\n", imt_name);
		return;
	}

	key = Key_StringToKeynum (key_name);
	if (key == -1) {
		Sys_Printf ("\"%s\" isn't a valid key\n", key_name);
		return;
	}

	if (!cmd) {
		if (imt->bindings[key].str)
			Sys_Printf ("%s %s \"%s\"\n", imt_name, key_name,
						imt->bindings[key].str);
		else
			Sys_Printf ("%s %s is not bound\n", imt_name, key_name);
		return;
	}
	Key_SetBinding (imt, key, cmd);
}

static void
Key_In_Bind_f (void)
{
	int         c, i;
	const char *imt, *key, *cmd = 0;
	char        cmd_buf[1024];

	c = Cmd_Argc ();

	if (c < 3) {
		Sys_Printf ("in_bind <imt> <key> [command] : attach a command to a "
					"key\n");
		return;
	}

	imt = Cmd_Argv (1);

	key = Cmd_Argv (2);

	if (c >= 4) {
		cmd = cmd_buf;
		cmd_buf[0] = 0;
		for (i = 3; i < c; i++) {
			strncat (cmd_buf, Cmd_Argv (i), sizeof (cmd_buf) -
					 strlen (cmd_buf));
			if (i != (c - 1))
				strncat (cmd_buf, " ", sizeof (cmd_buf) - strlen (cmd_buf));
		}
	}

	Key_In_Bind (imt, key, cmd);
}

static void
Key_Unbind_f (void)
{
	const char *key;

	if (Cmd_Argc () != 2) {
		Sys_Printf ("unbind <key> : remove commands from a key\n");
		return;
	}
	key = OK_TranslateKeyName (Cmd_Argv (1));
	Key_In_Unbind ("imt_mod", key);
}

static void
Key_Bind_f (void)
{
	int         c, i;
	const char *key, *cmd = 0;
	char        cmd_buf[1024];

	c = Cmd_Argc ();

	if (c < 2) {
		Sys_Printf ("bind <key> [command] : attach a command to a key\n");
		return;
	}

	key = OK_TranslateKeyName (Cmd_Argv (1));

	if (c >= 3) {
		cmd = cmd_buf;
		cmd_buf[0] = 0;
		for (i = 2; i < c; i++) {
			strncat (cmd_buf, Cmd_Argv (i), sizeof (cmd_buf) -
					 strlen (cmd_buf));
			if (i != (c - 1))
				strncat (cmd_buf, " ", sizeof (cmd_buf) - strlen (cmd_buf));
		}
	}

	Key_In_Bind ("imt_mod", key, cmd);
}

static void
Key_GIB_Bind_Get_f (void)
{
	const char *key, *cmd;
	int k;

	if (GIB_Argc () != 2) {
		GIB_USAGE ("key");
		return;
	}

	key = OK_TranslateKeyName (GIB_Argv (1));

	if ((k = Key_StringToKeynum (key)) == -1) {
		GIB_Error ("bind", "bind::get: invalid key %s", key);
		return;
	}

	if (!(cmd = Key_GetBinding ("IMT_MOD", k)))
		GIB_Return ("");
	else
		GIB_Return (cmd);
}

static void
in_key_togglemenu_f (cvar_t *var)
{
	int         k;

	if (!*var->string) {
		key_togglemenu = QFK_ESCAPE;
		return;
	}
	if ((k = Key_StringToKeynum (var->string)) == -1) {
		k = QFK_ESCAPE;
		Sys_Printf ("\"%s\" is not a valid key. setting to \"K_ESCAPE\"\n",
					var->string);
	}
	key_togglemenu = k;
}

static void
in_key_toggleconsole_f (cvar_t *var)
{
	int         k;

	if (!*var->string) {
		key_toggleconsole = -1;
		return;
	}
	if ((k = Key_StringToKeynum (var->string)) == -1) {
		Sys_Printf ("\"%s\" is not a valid key. not setting\n",
					var->string);
		return;
	}
	key_toggleconsole = k;
}

static void
Key_InputMappingTable_f (void)
{
	int         c;
	imt_t      *imt;

	c = Cmd_Argc ();

	if (c != 2) {
		Sys_Printf ("Current imt is %s\n", key_targets[key_game].active->name);
		Sys_Printf ("imt <imt> : set to a specific input mapping table\n");
		return;
	}

	imt = Key_FindIMT (Cmd_Argv (1));
	if (!imt) {
		Sys_Printf ("\"%s\" isn't a valid imt\n", Cmd_Argv (1));
		return;
	}

	key_targets[key_game].active = imt;
}

static void
Key_IMT_Keydest_f (void)
{
	int         c;
	imt_t      *imt;
	const char *imt_name = 0;
	const char *keydest;
	keydest_t   kd;

	c = Cmd_Argc ();
	switch (c) {
		case 3:
			imt_name = Cmd_Argv (2);
		case 2:
			keydest = Cmd_Argv (1);
			break;
		default:
			return;
	}
	for (kd = key_game; kd < key_last; kd++) {
		if (!strcasecmp (keydest_names[kd], keydest)) {
			break;
		}
	}
	if (kd == key_last) {
		Sys_Printf ("imt error: invalid keydest: %s\n", keydest);
		return;
	}

	if (!imt_name) {
		Sys_Printf ("Current imt is %s\n", key_targets[key_game].active->name);
		Sys_Printf ("imt <imt> : set to a specific input mapping table\n");
		return;
	}

	imt = key_target_find_imt (&key_targets[kd], imt_name);
	if (!imt) {
		Sys_Printf ("\"%s\" isn't an imt on %s\n", imt_name, keydest);
		return;
	}

	key_targets[kd].active = imt;
}

static void __attribute__((format(printf,2,3)))
key_printf (QFile *f, const char *fmt, ...)
{
	va_list     args;
	static dstring_t *string;

	if (!string) {
		string = dstring_new ();
	}
	va_start (args, fmt);
	dvsprintf (string, fmt, args);
	va_end (args);

	if (f) {
		Qprintf (f, "%s", string->str);
	} else {
		Sys_Printf ("%s", string->str);
	}
}

static void
key_write_imt (QFile *f, keydest_t kd, imt_t *imt)
{
	int         i;
	const char *bind;

	if (!imt || imt->written) {
		return;
	}
	imt->written = 1;
	key_write_imt (f, kd, imt->chain);
	if (imt->chain) {
		key_printf (f, "imt_create %s %s %s\n", keydest_names[kd],
					imt->name, imt->chain->name);
	} else {
		key_printf (f, "imt_create %s %s\n", keydest_names[kd], imt->name);
	}
	for (i = 0; i < QFK_LAST; i++) {
		bind = imt->bindings[i].str;
		if (bind) {
			key_printf (f, "in_bind %s %s \"%s\"\n", imt->name,
						Key_KeynumToString (i), bind);
		}
	}
}

void
Key_WriteBindings (QFile *f)
{
	keydest_t   kd;
	imt_t      *imt;

	for (kd = key_unfocused; kd < key_last; kd++) {
		for (imt = key_targets[kd].imts; imt; imt = imt->next) {
			imt->written = 0;
		}
	}
	key_printf (f, "imt_drop_all\n");
	for (kd = key_unfocused; kd < key_last; kd++) {
		if (key_targets[kd].imts) {
			for (imt = key_targets[kd].imts; imt; imt = imt->next) {
				key_write_imt (f, kd, imt);
			}
			key_printf (f, "imt_keydest %s %s\n", keydest_names[kd],
						key_targets[kd].active->name);
		}
	}
}

static void
Key_Bindlist_f (void)
{
	Key_WriteBindings (0);
}

static void
keyhelp_f (void)
{
	keyhelp = 1;
}

/*
  Key_Event

  Called by the system between frames for both key up and key down events
  Should NOT be called during an interrupt!
*/
VISIBLE void
Key_Event (knum_t key, short unicode, qboolean down)
{
//  Sys_Printf ("%d %d %d : %d\n", key_target, key_dest, key, down); //@@@

	if (down) {
		keydown[key]++;
		if (keyhelp) {
			Sys_Printf ("Key name for that key is \"%s\"\n",
						Key_KeynumToString (key));
			keyhelp = 0;
			return; // gobble the key
		}
	} else {
		keydown[key] = 0;
	}

	// handle escape specially, so the user can never unbind it
	if (key == key_togglemenu || key == key_toggleconsole) {
		Key_Console (key, unicode);
		return;
	}

	if (!down && Key_Game (key, unicode))
		return;

	// if not a consolekey, send to the interpreter no matter what mode is
	switch (key_dest) {
		case key_game:
			Key_Game (key, unicode);
			break;
		case key_message:
		case key_menu:
		case key_console:
			Key_Console (key, unicode);
			break;
		default:
			Sys_Error ("Bad key_dest");
	}
}

VISIBLE void
Key_FocusEvent (int gain)
{
	if (gain) {
		Key_CallDestCallbacks (key_dest);
	} else {
		Key_CallDestCallbacks (key_unfocused);
	}
}

void
Key_ClearStates (void)
{
	int         i;

	for (i = 0; i < QFK_LAST; i++) {
		if (keydown[i])
			Key_Event (i, 0, false);
		keydown[i] = false;
	}
}

static struct {
	keydest_t   kd;
	const char *imt_name;
	const char *chain_imt_name;
} default_imts[] = {
	{key_game,		"imt_mod",		0},
	{key_game,		"imt_0",		"imt_mod"},
	{key_game,		"imt_1",		"imt_0"},
	{key_game,		"imt_2",		"imt_0"},
	{key_game,		"imt_3",		"imt_0"},
	{key_game,		"imt_4",		"imt_0"},
	{key_game,		"imt_5",		"imt_0"},
	{key_game,		"imt_6",		"imt_0"},
	{key_game,		"imt_7",		"imt_0"},
	{key_game,		"imt_8",		"imt_0"},
	{key_game,		"imt_9",		"imt_0"},
	{key_game,		"imt_10",		"imt_0"},
	{key_game,		"imt_11",		"imt_0"},
	{key_game,		"imt_12",		"imt_0"},
	{key_game,		"imt_13",		"imt_0"},
	{key_game,		"imt_14",		"imt_0"},
	{key_game,		"imt_15",		"imt_0"},
	{key_game,		"imt_16",		"imt_0"},
	{key_demo,		"imt_demo",		0},
	{key_console,	"imt_console",	0},
	{key_message,	"imt_message",	0},
	{key_menu,		"imt_menu",		0},
	{key_last,		0,				0},
};

static void
Key_CreateDefaultIMTs (void)
{
	int         i;

	for (i = 0; default_imts[i].kd != key_last; i++) {
		Key_CreateIMT (default_imts[i].kd, default_imts[i].imt_name,
					   default_imts[i].chain_imt_name);
	}
}

void
Key_Init (cbuf_t *cb)
{
	cbuf = cb;

	Key_CreateDefaultIMTs ();

	OK_Init ();

	// register our functions
	Cmd_AddCommand ("in_bind", Key_In_Bind_f, "Assign a command or a set of "
					"commands to a key.\n"
					"Note: To bind multiple commands to a key, enclose the "
					"commands in quotes and separate with semi-colons.");
	Cmd_AddCommand ("in_unbind", Key_In_Unbind_f,
					"Remove the bind from the the selected key");
	Cmd_AddCommand ("unbindall", Key_Unbindall_f,
					"Remove all binds (USE CAUTIOUSLY!!!)");
	Cmd_AddCommand ("in_clear", Key_In_Clear,
					"Remove all binds from the specified imts");
	Cmd_AddCommand ("imt", Key_InputMappingTable_f, "");
	Cmd_AddCommand ("imt_keydest", Key_IMT_Keydest_f, "");
	Cmd_AddCommand ("imt_create", Key_IMT_Create_f,
					"create a new imt table:\n"
					"    imt_create <keydest> <imt_name> [chain_name]\n"
					"\n"
					"The new table will be attached to the specified keydest\n"
					"imt_name must not already exist.\n"
					"If given, chain_name must already exist and be on "
						"keydest.\n");
	Cmd_AddCommand ("imt_drop_all", Key_IMT_Drop_All_f,
					"delete all imt tables\n");
	Cmd_AddCommand ("bind", Key_Bind_f, "wrapper for in_bind that uses "
					"in_bind_imt for the imt parameter");
	Cmd_AddCommand ("unbind", Key_Unbind_f,
					"wrapper for in_unbind that uses in_bind_imt for the imt "
					"parameter");
	Cmd_AddCommand ("bindlist", Key_Bindlist_f, "list all of the key bindings");
	Cmd_AddCommand ("keyhelp", keyhelp_f, "display the keyname for the next "
					"RECOGNIZED key-press. If the key pressed produces no "
					"output, " PACKAGE_NAME " does not recognise that key.");

	GIB_Builtin_Add ("bind::get", Key_GIB_Bind_Get_f);

}

void
Key_Init_Cvars (void)
{
	Cvar_Get ("in_key_togglemenu", "", CVAR_NONE, in_key_togglemenu_f,
			  "Key for toggling the menu.");
	Cvar_Get ("in_key_toggleconsole", "K_BACKQUOTE", CVAR_NONE,
			  in_key_toggleconsole_f,
			  "Key for toggling the console.");
}

const char *
Key_GetBinding (const char *imt_name, knum_t key)
{
	imt_t      *imt;

	imt = Key_FindIMT (imt_name);
	if (imt) {
		return imt->bindings[key].str;
	}
	return 0;
}

VISIBLE void
Key_SetKeyDest(keydest_t kd)
{
	if ((int) kd < key_unfocused || kd >= key_last) {
		Sys_Error ("Bad key_dest");
	}
	key_dest = kd;
	Key_CallDestCallbacks (key_dest);
}

VISIBLE void
Key_KeydestCallback (keydest_callback_t *callback)
{
	if (num_keydest_callbacks == max_keydest_callbacks) {
		size_t size = (max_keydest_callbacks + KEYDEST_CALLBACK_CHUNK)
					  * sizeof (keydest_callback_t *);
		keydest_callbacks = realloc (keydest_callbacks, size);
		if (!keydest_callbacks)
			Sys_Error ("Too many keydest callbacks!");
		max_keydest_callbacks += KEYDEST_CALLBACK_CHUNK;
	}

	if (!callback)
		Sys_Error ("null keydest callback");

	keydest_callbacks[num_keydest_callbacks++] = callback;
}
