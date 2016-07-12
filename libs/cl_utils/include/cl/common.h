#pragma once

#include <CL/cl.h>

#include <string>
#include <iostream>


#define VERBOSE

#ifdef VERBOSE
    #define verbose_cout std::cout
    #define verbose_cerr std::cerr
#else
    #define verbose_cout if (false) std::cout
    #define verbose_cerr if (false) std::cerr
#endif

namespace cl {

    std::string getErrorString(cl_int errorCode);

    static bool failure(std::string filename, int line, cl_int returnCode) {
        if (returnCode != CL_SUCCESS) {
            verbose_cerr << "Failure at " << filename << ":" << line << "!\n"
                         << " Error " << returnCode << ": " << getErrorString(returnCode) << std::endl;
            return true;
        } else {
            return false;
        }
    }

    #define OK(call) (!failure(__FILE__, __LINE__, call))
    #define CHECKED(call) if (!OK(call)) throw "Fatal failure!";

    class Version {
    public:

        const int           majorVersion;
        const int           minorVersion;
        const std::string   info;


        Version(const int majorVersion, const int minorVersion, const std::string &info="") :
                majorVersion(majorVersion), minorVersion(minorVersion), info(info) { }

        bool operator<(Version other) const;
    };

    Version parseOCLVersion(std::string version);

}