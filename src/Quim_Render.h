#ifndef __EMCC__
  #include "../lib/style.h"
#endif
/*
---------------------------------------------
- MENU AND INTERFACE REDNERDING USING IMGUI -
---------------------------------------------
*/
void Quim_ImGui_Render(){
   #ifndef __EMCC__
      ImGui::SetNextWindowPos(ImVec2(0,0));
      ImGui::SetNextWindowSize(ImVec2(Quim_winx,128));
      ImGui::SetupImGuiStyle(true,0.9);
      ImGui::Begin(".:Chemestry Terminal:.");
     // ImGui::SetupImGuiStyle(true,0.5);
       ImGui::TextColored(ImVec4(1,1,0,1), "Console output:");
       ImGui::BeginChild("Scrolling");
        cmd->Show_messages();
       ImGui::EndChild();
      ImGui::End();  
   #endif
}
/*
----------------------------------------------------------
- THIS IS THE RENDERING OF THE BACKGROUND ELEMENTS IN 2D -
----------------------------------------------------------
*/
void Quim_draw_scenario(){
 glBindTexture(GL_TEXTURE_2D, Q_FLOOR_TEX);
 glBegin(GL_QUADS);
   glTexCoord2f(0,0);
   glVertex3f(0  ,0  , -100);
   glTexCoord2f(0,Quim_winy/128);
   glVertex3f(0  ,Quim_winy, -100);
   glTexCoord2f(Quim_winx/128,Quim_winy/128);
   glVertex3f(Quim_winx,Quim_winy, -100);
   glTexCoord2f(Quim_winx/128,0);
   glVertex3f(Quim_winx,  0, -100);
 glEnd();
}
/*
----------------------------------------------------
- FISH EYE EFFECT AND ALL PARTICLE STUFF GOES HERE -
----------------------------------------------------
*/
void Quim_draw_effects(){
 glBindTexture(GL_TEXTURE_2D, Q_FISHEYE_F);
 glBegin(GL_QUADS);
   glTexCoord2f(0,0);
   glVertex3f(0  ,0  , 100);
   glTexCoord2f(0,1);
   glVertex3f(0  ,Quim_winy, 100);
   glTexCoord2f(1,1);
   glVertex3f(Quim_winx,Quim_winy, 100);
   glTexCoord2f(1,0);
   glVertex3f(Quim_winx,  0, 100);
 glEnd();
}
/*
--------------------------------------------------------------
- THIS IS THE MAIN OPENGL RENDERING LOOP WHERE STUFF HAPPENS -
--------------------------------------------------------------
*/
void Quim_render(){
 #ifndef __EMCC__
   ImGui_ImplOpenGL2_NewFrame();
   ImGui_ImplGLUT_NewFrame();
   // ----------------------------------------------------------
   Quim_ImGui_Render();
   // ----------------------------------------------------------
   ImGui::Render();
   ImGuiIO& io = ImGui::GetIO();
   Quim_winx = io.DisplaySize.x;
   Quim_winy = io.DisplaySize.y;
  glViewport(0,0,(GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
 #endif
 // ----------------------------------------------------------
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 setOrtho();
 Quim_update();
 manager_usr->Self_update(self_x,self_y,self_a);
 // ----------------------------------------------------------
 glPushMatrix();
    Quim_draw_scenario();
 glPopMatrix();
 glPushMatrix();
    manager_usr->Player_drawall(true);
 glPopMatrix();
 glPushMatrix();
    manager_obj->Draw_object_list();
    Quim_draw_effects();
 glPopMatrix();
 // -----------------------------------------------------------
 #ifndef __EMCC__
   ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
 #endif
 // -----------------------------------------------------------
 glFlush();
 glutSwapBuffers();
}