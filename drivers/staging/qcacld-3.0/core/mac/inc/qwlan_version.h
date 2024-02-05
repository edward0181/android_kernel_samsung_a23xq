/*
 * Copyright (c) 2012-2018 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef QWLAN_VERSION_H
#define QWLAN_VERSION_H
/*===========================================================================

   FILE:
   qwlan_version.h

   BRIEF DESCRIPTION:
   WLAN Host Version file.
   Build number automatically updated by build scripts.

   ===========================================================================*/

#define QWLAN_VERSION_MAJOR            2
#define QWLAN_VERSION_MINOR            0
#define QWLAN_VERSION_PATCH            8
#if defined(CONFIG_LITHIUM)
#if defined(QCA_WIFI_QCA6390) //Hastings
#define QWLAN_VERSION_EXTRA            "X-HS220407A"
#elif defined(QCA_WIFI_QCA6490) // Hastings Prime
#define QWLAN_VERSION_EXTRA            "X-HP220407A"
#else
#define QWLAN_VERSION_EXTRA            "X-QCOM"
#endif
#else
#define QWLAN_VERSION_EXTRA            "X-HL220407A"
#endif
#define QWLAN_VERSION_BUILD            25

#if defined(CONFIG_LITHIUM)
#if defined(QCA_WIFI_QCA6390) //Hastings
#define QWLAN_VERSIONSTR               "2.0.8.25X-HS220407A"
#elif defined(QCA_WIFI_QCA6490) // Hastings Prime
#define QWLAN_VERSIONSTR               "2.0.8.25X-HP220407A"
#else
#define QWLAN_VERSIONSTR               "2.0.8.25X-QCOM"
#endif
#else
#define QWLAN_VERSIONSTR               "2.0.8.25X-HL220407A"
#endif

#endif /* QWLAN_VERSION_H */
