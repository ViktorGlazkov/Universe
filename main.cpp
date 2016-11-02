#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

struct Particle {
    float x;
    float y;
    float vx;
    float vy;
    float m;
};

const int N = 4;
Particle particles[N];

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++) {
        glVertex2f(particles[i].x, particles[i].y);
    }
    glEnd();

    glutSwapBuffers();
}

void timer(int = 0) {
    for(int i = 0; i < N; i++) {
        Particle &p0 = particles[i];
        for (int j = 0; j < N; j++) {
            if (i == j) {
                continue;
            }

            const Particle &p = particles[j];
            float  d = sqrt(pow((&p0.x - &p.x), 2) + pow((&p0.y - &p.y), 2));

            if (d > 3) {
                p0.vx += 0.00007 * p.m / pow(d, 2) * (p.x - p0.x) / d;
                p0.vy += 0.00007 * p.m / pow(d, 2) * (p.y - p0.y) / d;
            }

            p0.x += p0.vx;
            p0.y += p0.vy;
        }
    }
    display();
    glutTimerFunc(1, timer, 0);
}

Particle getParticle(float x, float y, float vx, float vy, float m) {
    Particle particle;
    particle.x = x;
    particle.y = y;
    particle.vx = vx;
    particle.vy = vy;
    particle.m = m;

    return particle;
}

void glut (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(240, 240);
    glutInitWindowPosition(20, 810);
    glutCreateWindow("Universe");
    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 200, 200, 0, -1, 1);
    glutDisplayFunc(display);
    timer();
    glutMainLoop();
}

int main(int argc, char **argv) {
    particles[0] = getParticle(100, 100, 0, 0, 1000);
    particles[1] = getParticle(130, 100, 0, -0.1, 7);
    particles[2] = getParticle(30, 100, 0, 0.1, 10);
    particles[3] = getParticle(25, 100, 0, 0.11, 0.1);

    glut(argc, argv);
}