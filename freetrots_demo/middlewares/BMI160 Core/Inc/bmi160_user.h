/*
 * bmi160_wrapper.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Ibrahim Ozdemir
 *      GitHub: ibrahimcahit
 */

#ifndef __BMI160_USER_H__
#define __BMI160_USER_H__

#include "bmi160.h"
#include "bmi160_defs.h"

#define TRUE 1
#define FALSE 0
#define PRINTIF_DEBUG 0

typedef struct {
    float BMI160_Ax_f32, BMI160_Ay_f32, BMI160_Az_f32;
    float BMI160_Gx_f32, BMI160_Gy_f32, BMI160_Gz_f32;

    int8_t INIT_OK_i8;
} BMI160_t;

int8_t bmi160ReadAccelGyro(BMI160_t *DataStruct);
void bmi160_thread_init(void);
int8_t sensor_spi_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t sensor_spi_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len);
#endif /* BMI160_WRAPPER_H_ */
