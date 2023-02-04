// ------------REQUEST NEEDED LIBS -----------
#include "../assets/missing.c"
// -------------------------------------------
// --- DATA STRUCTURE VARIABLE -------
int user_ptr = 0; // PLAYER POINTER FOR LIST
// -------------------------------------------
struct Dialog_box{               // .................................
    std::string message = "..."; // this is the dialog object to use
    float opacity = 1.0f;        // when the dialog starts each loop will decrease it's lifetime
    Dialog_box *parent = NULL;   // once the dialog runs out of life it gets destroyed and unrendered
};                               // .................................
// -------------------------------------------
struct User_node{
    int   token;  // this is the value which i'll use to identify users 
    float pos_x;  // this is the current position value
    float pos_y;  // it's where the player will be rendered
    float tar_x;  // ------------------
    float tar_y;  // this is the target to walk
    float rot_p;  // this is the rotation
    int v_num = 0;// this is the number of vertex
    GLuint usr_texture; // this is the player texture 
    double usr_Vertex[9][10000]; // --------------------
    double usr_UVMaps[6][10000]; // player model that must be loaded
    std::string username_p;      // username of the user
    User_node *Parent = NULL;    // Node pointer for structure
    Dialog_box *sent = NULL;     // Node pointer for dialog
};
// ------------------------------------------
class Player_manager{
    public:
    // --- VARIABLES OF PLAYER MANAGER ---
        User_node *online_users[1000]; // list of users
        User_node *auxiliar;           // temporal for reading
    // --- VARIABLES FOR MODEL LOADING ---
        std::string _modl; 
    // -- FUNCTIONS OF PLAYER MANAGER --
    Player_manager();      // Player manager constructor
    void Player_Joined();  // detect if a player has joined
    void Player_Init();    // start the players and request all
    void Players_Update(); // update player position
    void Self_update(float _ux, float _uy, float _ur); // update self player position    
    void Push_node_user(std::string _uname, int _ux, int _uy, int _token, char *_mdlurl, char *_texurl); 
    // insert a user/model into stack
    // -- FUNCTIONS FOR LOADING STUFF --
    GLuint  Quim_load_texture(char *filename, int w, int h); // load the texture
    int     Quim_load_model(char *filename, double mdl[9][10000], double _uv[6][10000], int _n);  
    // ----------------------------------
    void Player_drawall(bool draw_self); // this draws all the players in stack 
    // load the model
}; // --------------------------------------------
// -- CONSTRUCTOR FUNCTION WHICH WILL START UP OBJECT --
Player_manager::Player_manager(){
    cmd->Push_message("*", "XenonSys", "object for players created");
}

void Player_manager::Player_Init(){
    Push_node_user("default", 0,0,0, DEF_MDL, DEF_TEX);
}

