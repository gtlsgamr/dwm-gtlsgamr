/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 1;        /* horizontal padding for statusbar */
static const int vertpadbar         = 5;        /* vertical padding for statusbar */
static const char *fonts[]          = {  "Fixedsys Excelsior:size=13:antialias=true:autohint=false","Material Icons:style=Regular:size=12"};
static const char dmenufont[]       = "Fixedsys Excelsior:size=13:antialias=true:autohint=false";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char col_gray1[]       = "#d3d7cf";
static const char col_gray2[]       = "#d3d7cf";
static const char col_gray3[]       = "#000000";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#0000aa";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_cyan },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray2  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, OPAQUE, OPAQUE},
	[SchemeSel]  = { OPAQUE, OPAQUE, OPAQUE},
};
 
/* tagging */
static const char *tags[] = { "􏿽", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ NULL,       NULL,		  "centersmall",       0,       1,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", col_gray1,
	"-nf", col_gray3,
	"-sb", col_cyan,
	"-sf", col_gray4,
	NULL
};
static const char quicknotecommand[] = "touch ~/Documents/notes/scratchpad.md && st -t centersmall -e nvim ~/Documents/notes/scratchpad.md";
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
{ 0,					XF86XK_AudioMute,								spawn,				SHCMD("pamixer -t; kill -34 $(cat ~/.cache/pidofbar)") },	
{ 0,					XF86XK_AudioRaiseVolume,						spawn,				SHCMD("pamixer --allow-boost -i 3; kill -34 $(cat ~/.cache/pidofbar)") },	
{ 0,					XF86XK_AudioLowerVolume,						spawn,				SHCMD("pamixer --allow-boost -d 3; kill -34 $(cat ~/.cache/pidofbar)") },	
{ 0,					XF86XK_MonBrightnessUp,							spawn,				SHCMD("xbacklight -inc 5; kill -35 $(cat ~/.cache/pidofbar)") },	
{ 0,					XF86XK_MonBrightnessDown,						spawn,				SHCMD("xbacklight -dec 5; kill -35 $(cat ~/.cache/pidofbar)") },	
{ MODKEY,				XK_w,											spawn,				SHCMD("firefox") },	
{ MODKEY,				XK_r,											spawn,				SHCMD("setbg")},	
{ MODKEY,				XK_d,											spawn,				{.v = dmenucmd } },	
{ MODKEY,				XK_n,											spawn,				SHCMD("st -e nvim ")},	
{ MODKEY|ShiftMask,		XK_space,										togglefloating,		{0}},	
{ MODKEY|ShiftMask,		XK_n,											spawn,				SHCMD(quicknotecommand)},	
{ MODKEY,				XK_c,											spawn,				SHCMD("st -t centersmall -f 'mono:size=18' -e bc -lq")},	
{ MODKEY,				XK_e,											spawn,				SHCMD("st -t centersmall -e emoji")},	
{ MODKEY,				XK_Return,	 									spawn,				{.v = termcmd } },	
{ MODKEY|ShiftMask,		XK_Return,	 									spawn,				SHCMD("st -e tmux attach")},	
{ MODKEY,				XK_b,											togglebar,			{0} },	
{ MODKEY,				XK_j,											focusstack,			{.i = +1 } },	
{ MODKEY,				XK_k,											focusstack,			{.i = -1 } },	
{ MODKEY,				XK_h,											setmfact,			{.f = -0.05} },	
{ MODKEY,				XK_l,											setmfact,			{.f = +0.05} },	
{ MODKEY|ShiftMask,		XK_x,											spawn,				SHCMD("xkill") },	
{ MODKEY|ShiftMask,		XK_Print,										spawn,				SHCMD("maim -s -o -u test.png && upfile test.png && rm test.png") },	
{ 0,					XK_Print,										spawn,				SHCMD("maim ~/Documents/screenshots/screenshot_$(date '+%y%m%d%H%M%S').png; maim -o -u | xclip -selection clipboard -t image/png -i") },	
{ MODKEY,				XK_Print,										spawn,				SHCMD("maim -s -o -u | xclip -selection clipboard -t image/png -i")},	
{ MODKEY,				XK_space,										zoom,				{0} },	
{ MODKEY,				XK_Tab,											view,				{0} },	
{ MODKEY,				XK_q,											killclient,			{0} },	
{ MODKEY,				XK_t,											setlayout,			{.v = &layouts[0]} },	
{ MODKEY|ShiftMask,		XK_f,											setlayout,			{.v = &layouts[1]} },	
{ MODKEY,				XK_u,											setlayout,			{.v = &layouts[2]} },	
{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
{ MODKEY,				XK_f,											togglefullscr,		{0} },	
{ MODKEY,				XK_0,											view,				{.ui = ~0 } },	
{ MODKEY|ShiftMask,		XK_0,											tag,				{.ui = ~0 } },	
{ MODKEY,				XK_comma,										focusmon,			{.i = -1 } },	
{ MODKEY,				XK_period,	 									focusmon,			{.i = +1 } },	
{ MODKEY|ShiftMask,		XK_comma,										tagmon,				{.i = -1 } },	
{ MODKEY|ShiftMask,		XK_period,										tagmon,				{.i = +1 } },	
	TAGKEYS(XK_1,			0)
	TAGKEYS(XK_2,			1)
	TAGKEYS(XK_3,			2)
	TAGKEYS(XK_4,			3)
	TAGKEYS(XK_5,			4)
	TAGKEYS(XK_6,			5)
	TAGKEYS(XK_7,			6)
	TAGKEYS(XK_8,			7)
	TAGKEYS(XK_9,			8)
{ MODKEY|ShiftMask,		XK_q,											quit,				{0} },	
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

