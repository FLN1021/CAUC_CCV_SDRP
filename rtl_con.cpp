//
// Created by fln1021 on 23-9-30.
//

#include "rtl_con.h"

int verbose_ppm_set(rtlsdr_dev_t *dev, int ppm_error)
{
    int r;
    if (ppm_error == 0) {
        return 0;}
    r = rtlsdr_set_freq_correction(dev, ppm_error);
    if (r < 0) {
        fprintf(stderr, "WARNING: Failed to set ppm error.\n");
    } else {
        fprintf(stderr, "Tuner error set to %i ppm.\n", ppm_error);
    }
    return r;
}

int verbose_set_frequency(rtlsdr_dev_t *dev, uint64_t frequency)
{
    int r;
    r = rtlsdr_set_center_freq64(dev, frequency);
    if (r < 0) {
        fprintf(stderr, "WARNING: Failed to set center freq.\n");
    } else {
        fprintf(stderr, "Tuned to %f MHz.\n", (double)frequency * 1E-6);
    }
    return r;
}

int verbose_set_sample_rate(rtlsdr_dev_t *dev, uint32_t samp_rate)
{
    int r;
    r = rtlsdr_set_sample_rate(dev, samp_rate);
    if (r < 0) {
        fprintf(stderr, "WARNING: Failed to set sample rate.\n");
    } else {
        fprintf(stderr, "Sampling at %u S/s.\n", samp_rate);
    }
    return r;
}

int nearest_gain(rtlsdr_dev_t *dev, int target_gain)
{
    int i, r, err1, err2, count, nearest;
    int* gains;
    r = rtlsdr_set_tuner_gain_mode(dev, 1);
    if (r < 0) {
        fprintf(stderr, "WARNING: Failed to enable manual gain.\n");
        return r;
    }
    count = rtlsdr_get_tuner_gains(dev, nullptr);
    if (count <= 0) {
        return 0;
    }
//    gains = malloc(sizeof(int) * count);
    gains = new int[count];
    count = rtlsdr_get_tuner_gains(dev, gains);
    nearest = gains[0];
    for (i=0; i<count; i++) {
        err1 = abs(target_gain - nearest);
        err2 = abs(target_gain - gains[i]);
        if (err2 < err1) {
            nearest = gains[i];
        }
    }
    // free(gains);
    delete [] gains;
    return nearest;
}

int verbose_auto_gain(rtlsdr_dev_t *dev)
{
    int r;
    r = rtlsdr_set_tuner_gain_mode(dev, 0);
    if (r != 0) {
        fprintf(stderr, "WARNING: Failed to set tuner gain.\n");
    } else {
        fprintf(stderr, "Tuner gain set to automatic.\n");
    }
    return r;
}

int verbose_gain_set(rtlsdr_dev_t *dev, int gain)
{
    int r;
    r = rtlsdr_set_tuner_gain_mode(dev, 1);
    if (r < 0) {
        fprintf(stderr, "WARNING: Failed to enable manual gain.\n");
        return r;
    }
    r = rtlsdr_set_tuner_gain(dev, gain);
    if (r != 0) {
        fprintf(stderr, "WARNING: Failed to set tuner gain.\n");
    } else {
        fprintf(stderr, "Tuner gain set to %0.2f dB.\n", gain/10.0);
    }
    return r;
}

int verbose_reset_buffer(rtlsdr_dev_t *dev)
{
    int r;
    r = rtlsdr_reset_buffer(dev);
    if (r < 0) {
        fprintf(stderr, "WARNING: Failed to reset buffers.\n");}
    return r;
}

int verbose_device_search(char *s)
{
    int i, device_count, device, offset, rc;
    char *s2;
    char vendor[256] = {0}, product[256] = {0}, serial[256] = {0};
    device_count = rtlsdr_get_device_count();
    if (!device_count) {
        fprintf(stderr, "No supported devices found.\n");
        return -1;
    }
    fprintf(stderr, "Found %d device(s):\n", device_count);
    for (i = 0; i < device_count; i++) {
        memset(&vendor[0],  0, 256 * sizeof(char));
        memset(&product[0], 0, 256 * sizeof(char));
        memset(&serial[0],  0, 256 * sizeof(char));
        rc = rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        if ( rc == 0 )
            fprintf(stderr, "  %d:  %s, %s, SN: %s\n", i, vendor, product, serial);
        else
            fprintf(stderr, "  %d:  %s\n", i, "Failed to query data");
    }
    fprintf(stderr, "\n");
    /* does string look like raw id number */
    device = (int)strtol(s, &s2, 0);
    if (s2[0] == '\0' && device >= 0 && device < device_count) {
        fprintf(stderr, "Using device %d: %s\n",
                device, rtlsdr_get_device_name((uint32_t)device));
        return device;
    }
    /* does string exact match a serial */
    for (i = 0; i < device_count; i++) {
        memset(&vendor[0],  0, 256 * sizeof(char));
        memset(&product[0], 0, 256 * sizeof(char));
        memset(&serial[0],  0, 256 * sizeof(char));
        rc = rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        if (rc)
            continue;
        if (strcmp(s, serial) != 0) {
            continue;}
        device = i;
        fprintf(stderr, "Using device %d: %s\n",
                device, rtlsdr_get_device_name((uint32_t)device));
        return device;
    }
    /* does string prefix match a serial */
    for (i = 0; i < device_count; i++) {
        memset(&vendor[0],  0, 256 * sizeof(char));
        memset(&product[0], 0, 256 * sizeof(char));
        memset(&serial[0],  0, 256 * sizeof(char));
        rc = rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        if (rc)
            continue;
        if (strncmp(s, serial, strlen(s)) != 0) {
            continue;}
        device = i;
        fprintf(stderr, "Using device %d: %s\n",
                device, rtlsdr_get_device_name((uint32_t)device));
        return device;
    }
    /* does string suffix match a serial */
    for (i = 0; i < device_count; i++) {
        memset(&vendor[0],  0, 256 * sizeof(char));
        memset(&product[0], 0, 256 * sizeof(char));
        memset(&serial[0],  0, 256 * sizeof(char));
        rc = rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        if (rc)
            continue;
        offset = strlen(serial) - strlen(s);
        if (offset < 0) {
            continue;}
        if (strncmp(s, serial+offset, strlen(s)) != 0) {
            continue;}
        device = i;
        fprintf(stderr, "Using device %d: %s\n",
                device, rtlsdr_get_device_name((uint32_t)device));
        return device;
    }
    fprintf(stderr, "No matching devices found.\n");
    return -1;
}

