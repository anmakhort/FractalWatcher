#ifndef CONCOLOR_H
#define CONCOLOR_H

#define _ESC_			"\033["
#define _APPLY_			"m"
#define _RESET_ 		_ESC_ "0" _APPLY_

// Text modes:
#define _BOLD_			"1"
#define _DIM_			"2"
#define _ITALIC_		"3"
#define _UNDERLINE_ 	"4"
#define _BLINK_			"5"
#define _REVERSE_		"7"
#define _HIDDEN_		"8"

// Text colors:
#define _FG_BLACK_		"30"
#define _FG_RED_ 		"31"
#define _FG_GREEN_		"32"
#define _FG_YELLOW_		"33"
#define _FG_BLUE_  		"34"
#define _FG_MAGENTA_	"35"
#define _FG_CYAN_		"36"
#define _FG_WHITE_		"37"

// Background colors:
#define _BG_BLACK_		"40"
#define _BG_RED_ 		"41"
#define _BG_GREEN_		"42"
#define _BG_YELLOW_		"43"
#define _BG_BLUE_  		"44"
#define _BG_MAGENTA_	"45"
#define _BG_CYAN_		"46"
#define _BG_WHITE_		"47"

#define COLOR(text,color)			_ESC_ color _APPLY_ text _RESET_
#define BOLD(text,color)			_ESC_ _BOLD_ ";" color _APPLY_ text _RESET_
#define BOLD_ITALIC(text,color)		_ESC_ _BOLD_ ";" _ITALIC_ ";" color _APPLY_ text _RESET_
#define BOLD_UNDERLINE(text,color)	_ESC_ _BOLD_ ";" _UNDERLINE_ ";" color _APPLY_ text _RESET_

#define TEXT_BG_FG(text,bg,fg)				_ESC_ fg ";" bg _APPLY_ text _RESET_
#define TEXT_MODE_BG_FG(text,mode,bg,fg)	_ESC_ mode ";" fg ";" bg _APPLY_ text _RESET_

#endif