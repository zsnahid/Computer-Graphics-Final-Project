/* Group Member Name	            ID
1. Sakib, Md. Zahid Sadman 	    21-45904-3
2. Shakhawat, Mahmud Ibna	    20-43909-2
3. Mahin, Md. Mosaddek Hossain	20-43905-2
Team Leader Name:	Sakib, Md. Zahid Sadman
Section:	C
*/
#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define DEG_TO_RAD 0.0174532925

GLfloat earthRevolution = 0; // Angle for rotating the earth

// Global variable to store the elapsed time
float elapsedTime = 0.0;

// Function to update the elapsed time
void update(int value)
{
    // Set a rotation speed (adjust as needed)
    float rotationSpeed = 200.0; // 200 degrees per second

    // Update the elapsed time based on rotation speed
    elapsedTime += rotationSpeed / 360.0; // Increment by one full revolution

    // Schedule the next update
    glutTimerFunc(16, update, 0); // 60 frames per second (1000ms / 60 frames)

    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
}

GLuint LoadTexture(const char* filename)
{
    GLuint textureID;

    int width, height, channels;
    unsigned char* image = stbi_load("E:\\AIUB\\6th\\Graphics\\Code\\Solar\\earth_texture.jpg", &width, &height, &channels, 3); // 3 channels for RGB

    if (!image)
    {
        std::cerr << "Error loading texture: " << filename << std::endl;
        return 0; // Return 0 to indicate failure
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

GLuint earthTexture; // Global variable to store the earth texture ID

// Function to initialize the OpenGL environment
void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Setup lights
    GLfloat Position_Of_Light[] = {0, 1, 0, 1}; // Position of the light source
    GLfloat Color_Of_Light[] = {1, 1, 1, 1};    // Color of the light source: white

    glLightfv(GL_LIGHT0, GL_POSITION, Position_Of_Light); // Set the position of the light source number 0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Color_Of_Light);    // Set the diffuse color of light source number 0

    glEnable(GL_LIGHT1); // Enable the second light

    // Setup the second light
    GLfloat Position_Of_Light1[] = {0, -1, 0, 1}; // position for the second light
    GLfloat Color_Of_Light1[] = {1, 1, 1, 1};    // color for the second light: white

    glLightfv(GL_LIGHT1, GL_POSITION, Position_Of_Light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Color_Of_Light1);

    // Set material properties for enhanced lighting
    GLfloat material_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White color for diffuse reflection
    GLfloat material_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f}; // Increased ambient light
    GLfloat material_specular[] = {0.0f, 0.0f, 0.0f, 1.0f}; // No specular reflection

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f); // No shininess

    // Setup camera
    gluLookAt(0, 20, 0, // Camera position and orientation
              0, 0, 0,
              0, 0, 1);
    // Load the Earth texture
    earthTexture = LoadTexture("E:\\AIUB\\6th\\Graphics\\Code\\Solar\\earth_texture.jpg");
}

// Function to handle window resizing
void reshape(int width, int height)
{
    if (height == 0) height = 1;

    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

// Function to draw a the sun
void drawSun()
{
    GLfloat Material_Color[] = {1, 1, 0, 1}; // Color of the material

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Material_Color); // Set the material color
    glutSolidSphere(0.5, 40, 40);// Draw a solid sphere representing the sun
}


GLfloat sunRadius = 0.5;
GLfloat mercuryRadius = 0.05;
GLfloat venusRadius = 0.1;
GLfloat earthRadius = 0.2;
GLfloat marsRadius = 0.15;
GLfloat jupiterRadius = 0.4;
GLfloat saturnRadius = 0.35;
GLfloat uranusRadius = 0.3;
GLfloat neptuneRadius = 0.25;

GLfloat mercuryOrbitRadius = 0.7;
GLfloat venusOrbitRadius = 0.9;
GLfloat earthOrbitRadius = 1.5;
GLfloat marsOrbitRadius = 5.0;
GLfloat jupiterOrbitRadius = 8.0;
GLfloat saturnOrbitRadius = 12.0;
GLfloat uranusOrbitRadius = 16.0;
GLfloat neptuneOrbitRadius = 20.0;

