# BetterMenu
Just a neat menu source for the TF2 DarkStorm base

## Table of contents:
- [Format for adding items](#items)
 - [Example of adding items](#example)
- [Using animation](#animating)

## Items
This is the format for adding items. Note that the names have a 30 character limit

 ```cpp
 addTab(int index, char name[30], float *value)
 addBool(int index, char name[30], float *value)
 addFloat(int index, char name[30], float *value, int min, int max, int step)
 // Step is how much the item will increment / decrement
 ```

### Example
This is what adding items should look like.
 
 Random example header for a hack:
 ```cpp
 class Esp
 {
 public:
  float espTab = 0;  // You must use variables for your menu items.
  float enabled = 0; // If you don't, then the menu breaks because it can't control the values
  float hue = 0;     // Such as doing something like 'addBool(i, "Name", false)'
 };
 
 extern Esp gEsp;
 ```
 
 To actually use those values in the menu, insert them in the createList void in Menu.cpp like so:
 ```cpp
 #include "Example esp hack" // You must include your hack to use it's variables
 
 void Menu::createList()
 {
  int t = 0, i = 0; // These ints are used to keep track of how many
                    // items / tabs the menu will need to look for.
  
  t = (t, "ESP", &gEsp.espTab); // Note the & before all the variables used
  // Make sure you use an if statement with your tab variable, otherwise items will appear regardless of the tab
  if (gEsp.espTab == 1)
  {
    i = addBool(i, "Enabled", &gEsp.enabled);
    i = addFloat(i, "Outline hue", &gEsp.hue, 0, 255, 1);
  }
  
  tabAmount = t; itemAmount = i; // Do this to let the menu know how many items to look for
 }
 ```
## Animating
You may notice that the default menu has an interesting animation with the logos and tabs sliding into view. This is done using the Animate functions in Animate.h
