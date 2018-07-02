#include <GL/glut.h>
#include <glm.h>
#include <cstdio>

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
      case 'w':
        movz += 0.1;
        break;
      case 's':
        movz -= 0.1;
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

// Função callback chamada para fazer o desenho
void Desenha(void){
     int i;
     glMatrixMode(GL_MODELVIEW);
     //glLoadIdentity();
     // Limpa a janela de visualização com a cor de fundo especificada
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     //Drawing the model
     glPushMatrix(); // salvar as coordenadas correntes
     glTranslatef(0.0,0.0,570.0);
     glRotatef(-90,0.0,1.0,0.0);
     glRotatef(-20,0.0,0.0,1.0);
     //glRotatef(angle, 0, 1, 0); // rotacao eterna
     //HERE IS WHERE I DRAW MY OBJ
     glmDraw(cenario,GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
     glPopMatrix();

     glPushMatrix(); // salvar as coordenadas correntes
     glTranslatef(movz, 0, 0);
     glTranslatef(0.0,0.0,570.0);
     glRotatef(-90,0.0,1.0,0.0);
     glRotatef(-20,0.0,0.0,1.0);
     glScalef(0.3,0.3,0.2);
     glRotatef(angle, 0, 1, 0); // rotacao eterna
     glmDraw(aviao, GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
     glPopMatrix();

     /*
     angle = angle+0.6;
     if(angle > 360)
       angle = angle - 360;*/
     glutKeyboardFunc(tecla);
     glutSwapBuffers();
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
	gluPerspective(angle,fAspect,1,400.0);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	gluLookAt(0,0,600, 0,0,0, 0,1,0);
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

    glutDisplayFunc(Desenha);
    glutIdleFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(tecla);
    glutMouseFunc(GerenciaMouse);

    glutMainLoop();
    return 0;
}