GLfloat Mercury_Color[] = {0.8, 0.8, 0.8, 1};  // Gray color for Mercury
GLfloat Venus_Color[] = {0.9, 0.8, 0.2, 1};    // Yellow color for Venus
GLfloat Earth_Color[] = {0, 0, 1, 1};         // Blue color for the earth
GLfloat Mars_Color[] = {0.8, 0.2, 0.2, 1};        // Red color for Mars
GLfloat Jupiter_Color[] = {0.8, 0.6, 0.2, 1};     // Brownish color for Jupiter
GLfloat Saturn_Color[] = {0.8, 0.8, 0.6, 1};      // Pale yellow color for Saturn
GLfloat Uranus_Color[] = {0.4, 0.4, 1.0, 1};      // Light blue color for Uranus
GLfloat Neptune_Color[] = {0.2, 0.2, 0.6, 1};     // Dark blue color for Neptune

// Function to draw the rings of Saturn
void drawSaturnRings(GLfloat innerRadius, GLfloat outerRadius, GLfloat thickness)
{
    glBegin(GL_QUADS);

    for (int i = 0; i < 360; i++)
    {
        float angle1 = i * (3.14159 / 180.0);
        float angle2 = (i + 1) * (3.14159 / 180.0);

        float x1 = innerRadius * cos(angle1);
        float z1 = innerRadius * sin(angle1);

        float x2 = outerRadius * cos(angle1);
        float z2 = outerRadius * sin(angle1);

        float x3 = outerRadius * cos(angle2);
        float z3 = outerRadius * sin(angle2);

        float x4 = innerRadius * cos(angle2);
        float z4 = innerRadius * sin(angle2);

        glVertex3f(x1, -thickness, z1);
        glVertex3f(x2, -thickness, z2);
        glVertex3f(x3, -thickness, z3);
        glVertex3f(x4, -thickness, z4);
    }

    glEnd();
}

// Modified function to draw a planet with rings
void drawPlanet(GLfloat radius, GLfloat orbitRadius, GLfloat revolution, GLfloat color[])
{
    glPushMatrix();
    glRotatef(revolution, 0, 1, 0);
    glTranslatef(orbitRadius, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glutSolidSphere(radius, 30, 30);

    if (color == Saturn_Color)
    {
        glColor3f(0.8, 0.8, 0.6);
        drawSaturnRings(radius * 1.2, radius * 2.0, 0.2); // Adjust the thickness as needed
    }

    glPopMatrix();
}

// Function to draw a circle representing Earth's orbit on the xz plane
void drawOrbitCircle(GLfloat radius)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 360; i++)
    {
        float angle = i * (3.14159 / 180.0);
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0.0, z);
    }

    glEnd();
}
// Function to draw Earth with texture and material properties
void drawEarthWithTexture(GLfloat radius, GLfloat orbitRadius, GLfloat revolution)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, earthTexture);

    glPushMatrix();
    glRotatef(revolution, 0, 1, 0); // revolution around the Sun
    glTranslatef(orbitRadius, 0.0f, 0.0f);

    // Set material properties for enhanced lighting
    GLfloat material_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White color for diffuse reflection
    GLfloat material_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f}; // Increased ambient light
    GLfloat material_specular[] = {0.0f, 0.0f, 0.0f, 1.0f}; // No specular reflection

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f); // No shininess

    // Draw the Earth with texture
    glBegin(GL_TRIANGLES);
    for (int lat = 0; lat <= 180; lat += 1)
    {
        for (int lon = 0; lon <= 360; lon += 1)
        {
            float x1 = radius * sin(lat * DEG_TO_RAD) * cos(lon * DEG_TO_RAD);
            float y1 = radius * sin(lat * DEG_TO_RAD) * sin(lon * DEG_TO_RAD);
            float z1 = radius * cos(lat * DEG_TO_RAD);

            float x2 = radius * sin((lat + 10) * DEG_TO_RAD) * cos(lon * DEG_TO_RAD);
            float y2 = radius * sin((lat + 10) * DEG_TO_RAD) * sin(lon * DEG_TO_RAD);
            float z2 = radius * cos((lat + 10) * DEG_TO_RAD);

            float x3 = radius * sin((lat + 10) * DEG_TO_RAD) * cos((lon + 10) * DEG_TO_RAD);
            float y3 = radius * sin((lat + 10) * DEG_TO_RAD) * sin((lon + 10) * DEG_TO_RAD);
            float z3 = radius * cos((lat + 10) * DEG_TO_RAD);

            float x4 = radius * sin(lat * DEG_TO_RAD) * cos((lon + 10) * DEG_TO_RAD);
            float y4 = radius * sin(lat * DEG_TO_RAD) * sin((lon + 10) * DEG_TO_RAD);
            float z4 = radius * cos(lat * DEG_TO_RAD);

            glTexCoord2f(lon / 360.0, lat / 180.0);
            glVertex3f(x1, y1, z1);

            glTexCoord2f(lon / 360.0, (lat + 10) / 180.0);
            glVertex3f(x2, y2, z2);

            glTexCoord2f((lon + 10) / 360.0, (lat + 10) / 180.0);
            glVertex3f(x3, y3, z3);

            glTexCoord2f((lon + 10) / 360.0, lat / 180.0);
            glVertex3f(x4, y4, z4);
        }
    }
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}


