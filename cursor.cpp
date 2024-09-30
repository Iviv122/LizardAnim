
typedef struct{

	double x;
	double y;
	
}CursorPos;


CursorPos getCursor(GLFWwindow* window){
	CursorPos sample; 
	glfwGetCursorPos(window,&sample.x,&sample.y);
	sample.x -= (ScreenWidth/2);
	sample.y -= (ScreenHeight/2);
	return sample;
}


