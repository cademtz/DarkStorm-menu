#include "Menu.h"

#include "CDrawManager.h"
#include "commonColors.h"
#include "fontString.h"
#include "Animate.h"

#include <string>
#include <conio.h>

Menu gMenu;

void Menu::createList()
{
	int t = 0, i = 0; // Use these to keep track of tab / item amount

	t = addTab(t, "Misc", &misc); // Add a tab connected to a value
	if (misc == 1) // If this tab is selected, then load these items
	{
		i = addBool(i, "Bunny hop", &bHop); // Add an item connected to a value
		i = addBool(i, "Spin bot", &spinBot);
	}

	t = addTab(t, "ESP", &esp);
	if (esp == 1)
	{
		i = addBool(i, "Enabled", &enabled);
		i = addFloat(i, "Outline hue", &hue, 0, 255, 1);
	}
	
	// Feel free to clear all these test tabs and items if you like

	tabAmount = t; itemAmount = i;
}

void Menu::paint()
{
	if (bStartUp) // Only runs once
	{
		startUp();
	}

	if (GetAsyncKeyState(VK_INSERT) & 0x1)
	{
		menuToggle = !menuToggle;
	}

	if (menuToggle)
	{
		// Get the input of course!
		handleInput();

		// Refresh the list of items
		createList();

		// Draw the background
		gDrawManager.DrawRect(menuX, menuY, 600, 350, menuBack);

		// Adjust this to fit your cheat name
		gDrawManager.DrawRect(menuX - 40, menuY - 40, 180, 40, dark);

		// Ease the value of introAnimation to 0 by a factor of 0.9
		introAnimation = gAnimate.easeIn(introAnimation, 0, 0.9);

		// Feel free to put your cheat name here!
		gFontString.DrawString((menuX + 10) - introAnimation, menuY - 35, redTeam, tabFont, "BetterMenu");

		// Render all the tabs
		for (int i = 0; i < tabAmount; i++)
		{
			int x = menuX + 15;
			int y = menuY + (10 + (i * 30)); // Make each tab lower than the last

			if (i == tabIndex) // If the tab we're rendering is selected, make it blue
			{
				gFontString.DrawString(x - introAnimation, y, bluTeam, tabFont, tabArray[i].name);
			}
			else // If it's not selected, make a plain tab
			{
				gFontString.DrawString(x - introAnimation, y, light, tabFont, tabArray[i].name);
			}
		}

		// Render all the items in selected tab
		for (int i = 0; i < itemAmount; i++)
		{
			int x, y;
			if (i <= 11)
			{
				x = menuX + 200;
				y = menuY + 30 + (i * 28); // Make each item lower than the last
			}
			else if (i <= 23) // If there are too many items, start a new row
			{
				x = menuX + 320;
				y = menuY + 30 + ((i - 12) * 28);
			}
			else // And another row
			{
				x = menuX + 440;
				y = menuY + 30 + ((i - 24) * 28);
			}

			if (itemArray[i].type == BOOL) // If the item is a bool, then use checkboxes
			{
				if (i == itemIndex) // If our item is selected, make it blue
				{
					gFontString.DrawString(x, y - 15, bluTeam, itemFont, itemArray[i].name);
				}
				else // If it's not selected, make it plain
				{
					gFontString.DrawString(x, y - 15, light, itemFont, itemArray[i].name);
				}

				gDrawManager.DrawRect(x - 25, y - 15, 15, 15, dark); // Draw checkbox background
				gDrawManager.OutlineRect(x - 26, y - 16, 17, 17, gray); // Draw checkbox outline

				if (itemArray[i].value[0] == 1) // If the value = true, add a check in the box
				{
					gDrawManager.DrawRect(x - 23, y - 13, 11, 11, bluTeam);
				}
			}
			else if (itemArray[i].type == DECIMAL) // Otherwise, if it's a decimal, use sliders
			{
				// Get the distance from the value to the max out of 100
				int a = 100 * itemArray[i].value[0] / itemArray[i].max;

				gDrawManager.DrawRect(x - 26, y - 10, 100, 10, dark); // Draw the slider background
				gDrawManager.DrawRect(x - 26, y - 10, a, 10, bluTeam); // Draw the slider progress

				gDrawManager.DrawRect(x - 26, y + 2, 100, 1, gray); // Extra line below slider

				if (i == itemIndex)
				{
					gFontString.DrawString(x - 20, y - 25, bluTeam, itemFont, itemArray[i].name);

					// Draw the value next to the progress of the slider
					gFontString.DrawString(a + x - 20, y - 12, bluTeam, itemFont, to_string(int(itemArray[i].value[0])).c_str());
				}
				else
				{
					gFontString.DrawString(x - 20, y - 25, light, itemFont, itemArray[i].name);

					gFontString.DrawString(a + x - 20, y - 12, light, itemFont, to_string(int(itemArray[i].value[0])).c_str());
				}
			}
		}
	}
	else
	{
		introAnimation = 300; // Reset the animated offset
	}
}

