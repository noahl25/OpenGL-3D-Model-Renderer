#shader vertex
#version 330 core  

layout(location = 0) in vec4 position;  
layout(location = 1) in vec4 color;

flat out vec4 v_Color;
 
uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;
 
void main()  
{  
    gl_Position = u_Projection * u_View * u_Model * position;
 
    v_Color = color;
 
}  
#shader fragment
#version 330 core  

layout (location = 0) out vec4 outcolor; 

flat in vec4 v_Color;

void main()  
{  
    outcolor = v_Color;

}