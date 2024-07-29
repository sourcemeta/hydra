#ifndef SOURCEMETA_HYDRA_CRYPTO_H
#define SOURCEMETA_HYDRA_CRYPTO_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_CRYPTO_EXPORT
#else
#include "crypto_export.h"
#endif

#include <string> // std::string

/// @defgroup crypto Crypto
/// @brief This module offers a collection of cryptographic utilities for use in
/// the other modules.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/hydra/crypto.h>
/// ```

namespace sourcemeta::hydra {

/// @ingroup crypto
/// Generate a random UUID v4 string. For example:
///
/// ```cpp
/// #include <sourcemeta/hydra/crypto.h>
/// #include <iostream>
///
/// std::cout << sourcemeta::hydra::uuid() << "\n";
/// ```
auto SOURCEMETA_HYDRA_CRYPTO_EXPORT uuid() -> std::string;

} // namespace sourcemeta::hydra

#endif
