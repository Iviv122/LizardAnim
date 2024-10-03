#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

#define ScreenWidth 900
#define ScreenHeight 900


float scaleY = (float)1/(ScreenHeight);
float scaleX = (float)1/(ScreenWidth);

class Vector2{
public:
	double x;
	double y;
	
	Vector2(double x =0 , double y=0){
	this->x = x;
	this->y = y;
	};
};

class Point{
public:
	Vector2 pos;
	Vector2 velocity;
	int size;
	GLfloat radius;

	Point(double x, double y, int size, float radius){
	this->pos = Vector2(x,y);
	this->size = size;
	this->radius = radius;
	}	

	void Applyforce(){
	
	pos.x+=velocity.x;
	pos.y+=velocity.y;
	
	}
	void DrawPoint(){
	
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(pos.x,pos.y);
	glEnd();	
	
	}
	void Follow(Vector2 cursor,double radius){ // radius of untouch
	
	double speed = 5;	
	double dx = cursor.x-pos.x;
	double dy = cursor.y-pos.y;
	
	double distance = sqrt(dx*dx+dy*dy);

	if(distance < radius){ velocity.x =0;velocity.y=0; return;}

	double directionX = dx/distance;
	double directionY = dy/distance;

	double vx = directionX*speed;
	double vy = directionY*speed;

	velocity.x = vx;
	velocity.y = vy;

	}
	
	void drawHollowCircle(){
	int i;
	int lineAmount = 100; 	
	GLfloat twicePi = 2.0f * M_PI;
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    pos.x + (radius * cos(i *  twicePi / lineAmount)), 
			    pos.y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
	}

	void drawFilledCircle(int r,int g,int b){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r,g,b);
		glVertex2f(pos.x, pos.y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex3f(
		            pos.x + (radius * cos(i *  twicePi / triangleAmount)), 
			    pos.y + (radius * sin(i * twicePi / triangleAmount)),
			0
			);
		}
	glEnd();
	}

	void drawCircleOutline(double thick,int r,int g,int b){
	int i;
	int lineAmount = 100; 	
	GLfloat twicePi = 2.0f * M_PI;
	glLineWidth(thick);	
	glBegin(GL_LINE_LOOP);
	glColor3f(r,g,b);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    pos.x + (radius * cos(i *  twicePi / lineAmount)), 
			    pos.y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
	}
};

Vector2 getCursor(GLFWwindow* window){
	Vector2 sample; 
	glfwGetCursorPos(window,&sample.x,&sample.y);

	sample.y = -sample.y;

	sample.x -= (ScreenWidth/2);
	sample.y += (ScreenHeight/2);

	return sample;
}



int main(void){

	GLFWwindow* window; 

	vector<Point> points;
	for(int i=0;i<50;i++){
	points.push_back(Point(i*10,0,4,55-i));
	}
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
		
		Vector2 cursor = getCursor(window);		


		glLoadIdentity();
		glScalef(scaleX*2,scaleY*2, scaleX*2);		


		points[0].Follow(cursor,0);
		points[0].Applyforce();
		points[0].DrawPoint();
		//		points[0].drawHollowCircle();		
		points[0].drawCircleOutline(4,1,1,1);
		
		for(int i=1;i<points.size();i++){
		points[i].Follow(points[i-1].pos,10);
		points[i].Applyforce();
		points[i].DrawPoint();
		//		points[i].drawHollowCircle();	
		points[i].drawCircleOutline(4,1,1,1);
		}
	
		for(int i=0;i<points.size();i++){
		points[i].drawFilledCircle(0,255,0);		
	
		}

		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f(cursor.x,cursor.y);
		glVertex2f(0,0);
		glEnd();

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
