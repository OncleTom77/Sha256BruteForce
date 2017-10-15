//
//  avxImpl.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 08/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef avxImpl_hpp
#define avxImpl_hpp

#include <stdio.h>

/* sha256-x86.c - Intel SHA extensions using C intrinsics  */
/*   Written and place in public domain by Jeffrey Walton  */
/*   Based on code from Intel, and by Sean Gulley for      */
/*   the miTLS project.                                    */

/* Include the GCC super header */
#if defined(__GNUC__)
# include <stdint.h>
# include <x86intrin.h>
#endif

/* Microsoft supports Intel SHA ACLE extensions as of Visual Studio 2015 */
#if defined(_MSC_VER)
# include <immintrin.h>
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
typedef UINT32 uint32_t;
typedef UINT8 uint8_t;
#endif

void sha256_process_x86(uint32_t state[8], const uint8_t data[], uint32_t length);

#endif /* avxImpl_hpp */
