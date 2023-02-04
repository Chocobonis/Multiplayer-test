// -----------------------------------------------
// - THESE ARE THE MAIN INCLUDES FOR SYSTEM LIBS -
// -----------------------------------------------
#include <GL/glut.h> // OpenGL library to use
#include <iostream>  // 
#include <stdlib.h>  // main C++ libraries
#include <fstream>   //
#include <sstream>   //
#include <math.h>    //
#include <unistd.h>  //
#include <ctime>
#include <stdio.h>
#include <string.h>
// ---------------------------------
// - NETWORKING LIBRARIES REQUIRED -
// ---------------------------------
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// -------------------------------
// - EXTERNAL LIBRARY DEFINITION -
// -------------------------------
#define STB_IMAGE_IMPLEMENTATION"
#include "lib/stb_image.h"
#ifndef __EMCC__
 #include "lib/imgui/imgui.h"
 #include "lib/imgui/backends/imgui_impl_opengl2.h"
 #include "lib/imgui/backends/imgui_impl_glut.h"
#endif
// -----------------------------
// - GLOBAL VARIABLES ASSIGNED -
// -----------------------------
#include "src/Quim_vars.h" 
// --------------------------------
// - MODULES TO IMPLEMENT IN GAME -
// --------------------------------
#include "include/Quim_console.h"
#include "include/Quim_player.h"
// --- USER MANAGEMENT GOES HERE ---
Player_manager *manager_usr = new Player_manager();
// --- OBJECT AND ROM MANAGER GO HERE ---
#include "src/objects/Quim_roms.h"
Object_manager *manager_obj = new Object_manager();
// ---------------------------------
#include "src/Quim_Tools.h"
#include "src/Quim_controls.h"
#include "src/Quim_Render.h"
// -------------------------------
// - MAIN FUNCTION FOR ALL STUFF -
// -------------------------------
int main(int argc, char **argv){
    #ifndef __EMCC__
     IMGUI_CHECKVERSION();   // TEST VERSION OF IMGUI
     ImGui::CreateContext(); // CREATE AN IMGUI CONTEXT
    #endif
    // ---------------------------------------------------------
    glutInit(&argc, argv);                                      
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(Quim_winx, Quim_winy);                     //  
    glutCreateWindow("QuimChat:Beta");                           // this part initializes the opengl stuff
    // ---------------------------------------------------------
    #ifndef __EMCC__
      ImGuiIO &io = ImGui::GetIO(); (void) io;    // initialize input/output of the imgui API
      ImGui::StyleColorsDark();                   // define dark color for the im gui api
      ImGui_ImplGLUT_Init();                      // start the GLUT version of imgui
      ImGui_ImplGLUT_InstallFuncs();              // install functions of imgui
      ImGui_ImplOpenGL2_Init();                   // use opengl 2 on imgui (to avoid pipewire)
    #endif
    // ---------------------------------------------------------
    glClearDepth(1.0f);                                         // and the ImGui things in order to make
    glDepthFunc(GL_LEQUAL);                                     // the rendering function
    glQuimInit();                                                // 
    #ifndef __EMCC__
        glutIgnoreKeyRepeat(1);                                  // this is the main structure
    #endif
    glutDisplayFunc(Quim_render);                                // that will contain all things of the manager
    glutIdleFunc(Quim_delay);                                    // and enable the different threads
    glutPassiveMotionFunc(Quim_mouse);                           // 
    glutMouseFunc(Quim_move);
    glutMainLoop();
    // ----------------------------------------------------------
    #ifndef __EMCC__
      ImGui_ImplOpenGL2_Shutdown();               // end the OpenGL2 of ImGui
      ImGui_ImplGLUT_Shutdown();                  // shut down glut of imgui
      ImGui::DestroyContext();                    // destroy the context
    #endif
    // ----------------------------------------------------------
    return 0;
}