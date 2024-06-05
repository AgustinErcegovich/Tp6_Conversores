#include "MKL25Z.h"
#include "CONVERSORES.h"

void DAC_Init() {
    SIM -> SCGC6 |= SIM_SCGC6_DAC0_MASK;
    DAC0 -> C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

void DAC_Convertion(int valor) {
    DAC0 -> DAT[0].DATH = DAC_DATH_DATA1(valor >> 8);
    DAC0 -> DAT[0].DATH = DAC_DATL_DATA0(valor & 0xFF);
}

void ADC_Init() {
    SIM -> SCGS6 |= SIM_SCGC6_ADC0_MASK;
    ADC0 -> ADC_CFG1_MODE(3) | ADC_CFG1_ADCICLK(1) | ADC_CFG1_ADIV(0);
    ADC0 -> SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
    while (ADC0 -> SC3 & ADC_SC3_CAL_MASK);
}

float ADC_Convertion(int channel) {
    ADC0 -> SC1[0] = ADC_SC1_ADCH(channel);
    while (!(ADC0 -> SC1[0] & ADC_SC1_COCO_MASK));
    int valor = ADC0 -> R[0];
    float convertion = 3.3*valor/65535.0;
    return convertion;
}