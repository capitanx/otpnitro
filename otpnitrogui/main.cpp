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
    Label		lbBook;
    DropList	book;
    Label		lbFrom;
    EditString	from;
    Label		lbPage;
    EditIntSpin	pagen;
    Option		format;
    DocEdit		text;
    
    bookGenDialog dlg;
    
    void refreshBooks()
    {
        Page  * page  = new Page;
        
        std::istringstream f(page->list().c_str());
    	std::string line;
    	
    	book.ClearList();
    	while (std::getline(f, line))
    		book.Add(line.c_str());
        
		delete page;
    }
    
    void Exit()
    {
        if(PromptOKCancel("Exit OTP Nitro?"))
            Break();
    }
    
    void Help()
    {
		//TODO: Create a help dialog (html??)
        PromptOK("OTP Nitro HELP");
    }

	void About()
    {
        //TODO: Create a about dialog
        PromptOK("OTP Nitro ABOUT");
    }

	void Crypt()
    {
        Page   * page   = new Page;
        Crypto * crypto = new Crypto;
        
        string id  = book.Get().ToString();
        string msg = text.Get();
        string snt = from.GetText().ToString();
        
        // Get a usable page
        int pnum = page->next(id);
        if (pnum == -1) {
            PromptOK("Not found pages in book");
            return;
        }
        
        // Set page num to selector
        pagen.SetData(pnum);
        
        // Read page X from Book (RECV ID)
        string out = page->read(pnum,id);
        
        // Crypto
        string encrypted = crypto->encrypt(msg,out);
        
        // Print page
        Text * txt = new Text;
        txt->create(pnum,id,snt,encrypted);
        text.Set(txt->print(1));

        delete txt;
        delete page;
        delete crypto;
        
        //TODO: If the user dont burn the page, put the number in red on statusbar
        if(PromptOKCancel("Do you want to burn this page now? (recommended)"))
        {
        	if (!page->burn(pnum,id))
            	PromptOK("Error burning this page.");
        }
    }

	void Decrypt()
    {
        Page   * page   = new Page;
        Crypto * crypto = new Crypto;
        Text   * txt    = new Text;
        
        string msg  = text.Get().ToString();
        string id   = book.Get().ToString();
        string snt  = from.GetText().ToString();
	    int    pnum = pagen.GetData();
	    
	    // Auto-Check if the msg is formated
	    if (( format.Get() != 1 ) && ( msg.find("=") != std::string::npos ))
	        if(PromptOKCancel("Is a formated msg? (XXX DE YYY N = AAAA =)"))
	        {
	            format.Set(1);
	            from.Enable(0);
        		book.Enable(0);
        		pagen.Enable(0);
	        }
        
		// Decrypts the msg formated / plain
        if (format.Get() == 1)
            txt->parse(msg);
        else
            txt->create(pnum,id,snt,msg);

        // Read page X from Book (RECV ID)
        string out = page->read(txt->page,txt->from);

        if (out.length() == 0) {
            PromptOK("The page don't exist."); 
            return;
        }

        // Crypto
        crypto->replaceAll(txt->msg," ","");
        txt->msg = crypto->decrypt(txt->msg,out);

        // Print MSG
        text.Set(txt->print(0));

        delete txt;
        delete page;
        delete crypto;
        
        //TODO: If the user dont burn the page, put the number in red on statusbar
        if(PromptOKCancel("Do you want to burn this page now? (recommended)"))
        {
        	if (!page->burn(pnum,id))
            	PromptOK("Error burning this page.");
        }
    }
    
    void List()
    {
		refreshBooks();
    }
    
    void Generate()
    {	
		if(!dlg.IsOpen())
			dlg.Open(this);
    }
    
    void Burn()
    {
        //TODO: Create a page burn dialog
        PromptOK("BURN");
    }
    
	void FormatOpt()
    {
        if (format.GetData() == 0) {
        	from.Enable(1);
        	book.Enable(1);
        	pagen.Enable(1);
        } else {
            from.Enable(0);
        	book.Enable(0);
        	pagen.Enable(0);
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
        bar.Add("Refresh  books",THISBACK(List));
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
        	<< lbBook.LeftPos( 10, 50).TopPos(10, 25)
        	<< book.LeftPos(   60, 50).TopPos(10, 25)
        	<< lbFrom.LeftPos(130, 50).TopPos(10, 25)
        	<< from.LeftPos(  180, 50).TopPos(10, 25)
        	<< lbPage.LeftPos(250, 50).TopPos(10, 25)
        	<< pagen.LeftPos( 300, 50).TopPos(10, 25)
        	<< format.LeftPos(400,100).TopPos(10, 25)
            << text.LeftPos(    0,600).TopPos(50, 300)
        ;
        
        lbFrom.SetText("FROM:");
        lbBook.SetText("BOOK:");
        lbPage.SetText("PAGE:");
        format.SetLabel("Formated msg");
        
        format <<= THISBACK(FormatOpt);

		refreshBooks();
    }
};

GUI_APP_MAIN
{
	otpWindow app;
	app.SetRect(0, 0, 600, 350);
    app.Run();
}