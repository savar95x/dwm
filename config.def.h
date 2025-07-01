/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define EMAIL "librewolf 'https://gmail.com'"
//#define TORRENTCLIENT "(pgrep transmission-da &>/dev/null && transmission-qt) || (setsid -f transmission-daemon && transmission-qt)"
#define TORRENTCLIENT "(pgrep transmission-da &>/dev/null && st -e tremc) || (setsid -f transmission-daemon && st -e tremc)"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 22;       /* snap pixel */
static const unsigned int single_ov = 80;
static const unsigned int single_oh = 80;
static const unsigned int gappih    = 8;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;        /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
// underlining
static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 0;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 4;        /* horizontal padding for statusbar */
static const int vertpadbar         = 20;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=11", "Font Awesome 6 Free:style=solid:size=10.6" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#1D1F21"; // #1C2021
static const char col_gray2[]       = "#373737";
static const char col_gray3[]       = "#bdae93";
static const char col_gray4[]       = "#BDAE93"/*"#fbf1c7"*/;
static const char col_cyan[]        = "#BDAE93"; // #393939
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_gray3,  col_cyan  },
	[SchemeTitle]  = { col_gray3, col_gray1,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
//	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
//	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "floating",NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x25", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
//	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmenucmd } },
//	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("dmenu_run") },
//	{ MODKEY|ControlMask,		XK_space,  spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_grave,  spawn,          SHCMD(TERMINAL " -c floating -e lfrun ~/dox/notes/") },
//	{ MODKEY,			XK_grave,  spawn,          SHCMD(TERMINAL " -c floating -e nvim $HOME/dox/note.tmp") },
//	{ MODKEY|ShiftMask,             XK_tilde,  spawn,          SHCMD(TERMINAL " -e nvim $HOME/dox/note.tmp") },
	{ MODKEY|ShiftMask,	     XK_BackSpace, spawn,          SHCMD("$HOME/.local/scripts/dmpowermenu")},
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("$HOME/.local/scripts/takess")},
	{ MODKEY,		     	XK_Insert, spawn,          SHCMD("$HOME/.local/bin/dmpassmenu --type")},
	{     0 ,          XF86XK_MonBrightnessUp, spawn,          SHCMD("light -A 2 && pkill -RTMIN+13 dwmblocks")},
	{     0 ,        XF86XK_MonBrightnessDown, spawn,          SHCMD("light -U 2 && pkill -RTMIN+13 dwmblocks")},
	{     0 ,         XF86XK_AudioLowerVolume, spawn,          SHCMD("$HOME/.local/scripts/sb_audio dec 2 && pkill -RTMIN+10 dwmblocks")},
	{     0 ,         XF86XK_AudioRaiseVolume, spawn,          SHCMD("$HOME/.local/scripts/sb_audio inc 2 && pkill -RTMIN+10 dwmblocks")},
	{     0 ,          	 XF86XK_AudioMute, spawn,          SHCMD("$HOME/.local/scripts/sb_audio toggle && pkill -RTMIN+10 dwmblocks")},
	{ MODKEY,                       XK_s,      spawn,          SHCMD("$HOME/.local/scripts/dmlscripts") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$HOME/.local/scripts/dmweb")},
	{ MODKEY,                       XK_e,      spawn,          SHCMD(EMAIL) },
	{ MODKEY,                       XK_m,      spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
	{ MODKEY,                       XK_y,      spawn,          SHCMD(TERMINAL " -e ytfzf") },
	{ MODKEY,                       XK_t,      spawn,          SHCMD(TORRENTCLIENT) },
	{ MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e /home/savar/.local/bin/lfrun") },
//	{ MODKEY,                       XK_p,      spawn,          SHCMD(TERMINAL " -e shellcaster") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD(TERMINAL " -e newsboat") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD(TERMINAL " -e gotop") },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("pgrep xbanish && pkill xbanish || setsid -f xbanish -t 1")},
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,			XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
//	mod+shift+c for harder killclient
//	{ MODKEY|ShiftMask,		XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_bracketright,  viewnext,       {0} },
	{ MODKEY,                       XK_bracketleft,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_bracketright,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_bracketleft,   tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("$HOME/.local/scripts/dmpkillwm dwm") },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("$HOME/.config/dwm/autostart.sh") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	/*
	#ifndef __OpenBSD__
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,                   Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,                   Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,                   Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,                   Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,           Button1,        sigdwmblocks,   {.i = 6} },
	#endif
	*/
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	/*
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	*/
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

