#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
using namespace std;
#define ScreenWidth 900
#define ScreenHeight 900

#include "cursor.cpp" 

float scaleY = (float)1/(ScreenHeight);
float scaleX = (float)1/(ScreenWidth);

typedef struct{

	float x;
	float y;
	float size;
	
}DynamicPoint;

DynamicPoint createPoint(float x, float y, float size){
	DynamicPoint sample;
	sample.x = x;
	sample.y = y;
	sample.size = size;

	return sample;
}

void drawPoint(DynamicPoint point){
	glPointSize(point.size);	
	glBegin(GL_POINTS);
	glVertex2f(point.x,point.y);		
	glEnd();

}

int main(void){

	GLFWwindow* window; 

	CursorPos Cursor;

	vector<DynamicPoint> points;
	points.push_back(createPoint(10,10,5));

	if(!glfwInit()){
		return -1;
	}
	
	window = glfwCreateWindow(ScreenWidth,ScreenHeight,"LizardWhichFollowsMouse",NULL,NULL);	

	if(!window){
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window)){

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		glColor4f(1,1,1,1);		
		glPointSize(1);
		for(int x=0;x<ScreenHeight;x++){for(int y=0;y<ScreenWidth;y++){glVertex2f(x-(ScreenWidth/2),y-(ScreenHeight/2));}}		
		glEnd();	

		CursorPos cursor = getCursor(window);		
		

		for(int i=0;i<points.size();i++){
		drawPoint(points[i]);
		}

		glLoadIdentity();
		glScalef(scaleX*2,scaleY*2, scaleX*2);		
		glBegin(GL_LINES);
		glColor4f(0,0,0,1);		
		glVertex2f(cursor.x,-cursor.y);
		glVertex2f(0,0);

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
