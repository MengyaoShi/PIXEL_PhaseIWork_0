#include "BPixelTools/pxfec/include/SysCommand.h"
#include "BPixelTools/tools/include/VMELock.h"
#include "PixelFECInterface/include/PixelFECInterface.h"


#include <string>
#include <iostream>
#include <unistd.h>

#include "BPixelTools/tools/include/MultiplexingServer.h"
#include "BPixelTools/pxfec/include/ControlNetwork.h"

using namespace std;
using namespace Ph2_HwInterface;




//--------------------------------------------------
// some global variables needed for access to vme stuff inside of "exec"
//int32_t gBHandle=0;
PixelFECInterface* pixelFECInterface[22]={0};
ControlNetwork* cn[64]={0};

char * addressTablePtr;


PixelFECInterface* initPixelFEC(int slot){
    
    unsigned long fecBase=0x08000000 * slot;
    cout << fecBase << endl;
    RegManager * pRegManager = new RegManager(addressTablePtr, 0);
    
    int dummy_vmeslot=0; unsigned int dummy_feccrate=0; unsigned int dummy_fecslot = 0;
    PixelFECInterface* aFECInterface = new PixelFECInterface(pRegManager,dummy_vmeslot,dummy_feccrate,dummy_fecslot);
    
    cout<<"Init FEC in slot "<< slot <<endl;
    
    
    
    // tell the firmware explicitly to do all these actions. Arguments for all these functions are: mfec and set bit 0 or 1. There is no need for the fecchannel, it applied to both channels

//   aFECInterface->enableinternalclk();
//    std::cout << "Switching to FCLKA" << std::endl;
//    aFECInterface->disableinternalclk();

     aFECInterface->switchclk(0x10BA3071);

    // disable AMC13 data
    int disableexttrigger_ = aFECInterface->disableexttrigger(1,1);
    cout <<"disableexttrigger_ " << disableexttrigger_ << endl;

    int loopnormtrigger_ = aFECInterface->loopnormtrigger(1,1);
    cout <<"loopnormtrigger_ " << loopnormtrigger_ << endl;

    int injectrstroc_ = aFECInterface->injectrstroc(1,1);
    cout <<"injectrstroc_ " << injectrstroc_ << endl;

    int injectrsttbm_ = aFECInterface->injectrsttbm(1,1);
    cout <<"injectrsttbm_ " << injectrsttbm_ << endl;

    // enable external AMC13 trigger again
    disableexttrigger_ = aFECInterface->disableexttrigger(1,0);
    cout <<"disableexttrigger_ " << disableexttrigger_ << endl;
    
    
    return aFECInterface;
}


//--------------------------------------------------
void exec(SysCommand* cmd){
  int *slot;
  int *mfec;
  int *sector;
  if(cmd->type==SysCommand::kNONE) return;
  if (cmd->type==SysCommand::kSYS){
    if( cmd->Keyword("fec",&slot) ){ 
      pixelFECInterface[*slot]=initPixelFEC(*slot);
    } else if (cmd->Keyword("mfec",&slot,&mfec,&sector)) {
      cn[*sector   ]=new ControlNetwork(pixelFECInterface[*slot], *slot, *mfec, 1, SysCommand::getCNname(*sector   ));
      cn[*sector+32]=new ControlNetwork(pixelFECInterface[*slot], *slot, *mfec, 2, SysCommand::getCNname(*sector+32));
    } else if (cmd->Keyword("mfec",&slot,&mfec,"*")) {
      ControlNetwork* L12=new ControlNetwork(pixelFECInterface[*slot], *slot, *mfec, 1, "*");
      ControlNetwork* L3 =new ControlNetwork(pixelFECInterface[*slot], *slot, *mfec, 2, "*");
      for(int s=0; s<32; s++){
	cn[s   ]=L12;
	cn[s+32]=L3;
      }
    }else{
      cout << "unknown system command " << endl;
    }
  }else if (cn[cmd->CN]!=NULL){
    cn[cmd->CN]->Execute(cmd);
  }else{
    cout << "ControlNetwork doesn't exist "<< cmd->CN <<  " " << SysCommand::getCNname(cmd->CN) <<endl;
  }
}


//--------------------------------------------------
int main(int argc, char **argv){

  // default configuration variables 
  int port=0;                      // port, 0= no port,    define with option -port
  int VMEBoard=1; //CAEN interface   defisrc/pxfec.cxx:41:ne with option -vmecaenpci or -vmecaenusb
  string file="data/d.ini.P-A-2-08";        // init file            define with option -file


  // parse command line arguments
  for(int i=1; i<argc; i++){
    if (strcmp(argv[i],"-port")==0){
      i++;
      try{
	port=atoi(argv[i]);
      }catch(...){
	cerr << "bad port number " << argv[i] << endl;
	exit(1);
      }
    }else if (strcmp(argv[i],"-init")==0){
      i++;
      if(i<argc){
	file=(argv[i]);
      }else{
	cerr << "file argument missing " << endl;
      }
    }else if(strcmp(argv[i],"-vmecaenpci")==0){
      VMEBoard=1; // Optical CAEN interface
    }else if(strcmp(argv[i],"-vmecaenusb")==0){
      VMEBoard=2; // USB CAEN interface
    }else{
      cerr << "usage: pxfec [-port <port>] [-vmecaenpci | -vmecaenusb] [-init <filename>]" << endl;
      exit(1);
    }
  }

  addressTablePtr = (char *) "file:///home/fectest/FEC_mTCA/pixel/BPixelTools/pxfec/xml_files/ConnectionFile.xml";

  VMELock lock(1);
 

    
  // init SysCommand.
  int promptMode=3;  // use 3 to reflect the Network name in the prompt
  SysCommand* cmd=new SysCommand();
  if(cmd->Read(file.c_str())==0){
    do{
      lock.acquire();
      exec(cmd); 
      lock.release();
    } while (cmd->Next());
  }

  // init server
  MultiplexingServer serv(cmd);
  serv.setPrompt(cmd->TargetPrompt(promptMode,">"));
  if( port >0 ){
    serv.open(port);
  }


  // go
  while(serv.eventloop() ){
    lock.acquire();
    exec(cmd);
    lock.release();
    serv.setPrompt(cmd->TargetPrompt(promptMode,">"));
  }

  
}

