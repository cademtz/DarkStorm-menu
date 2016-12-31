#include "fontString.h"

fontString gFontString;

void fontString::DrawString( int x, int y, DWORD dwColor, unsigned long font, const char *pszText, ...)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start(va_alist, pszText);
	vsprintf_s(szBuffer, pszText, va_alist);
	va_end(va_alist);

	wsprintfW(szString, L"%S", szBuffer);

	gInts.Surface->DrawSetTextPos(x, y);
	gInts.Surface->DrawSetTextFont(font);
	gInts.Surface->DrawSetTextColor(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
	gInts.Surface->DrawPrintText(szString, wcslen(szString));
}