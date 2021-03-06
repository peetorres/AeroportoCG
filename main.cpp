#include <GL/glut.h>
#include <glm.h>
#include <cstdio>

void GerenciaMouse(int, int, int, int);
void tecla(unsigned char, int, int);
void Simulator();
void DesenhaCenario();
void Inicializa();
void AlteraTamanhoJanela(GLsizei, GLsizei);
void DesenhaAviao();
void EspecificaParametrosVisualizacao();

FILE *fp;
GLMmodel *cenario, *aviao;

GLfloat angle = 0, fAspect;
GLfloat movx = 0, movy = 0, movz = 0;


void GerenciaMouse (int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(angle >= 5){
          angle -= 5;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
      if(angle <= 130){
          angle += 5;
      }
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void tecla(unsigned char tecla, int x, int y){
    switch (tecla){
      case 'v':
        movz += 0.1;
        break;
      case 'b':
        movz -= 0.1;
        break;
      case 'w':
        movx += 0.1;
        break;
      case 's':
        movx -= 0.1;
        break;
      case 'd': // alçar voo
        angle += 1;
        break;
      case 'a': // alçar voo
        angle -= 1;
        break;
      case 'F':
        exit(0);
        break;
      case 'f':
        exit(0);
        break;
    }
}

void Simulator(void){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     DesenhaCenario();
     DesenhaAviao();
     //DesenhaAviao();
     //glutKeyboardFunc(tecla);
     glutSwapBuffers();
}

// Função callback chamada para fazer o desenho
void DesenhaCenario(void){
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix(); // salvar as coordenadas correntes
     glTranslatef(0.0,0.0,570.0);
     glRotatef(-90,0.0,1.0,0.0);
     glRotatef(-20,0.0,0.0,1.0);
     glScalef(2,2,2);
     //glRotatef(angle, 0, 1, 0); // rotacao eterna
     //HERE IS WHERE I DRAW MY OBJ
     glmDraw(cenario,GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
     glPopMatrix();
}

void DesenhaAviao(void){
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); // salvar as coordenadas correntes
  glTranslatef(movx, 0, movz);
  glTranslatef(0.0,0.0,570.0);
  glRotatef(-90,0.0,1.0,0.0);
  glRotatef(-20,0.0,0.0,1.0);
  glScalef(0.3,0.3,0.2);
  glRotatef(angle, 0, 1, 0); // rotacao eterna
  glmDraw(aviao, GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
  glPopMatrix();
  /* Se eu quiser deixar rodando eternamente
  angle = angle+0.6;
  if(angle > 360)
    angle = angle - 360;
  */
}



// Inicializa parâmetros de rendering
void Inicializa (void){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
  angle=60;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void){
  // Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
	gluPerspective(40,fAspect,20,100.0);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	gluLookAt(0,0,590, 1,0,0, 0,1,0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;
	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

// Programa Principal
int main(int argc, char* argv[]){
    glutInit(&argc, argv);

	  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(10,10);
    glutCreateWindow("TP III - CG");

    Inicializa();

    int i;
    cenario = glmReadOBJ("Cenario.obj");
    aviao = glmReadOBJ("Arsenal.obj");
    glmVertexNormals(cenario,180.0,0);
    glmVertexNormals(aviao,180.0,0);

    glutDisplayFunc(Simulator);
    glutIdleFunc(Simulator);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(tecla);
    glutMouseFunc(GerenciaMouse);

    glutMainLoop();
    return 0;
}
