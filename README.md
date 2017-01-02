# BetterMenu
Just a neat menu source for the TF2 DarkStorm base

## Table of contents:
- [How to quickly add the menu to your hack](#menu)
- [Format for adding items](#items)
 - [Example of adding items](#example)
- [Using Animate.h](#animating)
 - [Linear](#linear)
 - [Ease in](#ease-in)
 - [Ease out](#ease-out)
- [Credits](#credits)
 
## Menu
To quickly add this menu into your hack, all you have to do is add all the .cpp and .h files into your DarkStorm hack, and call `gMenu.paint()` in DarkStorm's `Panels.cpp` (Also known as Paint traverse.)

That's it! All you need to do is add tabs and items to control you hack. Feel free to follow the small tutorial below.

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
You may notice that the default menu has an interesting animation with the logo and tabs sliding into view. This is done using the easeIn function in Animate.h

There's three different animation functions you can use, and they're pretty simple, but to actually use them you will need to know a little bit about how they work.

###Linear
This is the most basic one. This has a linear effect meaning it moves at a constant speed.

You have `value` which must be less than `end` because it gets incremented by `speed` (which can be any value).

Example:
```cpp
#include "Animate.h" // You must include this to use the animate functions

float f = 1;

void yourHack::main()
{
 f = gAnimate.linear(f, 300, 0.5);
}
```

### Ease in:
This is what I used to animte the logo and tabs. easeIn will take `value` and multiply it by `speed`. This is so that the `value` will appear to be animated by starting at a fair speed and slowing to a stop (also known as easing in).

`value` must be greater than `end`, because it gets multiplied by `speed` (which MUST be less than 1) to get the slowing down effect.
This also means that if `speed` is 0.5, the animation will be faster than if `speed` were 0.9.

Note: Since the ease functions work by multiplying, using `0` for `value` will result in no animation.

Format:
```cpp
 int easeIn(float value, float end, float speed);
```

Example:
```cpp
#include "Animate.h" // You must include this to use the animate functions

float f = 300;

void yourHack::main()
{
 f = gAnimate.easeIn(f, 0, 0.9);
}
```

Important: Since you can't use negative numbers (because of buggy effects), just add or subtract a variable with your animated variable to get an opposite-direction effect.

### Ease out
This will cause a value to start increasing at a slow pace, accelerate, and eventualy halt at the end value.

Once you know how to use easeIn, this will be similar. The main difference is that `end` must be larger than `value`. This is so that `speed` (which MUST be greater than 1) can achieve the reverse effect of easeIn as described above.

Example:
```cpp
#include "Animate.h" // You must include this to use the animate functions

float f = 1;

void yourHack::main()
{
 f = gAnimate.easeOut(f, 300, 1.1);
}
```
## Credits

* gir489
  - Developed and released the base that I made the cheat menu for.
 
* katetem
  - Developed and released CrapStorm which I (Practically copied) the adding items and tabs functions from.
   
* josh33901 (or F1ssi0N)
  - Developed and released F1-Public which helped me learn how to use DarkStorm
