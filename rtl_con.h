//
// Created by fln1021 on 23-9-30.
//

#ifndef CAUC_CCV_SDRP_RTL_CON_H
#define CAUC_CCV_SDRP_RTL_CON_H

#include <cstring>
#include <rtl-sdr.h>
#include <cstdio>
#include <cstdlib>

/*!
 * Find nearest supported gain
 *
 * \param dev the device handle given by rtlsdr_open()
 * \param target_gain in tenths of a dB
 * \return 0 on success
 */

int nearest_gain(rtlsdr_dev_t *dev, int target_gain);

/*!
 * Enable auto gain and report status on stderr
 *
 * \param dev the device handle given by rtlsdr_open()
 * \return 0 on success
 */

int verbose_auto_gain(rtlsdr_dev_t *dev);

/*!
 * Set tuner gain and report status on stderr
 *
 * \param dev the device handle given by rtlsdr_open()
 * \param gain in tenths of a dB
 * \return 0 on success
 */

int verbose_gain_set(rtlsdr_dev_t *dev, int gain);

/*!
 * Set device frequency and report status on stderr
 *
 * \param dev the device handle given by rtlsdr_open()
 * \param frequency in Hz
 * \return 0 on success
 */

int verbose_set_frequency(rtlsdr_dev_t *dev, uint64_t frequency);

/*!
 * Set device sample rate and report status on stderr
 *
 * \param dev the device handle given by rtlsdr_open()
 * \param samp_rate in samples/second
 * \return 0 on success
 */

int verbose_set_sample_rate(rtlsdr_dev_t *dev, uint32_t samp_rate);

/*!
 * Reset buffer
 *
 * \param dev the device handle given by rtlsdr_open()
 * \return 0 on success
 */

int verbose_reset_buffer(rtlsdr_dev_t *dev);

/*!
 * Set the frequency correction value for the device and report status on stderr.
 *
 * \param dev the device handle given by rtlsdr_open()
 * \param ppm_error correction value in parts per million (ppm)
 * \return 0 on success
 */

int verbose_ppm_set(rtlsdr_dev_t *dev, int ppm_error);

int verbose_device_search(char *s);

#endif //CAUC_CCV_SDRP_RTL_CON_H
