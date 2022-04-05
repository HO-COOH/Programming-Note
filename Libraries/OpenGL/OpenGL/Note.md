## Setting up render context
- ``glfwInit``: initialize the library
- ``glfwCreateWindow(GLFWwindow*)``: create a windowed window
- ``glfwMakeContextCurrent(GLFWwindow*)``: make the window context current
- ``(glfwSwapInterval)``: limit the frames

## VS工程设置
1. 下载编译GLFW库
2. 链接`opengl32.lib` 和`glfw3.lib`
3. 

## vcpkg+CMAKE
```cmake
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(main PRIVATE glfw)
```

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

### ImGUI
API **independent** library to draw UI on the screen, eg. buttons, textfields, windows...  
[imgui github links](https://github.com/ocornut/imgui)



## Draw
- Loop until the user closes the window
```cpp
while(!glfwWindowShouldClose(GLFWwindow*))
```

## Additional Notes
### Coordinate
The bottom left of the window is (0,0)

### Error Handling
[youtube link](https://www.youtube.com/watch?v=FBbPWSOQ0-w&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=11&t=0s)
```cpp
#define ASSERT(x) if(!(x)) __debugbreak();	//MSVC specific
#define GLCall(x) x;\
	ASSERT(glCheckError());\
```
Note: ``glfwTerminate()`` will destory the OpenGL context, so any operation including deleteing program, deleting buffer, will result in an OpenGL error code. So these operations should be run before calling ``glfwTerminate()``. After abstracting ``VertexBuffer`` ,``VertexArray`` and ``IndexBuffer`` into classes, we should make these stack allocated object inside a scope. So their destructor will be called before terminate.
### Math
#### Projection matrix
Transform a space location to the device coordinates.
#### View projection matrix
Transform position, rotation, angle of the camera.
#### Model matrix
Transform position, rotation, angle of the object.

## GLSL
### 基本类型
- 标量类型
  - bool
  - int
  - uint
  - float
  - double
- 向量类型，其中n可以是2,3,4，引用其中的某个元素使用x y z w
  - bvecn
  - ivecn
  - uvecn
  - vecn (float vec)
  - dvecn
- 矩阵类型
  - matnxm，其中n和m都可以是2，3，4
  - matn，matnxn的缩写
  - dmatnxm （OpenGL4.0）
  - dmatn （OpenGL4.0）
- 结构体类型，使用类似于C++的语法定义

### 内置变量
GLSL内部定义了一些有特殊含义的自带变量，通常用于数据传输，以gl_开头
### 函数
- GLSL的函数不支持递归调用
- GLSL的函数形参支持`in` `out` `inout`修饰，类似于输入、输出引用，对于`out`参数，调用时类似于接受了一个undefined值
```glsl
//MyFunction调用时接收的值为(10.5, undefined, 10.0)
void MyFunction(in float inputValue, out int outputValue, inout float inAndOutValue)
{
	inputValue = 0.0;
	outputValue = int(inAndOutValue + inputValue);
	inAndOutValue = 3.0;
}

void main()
{
	float in1 = 10.5;
	int out1 = 5;
	float out2 = 10.0;
	MyFunction(in1, out1, out2);
	//调用结束后in1 = 10.5, out1 = 10, out2 = 3.0
}
```
### 顶点着色器
预定义的输出：
```glsl
out gl_PerVertex
{
	vec4 gl_Position;		//剪裁空间下的位置输出
	float gl_PointSize;		//只有绘制单点画元Point Primitive时才有效，会被限制在GL_POINT_SIZE_RANGE的范围中
	float gl_ClipDistance[]; //
};
```

### 片段着色器

### glm
	变换
		glm::mat4
			glm::mat4(1.0f)将初始化一个单位矩阵I
		注意以下变换矩阵与向量相乘得到变换后位置时，在2D下将z分量赋值0.0f，w分量赋值1.0f
		缩放
			glm::scale(glm::mat4 const& m, glm::vec3 const& v) -> glm::mat4
				按v的三个分量缩放生成一个变换矩阵与m相乘，返回相乘后的矩阵
			```cpp
				auto const t = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 0.0f)); //缩放
				auto const v = glm::vec2(1.0f, 2.0f); //点(1,2)
				auto const result = t * glm::vec4(v, 0.0f, 1.0f); //(1,4)
				std::cout << result << '\n';
			```
		位移
			glm::translate(glm::mat4 const& m, glm::vec3 const& v) -> glm::mat4
				按v的三个分量位移生成一个变换矩阵与m相乘，返回相乘后的矩阵
			在2D下，v的z分量赋值为0
			```cpp
				auto const t = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 0.0f));
				auto const v = glm::vec2(1.0f, 2.0f); //点(1,2)
				auto const result = t * glm::vec4(v, 0.0f, 1.0f); //(2,4)
				std::cout << result << '\n';
			```
		旋转
			glm::rotate(glm::mat4 const& m, T angle, glm::vec3 const& axis) -> glm::mat4
				绕着axis表示的轴旋转angle角度（弧度制）生成一个变换矩阵与m相乘，返回相乘后的矩阵
				在2D环境下即在x-y平面中绕坐标原点旋转，则axis应使用z轴（0，0，1）
			```cpp
				auto const t = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 2.0f));
				auto const v = glm::vec2(1.0f, 2.0f); //点(1,2)
				auto const result = t * glm::vec4(v, 0.0f, 1.0f);//(-2,1)
				std::cout << result << '\n';`
			```
	坐标
		从模型局部坐标到最终显示到屏幕上，需要3个矩阵变换
		局部坐标 ==(Model matrix)==> 世界坐标 ==(View Matrix)==> 观察坐标 ==(Projection matrix)==> 屏幕剪裁坐标
		即需要 
			glm::mat4 model
			glm::mat4 view
			glm::mat4 projection
		最后将局部位置vec3 local乘以这三个矩阵，得到最终opengl用的vec3 gl_Position
			result = projection * view * model * local
		projection matrix投影矩阵
			正射投影矩阵
				glm::ortho(T left, T right, T bottom, T top, T zNear, T zFar) -> glm::mat4
					在3D中根据3个方向的6个范围创建一个正射投影矩阵
				glm::ortho(T left, T right, T bottom, T top) -> glm::mat4
					在2D中根据xy方向的2个范围创建一个正射投影矩阵
		view matrix观察矩阵
			构建观察矩阵需要3个信息：
				摄像机（观察者）在世界坐标系中的坐标
				摄像机看向的方向
				摄像机的上方向
		