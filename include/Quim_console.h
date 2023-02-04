// INCLUDES FOR THE CONSOLE GO HERE

// --------------------------------------------------
// - THIS IS THE MAIN DATA STRUCTURE FOR THE OUTPUT -
// --------------------------------------------------
struct Output_message{
    std::string typef = "*";                      // this is the message type use: * X ! 
    std::string timestmp = "hh:mm";        // time stamp of when message was sent
    std::string guild = "XClient";        // who sent the output
    std::string message = "";              // message content
    Output_message *next = NULL;           // link to the table
    // final message will be:
    // {*}<hh/mm::TCClient>> output sent!
};
// ---------------------------------------------------
class Console{
    public:
      Output_message *list = NULL;
      Console();
      void Push_message(std::string _t, std::string _g, std::string _m);
      void Show_messages();
};
// ----------------------------------------------------
Console::Console(){}
// ----------------------------------------------------
void Console::Push_message(std::string _t, std::string _g, std::string _m){
    Output_message *msg = new Output_message();
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time
    int Hour   = localTime->tm_hour;
    int Min    = localTime->tm_min;
    
    msg->typef = _t;
    msg->timestmp = std::to_string(Hour) + ":" + std::to_string(Min);
    msg->guild = _g;
    msg->message = _m;

    msg->next = list;
    list = msg;

    if(debug == 1){
        std::cout<<"{x.x} <debug>> "<<_m<<" sent by "<<_g<<std::endl;
    }
}
// ------------------------------------------------------
void Console::Show_messages(){
    Output_message *aux = NULL;
    aux = list;
    while(aux != NULL){
        std::string tmp_msg = "{" + aux->typef + "} [" + aux->timestmp + "-" + aux->guild + "]>> " + aux->message + ".";
        #ifndef __EMCC__
          ImGui::Text(tmp_msg.c_str());
        #endif
        aux = aux->next;
    }
}
// --------------------------------------------------------
Console *cmd = new Console();