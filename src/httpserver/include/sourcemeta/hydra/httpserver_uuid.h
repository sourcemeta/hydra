#ifndef SOURCEMETA_HYDRA_HTTPSERVER_UUID_H
#define SOURCEMETA_HYDRA_HTTPSERVER_UUID_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTPSERVER_EXPORT
#else
#include "httpserver_export.h"
#endif

#include <string> // std::string

// This entire module is considered to be private and should not be directly
// used by consumers of this project
#if !defined(DOXYGEN)

namespace sourcemeta::hydra::http {

auto SOURCEMETA_HYDRA_HTTPSERVER_EXPORT uuid() -> std::string;

}

#endif

#endif
