 #define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>
#include "Utils.h"

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3* viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}

void Renderer::Render(const Scene& scene)
{
	line(0, 360, 1280, 360, glm::vec3(255, 255, 0));
	line(640, 0, 640, 720, glm::vec3(255, 255, 0));
	glm::vec2 x0(640, 360);
	
	std::vector<std::shared_ptr<MeshModel>> models = scene.getModels();
	std::vector<Camera> cameras = scene.GetCameras();
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Face> faces;
			
	for (std::vector<std::shared_ptr<MeshModel>>::iterator itr = models.begin(); itr != models.end(); itr++)
	{
		vertices = (*itr)->getVertices();
		std::vector<glm::vec3> newV;

		//(*itr)->SetWorldTransformation(Utils::Rotation(glm::vec3(0.01, 0, 0)));
		//(*itr)->SetWorldTransformation(Utils::Translation(glm::vec3(2, 20, 0)));
		glm::mat4x4 t = (*itr)->GetWorldTransformation();
		for(std::vector<glm::vec3>::iterator it = vertices.begin(); it != vertices.end(); it++)
			newV.push_back( t * glm::vec4(*it,1));

		//(*itr)->setVertices(vertices);
		faces = (*itr)->getFaces();
		normals = (*itr)->getNormals();
		for (std::vector<Face>::iterator it = faces.begin(); it != faces.end(); it++)
		{
			glm::vec4  p1,p2,p3;
			//glm::vec3  n1, n2, n3;
			p1 = glm::vec4(newV.at(it->GetVertexIndex(0)-1),1);
			p2 = glm::vec4(newV.at(it->GetVertexIndex(1)-1),1);
			p3 = glm::vec4(newV.at(it->GetVertexIndex(2)-1),1);

			
			/*float length = 10;
			n1 = length * normals.at(it->GetNormalIndex(0) - 1);
			n2 = length * normals.at(it->GetNormalIndex(1) - 1);
			n3 = length * normals.at(it->GetNormalIndex(2) - 1);*/

			line(x0.x +p1.x , x0.y + p1.y , x0.x + p2.x , x0.y + p2.y , glm::vec3(0, 0, 0));
			line(x0.x + p1.x , x0.y + p1.y , x0.x + p3.x , x0.y + p3.y , glm::vec3(0, 0, 0));
			line(x0.x + p2.x , x0.y + p2.y , x0.x + p3.x , x0.y + p3.y , glm::vec3(0, 0, 0));

			//line(x0.x + p1.x / p1.z, x0.y + p1.y / p1.z, x0.x + p2.x / p2.z, x0.y + p2.y / p2.z, glm::vec3(0, 0, 0));
			//line(x0.x + p1.x / p1.z, x0.y + p1.y / p1.z, x0.x + p3.x / p3.z, x0.y + p3.y / p3.z, glm::vec3(0, 0, 0));
			//line(x0.x + p2.x / p2.z, x0.y + p2.y / p2.z, x0.x + p3.x / p3.z, x0.y + p3.y / p3.z, glm::vec3(0, 0, 0));

			//line(p1.x, p1.y, p1.x + n1.x, p1.y + n1.y, glm::vec3(0, 255, 0));
			//line(x0.x + p2.x, x0.y + p2.y, x0.x + n2.x, x0.y + n2.y, glm::vec3(0, 255, 0));
			//line(x0.x + p3.x, x0.y + p3.y, x0.x + n3.x, x0.y + n3.y, glm::vec3(0, 255, 0));

		}
	}

	for (std::vector<Camera>::iterator itr = cameras.begin(); itr != cameras.end(); itr++)
	{
		vertices = itr->getVertices();
		faces = itr->getFaces();
		int i = 0;
		for (std::vector<Face>::iterator it = faces.begin(); it != faces.end(); it++)
		{
			i++;
			glm::vec3  p1, p2, p3;
			p1 = vertices.at(it->GetVertexIndex(0) - 1);
			p2 = vertices.at(it->GetVertexIndex(1) - 1);
			p3 = vertices.at(it->GetVertexIndex(2) - 1);
			double a = p1.x;
			line(500 + p1.x, 500 + p1.y, 500 + p2.x, 500 + p2.y, glm::vec3(255, 0, 0));
			//for (int i = 0; i < 400; i++)
				//line(500, 500, 500 + 200 * cos(i / 100.0*3.14 / 2), 500 + 200 * sin(i / 100.0*3.14 / 2),1);
			line(500 + p1.x, 500 + p1.y, 500 + p3.x, 500 + p3.y, glm::vec3(255, 0, 0));
			line(500 + p2.x, 500 + p2.y, 500 + p3.x, 500 + p3.y, glm::vec3(255, 0, 0));
			//printf("loop %d",i);
		}
	}
	
}

void Renderer::line(double x, double y, double x2, double y2, glm::vec3 color) {
	double w = x2 - x;
	double h = y2 - y;
	double dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w < 0) dx1 = -1; else if (w > 0) dx1 = 1;
	if (h < 0) dy1 = -1; else if (h > 0) dy1 = 1;
	if (w < 0) dx2 = -1; else if (w > 0) dx2 = 1;
	int longest = abs((int)w);
	int shortest = abs((int)h);
	if (!(longest > shortest)) {
		longest = abs((int)h);
		shortest = abs((int)w);
		if (h < 0) dy2 = -1; else if (h > 0) dy2 = 1;
		dx2 = 0;
	}
	int numerator = longest >> 1;
	for (int i = 0; i <= longest; i++) {
		putPixel((int)x, (int)y, color);
		numerator += shortest;
		if (!(numerator < longest)) {
			numerator -= longest;
			x += dx1;
			y += dy1;
		}
		else {
			x += dx2;
			y += dy2;
		}
	}
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}