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
 * @file sht21s/sht21s.c
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief SHT21S .
 */

#include "sht21s.h"
#include "timer.h" /* For delay */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHT21S_MAX_ADC    4096

void SHT21S_init (SHT21S_Device* dev)
{
    Gpio_config(dev->choicePin,GPIO_PINS_OUTPUT);

    Adc_enablePin(dev->adcDevice,dev->adcPin);
    /* Other for ADC? */
}

float SHT21S_measure (SHT21S_Device* dev, SHT21S_MeasureType type)
{
    uint32_t i = 0;
    uint16_t value = 0;
    float valuef = 0.0;

    if (type == SHT21S_MEASURETYPE_TEMPERATURE)
    {
        Gpio_clear(dev->choicePin);
        Timer_delay(500);
        Adc_readValue(dev->adcDevice,dev->adcChannel,&value,ADC_INPUTTYPE_SINGLE_ENDED);
        valuef = -46.85 + (175.72/SHT21S_MAX_ADC * (float)value);
    }
    else
    {
        Gpio_set(dev->choicePin);
        Timer_delay(500);
        Adc_readValue(dev->adcDevice,dev->adcChannel,&value,ADC_INPUTTYPE_SINGLE_ENDED);
        valuef = -6 + (125.0/SHT21S_MAX_ADC * (float)value);
    }

    return valuef;
}

/**************************** CLI Section *************************************/

static void SHT21S_cliHelp()
{
    Cli_sendHelpString("help","Print help information");
    Cli_sendHelpString("status","Print status information");
    Cli_sendHelpString("temperature","Measure and print temperature value");
    Cli_sendHelpString("humidity","Measure and print humidity value");
}

void SHT21S_cliParser(SHT21S_Device* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE])
{
    char message[7];
    float value = 0.0;

    if ((argc == 1) || ((argc == 2) && (strcmp(argv[1],"help") == 0)))
        SHT21S_cliHelp();

    if ((argc == 2) && (strcmp(argv[1],"temperature") == 0))
    {
        value = SHT21S_measure(dev,SHT21S_MEASURETYPE_TEMPERATURE);
        ftstr(value,message,2);
        Cli_sendStatusString("Temperature",message,"C");
    }
    else if ((argc == 2) && (strcmp(argv[1],"humidity") == 0))
    {
        value = SHT21S_measure(dev,SHT21S_MEASURETYPE_HUMIDITY);
        ftstr(value,message,2);
        Cli_sendStatusString("Humidity",message,"%H");
    }
    else if ((argc == 2) && (strcmp(argv[1],"status") == 0))
    {
//        Led_toggle(dev);
    }
}
