#include "otpnitrogui.h"

#include <CtrlLib/CtrlLib.h>
#define IMAGECLASS icons
#define IMAGEFILE  <otpnitrogui/icons.iml>
#include <Draw/iml.h>
#define TOPICFILE <otpnitrogui/help.tpp/all.i>
#include <Core/topic_group.h>

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
    	
    	Add(txtBookGen.SetLabel("Enter Book name (ID):").LeftPos( 10,180).TopPos(10, 25));
    	Add(bookId.LeftPos(                                       10,180).TopPos(30, 25));
    	Add(btnCancel.SetLabel( "Cancel").LeftPos(                35, 75).TopPos(65, 25));
    	Add(btnGen.SetLabel(    "Generate").LeftPos(             115, 75).TopPos(65, 25));
    	
    	btnGen    <<= THISBACK(DoGen);
    	btnCancel <<= THISBACK(DoClose);
    }
};

struct burnDialog : public TopWindow {

	Button		btnGen;
	Button		btnCancel;
	DropList	book;
	EditIntSpin	pagen;
	Label		txtBookGen;

	void DoBurn() {
		int    pnum = pagen.GetData();
    	string id   = book.Get().ToString();

    	if(id.length() == 0)
    		PromptOK("Please, this field cannot be empty.");

		Page  * page  = new Page;
		
    	if (page->burn(pnum,id))
    		PromptOK("Page burned successfully.");
    	else
            PromptOK("This page doesn't exist.");
    	
    	delete page;
	}
	
	void DoClose() {
    	Close();
	}

	typedef burnDialog CLASSNAME;

	burnDialog() {
    	SetRect(0, 0, 160, 100);
    	
    	Add(txtBookGen.SetLabel("Enter Book and page num:").LeftPos( 10,150).TopPos(10, 25));
    	Add(book.LeftPos(                                            10, 60).TopPos(30, 25));
    	Add(pagen.LeftPos(                                           90, 60).TopPos(30, 25));
    	Add(btnCancel.SetLabel( "Close").LeftPos(                    10, 60).TopPos(65, 25));
    	Add(btnGen.SetLabel(    "Burn").LeftPos(                     90, 60).TopPos(65, 25));
    	
    	btnGen    <<= THISBACK(DoBurn);
    	btnCancel <<= THISBACK(DoClose);
    	
    	Page  * page  = new Page;
        
        std::istringstream f(page->list().c_str());
    	std::string line;
    	
    	book.ClearList();
    	while (std::getline(f, line))
    		book.Add(line.c_str());
        
		delete page;
    }
};

struct aboutDialog : public TopWindow {

	ImageCtrl		logo;
	RichTextCtrl	text;

	void DoClose() {
    	Close();
	}

	typedef aboutDialog CLASSNAME;

	aboutDialog() {
    	SetRect(0, 0, 400, 280);
    	
    	Add(logo.SetImage(icons::main_icon_48).LeftPos(280,58).TopPos( 15,58));
    	Add(text.LeftPos(                              20,380).TopPos(30,280));

		text.SetData("_____[6 OTP[5/ NITRO]]__v0.1&&Is a secure One Time Pad implementation to use on computers or as assistant on manual operations.&&This project is licensed under the [^http://www.gnu.org/licenses/gpl-3.0.html^ GPLv3] license. More information in the [^https://code.haibane.org/crypto/otpnitro^ project page].&&2013-2014 (c) [^mailto:capi_x@haibane.org^ capi\_x@haibane.org]");
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
    
    bookGenDialog	dlgBook;
    aboutDialog		dlgAbout;
    burnDialog		dlgBurn;
    
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
		HelpWindow help;
    	help.GoTo("topic://otpnitrogui/help/main$en-us");
    	help.SetRect(0, 0, 600, 350);
    	help.Execute();
    }

	void About()
    {
        if(!dlgAbout.IsOpen())
			dlgAbout.Open(this);
    }