void Player_manager::Self_update(float _ux, float _uy, float _ur){
    auxiliar = online_users[0];
    auxiliar->pos_x = _ux;
    auxiliar->pos_y = _uy;
    auxiliar->rot_p = _ur;
}
// ------------ FUNCTION OF MODEL LOADING --------------
int Player_manager::Quim_load_model(char *filename, double mdl[9][10000], double _uv[6][10000], int _n){
 // -----------------------------------------------------------------------------------------
 std::cout<<"{*} <Xenon engine>> starting model loading"<<std::endl;
 std::string _m = "";                       // this segment implements a loading for 
 std::ifstream file(filename);              // the file of the models of each user
 std::string file_content;                  // it stores the content on a string
 while(std::getline(file, file_content)){   // so it can be analized later by interpreter
  _m = _m + file_content + "\n";            // it's mostly file reading
 }
 std::cout<<"{*} <Xenon engine>> file was loaded propperly result: \n"<<_m<<std::endl;
 // ------------------------------------------------------------------------------------------
 double vertices[3][10000];                // temporal vertex array
 double uvMappin[3][10000];                // temporal uv mapping array
 char vert1[20], vert2[20], vert3[20];     // temporal variables for conversion
 float tmpv1 = 0, tmpv2 = 0, tmpv3 = 0;    // -----------------------------------
 int vcounter = 0, tcounter = 0, bcounter = 0;  // reassembly variables for interpreter
 char v1[15],v2[15],v3[15];int trash;           // the algorithm reads the file
 int cv1,cv2,cv3,cv4,cv5,cv6;                   // and then stores the model on a node
 std::cout<<"{*} <Xenon engine>> mdloader has implemented all variables"<<std::endl;
 // -------------------------------------------------------------------------------------------
 std::istringstream m_tmp(_m);                  // convert the string of file to use sscanf
 std::string tmp_line = "";                     // this is the part where the current line is saved
 std::cout<<"{*} <Xenon engine>> starting the interpreter....."<<std::endl;
 while(std::getline(m_tmp, tmp_line)){          // while the file is not complete of reading
  char lh[128];                                 // THEN: ...................................
  char temporal[128];                                                 // used for sscanf
  strcpy(temporal, tmp_line.c_str());                                 // copy the temporal array
  sscanf(temporal, "%s", &lh);                                        // analyze what type of value it is
  std::cout<<"{*} <Xenon engine>> reading the line: "<<tmp_line<<std::endl;
  // ---------- IF READING A VERTEX ON THE FILE -----------------------------------------------
  if(strcmp(lh, "v") == 0){
   sscanf(temporal,"%s %s %s %s\n",&trash , &vert1, &vert2, &vert3 ); // if im reading vertex then extract them
   tmpv1 = atof(vert1);                                               //
   tmpv2 = atof(vert2);                                               // convert to decimals
   tmpv3 = atof(vert3);                                               // 
   vertices[0][vcounter] = tmpv1; vertices[1][vcounter] = tmpv2; vertices[2][vcounter] = tmpv3;
   vcounter++;                                                        // update line pointers
  }
  // ------------ READING A UV MAPPING VERTEX ON THE FILE -------------------------------------
  if(strcmp(lh, "vt") == 0){
   sscanf(temporal,"%s %s %s\n",&trash , &vert1, &vert2 );                    // scan texture mapping by vertex
   tmpv1 = atof(vert1);                                                       // 
   tmpv2 = atof(vert2);                                                       // then convert it into vertex/point
   tmpv3 = 0;                                                                 // this is just trash
   uvMappin[0][tcounter] = tmpv1; uvMappin[1][tcounter] = tmpv2;              // store new information found
   tcounter++;                                                                // move the pointer for uv mapping
  }
  // ----------- THESE ARE THE CONVERSIONS TO MAKE FOR THE FILE TO THE ASSEMBLY ----------------
  std::string tmp = "",num1 = "",num2 = "";    // the idea is to reassemble to avoid compression
  bool isL = true;                             //
  std::string tmp2 = "",num3 = "",num4 = "";   // these conversions are used for reassemble
  bool isL2 = true;                            //
  std::string tmp3 = "",num5 = "",num6 = "";   // the OBJ on the F stores the order of vertex
  bool isL3 = true;                            // so the idea is to organize the info
  bool ns1 = true,ns2 = true,ns3 = true;       // again
  // --------------------------------------------------------------------------------------------
  // -------------------- THE F REPRESENTS THE ORGANIZATION -------------------------------------
  if(strcmp(lh, "f") == 0){                                //
   std::cout<<"{*} <Xenon engine>> FOUND ASSEMBLY MODEL LINE"<<std::endl;
   sscanf(temporal, "%s %s %s %s ",&trash, &v1, &v2, &v3); // read and store all the information
   tmp = v1;tmp2 = v2; tmp3 = v3;                          // of the reorganization
   tmp = tmp+".";tmp2 = tmp2+"."; tmp3 = tmp3+".";         // add point to the reading
  // --------------------------------------------------------------------------------------------
   ns1 = true;ns2 = true;ns3 = true;                       //
   isL = true; isL2 = true; isL3 = true;                   // initialize values
  // --------------------------------------------------------------------------------------------
   std::cout<<"{*} <Xenon engine>> Reading: "<<tmp<<"::"<<tmp2<<"::"<<tmp3<<std::endl;
   sscanf(tmp.c_str() , "%i/%i", &cv1, &cv2); // 
   sscanf(tmp2.c_str(), "%i/%i", &cv3, &cv4); // scan each piece of the vertices to assemble vertex and UVMap
   sscanf(tmp3.c_str(), "%i/%i", &cv5, &cv6); //
  // --------------------------------------------------------------------------------------------
   cv1--; cv2--; cv3--; // 
   cv4--; cv5--; cv6--; // adjusteach segment
   std::cout<<"{*} <Xenon engine>> segment stuff"<<std::endl;
  // --------------------------------------------------------------------------------------------
   // THIS PART IS THE MAIN REASSEMBLE OF THE MODEL INSIDE THE FINAL ARRAYS
   std::cout<<"{*} <Xenon engine>> vertex 1 assembled with: "<<cv1<<"|"<<cv2<<std::endl;
   _uv[0][bcounter] = uvMappin[0][cv2]; _uv[1][bcounter] = uvMappin[1][cv2];
   mdl[0][bcounter] = vertices[0][cv1]; mdl[1][bcounter] = vertices[1][cv1]; mdl[2][bcounter] = vertices[2][cv1];
   std::cout<<"{*} <Xenon engine>> vertex 2 assembled with: "<<cv3<<"|"<<cv4<<std::endl;
   _uv[2][bcounter] = uvMappin[0][cv4]; _uv[3][bcounter] = uvMappin[1][cv4];
   mdl[3][bcounter] = vertices[0][cv3]; mdl[4][bcounter] = vertices[1][cv3]; mdl[5][bcounter] = vertices[2][cv3];
   std::cout<<"{*} <Xenon engine>> vertex 3 assembled with: "<<cv5<<"|"<<cv6<<std::endl;
   _uv[4][bcounter] = uvMappin[0][cv6]; _uv[5][bcounter] = uvMappin[1][cv6];
   mdl[6][bcounter] = vertices[0][cv5]; mdl[7][bcounter] = vertices[1][cv5]; mdl[8][bcounter] = vertices[2][cv5];
   std::cout<<"{*} <Xenon engine>> trit assembled..."<<std::endl;
   // NOTE: this part of the code actually assembles triangles of the models
   // in order to manage to have a model complete by triangles
   // ---------------------------------------------------------------------------------------------
   bcounter++; // number of triangles inside the model that was assembled
  }
  std::cout<<"{*} <Xenon engine>> complete!"<<std::endl;
 }
 // ------------------------------------------------------------------------------------------------
  return bcounter;   // return the ammount of triangles inside the model
}
// ------------ FUNCTION OF TEXTURE LOAD ---------------
GLuint Player_manager::Quim_load_texture(char *filename, int w, int h){
 std::cout<<"loading texture"<<std::endl;                                       // debug message
 GLuint tmp_txt;
 int comp = 4;
 unsigned char* image = stbi_load(filename, &w, &h, &comp, STBI_rgb_alpha);

  if(image == nullptr){
    std::cout<<"{*} <Xenon engine>> not found"<<std::endl;
    glGenTextures(1, &tmp_txt);
    glBindTexture(GL_TEXTURE_2D, tmp_txt);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);                
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                 // these are the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    #ifndef __EMCC__
      gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
    #else
     // glGenerateMipmap(GL_TEXTURE_2D);
    #endif
  
  }
  glGenTextures(1, &tmp_txt);
  glBindTexture(GL_TEXTURE_2D, tmp_txt);

 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

 stbi_image_free(image);
 std::cout<<"{*} <Xenon engine>> complete!"<<std::endl;
 return tmp_txt;
}
// -- FUNCTION TO CREATE A USER ON THE CLIENT  --
void Player_manager::Push_node_user(std::string _uname, int _ux, int _uy, int _token, char *_mdlurl, char *_texurl){
    User_node *newnode = new User_node(); // create a new player node
    newnode->username_p = _uname;         // 
    newnode->pos_x = _ux;                 // initialize all the objects
    newnode->pos_y = _uy;                 // and properties of the user 
    newnode->token = _token;              // basically download their profile
    // -----------------------------------
    newnode->v_num = Quim_load_model(_mdlurl, newnode->usr_Vertex, newnode->usr_UVMaps, newnode->v_num);
    newnode->usr_texture = Quim_load_texture(_texurl, 256,128); // THIS PART IMPLEMENTS MODEL FOR USERS
    newnode->Parent = NULL;
    // -----------------------------------
    if(online_users[user_ptr] != NULL){      // then before implementing our node to prevent trash
        User_node *p_tmp = new User_node();  // we check if the memory has something written previously
        auxiliar = online_users[user_ptr];   // if it wasn't clean at all we must make a temporal node
        auxiliar->Parent = p_tmp;            // link both nodes to separate them from the main list
        online_users[user_ptr] = NULL;       // and then delete the parent node, and both, child and parent
        delete p_tmp;                        // will be deleted
    }
    // -----------------------------------
    online_users[user_ptr] = newnode;        // then we assign our fresh new player into the list
    user_ptr++;
}
// -------------------------------------------
// -- DRAW AL,L THE PLAYERS ON THE USERLIST ----------
void Player_manager::Player_drawall(bool draw_self){ // THIS VARIABLE DEFINES IF THE PLAYER MUST BE DRAWN
    int draw_limit = 0;                              // ASSIGN A MAXIMUM DRAW LIMIT
    if(draw_self == false){draw_limit++;}            // IF NO THEN AVOID DRAWING 0
    glPushMatrix();                                  // PUSH PLAYER MATRIX
    for(int i = draw_limit; i < user_ptr; i++){      // LOOP THROUGH ALL LIST OF ONLINE USERS FETCHED
      auxiliar = online_users[i];                    // FETCH CURRENT USER ON THE LIST LOOP
      // ---------------------------------------------
      glPushMatrix();                                         // PLAYER MATRIX
        //glScalef(6,6,6);
        glTranslatef(auxiliar->pos_x,auxiliar->pos_y,0);      // TRANSLATE PLAYER
        glRotatef(-40,10,1,1);                                // ROTATION FOR ISOMETRIC PERSPECTIVE
        glRotatef(auxiliar->rot_p,0,auxiliar->rot_p,1);      // ROTATE TOWARDS ANGLE
        glBindTexture(GL_TEXTURE_2D, auxiliar->usr_texture);  // ASSING THE PLAYER'S TEXTURE
        glBegin(GL_TRIANGLES);                                // GET ALL PLAYER TRIANGLES
        // ----------------------------------------------------------------------------------
            for(int j = 0; j < auxiliar->v_num; j++){
                glTexCoord2f(auxiliar->usr_UVMaps[0][j], auxiliar->usr_UVMaps[1][j]);
                glVertex3f(auxiliar->usr_Vertex[0][j],auxiliar->usr_Vertex[1][j],auxiliar->usr_Vertex[2][j]);
            // - CREATE A TRIANGLE WITH THE INFORMATION FETCHED ON THE ARRAYS
                glTexCoord2f(auxiliar->usr_UVMaps[2][j], auxiliar->usr_UVMaps[3][j]);
                glVertex3f(auxiliar->usr_Vertex[3][j],auxiliar->usr_Vertex[4][j],auxiliar->usr_Vertex[5][j]);
            // - EVENTUALLY THIS WILL CREATE A MODEL WITH OUR PLAYERS
                glTexCoord2f(auxiliar->usr_UVMaps[4][j], auxiliar->usr_UVMaps[5][j]);
                glVertex3f(auxiliar->usr_Vertex[6][j],auxiliar->usr_Vertex[7][j],auxiliar->usr_Vertex[8][j]);
            }
        // ---------------------------------------------------------------------------------
        glEnd();
        glColor3f(1,1,1);
      glPopMatrix();
    }
    glPopMatrix();
}
/*
 *********************************
 * MULTIPLAYER LIBRARIES LICENCE *
 *********************************
 -----------------------------------------------------------------------
 This is the complete code of Xenon Source Engine written in C++ using OpenGL.
 It should be buildable on Windows and Linux, but it's not tested on windows.

 The code is all licensed under the terms of the GPL (gnu public license).  
 You should read the entire license, but the gist of it is that you can do 
 anything you want with the code, except selling your new version, unless we 
 get to an agreement.  The catch is that if you distribute new binary versions,
 you are required to make the entire source code available for free to everyone.

 The primary intent of this release is for entertainment and educational 
 purposes, but the GPL does allow commercial exploitation if you obey the 
 full license.  If you want to do something commercial and you just can't bear 
 to have your source changes released, we could still negotiate a separate 
 license agreement (for $$$), but I would encourage you to just live with the 
 GPL.

 Thanks to ClaraCF (https://github.com/ClaraCF) for helping with this release.

 ~ Boniikwiidz
 Boni!Ware
*/