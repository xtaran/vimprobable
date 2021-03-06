/*
    (c) 2009 by Leon Winter
    (c) 2009-2010 by Hannes Schueller
    (c) 2009-2010 by Matto Fransen
    (c) 2010 by Hans-Peter Deifel
    (c) 2010 by Thomas Adam
    see LICENSE file
*/

/* general settings */
static char startpage[1024]             = "http://www.vimprobable.org/";
static const gboolean enablePlugins     = TRUE; /* TRUE keeps plugins enabled */

/* appearance */
static const char statusbgcolor[]       = "#000000";            /* background color for status bar */
static const char statuscolor[]         = "#ffffff";            /* color for status bar */
static const char sslbgcolor[]          = "#b0ff00";            /* background color for status bar with SSL url */
static const char sslcolor[]            = "#000000";            /* color for status bar with SSL url */

                                        /*  normal,                 warning,                error       */
static const char *urlboxfont[]         = { "monospace normal 8",   "monospace normal 8",   "monospace bold 8"};
static const char *urlboxcolor[]        = { NULL,                   "#ff0000",              "#ffffff" };
static const char *urlboxbgcolor[]      = { NULL,                   NULL,                   "#ff0000" };

                                        /*  normal,                 error               */
static const char *completionfont[]     = { "monospace normal 8",   "monospace bold 8" };
                                                                                        /* topborder color */
static const char *completioncolor[]    = { "#000000",              "#ff00ff",              "#000000" };
                                                                                        /* current row background */
static const char *completionbgcolor[]  = { "#ffffff",              "#ffffff",              "#fff000" };
/* pango markup for prefix highliting:      opening,                closing             */
#define             COMPLETION_TAG_OPEN     "<b>"
#define             COMPLETION_TAG_CLOSE    "</b>"

static const char statusfont[]          = "monospace bold 8";   /* font for status bar */
#define             ENABLE_HISTORY_INDICATOR
#define             ENABLE_INCREMENTAL_SEARCH
#define             ENABLE_GTK_PROGRESS_BAR
#define             ENABLE_WGET_PROGRESS_BAR
static const int progressbartick        = 20;
static const char progressborderleft    = '[';
static const char progressbartickchar   = '=';
static const char progressbarcurrent    = '>';
static const char progressbarspacer     = ' ';
static const char progressborderright   = ']';

/* cookies */
#define             ENABLE_COOKIE_SUPPORT
#define             COOKIES_STORAGE_FILENAME    "%s/.config/vimprobable/cookies", getenv("HOME")
#define             COOKIES_STORAGE_READONLY    FALSE   /* if TRUE new cookies will be lost if you quit */

/* bookmarks */
#define             BOOKMARKS_STORAGE_FILENAME  "%s/.config/vimprobable/bookmarks", getenv("HOME")

/* history */
#define             HISTORY_MAX_ENTRIES         1000
#define             HISTORY_STORAGE_FILENAME    "%s/.config/vimprobable/history", getenv("HOME")
#define             CLOSED_URL_FILENAME         "%s/.config/vimprobable/closed", getenv("HOME")

/* quickmarks */
#define             QUICKMARK_FILE              getenv("HOME"), "/.config/vimprobable/quickmarks"

/* downloads directory */
#define             DOWNLOADS_PATH              "%s", getenv("HOME")

/* user styles */
#define             USER_STYLES_FILENAME        "%s/.config/vimprobable/style.css", getenv("HOME")

/* font size */
#define             DEFAULT_FONT_SIZE           12

/* Vimprobable version number */
#define             VERSION                     "0.9.20.5"
#define             INTERNAL_VERSION            "Vimprobable/" VERSION

/* user agent */
#define             USER_AGENT                  "Vimprobable/" VERSION

/* scrolling */
static unsigned int scrollstep          = 40;   /* cursor difference in pixel */
static unsigned int pagingkeep          = 40;   /* pixels kept when paging */
#define             DISABLE_SCROLLBAR