void Menu::startUp()
{
	itemFont = gInts.Surface->CreateFont();
	gInts.Surface->SetFontGlyphSet(itemFont, "Tahoma", 15, 1800, 0, 0, FONTFLAG_ANTIALIAS);

	tabFont = gInts.Surface->CreateFont();
	gInts.Surface->SetFontGlyphSet(tabFont, "Impact", 26, 1800, 0, 0, FONTFLAG_ANTIALIAS);

	bStartUp = false; // create the fonts once to prevent an overload leading to a crash
}

int Menu::addSpace(int arrayIndex)
{
	tabArray[arrayIndex].type = SPACE;
	return arrayIndex + 1;
}

int Menu::addTab(int arrayIndex, char name[30], float *value)
{
	if (*value != 0 && *value != 1) // If it's not a bool value, then don't make it
		return arrayIndex;

	if (name == NULL || name == "") // If it has no name, then don't make it
		return arrayIndex;

	tabArray[arrayIndex].type = TAB;
	tabArray[arrayIndex].value = value;
	tabArray[arrayIndex].min = 0;
	tabArray[arrayIndex].max = 1;
	tabArray[arrayIndex].step = 1;

	strcpy(tabArray[arrayIndex].name, name);

	return arrayIndex + 1;
}

int Menu::addBool(int arrayIndex, char name[30], float *value)
{
	if (*value != 0 && *value != 1) // If it's not a bool value, then don't make it
		return arrayIndex;

	if (name == NULL || name == "") // If it has no name, then don't make it
		return arrayIndex;

	itemArray[arrayIndex].type = BOOLEAN;
	itemArray[arrayIndex].value = value;
	itemArray[arrayIndex].min = 0;
	itemArray[arrayIndex].max = 1;
	itemArray[arrayIndex].step = 1;

	strcpy(itemArray[arrayIndex].name, name);
	
	return arrayIndex + 1;
}

int Menu::addFloat(int arrayIndex, char name[30], float *value, float min, float max, float step)
{
	if (name == NULL || name == "") // If it has no name, then don't make it
		return arrayIndex;

	itemArray[arrayIndex].type = DECIMAL;
	itemArray[arrayIndex].value = value;
	itemArray[arrayIndex].min = min;
	itemArray[arrayIndex].max = max;
	itemArray[arrayIndex].step = step;

	strcpy(itemArray[arrayIndex].name, name);

	return arrayIndex + 1;
}

void Menu::handleInput()
{
	if (GetAsyncKeyState(VK_TAB) & 0x1)
	{
		itemIndex = 0; // Reset the item index to prevent buggy selections

		if (tabIndex + 1 > tabAmount - 1) // If you're about to go above the amount, go to 0
		{
			tabArray[tabIndex].value[0] = 0;
			tabIndex = 0;
			tabArray[tabIndex].value[0] = 1; // Just a sloppy way of making sure one tab is enabled
		}
		else // Otherwise, increment
		{
			tabArray[tabIndex].value[0] = 0;
			tabIndex++;
			tabArray[tabIndex].value[0] = 1;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x1)
	{
		if (itemIndex + 1 > itemAmount - 1) // If you're about to go above the amount, go to 0
		{
			itemIndex = 0;
		}
		else // Otherwise, increment
		{
			itemIndex++;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x1)
	{
		if (itemIndex - 1 < 0) // If you're about to go below the amount, go to the max
		{
			itemIndex = itemAmount - 1;
		}
		else // Otherwise, decrement
		{
			itemIndex--;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x1)
	{
		// If you're about to go below the min, then go back to the max
		if (itemArray[itemIndex].value[0] - itemArray[itemIndex].step < itemArray[itemIndex].min)

			itemArray[itemIndex].value[0] = itemArray[itemIndex].max;

		else // Otherwise, keep going down

			itemArray[itemIndex].value[0] -= itemArray[itemIndex].step;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x1)
	{
		// If you're about to go above the max, then go back to the min
		if (itemArray[itemIndex].value[0] + itemArray[itemIndex].step > itemArray[itemIndex].max)

			itemArray[itemIndex].value[0] = itemArray[itemIndex].min;

		else // Otherwise, keep going up

			itemArray[itemIndex].value[0] += itemArray[itemIndex].step;
	}
}
