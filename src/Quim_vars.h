// --------------------------------
// - THESE ARE THE MAIN VARIABLES -
// --------------------------------
int debug = 1; // is debug mode enabled?
// WINDOWS SIZE VARIABLES FOR RENDERING AND CONTROLS
int Quim_winx = 640; // window resolution
int Quim_winy = 480; //
// ----- IMPLEMENT MATH CONSTANTS --
#define Quim_PI 3.14159
// -------------------------------------
// - DEFAULT INFORMATION FOR THE MODEL -
// -------------------------------------
char *DEF_MDL = "./assets/models/generic.obj";
char *DEF_TEX = "assets/textures/chars.bmp";
// ---------------------------------
int mouse_x = 0; // save the mouse position
int mouse_y = 0; // ---------------------- 
float self_x  = Quim_winx>>1; // save the player positon
float self_y  = Quim_winy>>1; // ----------------------
int self_a  = 0; // save the player angle
float targ_p[2] = {self_x, self_y};   // ----------------------
// ---------------------------------
 time_t currentTime;
 struct tm *localTime;
// ---------------------------------
GLuint Q_FLOOR_TEX; // this is the floor texture  
GLuint Q_FISHEYE_F; // this is the fish eye effect