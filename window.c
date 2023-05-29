/*!\file window.c
 *
 * \brief introduction aux textures (plus ce qui a été vu avant) 
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr 
 * \date February 15 2018
 */

#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>

/* Prototypes des fonctions statiques contenues dans ce fichier C */
static void init(void);
static void draw(void);
static void quit(void);

/*!\brief largeur et hauteur de la fenêtre */
static int _wW = 800, _wH = 600;
/*!\brief identifiant du Vertex Array Object */
static GLuint _vao = 0;
/*!\brief identifiant des Vertex Buffer Objects */
static GLuint _buffer[2] = { 0 };
/*!\brief identifiant du GLSL program */
static GLuint _pId = 0;
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
  /* indices pour réaliser le maillage des géométrie, envoyés dans le
   * VBO ELEMENT_ARRAY_BUFFER */
   

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


/*
5,6,1,
5,1,4,
5,4,3,
5,3,8,
7,2,3,
7,3,8,
6,2,7,
6,1,9*/

};


/* données-sommets envoyées dans le VBO ARRAY_BUFFER */
GLfloat data[] = {
0,0,1, 1, 1, 1,  1,  1,

-1,1,0,1, 1, 1,  1,  0,
1,1,0,1, 1, 1,  1,  1,
1,-1,0,1, 1, 1,  1,  0,
-1,-1,0,1, 1, 1,  1,  1,

-2,-2,-1,1, 1, 1,  1,  1,
-2,2,-1,1, 1, 1,  1,  0,
2,2,-1,1, 1, 1,  1,  1,
2,-2,-1,1, 1, 1,  1,  0,

1,-1,-2,1, 1, 1,  1,  1,
-1,-1,-2,1, 1, 1,  1,  0,
-1,1,-2,1, 1, 1,  1,  1,
1,1,-2,1, 1, 1,  1,  0,

2,2,-3,1, 1, 1,  1,  1,
2,-2,-3,1, 1, 1,  1,  0,
-2,-2,-3,1, 1, 1,  1,  1,
-2,2,-3,1, 1, 1,  1,  0,


};
  const GLuint B = RGB(255, 255, 255), N = 0;
  GLuint tex[] = { B, N, N, B };
  /* Génération d'un identifiant de VAO */
  glGenVertexArrays(1, &_vao);
  /* Lier le VAO-machine-GL à l'identifiant VAO généré */
  glBindVertexArray(_vao);
  /* Activation des 3 premiers indices d'attribut de sommet */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  /* Génération de deux identifiants de VBO un pour ARRAY_BUFFER, un
   * pour ELEMENT_ARRAY_BUFFER */
  glGenBuffers(2, _buffer);
  /* Lier le VBO-ARRAY_BUFFER à l'identifiant du premier VBO généré */
  glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
  /* Transfert des données VBO-ARRAY_BUFFER */
  glBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
  /* Paramétrage 3 premiers indices d'attribut de sommet */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof *data, (const void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof *data, (const void *)(3 * sizeof *data));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof *data, (const void *)(6 * sizeof *data));
  /* Lier le VBO-ELEMENT_ARRAY_BUFFER à l'identifiant du second VBO généré */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer[1]);
  /* Transfert des données d'indices VBO-ELEMENT_ARRAY_BUFFER */
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idata, idata, GL_STATIC_DRAW);
  /* dé-lier le VAO puis les VAO */
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  /* générer un identifiant de texture */
  glGenTextures(1, &_texId);
  /* lier l'identifiant de texture comme texture 2D (1D ou 3D
   * possibles) */
  glBindTexture(GL_TEXTURE_2D, _texId);
  /* paramétrer la texture, voir la doc de la fonction glTexParameter
   * sur
   * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml */
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /* envoi de la donnée texture depuis la RAM CPU vers la RAM GPU voir
   * la doc de glTexImage2D (voir aussi glTexImage1D et glTexImage3D)
   * sur
   * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
  /* dé-lier la texture 2D */
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Création du programme shader (voir le dossier shader) */
  _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
  /* Set de la couleur (RGBA) d'effacement OpenGL */
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  /* activation de la texture 2D */
  glEnable(GL_TEXTURE_2D);
  /* activation du test de profondeur afin de prendre en compte la
   * notion de devant-derrière. */
  glEnable(GL_DEPTH_TEST);
  /* Création des matrices GL4Dummies, une pour la projection, une
   * pour la modélisation et une pour la vue */
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  gl4duGenMatrix(GL_FLOAT, "modelMatrix");
  gl4duGenMatrix(GL_FLOAT, "viewMatrix");
  /* on active la matrice de projection créée précédemment */
  gl4duBindMatrix("projectionMatrix");
  /* la matrice en cours reçoit identité (matrice avec des 1 sur la
   * diagonale et que des 0 sur le reste) */
  gl4duLoadIdentityf();
  /* on multiplie la matrice en cours par une matrice de projection
   * orthographique ou perspective */
  /* décommenter pour orthographique gl4duOrthof(-1, 1, -1, 1, 0, 100); */
  gl4duFrustumf(-1, 1, -1, 1, 2, 100);
  /* dans quelle partie de l'écran on effectue le rendu */
  glViewport(0, 0, _wW, _wH);
}
/*!\brief Cette fonction dessine dans le contexte OpenGL actif. */
static void draw(void) {

  /* une variable d'angle, maintenant elle passe ne degrés */
  static GLfloat angle = 0.0f;
  /* effacement du buffer de couleur, nous rajoutons aussi le buffer
   * de profondeur afin de bien rendre les fragments qui sont devant
   * au dessus de ceux qui sont derrière. Commenter le
   * "|GL_DEPTH_BUFFER_BIT" pour voir la différence. Nous avons ajouté
   * l'activation du test de profondeur dans la fonction init via
   * l'appel glEnable(GL_DEPTH_TEST). */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* activation du programme _pId */
  glUseProgram(_pId);
  /* lier (mettre en avant ou "courante") la matrice vue créée dans
   * init */
  gl4duBindMatrix("viewMatrix");
  /* Charger la matrice identité dans la matrice courante (liée) */
  gl4duLoadIdentityf();
  /* Composer la matrice vue courante en simulant une "caméra" à
   * l'aide de la fonction LookAt(xyz_position_cam,
   * xyz_ou_elle_regarde, xyz_son_vecteur_haut) */
  gl4duLookAtf(0, 1, 10, 0, 0, 0, 0, 1, 0);
  /* lier (mettre en avant ou "courante") la matrice modèle créée dans
   * init */
  gl4duBindMatrix("modelMatrix");
  /* Charger la matrice identité dans la matrice courante (liée) */
  gl4duLoadIdentityf();
  /* on transmet la variable d'angle en l'intégrant dans la matrice
   * modèle. Soit composer la matrice courante avec une rotation
   * "angle" autour de l'axe y (0, 1, 0) */
  gl4duRotatef(angle, 0, 1, 0);
  /* on incrémente angle d'un 1/60 de 1/4 de tour soit (360° x 1/60). Tester
   * l'application en activant/désactivant la synchronisation
   * verticale de votre carte graphique. Que se passe-t-il ? Trouver
   * une solution pour que résultat soit toujours le même. */
  angle += 0.25f * (1.0f / 60.0f) * 360.0f;
  /* Envoyer, au shader courant, toutes les matrices connues dans
   * GL4Dummies */
  gl4duSendMatrices();
  
  
  GLfloat hauteur_pointe = 1;
  GLfloat bas_pyramide_x = 1, bas_pyramide_y = 1, bas_pyramide_z = 0;
  GLfloat etage_1_x = 2, etage_1_y = 2, etage_1_z = -1;
  GLfloat etage_2_x = 1, etage_2_y = 1, etage_2_z = -2;
  GLfloat etage_3_x = 2, etage_3_y = 2, etage_3_z = -3;
  
  
  GLfloat updatedData[] = {
0,0,hauteur_pointe,                                   1,1,1,  1,0,

-bas_pyramide_x, bas_pyramide_y, bas_pyramide_z,      1,1,1,  1,0,
 bas_pyramide_x, bas_pyramide_y, bas_pyramide_z,      1,1,1,  1,1,
 bas_pyramide_x,-bas_pyramide_y, bas_pyramide_z,      1,1,1,  1,0,
-bas_pyramide_x,-bas_pyramide_y, bas_pyramide_z,      1,1,1,  1,1,

-etage_1_x,-etage_1_y, etage_1_z,                     1,1,1,  1,0
-etage_1_x, etage_1_y, etage_1_z,                     1,1,1,  1,1   
 etage_1_x, etage_1_y, etage_1_z,                     1,1,1,  1,0
 etage_1_x,-etage_1_y, etage_1_z,                     1,1,1,  1,1

 etage_2_x ,-etage_2_y , etage_2_z,                   1,1,1,  1,0
-etage_2_x ,-etage_2_y , etage_2_z,                   1,1,1,  1,1
-etage_2_x , etage_2_y , etage_2_z,                   1,1,1,  1,0
 etage_2_x , etage_2_y , etage_2_z,                   1,1,1,  1,1

 etage_3_x, etage_3_y, etage_3_z,                     1,1,1,  1,0
 etage_3_x,-etage_3_y, etage_3_z,                     1,1,1,  1,1
-etage_3_x,-etage_3_y, etage_3_z,                     1,1,1,  1,0
-etage_3_x, etage_3_y, etage_3_z,                     1,1,1,  1,1

};


  glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(updatedData), updatedData, GL_STATIC_DRAW);


  /* activer l'étage de textures 0, plusieurs étages sont disponibles,
   * nous pouvons lier une texture par type et par étage */
  glActiveTexture(GL_TEXTURE0);
  /* lier la texture _texId comme texture 2D */
  glBindTexture(GL_TEXTURE_2D, _texId);
  /* envoyer une info au program shader indiquant que tex est une
   * texture d'étage 0, voir le type (sampler2D) de la variable tex
   * dans le shader */
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  /* envoi d'un booléen pour inverser l'axe y des coordonnées de
   * textures (plus efficace à faire dans le vertex shader */
  glUniform1i(glGetUniformLocation(_pId, "inv"), 1); 
  /* Lier le VAO-machine-GL à l'identifiant VAO _vao */
  glBindVertexArray(_vao);
  /* Dessiner le VAO comme une bande d'un triangle avec 4 sommets
   * commençant à 0
   *
   * Attention ! Maintenant nous dessinons avec DrawElement qui
   * utilise les indices des sommets poassés pour mailler */
  glDrawElements(GL_TRIANGLE_STRIP, 36 + 24+ 24, GL_UNSIGNED_INT, (const GLvoid *)0);
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
  if(_vao)
    glDeleteVertexArrays(1, &_vao);
  /* suppression du VBO _buffer en GPU, maintenant il y en a deux */
  if(_buffer[0])
    glDeleteBuffers(2, _buffer);
  /* nettoyage des éléments utilisés par la bibliothèque GL4Dummies */
  gl4duClean(GL4DU_ALL);
}
