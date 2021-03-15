# Overview
The entire sauce is a 2d array of components. some components have an onclick
function that user defines. When a user clicks on a component, the igl handles 
the ui changes and updates the users classes or whatever by calling the provided 
onclick function. 
> perhaps we can also add a condition parameter that igl can use to check if it 
should be throwing some visual error when the user tries to click a button that 
shouldn't be clicked


# components
- struct
- type (enum)
- void* to the actual component
## Types of components
- button 
- view pane
## Button 
- grid_x
- grid_y
- grid_width
- grid_height
- type [rect, triangle]
- onclick function
- created with igl_create_button

### igl\_create\_button


# 
