
#ifndef ARX_PLATFORM_PLATFORMCONFIG_H
#define ARX_PLATFORM_PLATFORMCONFIG_H

/*!
 * Low-level configuration.
 * Please only add config flags that change rarely (such as compiler features)
 * in order to not break incremental builds. Particularly, availability of
 * libraries and their features belongs in src/Configure.h.in
 */

// Support for __attribute__((format(printf, i, j)))
#define ARX_HAVE_ATTRIBUTE_FORMAT_PRINTF 0

// Support for __builtin_trap()
#define ARX_HAVE_BUILTIN_TRAP 0

#endif // ARX_PLATFORM_PLATFORMCONFIG_H
