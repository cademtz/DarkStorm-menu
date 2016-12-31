#include "Menu.h"

#include "CDrawManager.h"
#include "commonColors.h"
#include "fontString.h"

#include <string>
#include <conio.h>

Menu gMenu;

void Menu::createList()
{
	int t = 0, i = 0; // Use these to find how many items / tabs to look for

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
		i = addFloat(i, "Hue", &hue, 0, 255, 1);
	}

	tabAmount = t; itemAmount = i;
}

void Menu::paint()
{
	if (bFontSetup) // So we only create the fonts once
	{
		fontSetup(); // Create the needed fonts
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

		// Draw the transparent background
		gDrawManager.DrawRect(menuX, menuY, 600, 350, menuBack);

		// Render all the tabs
		for (int i = 0; i < tabAmount; i++)
		{
			int x = menuX + 10;
			int y = menuY + (20 + (i * 40)); // Everytime a tab is found, make it lower than the last

			if (i == tabIndex) // If the tab we're rendering is selected, make it blue
			{
				gFontString.DrawString(x + 5, y, bluTeam, tabFont, tabArray[i].name);
			}
			else // If it's not selected, make a plain tab
			{
				gFontString.DrawString(x + 5, y, light, tabFont, tabArray[i].name);
			}
		}

		// Render all the items in selected tab
		for (int i = 0; i < itemAmount; i++)
		{
			int x = menuX + 200;
			int y = menuY + (60 + (i * 40)); // Make each item lower than the last

			if (itemArray[i].type == boolean) // If the item is a bool, then use checkboxes
			{
				if (i == itemIndex) // If our item is selected, make it blue
				{
					gFontString.DrawString(x, y - 15, bluTeam, itemFont, itemArray[i].name);
				}
				else // If it's not selected, make it plain
				{
					gFontString.DrawString(x, y - 15, light, itemFont, itemArray[i].name);
				}

				gDrawManager.DrawRect(x - 25, y - 15, 20, 20, dark); // Draw checkbox background

				if (itemArray[i].value[0] == 1) // If the value = true, add a check in the box
				{
					gDrawManager.DrawRect(x - 22, y - 12, 14, 14, bluTeam);
				}
			}
			else if (itemArray[i].type == decimal) // Otherwise, if it's a decimal, use sliders
			{
				if (i == itemIndex)
				{
					gFontString.DrawString(x - 25, y - 25, bluTeam, itemFont, itemArray[i].name);
				}
				else
				{
					gFontString.DrawString(x - 25, y - 25, light, itemFont, itemArray[i].name);
				}

				// Get the distance from the value to the max out of 100
				int a = 100 * itemArray[i].value[0] / itemArray[i].max;

				gDrawManager.DrawRect(x - 25, y, 100, 10, dark); // Draw the slider background
				gDrawManager.DrawRect(x - 25, y, a, 10, bluTeam); // Draw the slider progress

				// Draw the value next to the progress of the slider
				gFontString.DrawString(a + x - 25, y, light, itemFont, to_string(int(itemArray[i].value[0])).c_str());
			}
		}
	}
}

void Menu::fontSetup()
{
	itemFont = gInts.Surface->CreateFont();
	gInts.Surface->SetFontGlyphSet(itemFont, "Trebuchet MS", 20, 800, 0, 0, FONTFLAG_ANTIALIAS);

	tabFont = gInts.Surface->CreateFont();
	gInts.Surface->SetFontGlyphSet(tabFont, "Tahoma", 40, 4000, 0, 0, FONTFLAG_ANTIALIAS);

	bFontSetup = false; // create the fonts once to prevent an overload leading to a crash
}

// All these "add" voids are used because DarkStorm does not like it when you use structs with {}

int Menu::addTab(int arrayIndex, char name[30], float *value)
{
	if (*value != 0 && *value != 1) // If it's not a bool value, then don't make it
		return arrayIndex;

	if (name == NULL || name == "") // If it has no name, then don't make it
		return arrayIndex;

	tabArray[arrayIndex].type = tab;
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

	itemArray[arrayIndex].type = boolean;
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

	itemArray[arrayIndex].type = decimal;
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
			tabArray[tabIndex].value[0] = 1; // Just a sloppy way of making sure one tab is enabled
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
	else if (GetAsyncKeyState(VK_UP) & 0x1)  // If you're about to go below the amount, go to the max
	{
		if (itemIndex - 1 < 0)
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