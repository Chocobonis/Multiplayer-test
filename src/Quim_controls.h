void Quim_mouse(int x, int y){
   // int aspect_r= (Quim_winx/Quim_winy)*25;
    self_a = 180+(
      (atan2(
        (x-(self_x)),
        (y-(self_y))
            )*180)
    // --------------- divided PI        
    /Quim_PI
    );
    //std::cout<<"{*} [QuimChat]>> "<<self_x+((Quim_winx>>1))<<std::endl;
}

void Quim_move(int button, int state, int x, int y){
  /*int aspect_r= (Quim_winx/Quim_winy)*25;
  float prj_x = (x-((Quim_winx>>1)))/aspect_r;
  float prj_y = (y-((Quim_winy>>1)))/aspect_r;*/
  //std::cout<<"{*} [QuimChat]>> "<<prj_x<<" "<<prj_y<<std::endl;
  targ_p[0] = x;
  targ_p[1] = y;
}

void Quim_update(){
  if(((int)targ_p[0] % 2)!=0){targ_p[0]+=1;}
  if(((int)targ_p[1] % 2)!=0){targ_p[1]+=1;}
  if(self_x < targ_p[0]){self_x+=2;}
  if(self_x > targ_p[0]){self_x-=2;}
  if(self_y < targ_p[1]){self_y+=2;}
  if(self_y > targ_p[1]){self_y-=2;}
}