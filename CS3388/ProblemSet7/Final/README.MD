# Problem Set 7 - Arsalaan Ali

## Part 1

### VertexShaderCode

I take in the vertex attributes of g_vert_buffer and g_color_buffer using

```
layout(location = 0) in vec3 vertexPosition;\n\
layout(location = 1) in vec3 color;\n\
```

this code allows the shader to grab the values from the vertex buffer and color buffer

I use `out vec3 fragmentColor;\n\` to pass a value onto the fragment shader

then I set the vertex position to the value from the vertex buffer using `gl_Position = vec4(vertexPosition, 1.0);\n\` \
then I set the fragmentColor value, which will be passed on to the fragmentShader, to the value from the color buffer using `fragmentColor = color;\n\`

### FragmentShaderCode

I take in the fragmentColor value passed from the vertex shader using `in vec3 fragmentColor;\n\`
and then I set the output, which will determine the color, using `out vec4 color;\n\`

I use this code to check if the r value is above 0.5, and if it is I output black, otherwise i output the actual color

```
void main() {\n\
			//SHADER CODE\n\
            float r_val = fragmentColor.r;\n\
			if(r_val > 0.5){\n\
				color = vec4(0.0, 0.0, 0.0, 0.0);\n\
			}\n\
			else{\n\
				color = vec4(fragmentColor, 1.0);\n\
			}\n\
		}\n";
```

## Part 2

### Error in given code

In the given code these lines were missing

```
GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
```

And the program did not compile without them, so I added them in

### VertexShaderCode

Is the same as part 1 except the value passed to fragmentshader is a vec2 from the UV buffer instead of a vec3.

### FragmentShaderCode

This code is used to set the color to the values from the UV map, with blue being 0 and alpha being 1 \
`fragmentColor = vec4(fragmentTexture.x, fragmentTexture.y, 0 0, 1.0);\n\`

## Part 3

### VertexShaderCode

Same as part 2.

### FragmentShaderCode

I use these lines to create variables to hold the uniform textures and blends

```
uniform sampler2D tex1;\n\
uniform sampler2D tex2;\n\
uniform float blend1;\n\
uniform float blend2;\n\
```

Then I use these lines to set the output variable that will return the color, and then get the 2 colors from the 2 textures, and then blend them using the formula blend1\*color1 + blend2\*color2

```
out vec4 FragColor;\n\
void main() {\n\
    vec4 color1 = texture(tex1, UV);\n\
    vec4 color2 = texture(tex2, UV);\n\
    FragColor = blend1 * color1 + blend2 * color2;\n\
}\n";
```
