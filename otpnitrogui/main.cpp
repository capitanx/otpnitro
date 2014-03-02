#include "otpnitrogui.h"

#include <CtrlLib/CtrlLib.h>

#include "../crypto.h"
#include "../page.h"
#include "../text.h"
#include "../otpnitro.h"

using namespace Upp;

struct bookGenDialog : public TopWindow {

	Button		btnGen;
	Button		btnCancel;
	EditString	bookId;
	Label		txtBookGen;

	void DoGen() {
    	WString id = bookId.GetText();

    	if(id.GetCount() == 0)
    		PromptOK("Please, this field cannot be empty.");
    	else
    	{
    		Page * page = new Page;
    		page->generate(id.ToString());
    		delete page;
    		Close();
    	}
	}
	
	void DoClose() {
    	Close();
	}

	typedef bookGenDialog CLASSNAME;

	bookGenDialog() {
    	SetRect(0, 0, 200, 100);
    	
    	Add(txtBookGen.SetLabel("Enter Book name (ID):").LeftPos( 10,150).TopPos(10, 25));
    	Add(bookId.LeftPos(                                       10,180).TopPos(30, 25));
    	Add(btnCancel.SetLabel( "Cancel").LeftPos(                60, 60).TopPos(65, 25));
    	Add(btnGen.SetLabel(    "Generate").LeftPos(             130, 60).TopPos(65, 25));
    	
    	btnGen    <<= THISBACK(DoGen);
    	btnCancel <<= THISBACK(DoClose);
    }
};

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
    
    bookGenDialog dlg;
    
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
		if(!dlg.IsOpen())
			dlg.Open(this);
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
    
    void booksMenu(Bar& bar)
    {
        bar.Add("List books",    THISBACK(List));
        bar.Add("Generate book", THISBACK(Generate));
        bar.Add("Burn page",     THISBACK(Burn));
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
        bar.Add("Books",  THISBACK(booksMenu));
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