# OTP Nitro

## About

*OTP Nitro* is a secure [One Time Pad][OneTimePad] implementation to use on computers or as assistant on manual operations.


## CLI Usage

* Generate OTP pages on the "TST" book:

	```
	C:\> .\otpnitro.exe -g -r TST
	OTP Nitro 0.1
	[I] Generating OTP: TST. OK
	```
	
* Encrypt message:

	```
	C:\> otpnitro.exe -e -s CPX -r TST -m "ESTO ES UNA PRUEBA"
	OTP Nitro 0.1
	[I] Encrypted msg:
	TST DE CPX 11 = RHJQG AKZQV RUMKV IYHJY YQYVT =
	```
	
* Decrypt message:

	```
	C:\> otpnitro.exe -d -p 11 -s CPX -r TST -m "RHJQG AKZQV RUMKV IYHJY YQYVT"
	OTP Nitro 0.1
	[I] Decrypted msg:
	TST DE CPX 11 = ESTO ES UNA PRUEBA =
	```
	
* Decrypt formated message:

	```
	C:\> otpnitro.exe -d -f "TST DE CPX 11 = RHJQG AKZQV RUMKV IYHJY YQYVT ="
	OTP Nitro 0.1
	[I] Decrypted msg:
	TST DE CPX 11 = ESTO ES UNA PRUEBA =
	```
	
* Burn a page:

	```
	C:\> otpnitro.exe -b -p 11 -r TST
	OTP Nitro 0.1
	[I] Burn page 11. OK
	```

## GUI Usage

1. **Introduction**
	*OTP Nitro* is a secure One Time Pad implementation to use on computers or as assistant on manual operation.

2. **Concepts**
	In this chapter we describe the basic concepts to use in this app.
	
	a. **Books**
	The cipher data is stored on books, every book have "pages" where the data is generated. The books usually have very short names, from 3 to 5 characters.
	
	b. **Pages**
		The pages store the cipher to crypt and decrypt, every page is unique and after use it you must burn the used page.

	c. **From field**
		The recipient is anyone who have the same book than you used to crypt the message and you must identify yourself as sender in the from field. The IDs usually have very short names, from 3 to 5 characters.

	d. **Formatted message**
		To have a send/receive standar format, please use this one:
		
            <BOOK> DE <FROM> <PAGE> = <MESSAGE> =
	**Example**:
		
		    TST DE CPX 2 = QSZBO IGFIY NVTVY BFXCB KROAP =

3. **Operations**
	In this chapter we describe the basic operations.

	a. **Generate a book**
		The first operation is generate a book, to do this, please use the menu: Books -> Generate Book or press CTRL + G keys.

	b. **Crypt**
		To crypt a message you must provide a valid book in the selector, an arbitrary ID in the form field and a message unformated to crypt. The page will be selected automatically. Later you must use the menu: Crypto -> Crypt or press CTRL + E keys.

	c. **Decrypt**
		To decrypt a message you can provide a formatted message, in this case you only must select the "Formatted msg" option. If you dont have the format, you can enter all fields manually. Later you must use the menu: Crypto -> Decrypt or press CTRL + D keys.

	d. **Burn page**
		It is recommended to burn the page after use, but if you want to do this manually  (or later) you can use the menu: Crypto -> Burn page or press CTRL + B keys.

	e. **Refresh books**
		If you modify or delete any book in the filesystem you must refresh the books in the app. To do that you can use the menu: Crypto -> Refresh books or press CTRL + R keys.

4. **Internals**
	In this chapter we describe internal operations, know bugs or missing features.

	a. **Settings**
		The settings/config file must be located on %APPDATA%/.otpnitro/otpnitro.ini or $HOME/.otpnitro/otpnitro.ini

	b. **Book storing**
		By default the books are stored on %APPDATA%/.otpnitro/PAGES or $HOME/.otpnitro/PAGES (this can be changed in the config file)

	c. **Max pages parameter**
		Is the number of pages generated for book. (this value limits the number of messages to be crypted on a book)

	d. **Max chars parameter**
		Is the number of characters generated for page. (this value limits the number of text to be crypted)

	e. **Project URL**
		For more information, updates, etc. you can visit the project homepage_.

5. **License**
	This program is under the GPLv3 license.

6. **Authors**
	* [@capi_x][@capi_x] *capi_x.AT.haibane.org*

7. **Acknowledges**
	* [@Mario_vilas][@Mario_vilas] - Thanks for GUI and crypto testing.
	* [@sha0coder][@sha0coder] - Thanks for CLI and GUI testing.
	* [@AloneInTheShell][@AloneInTheShell] - Thanks for CLI and LIB testing.


## CLI compile guide

1) **Generic**:

    	make

2) **Debian**:

    	make debian

2) **FreeBSD**:

    	CXX=clang++ gmake freebsd

3) **Haiku**::

    	make haiku

4) **OS/2**:

    	make os2

5) **Windows**:

    	make windows
	
6) **DOS**:

    	make dos


## GUI compile guide 

1) **Generic**:

	    cd qotpnitro && qmake && make

2) **Debian**:

	    make debian-gui

2) **FreeBSD**:

	    CXX=clang++ gmake freebsd-gui

3) **Haiku**:

	    make haiku-gui

4) **OS/2**:

        make os2-gui

5) **Windows**:

        make windows-gui


## Bindings

*OTP Nitro* supports bindings to other languages using [SWIG][SWIG]

1. **Python**

	a. **Compile**:

		make bindings

	b. **Generic Compile**:

		make python-otpnitro
	
	c. **Debian Install**:

		make debian-python

	d. **FreeBSD Install**:

		make freebsd-python

	e. **PIP Install**:
	
		pip install otpnitro

	f. **Usage**
		Once installed:

			>> import otpnitro
			>> page = otpnitro.Page()
			>> print page.list() 


## API

The API documentation is located here:

* [HTML](http://www.haibane.org/doc/otpnitro/index.html)
* [PDF](http://www.haibane.org/doc/otpnitro.pdf)

## Features

* Generate pages and books
* Encrypt messages
* Decrypt messages
* Burn pages (secure delete)
* Automatic text format (header)
* GUI using [Qt][Qt]
* API and library
* Bindings


## TODO

* Automatic file parse daemon
* Print pages


## License

*OTP Nitro* is released under the [GPLv3][GPLv3] license.



[OneTimePad]: https://en.wikipedia.org/wiki/One-time_pad
[@capi_x]: https://twitter.com/capi_x
[@Mario_vilas]: https://twitter.com/mario_vilas
[@sha0coder]: https://twitter.com/sha0coder
[@AloneInTheShell]: https://twitter.com/AloneInTheShell
[MinGW]: http://sourceforge.net/projects/mingw/files/
[Qt]: https://www.qt.io/
[UppEnviroment]: http://www.ultimatepp.org/www$uppweb$download$en-us.html
[homepage]: https://code.haibane.org/crypto/otpnitro
[GPLv3]: http://www.gnu.org/licenses/gpl-3.0.txt
[SWIG]: http://www.swig.org/

