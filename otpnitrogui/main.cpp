/**
 * OTPNitro
 *
 *  Copyright 2014 by capi_x <capi_x@haibane.org>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0 <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

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
#include "../config.h"
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
    		GetOwner()->Update();
    		Close();
    	}
	}
	
	void DoClose() {
    	Close();
	}

	typedef bookGenDialog CLASSNAME;

	bookGenDialog() {
    	SetRect(0, 0, 200, 100);
    	
    	Add(txtBookGen.SetLabel("Enter Book name (ID):").LeftPos(          10,180).TopPos(10, 25));
    	Add(bookId.LeftPos(                                                10,180).TopPos(30, 25));
    	Add(btnCancel.SetImage(icons::cancel).SetLabel( "Cancel").LeftPos( 10, 80).TopPos(65, 25));
    	Add(btnGen.SetImage(icons::generate).SetLabel("Generate").LeftPos(110, 80).TopPos(65, 25));
    	
    	btnGen    <<= THISBACK(DoGen);
    	btnCancel <<= THISBACK(DoClose);;
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
    	SetRect(0, 0, 190, 100);
    	
    	Add(txtBookGen.SetLabel("Enter Book and page num:").LeftPos(     10,150).TopPos(10, 25));
    	Add(book.LeftPos(                                                10, 80).TopPos(30, 25));
    	Add(pagen.LeftPos(                                              100, 80).TopPos(30, 25));
    	Add(btnCancel.SetImage(icons::cancel).SetLabel( "Close").LeftPos(10, 80).TopPos(65, 25));
    	Add(btnGen.SetImage(icons::burn).SetLabel(      "Burn").LeftPos(100, 80).TopPos(65, 25));
    	
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

		text.SetData("_____[6 OTP[5/ NITRO]]__v0.4&&Is a secure One Time Pad implementation to use on computers or as assistant on manual operations.&&This project is licensed under the [^http://www.gnu.org/licenses/gpl-3.0.html^ GPLv3] license. More information in the [^https://code.haibane.org/crypto/otpnitro^ project page].&&2013-2014 (c) [^mailto:capi_x@haibane.org^ capi_x@haibane.org]");
    }
};

struct encodeDialog : public TopWindow {
	
	Button	btnEncode, btnDecode, btnOpenE, btnClearE, btnSaveE, btnBinaryE, btnOpenD, btnClearD, btnSaveD, btnBinaryD;
	Label	lbEncode,  lbDecode;
	DocEdit	encode,    decode;

	void DoEncode() {
		Text * txt = new Text;
		
		string msgEnc = txt->encodeB26((unsigned char *)decode.Get().Begin(),(long)decode.Get().GetCount());
        encode.Set(msgEnc);
        
        delete txt;
	}
	
	void DoDecode() {
		Text * txt = new Text;
		
		int decLen = encode.Get().GetCount() / 2;
		unsigned char * msgDec = new unsigned char[decLen];
		
		txt->decodeB26( msgDec, encode.Get().ToString() );
		string msgDecStr((char *)msgDec, decLen);
		decode.Set(msgDecStr);

        delete txt;
        delete[] msgDec;
	}

	void DoClose() {
    	Close();
	}
	
	void DoOpenE() {
		FileSel	fs;
        fs.Type("File(s)", "*.txt *.*");
        
        if (!fs.ExecuteOpen())
            return;

		FileStream file;
        file.Open(fs.Get(),600);
        encode.Load(file);
        file.Close();
	}
	
	void DoSaveE() {
		FileSel	fs;
        fs.Type("Text file(s)", "*.txt *.*");
        
        if (!fs.ExecuteSaveAs())
            return;
        
        FileStream file;
        file.Open(fs.Get(),600);
        encode.Save(file);
        file.Close();
	}
	
	void DoClearE() {
		encode.Clear();
	}
	
	void DoBinaryE() {
		FileSel	fs;
        fs.Type("File(s)", "*.*");
        
        if (!fs.ExecuteOpen())
            return;

		FileStream file;
        file.Open(fs.Get(),600);
        
        Text * txt = new Text;
		
		int decLen = file.GetSize();
		unsigned char * msgDec = new unsigned char[decLen];
		file.GetAll(msgDec, decLen);
		
		string msgEnc = txt->encodeB26( msgDec, decLen );

		FileSel	fsOut;
		fsOut.Type("Text file(s)", "*.txt *.*");
		
		if (!fsOut.ExecuteSaveAs())
			return;
		
		FileStream fileOut;
		fileOut.Open(fsOut.Get(),600);
		fileOut.Put(msgEnc);
		
		fileOut.Close();
        delete txt;
        delete[] msgDec;
        file.Close();
	}
	
	void DoOpenD() {
		FileSel	fs;
        fs.Type("Text file(s)", "*.txt *.*");
        
        if (!fs.ExecuteOpen())
            return;

		FileStream file;
        file.Open(fs.Get(),600);
        decode.Load(file);
        file.Close();
	}
	
	void DoSaveD() {
		FileSel	fs;
        fs.Type("File(s)", "*.*");
        
        if (!fs.ExecuteSaveAs())
            return;
        
        FileStream file;
        file.Open(fs.Get(),600);
        decode.Save(file);
        file.Close();
	}
	
	void DoBinaryD() {
		FileSel	fs;
        fs.Type("Text file(s)", "*.txt *.*");
        if (!fs.ExecuteOpen())
            return;

		FileStream file;
        file.Open(fs.Get(),600);
        
        Text * txt = new Text;
		
		int decLen  = file.GetSize() / 2;
		int origLen = file.GetSize();
		unsigned char * msgDec  = new unsigned char[decLen];
		char * msgOrig = new char[origLen];
		file.GetAll(msgOrig, origLen);

		txt->decodeB26( msgDec, msgOrig );
		string msgDecStr((char *)msgDec, decLen);
		
		FileSel	fsOut;
		fsOut.Type("File(s)", "*.*");
		
		if (!fsOut.ExecuteSaveAs())
			return;
		
		FileStream fileOut;
		fileOut.Open(fsOut.Get(),600);
		fileOut.Put(msgDecStr);
		
		fileOut.Close();
        delete txt;
        delete[] msgDec;
        file.Close();
	}
	
	void DoClearD() {
		decode.Clear();
	}

	typedef encodeDialog CLASSNAME;

	encodeDialog() {
    	SetRect(0, 0, 800, 400);
    	
    	Add(btnEncode.SetImage(icons::crypt).SetLabel("Encode").LeftPos(   20,380).TopPos(340,40));
    	Add(btnDecode.SetImage(icons::decrypt).SetLabel("Decode").LeftPos(400,380).TopPos(340,40));
    	
    	Add(lbDecode.SetLabel("Decoded data:").LeftPos( 40,380).TopPos(20,20));
    	Add(lbEncode.SetLabel("Encoded data:").LeftPos(420,380).TopPos(20,20));
    	
    	Add(btnBinaryE.SetImage(icons::encod).LeftPos( 320,20).TopPos( 20,20));
    	Add(btnOpenD.SetImage(icons::open).LeftPos(    340,20).TopPos( 20,20));
    	Add(btnSaveD.SetImage(icons::save).LeftPos(    360,20).TopPos( 20,20));
    	Add(btnClearD.SetImage(icons::clear).LeftPos(  380,20).TopPos( 20,20));
    	
    	Add(btnBinaryD.SetImage(icons::decod).LeftPos( 700,20).TopPos( 20,20));
    	Add(btnOpenE.SetImage(icons::open).LeftPos(    720,20).TopPos( 20,20));
    	Add(btnSaveE.SetImage(icons::save).LeftPos(    740,20).TopPos( 20,20));
    	Add(btnClearE.SetImage(icons::clear).LeftPos(  760,20).TopPos( 20,20));
    	
    	Add(decode.LeftPos( 20,380).TopPos(40,280));
    	Add(encode.LeftPos(400,380).TopPos(40,280));

		btnBinaryD <<= THISBACK(DoBinaryD);
		btnBinaryE <<= THISBACK(DoBinaryE);
    	btnEncode  <<= THISBACK(DoEncode);
    	btnDecode  <<= THISBACK(DoDecode);
    	btnOpenE   <<= THISBACK(DoOpenE);
    	btnClearE  <<= THISBACK(DoClearE);
    	btnSaveE   <<= THISBACK(DoSaveE);
    	btnOpenD   <<= THISBACK(DoOpenD);
    	btnClearD  <<= THISBACK(DoClearD);
    	btnSaveD   <<= THISBACK(DoSaveD);
	}
};

struct settingsDialog : public TopWindow {
	
	Button		btnSave, btnCancel, btnFile;
	Label		lbPath,  lbPages,  lbChars;
	EditString	esPath;
	EditIntSpin	esPages, esChars;

	void DoSave() {
		Config * cfg = new Config;
		
		std::string path = esPath.GetText().ToString();
    	cfg->setPath((char *)path.c_str());
    	cfg->setPages(esPages.GetData());
    	cfg->setChars(esChars.GetData());
    	
    	cfg->saveConfig();

		delete cfg;
		
		PromptOK("Settings updated");
		GetOwner()->Update();
		
		Close();
	}
	
	void DoFile() {
		FileSel	fs;
        fs.Type("Pages storage folder", "");
        if (fs.ExecuteSelectDir()) {	        
	        string seldir = fs.Get();
	        seldir.append("/");
			esPath.SetText(seldir);
        }
	}
	
	void DoCancel() {
    	Close();
	}

	typedef settingsDialog CLASSNAME;

	settingsDialog() {
    	SetRect(0, 0, 320, 270);
    	
    	Add(lbPath.SetLabel("Books path").LeftPos(         20,280).TopPos( 15,40));
    	Add(lbPages.SetLabel("Max pages per book").LeftPos(20,280).TopPos( 75,40));
    	Add(lbChars.SetLabel("Max chars per page").LeftPos(20,280).TopPos(135,40));
    	
    	Add(esPath.LeftPos( 20,250).TopPos( 50,20));
    	Add(esPages.LeftPos(20,280).TopPos(110,20));
    	Add(esChars.LeftPos(20,280).TopPos(170,20));
    	
    	Add(btnFile.SetImage(icons::open).LeftPos(                        280,20).TopPos( 50,20));
    	Add(btnSave.SetImage(icons::save).SetLabel("Save").LeftPos(        70,80).TopPos(220,25));
		Add(btnCancel.SetImage(icons::cancel).SetLabel("Cancel").LeftPos( 170,80).TopPos(220,25));
    	
    	btnFile   <<= THISBACK(DoFile);
    	btnSave   <<= THISBACK(DoSave);
    	btnCancel <<= THISBACK(DoCancel);
	}
};

struct otpWindow : TopWindow {
	
	MenuBar			menu;
	Label			lbBook;
	DropList		book;
	Label			lbFrom;  	
    EditString		from;
    Label			lbPage;
    EditIntSpin		pagen;
    Option			format;
    DocEdit			text;
    
    bookGenDialog	dlgBook;
    aboutDialog		dlgAbout;
    burnDialog		dlgBurn;
    encodeDialog	dlgEncode;
    settingsDialog	dlgSettings;
    
    virtual void Updated() {
        refreshBooks();
    }
    
    virtual void WhenDrop() {
        refreshBooks();
    }
    
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
        txt->replaceAll(txt->msg," ","");
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
    
    void Encode()
    {	
		if(!dlgEncode.IsOpen()) {
			
			dlgEncode.encode.Clear();
			dlgEncode.decode.Clear();
			
			dlgEncode.Open(this);
		}
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
    
    void Settings()
    {
        if(!dlgSettings.IsOpen()) {
            
            book.SetData("");
            
            Config * cfg = new Config;
    		dlgSettings.esPath.SetText(cfg->getPath());
    		dlgSettings.esPages.SetData(cfg->getPages());
    		dlgSettings.esChars.SetData(cfg->getChars());
    		delete cfg;
    		
			dlgSettings.Open(this);
			dlgSettings.btnCancel.SetFocus();
        }
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
        bar.Add("Clear",    THISBACK(Clear)).Image(icons::clear).Key(K_CTRL_K);
        bar.Separator();
        bar.Add("Open",     THISBACK(Open)).Image(icons::open).Key(K_CTRL_O);
		bar.Add("Save",     THISBACK(Save)).Image(icons::save).Key(K_CTRL_S);
		bar.Separator();
		bar.Add("Settings", THISBACK(Settings)).Image(icons::config).Key(K_CTRL_T);
		bar.Separator();
        bar.Add("Exit",     THISBACK(Exit)).Image(icons::exit).Key(K_CTRL_Q);
    }
    
    void cryptoMenu(Bar& bar)
    {
        bar.Add("Crypt",    THISBACK(Crypt)).Image(icons::crypt).Key(K_CTRL_E);
        bar.Add("Decrypt",  THISBACK(Decrypt)).Image(icons::decrypt).Key(K_CTRL_D);
        bar.Add("Encode",   THISBACK(Encode)).Image(icons::encode).Key(K_CTRL_N);
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
        book.WhenDrop = THISBACK(refreshBooks);

		dlgBook.Icon(icons::generate);
		dlgBook.Title("Generate book");
		dlgBurn.Icon(icons::burn);
		dlgBurn.Title("Burn page");
		dlgAbout.Icon(icons::main_icon_16);
		dlgAbout.Title("About");
		dlgEncode.Icon(icons::encode);
		dlgEncode.Title("Encode and Decode text");
		dlgSettings.Icon(icons::config);
		dlgSettings.Title("Settings");
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