// Global variable to store meteor shower streaks
std::vector<std::pair<GLfloat, GLfloat>> meteorShowerStreaks;

// Function to update meteor shower streaks
void updateMeteorShower(int value)
{
    // Move existing streaks
    for (auto& streak : meteorShowerStreaks)
    {
        streak.first += 0.1f; // Adjust the speed of the streaks
    }

    // Add new streaks randomly
    if (rand() % 100 < 5) // Adjust the probability of adding a new streak
    {
        GLfloat x = static_cast<GLfloat>(rand()) / RAND_MAX * 50.0 - 25.0; // Random x coordinate in the range [-25, 25]
        GLfloat z = static_cast<GLfloat>(rand()) / RAND_MAX * 50.0 - 25.0; // Random z coordinate in the range [-25, 25]

        meteorShowerStreaks.emplace_back(x, z);
    }

    // Remove streaks that are out of bounds
    meteorShowerStreaks.erase(
        std::remove_if(
            meteorShowerStreaks.begin(),
            meteorShowerStreaks.end(),
            [](const std::pair<GLfloat, GLfloat>& streak) { return streak.first > 25.0; }
        ),
        meteorShowerStreaks.end()
    );

    glutPostRedisplay();
    glutTimerFunc(16, updateMeteorShower, 0);
}

// Function to draw meteor shower streaks
void drawMeteorShower()
{
    glDisable(GL_LIGHTING); // Disable lighting for meteor shower lines
    glLineWidth(1.0f); // Line width
    glColor3f(1.0f, 0.6f, 0.0f); // Set color to orange

    for (const auto& streak : meteorShowerStreaks)
    {
        glBegin(GL_LINES);
        glVertex3f(streak.first, -25.0f, streak.second);
        glVertex3f(streak.first, 25.0f, streak.second);
        glEnd();
    }
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING); // Re-enable lighting
}

//Global variable to track whether to switch the view
bool switchToEarhView = false;

// Function to handle keyboard input
void keyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        switchToEarhView = true;
        glutPostRedisplay(); // Trigger a redisplay to switch the view immediately
    }
    else if(key == GLUT_KEY_LEFT)
    {
        switchToEarhView = false;
        glutPostRedisplay();
    }
}

