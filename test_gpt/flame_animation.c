#include <GL/glut.h>
#include <stdlib.h>

#define MAX_PARTICLES 1000
#define GRAVITY -0.5
#define DAMPING 0.98

typedef struct {
    float position[3];
    float velocity[3];
    float color[3];
    float lifespan;
} Particle;

Particle particles[MAX_PARTICLES];

void initParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position[0] = 0.0f;
        particles[i].position[1] = 0.0f;
        particles[i].position[2] = 0.0f;
        
        particles[i].velocity[0] = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;
        particles[i].velocity[1] = ((float)rand() / RAND_MAX) * 0.7f + 0.5f;
        particles[i].velocity[2] = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;
        
        particles[i].color[0] = 1.0f;
        particles[i].color[1] = 0.5f + (float)rand() / RAND_MAX * 0.5f;
        particles[i].color[2] = 0.0f;
        
        particles[i].lifespan = 1.0f;
    }
}

void updateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].velocity[1] += GRAVITY;
        particles[i].velocity[0] *= DAMPING;
        particles[i].velocity[1] *= DAMPING;
        particles[i].velocity[2] *= DAMPING;
        
        particles[i].position[0] += particles[i].velocity[0];
        particles[i].position[1] += particles[i].velocity[1];
        particles[i].position[2] += particles[i].velocity[2];
        
        particles[i].lifespan -= 0.01f;
        
        if (particles[i].lifespan < 0.0f) {
            particles[i].position[0] = 0.0f;
            particles[i].position[1] = 0.0f;
            particles[i].position[2] = 0.0f;
            
            particles[i].velocity[0] = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;
            particles[i].velocity[1] = ((float)rand() / RAND_MAX) * 0.7f + 0.5f;
            particles[i].velocity[2] = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;
            
            particles[i].color[0] = 1.0f;
            particles[i].color[1] = 0.5f + (float)rand() / RAND_MAX * 0.5f;
            particles[i].color[2] = 0.0f;
            
            particles[i].lifespan = 1.0f;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f, -0.5f, -2.5f);
    
    glBegin(GL_POINTS);
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        glColor3f(particles[i].color[0], particles[i].color[1], particles[i].color[2]);
        glVertex3f(particles[i].position[0], particles[i].position[1], particles[i].position[2]);
    }
    
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    updateParticles();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Flame Animation");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    initParticles();
    
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    
    return 0;
}