/* searching */
#define             ENABLE_MATCH_HIGHLITING
static const int searchoptions          = CaseInsensitive | Wrapping;
static const gboolean complete_case_sensitive = TRUE;

/* search engines */
static Searchengine searchengines[] = {
    { "i",          "http://ixquick.com/do/metasearch.pl?query=%s" },
    { "s",          "https://ssl.scroogle.org/cgi-bin/nbbwssl.cgi?Gw=%s" },
    { "w",          "https://secure.wikimedia.org/wikipedia/en/w/index.php?title=Special%%3ASearch&search=%s&go=Go" },
    { "wd",         "https://secure.wikimedia.org/wikipedia/de/w/index.php?title=Special%%3ASearch&search=%s&go=Go" },
};
static Searchengine *defsearch = &searchengines[0];

/* key bindings for normal mode
    Note: GDK_VoidSymbol is a wildcard so it matches on every modkey
*/
static Key keys[] = {
    /* modmask,             modkey,         key,            function,   argument */
    { 0,                    GDK_q,          GDK_1,          quickmark,  { .s = "1" } },
    { 0,                    GDK_q,          GDK_2,          quickmark,  { .s = "2"  } },
    { 0,                    GDK_q,          GDK_3,          quickmark,  { .s = "3" } },
    { 0,                    GDK_q,          GDK_4,          quickmark,  { .s = "4" } },
    { 0,                    GDK_q,          GDK_5,          quickmark,  { .s = "5" } },
    { 0,                    GDK_q,          GDK_6,          quickmark,  { .s = "6" } },
    { 0,                    GDK_q,          GDK_7,          quickmark,  { .s = "7" } },
    { 0,                    GDK_q,          GDK_8,          quickmark,  { .s = "8" } },
    { 0,                    GDK_q,          GDK_9,          quickmark,  { .s = "9" } },
    { 0,                    0,              GDK_0,          scroll,     {ScrollJumpTo   | DirectionLeft} },
    { GDK_SHIFT_MASK,       0,              GDK_dollar,     scroll,     {ScrollJumpTo   | DirectionRight} },

    { 0,                    GDK_g,          GDK_t,          fake_key_event,   { .s = "l", .i = ShiftMask + ControlMask  }},
    { GDK_SHIFT_MASK,       GDK_g,          GDK_T,          fake_key_event,   { .s = "h", .i = ShiftMask + ControlMask  }},
    { 0,                    GDK_g,          GDK_1,          fake_key_event,   { .s = "1", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_2,          fake_key_event,   { .s = "2", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_3,          fake_key_event,   { .s = "3", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_4,          fake_key_event,   { .s = "4", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_5,          fake_key_event,   { .s = "5", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_6,          fake_key_event,   { .s = "6", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_7,          fake_key_event,   { .s = "7", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_8,          fake_key_event,   { .s = "8", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_9,          fake_key_event,   { .s = "9", .i = ControlMask   } },
    { 0,                    GDK_g,          GDK_0,          fake_key_event,   { .s = "0", .i = ControlMask   } },

    { 0,                    GDK_g,          GDK_g,          scroll,     {ScrollJumpTo   | DirectionTop} },
    { GDK_SHIFT_MASK,       0,              GDK_G,          scroll,     {ScrollJumpTo   | DirectionBottom} },
    { 0,                    0,              GDK_h,          scroll,     {ScrollMove     | DirectionLeft     | UnitLine} },
    { 0,                    0,              GDK_j,          scroll,     {ScrollMove     | DirectionBottom   | UnitLine} },
    { 0,                    0,              GDK_k,          scroll,     {ScrollMove     | DirectionTop      | UnitLine} },
    { 0,                    0,              GDK_l,          scroll,     {ScrollMove     | DirectionRight    | UnitLine} },
    { 0,                    0,              GDK_space,      scroll,     {ScrollMove     | DirectionBottom   | UnitPage} },
    { GDK_SHIFT_MASK,       0,              GDK_space,      scroll,     {ScrollMove     | DirectionTop      | UnitPage} },
    { GDK_CONTROL_MASK,     0,              GDK_b,          scroll,     {ScrollMove     | DirectionTop      | UnitPage} },
    { GDK_CONTROL_MASK,     0,              GDK_f,          scroll,     {ScrollMove     | DirectionBottom   | UnitPage} },
    { GDK_CONTROL_MASK,     0,              GDK_d,          scroll,     {ScrollMove     | DirectionBottom   | UnitBuffer} },
    { GDK_CONTROL_MASK,     0,              GDK_u,          scroll,     {ScrollMove     | DirectionTop      | UnitBuffer} },
    { GDK_CONTROL_MASK,     0,              GDK_e,          scroll,     {ScrollMove     | DirectionBottom   | UnitLine} },
    { GDK_CONTROL_MASK,     0,              GDK_y,          scroll,     {ScrollMove     | DirectionTop      | UnitLine} },

    { GDK_CONTROL_MASK,     0,              GDK_i,          navigate,   {NavigationBack} },
    { GDK_CONTROL_MASK,     0,              GDK_o,          navigate,   {NavigationForward} },
    { GDK_SHIFT_MASK,       0,              GDK_H,          navigate,   {NavigationBack} },
    { GDK_SHIFT_MASK,       0,              GDK_L,          navigate,   {NavigationForward} },
    { 0,                    0,              GDK_r,          navigate,   {NavigationReload} },
    { GDK_SHIFT_MASK,       0,              GDK_R,          navigate,   {NavigationForceReload} },
    { GDK_CONTROL_MASK,     0,              GDK_c,          navigate,   {NavigationCancel} },

    { 0,                    0,              GDK_plus,       zoom,       {ZoomIn         | ZoomText} },
    { 0,                    0,              GDK_minus,      zoom,       {ZoomOut        | ZoomText} },
    { 0,                    GDK_z,          GDK_i,          zoom,       {ZoomIn         | ZoomText} },
    { 0,                    GDK_z,          GDK_o,          zoom,       {ZoomOut        | ZoomText} },
    { 0,                    GDK_z,          GDK_z,          zoom,       {ZoomReset      | ZoomText} },
    { GDK_SHIFT_MASK,       GDK_z,          GDK_I,          zoom,       {ZoomIn         | ZoomFullContent} },
    { GDK_SHIFT_MASK,       GDK_z,          GDK_O,          zoom,       {ZoomOut        | ZoomFullContent} },
    { GDK_SHIFT_MASK,       GDK_z,          GDK_Z,          zoom,       {ZoomReset      | ZoomFullContent} },

    { 0,                    0,              GDK_y,          yank,       {SourceURL      | ClipboardPrimary  | ClipboardGTK} },
    { GDK_SHIFT_MASK,       0,              GDK_Y,          yank,       {SourceSelection} },

    { 0,                    GDK_g,          GDK_u,          descend,    {NthSubdir} },
    { GDK_SHIFT_MASK,       GDK_g,          GDK_U,          descend,    {Rootdir} },

    { 0,                    GDK_g,          GDK_h,          open_arg,   {TargetCurrent, startpage} },
    { GDK_SHIFT_MASK,       GDK_g,          GDK_H,          open_arg,   {TargetNew,     startpage} },

    { 0,                    0,              GDK_p,          paste,      {TargetCurrent  | ClipboardPrimary  | ClipboardGTK} },
    { GDK_SHIFT_MASK,       0,              GDK_P,          paste,      {TargetNew      | ClipboardPrimary  | ClipboardGTK} },

    { GDK_CONTROL_MASK,     0,              GDK_a,          number,     {Increment} },
    { GDK_CONTROL_MASK,     0,              GDK_x,          number,     {Decrement} },

    { 0,                    0,              GDK_n,          search,     {DirectionNext      | CaseInsensitive   | Wrapping} },
    { GDK_SHIFT_MASK,       0,              GDK_N,          search,     {DirectionPrev      | CaseInsensitive   | Wrapping} },

    { GDK_SHIFT_MASK,       0,              GDK_colon,      input,      {.s = ":" } },
    { 0,                    0,              GDK_o,          input,      {.s = ":open "} },
    { GDK_SHIFT_MASK,       0,              GDK_O,          input,      {.s = ":open ", .i = InsertCurrentURL} },
    { 0,                    0,              GDK_t,          input,      {.s = ":tabopen "} },
    { GDK_SHIFT_MASK,       0,              GDK_T,          input,      {.s = ":tabopen ", .i = InsertCurrentURL} },
    { 0,                    0,              GDK_slash,      input,      {.s = "/"} },
    { GDK_SHIFT_MASK,       0,              GDK_slash,      input,      {.s = "/"} },
    { GDK_SHIFT_MASK,       0,              GDK_question,   input,      {.s = "?"} },

    { 0,                    GDK_VoidSymbol, GDK_Escape,     set,        {ModeNormal} },
    { GDK_CONTROL_MASK,     0,              GDK_z,          set,        {ModePassThrough} },
    { GDK_CONTROL_MASK,     0,              GDK_v,          set,        {ModeSendKey} },
    { 0,                    0,              GDK_f,          set,        { .i = ModeHints, .s = "current" } },
    { GDK_SHIFT_MASK,       0,              GDK_F,          set,        { .i = ModeHints, .s = "new" } },

    { 0,                    GDK_g,          GDK_i,          focus_input,{} },
    { 0,                    0,              GDK_u,          revive,     {} },

    { 0,                    0,              GDK_d,          quit,       {0} },

    { 0,                    0,              GDK_w,          toggle_plugins,{0} },
    { 0,                    0,              GDK_e,          toggle_images,{0} },
};

/* command mapping */
static Command commands[] = {
    /* command,                                             function,   argument */
    { "ba",                                                 navigate,    {NavigationBack} },
    { "back",                                               navigate,    {NavigationBack} },
    { "ec",                                                 script,      {Info} },
    { "echo",                                               script,      {Info} },
    { "echoe",                                              script,      {Error} },
    { "echoerr",                                            script,      {Error} },
    { "fw",                                                 navigate,    {NavigationForward} },
    { "fo",                                                 navigate,    {NavigationForward} },
    { "forward",                                            navigate,    {NavigationForward} },
    { "javascript",                                         script,      {Silent} },
    { "o",                                                  open_arg,    {TargetCurrent} },
    { "open",                                               open_arg,    {TargetCurrent} },
    { "q",                                                  quit,        {0} },
    { "quit",                                               quit,        {0} },
    { "re",                                                 navigate,    {NavigationReload} },
    { "re!",                                                navigate,    {NavigationForceReload} },
    { "reload",                                             navigate,    {NavigationReload} },
    { "reload!",                                            navigate,    {NavigationForceReload} },
    { "qt",                                                 search_tag,  {0} },
    { "st",                                                 navigate,    {NavigationCancel} },
    { "stop",                                               navigate,    {NavigationCancel} },
    { "t",                                                  open_arg,    {TargetNew} },
    { "tabopen",                                            open_arg,    {TargetNew} },
    { "print",                                         	    print_frame, {0} },
    { "bma",                                                bookmark,    {0} },
    { "bookmark",                                           bookmark,    {0} },
    { "source",                                             view_source, {0} },
};

/* mouse bindings
   you can use MOUSE_BUTTON_1 to MOUSE_BUTTON_5
*/
static Mouse mouse[] = {
    /* modmask,             modkey,         button,            function,   argument */
    { 0,                    0,              MOUSE_BUTTON_2,    paste,      {TargetCurrent  | ClipboardPrimary  | ClipboardGTK, rememberedURI} },
    { GDK_CONTROL_MASK,     0,              MOUSE_BUTTON_2,    paste,      {TargetNew  | ClipboardPrimary  | ClipboardGTK} },
    { GDK_CONTROL_MASK,     0,              MOUSE_BUTTON_1,    open_arg,   {TargetNew, rememberedURI} },
};
