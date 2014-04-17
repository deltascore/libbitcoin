/* libsodium: utils.c, v0.4.5 2014/04/16 */
/*
 * Copyright (c) 2013-2014
 * Frank Denis <j at pureftpd dot org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <bitcoin/utility/external/zeroize.h>

#include <stdint.h>
#include <stdlib.h>

// TODO: deal with determination of HAVE_SECUREZEROMEMORY and HAVE_MEMSET_S
void zeroize(void* const buffer, const size_t length)
{
#ifdef HAVE_SECUREZEROMEMORY
    SecureZeroMemory(buffer, length);
#elif defined(HAVE_MEMSET_S)
    if (memset_s(buffer, (rsize_t)length, 0, (rsize_t)length) != 0) 
    {
        abort();
    }
#else
    size_t i;
    volatile uint8_t* vbuffer = (volatile uint8_t*)buffer;

    for (i = 0; i < length; i++)
    {
        vbuffer[i] = 0U;
    }
#endif
}