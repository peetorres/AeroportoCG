#include <GL/glut.h>
#include <glm.h>
#include <cstdio>

FILE *fp;
GLMmodel *cenario, *aviao;

GLfloat angle = 0, fAspect;
GLfloat x = 0, y = 0;

void tecla(unsigned char tecla, int x, int y){
    if(tecla == 'd'){
      x += 10;
    }
    if(tecla == 'a'){
      x -= 10;
    }
    if(tecla == 's'){
      y -= 10;
    }
    if(tecla == 'w'){
      y += 10;
    }
    if (tecla == 'F'){
            exit(0);
    }
    else if (tecla == 'f'){
        exit(0);
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
     glTranslatef(3.0,3.0,570.0);
     glRotatef(-90,0.0,1.0,0.0);
     glRotatef(-20,0.0,0.0,1.0);
     glScalef(0.3,0.3,0.2);
     glRotatef(angle, 0, 1, 0); // rotacao eterna
     glmDraw(aviao, GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
     glPopMatrix();


     angle = angle+0.6;
     if(angle > 360)
       angle = angle - 360;
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
	gluPerspective(angle,fAspect,0.1,400.0);
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

    glutMainLoop();
    return 0;
}
