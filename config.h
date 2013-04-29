/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Sans-Serif Bold 9";
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#eeeeee";
static const char selbordercolor[]  = "#33b5e5";
static const char selbgcolor[]      = "#000000";
static const char selfgcolor[]      = "#33b5e5";
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int hgap      = 14;       /* snap pixel */
static const unsigned int vgap      = 14;
static const unsigned int flt       = 14/4;
static const unsigned int fld       = 14/4;
static const unsigned int fls       = 100;
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool showsystray       = True;

/* tagging */
static const char *tags[] = { "\u2776", "\u2777", "\u2778", "\u2779", "\u277A", "\u277B", "\u277C", "\u277D", "\u277E" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,      NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\u25C8",      tile },    /* first entry is default */
	{ "\u25A3",      NULL },    /* no layout function means floating behavior */
	{ "\u25C9",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *fmcmd[]  = { "urxvt", "-e", "ranger", NULL };
static const char *bwcmd[]  = { "firefox", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = bwcmd} },
	{ MODKEY,                       XK_r,      spawn,          {.v = fmcmd} },
	{ MODKEY,                       XK_f,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.134} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.134} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      togglelayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      togglelayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      togglelayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  togglelayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	//{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
};