// Function to display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.0f, 0.1f, 1.0f); // Background Color: Dark Violet

    if(switchToEarhView)
    {
        glLoadIdentity();
        gluLookAt(2, 2, 0, // Camera position
                  0, 0, 0,  // Look at point
                  0, 1, 0); // Up vector pointing towards y-axis

        //drawMoonWithTexture(moonRadius, earthOrbitRadius, moonOrbitRadius, elapsedTime * 1.0);
        drawSun();
        drawEarthWithTexture(earthRadius, earthOrbitRadius, elapsedTime * 3.0);
        drawOrbitCircle(earthOrbitRadius);

        // Draw white dots resembling distant stars in the background
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

        glPointSize(1.0f); // Set the size of the points
        glBegin(GL_POINTS);
        for (int i = 0; i < 500; ++i)
        {
            float x = static_cast<float>(rand()) / RAND_MAX * 50.0 - 25.0; // Random x coordinate in the range [-25, 25]
            float y = static_cast<float>(rand()) / RAND_MAX * 50.0 - 25.0; // Random y coordinate in the range [-25, 25]
            float z = static_cast<float>(rand()) / RAND_MAX * 50.0 - 25.0; // Random z coordinate in the range [-25, 25]

            glVertex3f(x, y, z);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }

    else
    {
        glLoadIdentity();
        gluLookAt(20, 20, 0, // Camera position
                  0, 0, 0,  // Look at point
                  0, 1, 0); // Up vector pointing towards z-axis

        drawSun();

        drawPlanet(mercuryRadius, mercuryOrbitRadius, elapsedTime * 5.0, Mercury_Color);
        drawOrbitCircle(mercuryOrbitRadius);

        drawPlanet(venusRadius, venusOrbitRadius, elapsedTime * 4.0, Venus_Color);
        drawOrbitCircle(venusOrbitRadius);

        drawPlanet(earthRadius, earthOrbitRadius, elapsedTime * 1.0, Earth_Color);

        drawOrbitCircle(earthOrbitRadius);

        drawPlanet(marsRadius, marsOrbitRadius, elapsedTime * 2.0, Mars_Color);
        drawOrbitCircle(marsOrbitRadius);

        drawPlanet(jupiterRadius, jupiterOrbitRadius, elapsedTime * 0.8, Jupiter_Color);
        drawOrbitCircle(jupiterOrbitRadius);

        drawPlanet(saturnRadius, saturnOrbitRadius, elapsedTime * 0.5, Saturn_Color);
        drawOrbitCircle(saturnOrbitRadius);

        drawPlanet(uranusRadius, uranusOrbitRadius, elapsedTime * 0.3, Uranus_Color);
        drawOrbitCircle(uranusOrbitRadius);

        drawPlanet(neptuneRadius, neptuneOrbitRadius, elapsedTime * 0.2, Neptune_Color);
        drawOrbitCircle(neptuneOrbitRadius);

        // Draw white dots resembling distant stars in the background
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

        glPointSize(1.0f); // Set the size of the points
        glBegin(GL_POINTS);
        for (int i = 0; i < 500; ++i)
        {
            float x = static_cast<float>(rand()) / RAND_MAX * 50.0 - 25.0; // Random x coordinate in the range [-25, 25]
            float y = static_cast<float>(rand()) / RAND_MAX * 50.0 - 25.0; // Random y coordinate in the range [-25, 25]
            float z = static_cast<float>(rand()) / RAND_MAX * 50.0 - 25.0; // Random z coordinate in the range [-25, 25]

            glVertex3f(x, y, z);
        }
        glEnd();
        glEnable(GL_LIGHTING);

        drawMeteorShower(); //Draw moving lines resembling meteor shower
    }
    glutSwapBuffers();
    glFlush();
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << gluErrorString(error) << std::endl;
    }
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Solar System");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, update, 0); // Schedule the first update
    glutTimerFunc(0, updateMeteorShower, 0); // Schedule the first update for meteor shower
    glutSpecialFunc(keyboard); // Register the keyboard function
    glutMainLoop();

    return 0;
}
