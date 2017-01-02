# BetterMenu
Just a neat menu source for the TF2 DarkStorm base

## Table of contents:
- [Format for adding items](#items)
 - [Example of adding items](#example)
- [Using animation](#animating)
 - [Ease in](#Ease in)

## Items
This is the format for adding items. Note that the names have a 30 character limit

 ```cpp
 int addTab(int index, char name[30], float *value);
 int addBool(int index, char name[30], float *value);
 int addFloat(int index, char name[30], float *value, int min, int max, int step);
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
You may notice that the default menu has an interesting animation with the logo and tabs sliding into view. This is done using the ease functions in Animate.h

There's actully three different animation functions you can use, and they're pretty simple, but to actually use them you will need to know a little bit about how they work.

### Ease in:
This is what I used to animte the logo and tabs. easeIn will take a float value and multiply it by a value LESS than 1. This is so that the animated value will start at a fair speed, and slow to a stop (also known as easing in).

Format:
```cpp
 int easeIn(float value, float end, float speed);
 // Note that the speed MUST be less than 1, or it will skip to the end of the animation
 // to prevent really buggy results.
 
 // The value must also be greater than the end (The value the animation will try to reach)
 // since it works by decreasing the animated value. This means that you can't use negative values either.
 // You can just add / subtract if you want to decrease or increase a value.
```

Example:
```cpp
#include "Animate.h" // You must include this to use the animate functions

float f = 300;

void yourHack::main()
{
 f = easeIn(f, 300 /*This is the value easeIn will try to reach*/, 0.9 /*Speed*/);
}
```

If you add or subtract a value like the X axis of a square, then the square will ease into the left / right.
