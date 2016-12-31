#pragma once
#include "CDrawManager.h"

#define FONTFLAG_NONE 0x000
#define FONTFLAG_ITALIC 0x001
#define FONTFLAG_UNDERLINE 0x002
#define FONTFLAG_STRIKEOUT 0x004
#define FONTFLAG_SYMBOL 0x008
#define FONTFLAG_ANTIALIAS 0x010
#define FONTFLAG_GAUSSIANBLUR 0x020
#define FONTFLAG_ROTARY 0x040
#define FONTFLAG_DROPSHADOW 0x080
#define FONTFLAG_ADDITIVE 0x100
#define FONTFLAG_OUTLINE 0x200
#define FONTFLAG_CUSTOM 0x400

class fontString
{
public:
	void DrawString( int x, int y, DWORD dwColor, unsigned long font, const char *pszText, ... );
};

extern fontString gFontString;