	void Crypt()
    {
        string id  = book.Get().ToString();
        string msg = text.Get();
        string snt = from.GetText().ToString();

		if (id.length() == 0) {
            PromptOK("You must select a book");
            return;
        }
        
        if (snt.length() == 0) {
            PromptOK("Please, you must put an id in the field \"from\"");
            return;
        }
        
        if (msg.length() == 0) {
            PromptOK("Empty message! rly?");
            return;
        }
        
        Page   * page   = new Page;
        Crypto * crypto = new Crypto;
        
        // Get a usable page
        int pnum = page->next(id);
        if (pnum == -1) {
            PromptOK("Not found pages in book");
            delete page;
            delete crypto;
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

        //TODO: If the user dont burn the page, put the number in red on statusbar
        if(PromptOKCancel("Do you want to burn this page now? (recommended)"))
        {
        	if (!page->burn(pnum,id))
            	PromptOK("Error burning this page.");
        }
        
        delete txt;
        delete page;
        delete crypto;
    }

	void Decrypt()
    {
        string msg  = text.Get().ToString();
        string id   = book.Get().ToString();
        string snt  = from.GetText().ToString();
	    int    pnum = pagen.GetData();
	    
	    // Auto-Check if the msg is formated
	    if (( format.Get() != 1 ) && ( msg.find("=") != std::string::npos ))
	    {
	        if(PromptOKCancel("Is a formated msg? (XXX DE YYY N = AAAA =)"))
	        {
	            format.Set(1);
	            from.Enable(0);
        		book.Enable(0);
        		pagen.Enable(0);
	        }
	    }
        else
        {
            if (id.length() == 0) {
	            PromptOK("You must select a book");
	            return;
	        }
			if (snt.length() == 0) {
	            PromptOK("Please, you must put an id in the field \"from\"");
	            return;
	        }
			if (msg.length() == 0) {
	            PromptOK("Empty message! rly?");
	            return;
	        }
        }
        
        Page   * page   = new Page;
        Crypto * crypto = new Crypto;
        Text   * txt    = new Text;
        
		// Decrypts the msg formated / plain
        if (format.Get() == 1)
            txt->parse(msg);
        else
            txt->create(pnum,id,snt,msg);

        // Read page X from Book (RECV ID)
        string out = page->read(txt->page,txt->book);

        if (out.length() == 0) {
            PromptOK("The page don't exist.");
            delete page;
            delete crypto;
            delete txt;
            return;
        }

        // Crypto
        crypto->replaceAll(txt->msg," ","");
        txt->msg = crypto->decrypt(txt->msg,out);

        // Print MSG
        text.Set(txt->print(0));

        book.Set(txt->book.c_str());
        from.SetData(txt->from.c_str());
        pagen.SetData(txt->page);

        //TODO: If the user dont burn the page, put the number in red on statusbar
        if(PromptOKCancel("Do you want to burn this page now? (recommended)"))
        {
        	if (!page->burn(pnum,id))
            	PromptOK("Error burning this page.");
        }
        
        delete txt;
        delete page;
        delete crypto;
    }
    
    void List()
    {
		refreshBooks();
    }
    
    void Generate()
    {	
		if(!dlgBook.IsOpen())
			dlgBook.Open(this);
    }
    
    void Burn()
    {
		if(!dlgBurn.IsOpen())
			dlgBurn.Open(this);
    }
    
    void Clear()
    {
        text.Clear();
    }
    
    void Open()
    {
        FileSel	fs;
        fs.Type("Text file(s)", "*.txt *.*");
        fs.ExecuteOpen();

		FileStream file;
        file.Open(fs.Get(),600);
        text.Load(file);
        file.Close();
    }

	void Save()
    {
        FileSel	fs;
        fs.Type("Text file(s)", "*.txt");
        fs.ExecuteSaveAs();
        
        FileStream file;
        file.Open(fs.Get(),600);
        text.Save(file);
        file.Close();
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
        bar.Add("Clear", THISBACK(Clear)).Image(icons::clear).Key(K_CTRL_K);
        bar.Separator();
        bar.Add("Open", THISBACK(Open)).Image(icons::open).Key(K_CTRL_O);
		bar.Add("Save", THISBACK(Save)).Image(icons::save).Key(K_CTRL_S);
		bar.Separator();
        bar.Add("Exit", THISBACK(Exit)).Image(icons::exit).Key(K_CTRL_Q);
    }
    
    void cryptoMenu(Bar& bar)
    {
        bar.Add("Crypt",   THISBACK(Crypt)).Image(icons::crypt).Key(K_CTRL_E);
        bar.Add("Decrypt", THISBACK(Decrypt)).Image(icons::decrypt).Key(K_CTRL_D);
    }
    
    void booksMenu(Bar& bar)
    {
        bar.Add("Refresh  books",THISBACK(List)).Image(icons::refresh).Key(K_CTRL_R);
        bar.Add("Generate book", THISBACK(Generate)).Image(icons::generate).Key(K_CTRL_G);
        bar.Add("Burn page",     THISBACK(Burn)).Image(icons::burn).Key(K_CTRL_B);
    }
    
    void helpMenu(Bar& bar)
    {
        bar.Add("Help",  THISBACK(Help)).Image(icons::help).Key(K_F1);
        bar.Separator();
        bar.Add("About", THISBACK(About)).Image(icons::about);
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
        	<< lbBook.LeftPos( 10, 60).TopPos(10, 25)
        	<< book.LeftPos(   65, 60).TopPos(10, 25)
        	<< lbFrom.LeftPos(135, 60).TopPos(10, 25)
        	<< from.LeftPos(  185, 60).TopPos(10, 25)
        	<< lbPage.LeftPos(255, 60).TopPos(10, 25)
        	<< pagen.LeftPos( 305, 60).TopPos(10, 25)
        	<< format.LeftPos(400,195).TopPos(10, 25)
            << text.LeftPos(    0,600).TopPos(50, 300)
        ;
        
        lbFrom.SetText("FROM:");
        lbBook.SetText("BOOK:");
        lbPage.SetText("PAGE:");
        format.SetLabel("Formatted msg");
        
        format <<= THISBACK(FormatOpt);

		dlgBook.Icon(icons::generate);
		dlgBook.Title("Generate book");
		dlgBurn.Icon(icons::burn);
		dlgBurn.Title("Burn page");
		dlgAbout.Icon(icons::main_icon_16);
		dlgAbout.Title("About");
		refreshBooks();
    }
};

GUI_APP_MAIN
{
	otpWindow app;
	app.Icon(icons::main_icon_32,icons::main_icon_48);
	app.SetRect(0, 0, 600, 350);
    app.Run();
}