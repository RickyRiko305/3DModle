#include <glad/glad.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

void ParseObj(vector < vector<float> > & vertice, vector < vector <unsigned int> > & indice);

float r = 0.1f, g = 0.2f, b = 0.4f;
float x = 0.0f, y = 0.0f, z = 0.0f;

vector < vector<float> > vertice(4, vector<float>());
vector < vector<unsigned int> > indice(4,vector<unsigned int> ());

unsigned int vao;

glm::mat4 proj = glm::ortho(-480.0f, 480.0f, -270.0f, 270.0f, -480.0f, 480.0f);
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);

string path1("res/Textures/GRANDEB2.JPG");
string path2("res/Textures/GRANDECO.JPG");

Shader shader;
VertexBuffer vb[4];
IndexBuffer ib[4];
Texture texture1, texture2;

void init()
{
	ParseObj(vertice, indice);

	texture1.add(path1);
	texture2.add(path2);

	model = glm::translate(model, glm::vec3(0.0f, -120.0f, 00.0f));
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	shader.CreateShader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	shader.Bind();

	texture1.Bind(0);
	shader.SetUniform1i("u_Texture1", 0);
	texture2.Bind(1);
	shader.SetUniform1i("u_Texture2", 1);

	shader.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
	shader.SetUniform3f("u_lightPos", 200.0f, 300.0f, 250.0f);

	shader.SetUniformMatrix4fv("u_model", 1, GL_FALSE, &model[0][0]);
	shader.SetUniformMatrix4fv("u_view", 1, GL_FALSE, &view[0][0]);
	shader.SetUniformMatrix4fv("u_projection", 1, GL_FALSE, &proj[0][0]);

	for (int i = 0; i < 4; i++)
	{
		vb[i].add(vertice[i].size() * sizeof(float), &vertice[i][0]);
		ib[i].add(&indice[i][0], indice[i].size());
	}

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 1);

	shader.Bind();

	for (int i = 0; i < 4; i++)
	{
		vb[i].Bind();
		ib[i].Bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glDrawElements(GL_TRIANGLES, ib[i].GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		model = glm::translate(model, glm::vec3(0.0f, 20.0f, 0.0f));
	}

	if (key == 's')
	{
		model = glm::translate(model, glm::vec3(0.0f, -20.0f, 0.0f));
	}
	if (key == 'a')
	{
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0f));
	}
	if (key == 'd')
	{
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f));
	}

	shader.SetUniformMatrix4fv("u_model", 1, GL_FALSE, &model[0][0]);

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{

	if (state == GLUT_DOWN && button == 3)
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
	else if (state == GLUT_DOWN && button == 4)
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			r = 1.0, g = b = 0.0;
		if (state == GLUT_UP)
			g = 1.0, r = b = 0.0;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		r = 0.1f, g = 0.2f, b = 0.4f;
	}
	shader.SetUniformMatrix4fv("u_model", 1, GL_FALSE, &model[0][0]);

	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		view = glm::rotate(view, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (key == GLUT_KEY_RIGHT)
	{
		view = glm::rotate(view, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (key == GLUT_KEY_UP)
	{
		view = glm::rotate(view, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (key == GLUT_KEY_DOWN)
	{
		view = glm::rotate(view, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	}

	shader.SetUniformMatrix4fv("u_view", 1, GL_FALSE, &view[0][0]);

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitWindowSize(960, 540);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	int window = glutCreateWindow("3D Model");

	if (!gladLoadGL())
		cout << "GL Load Error\n";

	glClearColor(r, g, b, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	init();
	cout << glGetString(GL_VENDOR) << endl << glGetString(GL_VERSION) << endl;

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(SpecialKey);
	glutMainLoop();

	return 0;
}