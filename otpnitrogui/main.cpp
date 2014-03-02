#include "otpnitrogui.h"

#include <CtrlLib/CtrlLib.h>

#include "../crypto.h"
#include "../page.h"
#include "../text.h"
#include "../otpnitro.h"

using namespace Upp;

struct otpWindow : TopWindow {

    MenuBar		menu;
    Label		lbFrom;
    DropList	from;
    Label		lbTo;
    EditString	to;
    Label		lbPage;
    EditIntSpin	page;
    Option		format;
    DocEdit		text;
    
    void Exit()
    {
        if(PromptOKCancel("Exit OTP Nitro?"))
            Break();
    }
    
    void Help()
    {
        PromptOK("OTP Nitro HELP");
    }

	void About()
    {
        PromptOK("OTP Nitro ABOUT");
    }

	void Crypt()
    {
        PromptOK("CRYPT");
    }

	void Decrypt()
    {
        PromptOK("DECRYPT");
    }
    
    void List()
    {
        Page   * page   = new Page;
		PromptOK(page->list().c_str());
		delete page;
    }
    
    void Generate()
    {
        PromptOK("GENERATE");
    }
    
    void Burn()
    {
        PromptOK("BURN");
    }
    
	void FormatOpt()
    {
        if (format.GetData() == 0) {
        	from.Enable(1);
        	to.Enable(1);
        	page.Enable(1);
        } else {
            from.Enable(0);
        	to.Enable(0);
        	page.Enable(0);
        }
    }
    
    void editMenu(Bar& bar)
    {
        bar.Add("Exit", THISBACK(Exit));
    }
    
    void cryptoMenu(Bar& bar)
    {
        bar.Add("Crypt",   THISBACK(Crypt));
        bar.Add("Decrypt", THISBACK(Decrypt));
    }
    
    void pagesMenu(Bar& bar)
    {
        bar.Add("List",     THISBACK(List));
        bar.Add("Generate", THISBACK(Generate));
        bar.Add("Burn",     THISBACK(Burn));
    }
    
    void helpMenu(Bar& bar)
    {
        bar.Add("Help",  THISBACK(Help));
        bar.Separator();
        bar.Add("About", THISBACK(About));
    }

    void MainMenu(Bar& bar)
    {
        bar.Add("File",   THISBACK(editMenu));
        bar.Add("Crypto", THISBACK(cryptoMenu));
        bar.Add("Pages",  THISBACK(pagesMenu));
        bar.Add("Help",   THISBACK(helpMenu));
    }

    typedef otpWindow CLASSNAME;

    otpWindow() {
        Title("OTPNitro GUI");
        AddFrame(menu);
        menu.Set(THISBACK(MainMenu));
        
        *this
        	<< lbFrom.LeftPos( 10, 50).TopPos(10, 25)
        	<< from.LeftPos(   60, 50).TopPos(10, 25)
        	<< lbTo.LeftPos(  150, 50).TopPos(10, 25)
        	<< to.LeftPos(    180, 50).TopPos(10, 25)
        	<< lbPage.LeftPos(270, 50).TopPos(10, 25)
        	<< page.LeftPos(  310, 50).TopPos(10, 25)
        	<< format.LeftPos(400,100).TopPos(10, 25)
            << text.LeftPos(   0, 600).TopPos(50, 300)
        ;
        
        lbTo.SetText("TO:");
        lbFrom.SetText("BOOK:");
        lbPage.SetText("PAGE:");
        format.SetLabel("Formated msg");
        
        format <<= THISBACK(FormatOpt);
    }
};

GUI_APP_MAIN
{
	otpWindow app;
	app.SetRect(0, 0, 600, 350);
    app.Run();
}