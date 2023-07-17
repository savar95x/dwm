/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define BROWSER "firefox"
#define BROWSERALT "vimb"
// firefox, chromium, min, badwolf

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 4;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#1D2021";
static const char col_gray2[]       = "#282828";
static const char col_gray3[]       = "#bdae93";
static const char col_gray4[]       = "#BDAE93"/*"#fbf1c7"*/;
static const char col_cyan[]        = "#404040";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_gray3,  col_cyan  },
	[SchemeTitle]  = { col_gray4, "#1D2021",  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
//	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  //	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("dmenu_run")},
  { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("dmenu_run")},
  { MODKEY|ShiftMask,	XK_BackSpace,	   spawn,          SHCMD("$HOME/.local/binbg/dmpowermenu")},
  {  NULL ,         XF86XK_AudioLowerVolume, spawn,          SHCMD("pamixer -d 2 --allow-boost --set-limit 140 && pkill -RTMIN+10 dwmblocks")},
  {  NULL ,         XF86XK_AudioRaiseVolume, spawn,          SHCMD("pamixer -i 2 --allow-boost --set-limit 140 && pkill -RTMIN+10 dwmblocks")},
  { MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER)},
  { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD(BROWSERALT)},
  { MODKEY,                       XK_c,      spawn,          SHCMD("pgrep xbanish && pkill xbanish || setsid -f xbanish -t 1")},
  { MODKEY|ShiftMask,		XK_w,      spawn,          SHCMD("$HOME/.local/binbg/checkiitmlan")},
  { MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e lf") },
  { MODKEY,                       XK_n,      spawn,          SHCMD(TERMINAL " -e newsboat") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " -e neomutt") },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD(BROWSER " 'https://gmail.com'") },
//	{ MODKEY,                       XK_e,      spawn,          SHCMD(BROWSER " 'https://gmail.com'") },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD(TERMINAL " -e notes") },
	{ MODKEY,                       XK_m,      spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD(TERMINAL " -e gotop") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD(TERMINAL " -e shellcaster")},
	{ MODKEY,                       XK_s,      spawn,          SHCMD("$HOME/.local/binbg/dmlscripts") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
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
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
//	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,			XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,		XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,			XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
//	{ MODKEY,                       XK_Right,  viewnext,       {0} },
//	{ MODKEY,                       XK_Left,   viewprev,       {0} },
//	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
//	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
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
	//{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("$HOME/.local/binbg/dmpkillwm dwm") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

