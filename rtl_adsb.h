//
// Created by fln1021 on 23-9-30.
// Migreated from rtl_adsb.c
//

#ifndef CAUC_CCV_SDRP_RTL_ADSB_H
#define CAUC_CCV_SDRP_RTL_ADSB_H

#include <rtl-sdr.h>
#include <pthread.h>
#include <libusb-1.0/libusb.h>
#include <cstdio>
#include <cstring>
#include <csignal>
#include "rtl_con.h"

#define ADSB_RATE			2000000
#define ADSB_FREQ			1090000000
#define DEFAULT_ASYNC_BUF_NUMBER	12
#define DEFAULT_BUF_LENGTH		(16 * 16384)
#define AUTO_GAIN			(-100)

#define MESSAGEGO    253
#define OVERWRITE    254
#define BADSAMPLE    255

#define preamble_len	16
#define long_frame		112
#define short_frame		56

/* signals are not threadsafe by default */
#define safe_cond_signal(n, m) pthread_mutex_lock(m); pthread_cond_signal(n); pthread_mutex_unlock(m)
#define safe_cond_wait(n, m) pthread_mutex_lock(m); pthread_cond_wait(n, m); pthread_mutex_unlock(m)

extern int adsb_dec();

#endif //CAUC_CCV_SDRP_RTL_ADSB_H
