%module otpnitro
%{
    #include "page.h"
    #include "text.h"
    #include "crypto.h"
    #include "config.h"
%}

/* C++ String to Python string */
%typemap(out) std::string {
    $result = PyString_FromString($1.c_str());
}

%typemap(out) string {
    $result = PyString_FromString($1.c_str());
}

/* Parse the header file to generate wrappers */
%include "page.h"
%include "rand.h"
%include "text.h"
%include "crypto.h"
%include "config.h"

