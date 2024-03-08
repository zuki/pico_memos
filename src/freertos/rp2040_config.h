/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: MIT AND BSD-3-Clause
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 */

#ifndef RP2040_CONFIG_H
#define RP2040_CONFIG_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 は、ユーザがコアごとに異なるベクタ
 * テーブルオフセットを設定した場合にそれを必要とするコアに例外ハンドラを動的に
 * 設定することを意味する
 */
#ifndef configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #if defined( PICO_NO_RAM_VECTOR_TABLE ) && ( PICO_NO_RAM_VECTOR_TABLE == 1 )
        #define configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #else
        #define configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #endif
#endif

/* configSUPPORT_PICO_SYNC_INTEROP == 1 は、SDK pico_syncのsem/mutex/queue
 * などがFreeRTOSのタスクから呼び出された場合に正しく動くことを意味する。
 */
#ifndef configSUPPORT_PICO_SYNC_INTEROP
    #if LIB_PICO_SYNC
        #define configSUPPORT_PICO_SYNC_INTEROP    1
    #endif
#endif

/* configSUPPORT_PICO_SYNC_INTEROP == 1 は、SDK pico_timeのsleep_ms/
 * sleep_us/sleep_untilがFreeRTOSのタスクから呼び出された場合に正しく動き、
 * 実際にFreeRTOSレベルでブロックすることを意味する。
 */
#ifndef configSUPPORT_PICO_TIME_INTEROP
    #if LIB_PICO_TIME
        #define configSUPPORT_PICO_TIME_INTEROP    1
    #endif
#endif

#if ( configNUMBER_OF_CORES > 1 )

/* configTICK_CORE はどちらのコアがSystick割り込みを処理するかを示す
 */
    #ifndef configTICK_CORE
        #define configTICK_CORE    0
    #endif
#endif

/* このSMPポートには2つのスピンロックが必要であり、これはSDKからの
 * 要請である。使用されるスピンロック番号は静的に定義される。ここでは
 * SDKによりRTOS用に確保されている値をデフォルトで設定している。 */
#ifndef configSMP_SPINLOCK_0
    #define configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#endif

#ifndef configSMP_SPINLOCK_1
    #define configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* ifndef RP2040_CONFIG_H */
