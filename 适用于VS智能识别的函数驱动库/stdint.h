/*****************************************************************************/
/* STDINT.H                                                                  */
/* ¾«¼òÌáÈ¡°æ                                                                 */
/* Copyright (c) 2002 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
#ifndef _STDINT_H_
#define _STDINT_H_

typedef   signed char    int8_t;
typedef unsigned char   uint8_t;
typedef          int    int16_t;
typedef unsigned int   uint16_t;
typedef          long   int32_t;
typedef unsigned long  uint32_t;
typedef          long long  int64_t;
typedef unsigned long long uint64_t;

typedef  int8_t   int_least8_t;
typedef uint8_t  uint_least8_t;
typedef  int16_t  int_least16_t;
typedef uint16_t uint_least16_t;
typedef  int32_t  int_least32_t;
typedef uint32_t uint_least32_t;
typedef  int64_t  int_least64_t;
typedef uint64_t uint_least64_t;

typedef  int16_t  int_fast8_t;
typedef uint16_t uint_fast8_t;
typedef  int16_t  int_fast16_t;
typedef uint16_t uint_fast16_t;
typedef  int32_t  int_fast32_t;
typedef uint32_t uint_fast32_t;
typedef  int64_t  int_fast64_t;
typedef uint64_t uint_fast64_t;

typedef          long intptr_t;
typedef unsigned long uintptr_t;
typedef          long long intmax_t;
typedef unsigned long long uintmax_t;

#endif /* _STDINT_H_ */
