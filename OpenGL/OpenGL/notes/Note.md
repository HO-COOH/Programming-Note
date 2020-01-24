## Setting up render context
- ``glfwInit``: initialize the library
- ``glfwCreateWindow(GLFWwindow*)``: create a windowed window
- ``glfwMakeContextCurrent(GLFWwindow*)``: make the wond'ws context current
- ``(glfwSwapInterval)``: limit the frames

## Components
### vertex shader
Runs for every vertex.
### fragment shader
Runs for every pixel.
### vertex buffer
1. Create a vertex data in an array (float array)
2. declare an ``unsigned int`` to record the index and generate a buffer object
```cpp
unsigned int vbo;
glGenBuffers(1, &vbo);
```
3. bind the buffer with buffer data
```cpp
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, /*size of data*/, /*pointer to data*/, GL_STATIC_DRAW);
```
### vertex attributes & layout
Define numbers of components(attributes) per vertex and numbers of components(elements) per attribute in the vertex buffer and number of vertices.
```cpp
glVertexAttribPointer(/*index of the attribute(start from zero)*/,
	/*components in this attribute*/,
	/*Type*/ GL_FLOAT,
	/*Normalized?*/ GL_FALSE/GL_TRUE,
	/*stride (number of bytes of one vertex)*/,
	/*byte offset of this attribute in one vertex*/
);
glEnableVertexAttribArray(/*index of the attribute layout to be enabled*/);
```

### index buffer
Remove redundant vertices.  
1. Create index data in an array **(must be unsigned)**
2. declare an ``unsigned int`` to record the index and generate a buffer object by
```cpp
unsigned int ibo;
glGenBuffers(1, &ibo);
```
3. bind the buffer with buffer data
```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, /*size of data*/, /*pointer to data*/, GL_STATI_DRAW);
```
### vertex array
A way to bind vertex buffers to a certain layout(attributes). So instead of having to explicitly specify the vertex layout every time before draw call by:
1. bind vertex buffer
2. bind index buffer
3. bind shader
4. specify the layout of the vertex buffer and draw

With a vertex array object, we only need to specify which vertex array object to bind before each draw call
1. set up and bind vertex array
```cpp
unsigned int vao;
glGenVertexArrays(1, &vao);	//generate 1 vertex array object
glBindVertexArray(vao);
```
2. set up vertex buffer and layout as before, at this time, the vertex array is bind with the vertex buffer that is currently generated
3. bind index buffer
4. bind shader
5. specify the vertex array object and draw

### Uniform
Exchanging data CPU<=>GPU. Uniforms are set per draw call. In fragment shader, declare a uniform by:
```
uniform vec4 u_Color;
```
In C++ source file, set up uniform after using the shader program by:
1. Get the index (location) of the uniform 
```cpp
int location=glGetUniform(/*the shader program id*/, "u_Color");
```
2. set up the uniform
```cpp
glUniform4f(location, /*four float components*/...);
```

### Textures
On 2D graphics, textures are images drawn on top of an object. The fragment shader decides the color of the final color of individual pixels.  
In OpenGL, there are various ``slots`` we can bind textures to. We are able to bind more than 1 textures at once. On Windows, typically we have 32 ``slots``. *Heavily depends on the hardware.*
1. declare an ``unsigned int`` index and generate a texture object
```cpp
unsigned int id;
glGenTextures(1, &id);
```
2. set up texture parameters
```cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
```
3. prepare texture data
```cpp
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
```
4. Enable the texture and bind 
```cpp
glActiveTexture(GL_TEXTURE0 + slot);
glBindTexture(GL_TEXTURE_2D, id);
```
- internal format: how OpenGL will store a texture data
- format: the format of the data you're providing OpenGL with  
After setting up texture, we need to tell the shader which texture ``slot`` to sample from. The way to achieve this is via a ``uniform``.
### Blending
Blending determines how to combine the output color with what is already in the target buffer. 
- Output=the color we output from fragment shader(**source/textures**)
- Target=the buffer which the fragment shader is drawing to(**destination/the original object**)  
```fragment shader -> source + destination -(blend)-> final```
1. Enable blending by
```cpp
glEnable(GL_BLEND);
glDisable(GL_BLEND);	//disable blending
```
2. Determine the blending function
```cpp
glBlendFunc(src,	//how the src RGBA factor is computed, default: GL_ONE
	dest		//how the dest RGBA factor is computed, default: GL_ZERO)
glBlendEquation(mode);	//how to combine the src and dest colors, defaul: GL_FUNC_ADD
```


## Draw
- Loop until the user closes the window
```cpp
while(!glfwWindowShouldClose(GLFWwindow*))
```

## Additional Notes
### Coordinate
The bottom left of the window is (0,0)

### Error Handling
Note: ``glfwTerminate()`` will destory the OpenGL context, so any operation including deleteing program, deleting buffer, will result in an OpenGL error code. So these operations should be run before calling ``glfwTerminate()``. After abstracting ``VertexBuffer`` ,``VertexArray`` and ``IndexBuffer`` into classes, we should make these stack allocated object inside a scope. So their destructor will be called before terminate.
### Math

