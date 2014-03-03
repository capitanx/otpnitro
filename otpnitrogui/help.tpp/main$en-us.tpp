topic "OTPNITRO Main help";
[ $$0,0#00000000000000000000000000000000:Default]
[{_} 
[s0;=b8; [*6 OTP][*/+184 NITRO]&]
[s0;b8; &]
[s0;b8; [*_+117 1. Introduction]&]
[s0;b8; [* OTP][*/2 NITRO] is a secure One Time Pad implementation to 
use on computers or as assistant on manual operation.&]
[s0;b8; &]
[s0;b8; &]
[s0;b8; [*_+117 2. Concepts]&]
[s0;b8; In this chapter we describe the basic concepts to use in 
this app.&]
[s0;b8; &]
[s0;b8; [* 2.1 Books]&]
[s0;b8; The cypher data is stored on books, every book have `"pages`" 
where the data is generated. The books usually have very short 
names, from 3 to 5 characters.&]
[s0;b8; &]
[s0;b8; [* 2.2 Pages]&]
[s0;b8; The pages store the cypher to crypt and decrypt, every page 
is unique and after use it you must burn the used page.&]
[s0;b8; &]
[s0;b8; [* 2.3 From field]&]
[s0;b8; The recipient is anyone who have the same book than you used 
to crypt the message and you must identify yourself as sender 
in the from field. The IDs usually have very short names, from 
3 to 5 characters.&]
[s0;b8; &]
[s0;b8; [* 2.4 Formatted message]&]
[s0;b8; To have a send/receive standar format, please use this one:&]
[s0;b8; &]
[s0;b8; -|[2 <BOOK> ][*2 DE][2  <FROM> <PAGE> ][*2 `=][2  <MESSAGE> ][*2 `=]&]
[s0;b8;* &]
[s0;i150;b8;O0; [* Example:]&]
[s0;b8;* &]
[s0;b8; -|[2 TST DE CPX 2 `= QSZBO IGFIY NVTVY BFXCB KROAP `=]&]
[s0;b8; &]
[s0;b8; &]
[s0;b8; [*_+117 3. Operations]&]
[s0;b8; In this chapter we describe the basic operations.&]
[s0;b8; &]
[s0;b8; [* 3.1 Generate a book]&]
[s0;b8; The first operation is generate a book, to do this, please 
use the menu: [/ Books `-> Generate Book] or press [/ CTRL `+ G ]keys.&]
[s0;b8; &]
[s0;b8; [* 3.2 Crypt]&]
[s0;b8; To crypt a message you must provide a valid book in the selector, 
an arbitrary ID in the form field and a message unformated to 
crypt. The page will be selected automatically.&]
[s0;b8; Later you must use the menu: [/ Crypto `-> Crypt] or press [/ CTRL 
`+ E] keys.&]
[s0;b8; &]
[s0;b8; [* 3.3 Decrypt]&]
[s0;b8; To decrypt a message you can provide a formatted message, 
in this case you only must select the `"Formatted msg`" option. 
If you dont have the format, you can enter all fields manually.&]
[s0;b8; Later you must use the menu: [/ Crypto `-> Decrypt] or press 
[/ CTRL `+ D] keys.&]
[s0;b8; &]
[s0;b8; [* 3.4 Burn page]&]
[s0;b8; It is recommended to burn the page after use, but if you 
want to do this manually  (or later) you can use the menu: [/ Crypto 
`-> Burn page] or press [/ CTRL `+ B] keys.&]
[s0;b8; &]
[s0;b8; [* 3.5 Refresh books]&]
[s0;b8; If you modify or delete any book in the filesystem you must 
refresh the books in the app. To do that you can use the menu: 
[/ Crypto `-> Refresh books] or press [/ CTRL `+ R] keys.&]
[s0;b8; &]
[s0;b8; &]
[s0;b8; [*_+117 4. Internals]&]
[s0;b8; In this chapter we describe internal operations, know bugs 
or missing features.&]
[s0;b8; &]
[s0;b8; [* 4.1 Book storing]&]
[s0;b8; At this moment the books will be stored in the execution 
path under the [/ `"PAGES`"] folder, in next updates we must provide 
an configuration file to specify a fixed path.&]
[s0;b8; &]
[s0;b8; [* 4.2 Project URL]&]
[s0;b8; For more information, updates, etc. you can visit the [^https`:`/`/code`.haibane`.org`/projects`/otpnitro^ p
roject homepage].&]
[s0;b8; &]
[s0;b8; &]
[s0;b8; [*_+117 5. License]&]
[s0;b8; This program is under the [^http`:`/`/www`.gnu`.org`/licenses`/gpl`-3`.0`.html^ G
PLv3] license.&]
[s0;b8; &]
[s0;b8; &]
[s0;b8; [*_+117 6. Authors]&]
[s0;b8; [^https`:`/`/twitter`.com`/capi`_x^ `@capi`_x] <capi`_x`@haibane.org>&]
[s0;b8; &]
[s0;b8; &]
[s0;b8; [*_+117 7. Acknowledges]&]
[s0;b8; [^https`:`/`/twitter`.com`/Mario`_vilas^ `@Mario`_vilas] `- 
Thanks for crypto and GUI testing.&]
[s0;b8; ]]