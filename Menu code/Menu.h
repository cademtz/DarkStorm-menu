#pragma once
#include "SDK.h"

// Defining easy to use menu item types
#define tab "tab"
#define boolean "bool"
#define decimal "decimal"

// Struct to keep all the data of a menu item in one variable
struct menuItem
{
	char name[30];
	float *value;
	float min;
	float max;
	float step;
	string type;
};

class Menu
{
public:
	void paint();

	// Making arrays to list items in for statements
	menuItem tabArray[16];
	menuItem itemArray[32];
	int itemAmount, tabAmount; // Let the for statements know how far to go
	int tabIndex = 0, itemIndex = 0; // Keep track and control the user's selecting ability

	// If you want mouse controls or an adjustable menu, all the positions are controled by these two values!
	int menuX = 0, menuY = 200;

	// Using voids to easily add items to the menu
	int addTab(int arrayIndex, char name[30], float *value);
	int addBool(int arrayIndex, char name[30], float *value);
	int addFloat(int arrayIndex, char name[30], float *value, float min, float max, float step);

private:
	void handleInput();
	void createList();
	void startUp();

	unsigned long tabFont; // Declaring variables to hold the fonts
	unsigned long itemFont;

	bool menuToggle = false;
	bool bStartUp = true;

	// Just a big block of values to use for the items. Remove these if you want
	float misc = 0;
	float bHop = 0;
	float spinBot = 0;

	float esp = 0;
	float enabled = 0;
	float hue = 0;

	// Value used for animated the logo / tabs
	float introAnimation = 300;
};

extern Menu gMenu;
