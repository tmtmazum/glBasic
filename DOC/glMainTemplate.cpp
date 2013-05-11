#include <iostream>
#include <GL/glut.h>

void draw()
{

}

void handleKeyPress(unsigned char key, int x, int y)
{
  
}

void handleSpecialPress(int key, int x, int y)
{
  
}


int main(int argc, char** argv)
{
  glutInit(&argC, argV);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(10,10);
  glutCreateWindow("glTest");

  glutDisplayFunc(draw);
  /* where draw(): lambda<void> */
  
  glutKeyboardFunc(handleKeyPress);
  /* where handleKeyPress(
   *		key: unsigned-char, 
   * 		x:int, 
   * 		y:int): lambda<void> */
  
  glutSpecialFunc(handleSpecialpress);
  /* where handleSpecialPress(
   *		key: int, 
   * 		x:int, 
   * 		y:int): lambda<void> */
  
  glutIdleFunc(draw);
  /* where draw(): lambda */
  
  glutMainLoop();

  return 0;
}