/******************************************************************************
 * Copyright (C) 2016 Marco Giammarini
 *
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/**
 * @file sht21s/sht21s.h
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief SHT21S .
 */

#ifndef __WARCOMEB_SHT21S_H
#define __WARCOMEB_SHT21S_H

#define WARCOMEB_SHT21S_LIBRARY_VERSION     "0.1"
#define WARCOMEB_SHT21S_LIBRARY_VERSION_M   0
#define WARCOMEB_SHT21S_LIBRARY_VERSION_m   1
#define WARCOMEB_SHT21S_LIBRARY_TIME        0

#include "libohiboard.h"

#include "cli/cli.h"

typedef enum {
    SHT21S_MEASURETYPE_TEMPERATURE,
    SHT21S_MEASURETYPE_HUMIDITY
} SHT21S_MeasureType;

/**
 *
 */
typedef struct _SHT21S_Device
{
    Gpio_Pins choicePin;

    Adc_Pins adcPin;
    Adc_ChannelNumber adcChannel;
    Adc_DeviceHandle adcDevice;
    uint16_t adcResolution;

} SHT21S_Device;

void SHT21S_init (SHT21S_Device* dev);

float SHT21S_measure (SHT21S_Device* dev, SHT21S_MeasureType type);

void SHT21S_cliParser(SHT21S_Device* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE]);

#endif /* __WARCOMEB_SHT21S_H */
