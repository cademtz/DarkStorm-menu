# DarkStorm-menu
Just a neat menu source for the TF2 DarkStorm base

## Format for adding items:
 ```cpp
 addTab(int index, char name[30], float *value)
 addBool(int index, char name[30], float *value)
 addFloat(int index, char name[30], float *value, int min, int max, int step)
 // Step is how much the item will increment / decrement
 ```

## If you don't know how to properly add items to the menu, refer to this example:
 
 Random example header for a hack:
 ```cpp
 class Esp
 {
 public:
  float espTab = 0;
  float enabled = 0;
  float hue = 0;
 };
 
 extern Esp gEsp
 ```
 
 To actually use those values in the menu to modify, insert them in the createList void in Menu.cpp like so:
 ```cpp
 #include "Example esp hack" // You must include your hack
 
 void Menu::createList()
 {
  int t = 0, i = 0; // Use I to add items, and T to add tabs
  
  t = (t, "ESP", &gEsp.espTab); // Note the & before all the variables used
  // Make sure you use an if statement with your tab variable, otherwise it will appear regardless of the tab
  if (gEsp.espTab)
  {
    i = addBool(i, "Enabled", &gEsp.enabled);
    i = addFloat(i, "Outline hue", &gEsp.hue, 0, 255, 1);
  }
  
  tabAmount = t; itemAmount = i; // Do this to let the menu know what items to look for
 }
 ```
