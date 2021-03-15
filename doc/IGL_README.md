# Overview
Using user provided gird\_(width/height), represents the framebuffer as a 
grid of components, some components have an onclick function 
When a user clicks on a component, the igl handles 
the ui changes and updates the users modules by calling the provided 
onclick function. 

> perhaps we can also add a condition parameter that igl can use to check if it 
should be throwing some visual error when the user tries to click a button that 
shouldn't be clicked


## Main
### igl\_init
Initializes igl, grid\_num\_x and grid\_num\_y
*Parameters*
- int grid\_num\_x
- int grid\_num\_y
*Returns*
- true if successful
- false otherewise

### igl\_update\_mouse
Updates the view buffer and user module based on mouse event
*Parameters* 
- mouse\_event\_t evt
*Returns*
- true if successful
- false otherewise

## Mouse Pointer [struct]
- pointer\_size
- x
- y
- content\_beneath \[pointer\_size][pointer\_size]
# component [struct]
- type (enum)
- void\* [ptr to the actual component]
- highlight [bool]
- hover [bool]
- alt\_color [color\_t]

## Types of components
- button 
- view pane


## Button [struct]
- grid\_x
- grid\_y
- grid\_width
- grid\_height
- type [rect, triangle]
- onclick function

### onclick function
typedef bool (\*onclick\_fn\_t)(void);

### igl\_create\_button [function]
Creates a button
*Parameters*
- grid\_x
- grid\_y
- grid\_width
- grid\_height
- igl\_button\_type\_t type 
- color\_t color
*Returns*

### igl\_button\_type\_t [enum]
*Values*
- BTN\_T\_RECT
- BTN\_T\_TRIA
- BTN\_T\_CHAR

### igl\_set_\highlight [function]
Sets a component to be highlighted when clicked.
*Parameters*
- component\* component component to be highlighted
- color\_t alt\_color   color around component when clicked or hovered over

### igl\_set_\hover [function]
Sets a component to be highlighted when hovered over.
*Parameters*
- component\* component
- color\_t alt\_color

### igl\_set_\onclick [function]
Sets a component to clickable and sets the onclick function
*Parameters*
- component\* component
- color\_t color
- onclick\_fn\_t fn

### igl\_rotate\_btn 
Used to rotate a button, only really useful with rectangular buttons
- button\_t button
- int degrees
