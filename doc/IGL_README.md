# Overview
The entire sauce is a 2d array of components. some components have an onclick
function that user defines. When a user clicks on a component, the igl handles 
the ui changes and updates the users classes or whatever by calling the provided 
onclick function. 
> perhaps we can also add a condition parameter that igl can use to check if it 
should be throwing some visual error when the user tries to click a button that 
shouldn't be clicked


# component [struct]
- type (enum)
- void\* [ptr to the actual component]
- highlight [bool]
- highlight\_color [color\_t]

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
* Parameters *
- grid\_x
- grid\_y
- grid\_width
- grid\_height
- igl\_type\_t type 
- color\_t color

### igl\_set_\highlight [function]
Sets a component to be highlighted when clicked.
* Parameters *
- component\* component
- color\_t color

### igl\_set_\onclick [function]
Sets a component to clickable and sets the onclick function
* Parameters *
- component\* component
- color\_t color
- onclick\_fn\_t fn

# 
