#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Prototypes des fonctions statiques contenues dans ce fichier C */
static void init(void);
static void draw(void);
static void quit(void);

/*!\brief largeur et hauteur de la fenêtre */
static int _wW = 800, _wH = 600;
/*!\brief identifiant du Vertex Array Object */
static GLuint _vao[2] ;
/*!\brief identifiant des Vertex Buffer Objects */
static GLuint _buffer[2] = { 0 };
static GLuint _bufferf[2] = { 0 };
/*!\brief identifiant du GLSL program */
static GLuint _pidFeu = 0;
/*!\brief identifiant d'une texture */
static GLuint _texId = 0;

/*!\brief créé la fenêtre d'affichage, initialise GL et les données,
 * affecte les fonctions d'événements et lance la boucle principale
 * d'affichage.
 */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies", 20, 20, 
			 _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}

static void init(void) {
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*Poubelle*/
GLuint idata[] = {
0, 1, 2,
0, 2, 3,
0, 3, 4,
0, 4, 1,

/*1*/
1,2,7,
7,6,1,

1,6,4,
4,6,5,

5,4,3,
3,5,8,

8,7,2,
2,3,8,

/*2*/
8,5,10,
10,9,8,

8,9,7,
7,9,12,

12,7,6,
6,12,11,

11,10,5,
5,6,11,

/*3*/

11, 12, 13,
13, 16, 11,

11, 16, 10,
10, 16, 15,

15, 10, 9,
9,15,14,

14, 13, 12,
12, 9, 14,

14, 17, 18,
18,19,14,
14,19,20,
20,21,14,
14,21,17,


};




  GLfloat hauteur_pointe = 0;
  GLfloat etage_3_x       = 0 ,                               etage_3_y       = 0 ,                               etage_3_z        = -3;
  GLfloat bas_pyramide_x  = 1  ,     bas_pyramide_y  = 1 ,                                                       bas_pyramide_z   = 0;
  GLfloat etage_1_x       = 1.3,     etage_1_y       = 1.3,      etage_1_z        = -1;
  GLfloat etage_2_x       = 1 ,     etage_2_y       = 1,        etage_2_z        = -2;
  GLfloat noeud = 0.5;

  
  
  GLfloat data[] = {
0,0,hauteur_pointe,                                   1,1,1,  1,0,

-bas_pyramide_x, bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,
 bas_pyramide_x, bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,
 bas_pyramide_x,-bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,
-bas_pyramide_x,-bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,

-etage_1_x ,-etage_1_y , etage_1_z,                     0,0,0,  1,0,
-etage_1_x , etage_1_y , etage_1_z,                     0,0,0,  1,0,   
 etage_1_x , etage_1_y , etage_1_z,                     0,0,0,  1,0,
 etage_1_x ,-etage_1_y , etage_1_z,                     0,0,0,  1,0,

 etage_2_x ,-etage_2_y , etage_2_z,                     0,0,0,  1,0,
-etage_2_x ,-etage_2_y , etage_2_z,                     0,0,0,  1,0,
-etage_2_x , etage_2_y , etage_2_z,                     0,0,0,  1,0,
 etage_2_x , etage_2_y , etage_2_z,                     0,0,0,  1,0,

 etage_3_x, etage_3_y, etage_3_z,                     0,0,0,  1,0,
 etage_3_x,-etage_3_y, etage_3_z,                     0,0,0,  1,0,
-etage_3_x,-etage_3_y, etage_3_z,                     0,0,0,  1,0,
-etage_3_x, etage_3_y, etage_3_z,                     0,0,0,  1,0,

 noeud , noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
 noeud ,-noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
-noeud ,-noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
-noeud , noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
-noeud , noeud -0.2,  etage_3_z  - 0.5,                     0,0,0,  1,0,

};




  /*data feu*/
  GLfloat dataf[] = {
0,0,hauteur_pointe,                                   1,1,1,  1,0,

-bas_pyramide_x, bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,
 bas_pyramide_x, bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,
 bas_pyramide_x,-bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,
-bas_pyramide_x,-bas_pyramide_y , bas_pyramide_z,      0,0,0,  1,0,

-etage_1_x ,-etage_1_y , etage_1_z,                     0,0,0,  1,0,
-etage_1_x , etage_1_y , etage_1_z,                     0,0,0,  1,0,   
 etage_1_x , etage_1_y , etage_1_z,                     0,0,0,  1,0,
 etage_1_x ,-etage_1_y , etage_1_z,                     0,0,0,  1,0,

 etage_2_x ,-etage_2_y , etage_2_z,                     0,0,0,  1,0,
-etage_2_x ,-etage_2_y , etage_2_z,                     0,0,0,  1,0,
-etage_2_x , etage_2_y , etage_2_z,                     0,0,0,  1,0,
 etage_2_x , etage_2_y , etage_2_z,                     0,0,0,  1,0,

 etage_3_x, etage_3_y, etage_3_z,                     0,0,0,  1,0,
 etage_3_x,-etage_3_y, etage_3_z,                     0,0,0,  1,0,
-etage_3_x,-etage_3_y, etage_3_z,                     0,0,0,  1,0,
-etage_3_x, etage_3_y, etage_3_z,                     0,0,0,  1,0,

 noeud , noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
 noeud ,-noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
-noeud ,-noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
-noeud , noeud ,      etage_3_z  - 0.5,                     0,0,0,  1,0,
-noeud , noeud -0.2,  etage_3_z  - 0.5,                     0,0,0,  1,0,

};

  const GLuint B = RGB(255, 255, 255), N = 0;
  GLuint tex[] = { B, N, N, B };
  glGenVertexArrays(2, _vao);

  glBindVertexArray(_vao[0]);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glGenBuffers(2, _buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof *data, (const void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof *data, (const void *)(3 * sizeof *data));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof *data, (const void *)(6 * sizeof *data));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idata, idata, GL_STATIC_DRAW);

  /*feu*/

  glBindVertexArray(_vao[1]);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glGenBuffers(2, _bufferf);
  glBindBuffer(GL_ARRAY_BUFFER, _bufferf[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof dataf, dataf, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof *dataf, (const void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof *dataf, (const void *)(3 * sizeof *dataf));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof *dataf, (const void *)(6 * sizeof *dataf));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferf[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idata, idata, GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glGenTextures(1, &_texId);

  glBindTexture(GL_TEXTURE_2D, _texId);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
  glBindTexture(GL_TEXTURE_2D, 0);

  _pidFeu = gl4duCreateProgram("<vs>shaders/basic_feu.vs", "<fs>shaders/basic_feu.fs", NULL);
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  gl4duGenMatrix(GL_FLOAT, "modelMatrix");
  gl4duGenMatrix(GL_FLOAT, "viewMatrix");
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-1, 1, -1, 1, 2, 100);
  glViewport(0, 0, _wW, _wH);

  srand(time(NULL));

}
/*!\brief Cette fonction dessine dans le contexte OpenGL actif. */



float randomFloat(float a, float b) {
    // Initialisation du générateur de nombres aléatoires
    //srand(time(NULL));

    // Calcul de la plage et ajout du décalage
    float range = b - a;
    float random = ((float)rand() / RAND_MAX) * range + a;

    return random;
}

static void draw(void) {

  static GLfloat angle = 0.0f;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, _bufferf[0]);
  glUseProgram(_pidFeu);
  gl4duBindMatrix("viewMatrix");
  gl4duLoadIdentityf();
  gl4duLookAtf(0, 1, 10, 0, 0, 0, 0, 1, 0);
  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();
  gl4duRotatef(angle, 0, 1, 0);
  gl4duRotatef( 90, 1, 0, 0);
   gl4duTranslatef(0, 0, 4);
  angle += 0.25f * (1.0f / 60.0f) * 360.0f;
  gl4duSendMatrices();
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId);
  glUniform1i(glGetUniformLocation(_pidFeu, "tex"), 0);
  glUniform1i(glGetUniformLocation(_pidFeu, "inv"), 1); 
  glBindVertexArray(_vao[1]);

  static int t = 0;
  t++;
  if (t%10 == 9 ){
    GLfloat hauteur_pointe = 1 + randomFloat(-0.5, 1.);
    GLfloat etage_3_x       = 0.5 ,                               etage_3_y       = 0.5 ,                               etage_3_z        = -3;
    GLfloat decal =  hauteur_pointe - etage_3_z  ;
    

    GLfloat bas_pyramide_x  = 0.5  ,     bas_pyramide_y  = 0.5  ,                                                       bas_pyramide_z   = 0;
    GLfloat etage_1_x       = 1   + randomFloat(-0.25, 0.25),     etage_1_y       = 1   + randomFloat(-0.25, 0.5),      etage_1_z        = -1;
    GLfloat etage_2_x       = 1. + randomFloat(-0.25, 0.25),     etage_2_y       = 1. + randomFloat(-0.25, 0.5),        etage_2_z        = -2;

    GLfloat updatedData[] = {
      0,0,hauteur_pointe,                                   1,1,1,  1,0,

      -bas_pyramide_x + randomFloat(-0.25, 0.25), bas_pyramide_y + randomFloat(-0.25, 0.25), bas_pyramide_z,      1,1,0,  1,0,
      bas_pyramide_x + randomFloat(-0.25, 0.25), bas_pyramide_y + randomFloat(-0.25, 0.25), bas_pyramide_z,      1,1,0,  1,0,
      bas_pyramide_x + randomFloat(-0.25, 0.25),-bas_pyramide_y + randomFloat(-0.25, 0.25), bas_pyramide_z,      1,1,0,  1,0,
      -bas_pyramide_x + randomFloat(-0.25, 0.25),-bas_pyramide_y + randomFloat(-0.25, 0.25), bas_pyramide_z,      1,1,0,  1,0,

      -etage_1_x + randomFloat(-0.25, 0.25),-etage_1_y + randomFloat(-0.25, 0.25), etage_1_z,                     1,0.5,0,  1,0,
      -etage_1_x + randomFloat(-0.25, 0.25), etage_1_y + randomFloat(-0.25, 0.25), etage_1_z,                     1,0.5,0,  1,0,   
      etage_1_x + randomFloat(-0.25, 0.25), etage_1_y + randomFloat(-0.25, 0.25), etage_1_z,                     1,0.5,0,  1,0,
      etage_1_x + randomFloat(-0.25, 0.25),-etage_1_y + randomFloat(-0.25, 0.25), etage_1_z,                     1,0.5,0,  1,0,

      etage_2_x + randomFloat(-0.25, 0.25),-etage_2_y + randomFloat(-0.25, 0.25), etage_2_z,                     1,0,0,  1,0,
      -etage_2_x + randomFloat(-0.25, 0.25),-etage_2_y + randomFloat(-0.25, 0.25), etage_2_z,                     1,0,0,  1,0,
      -etage_2_x + randomFloat(-0.25, 0.25), etage_2_y + randomFloat(-0.25, 0.25), etage_2_z,                     1,0,0,  1,0,
      etage_2_x + randomFloat(-0.25, 0.25), etage_2_y + randomFloat(-0.25, 0.25), etage_2_z,                     1,0,0,  1,0,

      etage_3_x, etage_3_y, etage_3_z,                     1,0,0,  1,0,
      etage_3_x,-etage_3_y, etage_3_z,                     1,0,0,  1,0,
      -etage_3_x,-etage_3_y, etage_3_z,                     1,0,0,  1,0,
      -etage_3_x, etage_3_y, etage_3_z,                     1,0,0,  1,0,

    };
    glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(updatedData), updatedData, GL_STATIC_DRAW);
  }
  glUniform1i(glGetUniformLocation(_pidFeu, "isTrans"), 0); 
  glDrawElements(GL_TRIANGLE_STRIP, 36 + 24+ 24 +15, GL_UNSIGNED_INT, (const GLvoid *)0);
  gl4duRotatef( 180, 1, 0, 0);
  gl4duTranslatef(0, 0, 4);
  gl4duSendMatrices();
  glBindVertexArray(_vao[0]);
  glUniform1i(glGetUniformLocation(_pidFeu, "isTrans"), 1); 
  glDrawElements(GL_TRIANGLE_STRIP, 36 + 24+ 24 , GL_UNSIGNED_INT, (const GLvoid *)0);



  

  /* dé-lier le VAO */
  glBindVertexArray(0);
  /* désactiver le programme shader */
  glUseProgram(0);
}
/*!\brief appelée au moment de sortir du programme (atexit), elle
 *  libère les éléments OpenGL utilisés.*/
static void quit(void) {
  /* suppression de la texture _texId en GPU */
  if(_texId)
    glDeleteTextures(1, &_texId);
  /* suppression du VAO _vao en GPU */
  if(_vao[1])
    glDeleteVertexArrays(2, _vao);
  /* suppression du VBO _buffer en GPU, maintenant il y en a deux */
  if(_buffer[0])
    glDeleteBuffers(2, _buffer);
  if(_bufferf[0])
    glDeleteBuffers(2, _bufferf);
  // Désactiver le blending
glDisable(GL_BLEND);

  /* nettoyage des éléments utilisés par la bibliothèque GL4Dummies */
  gl4duClean(GL4DU_ALL);
}
