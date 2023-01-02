/* 
 * File:   millis.h
 * Author: pc
 *
 * Created on 2022년 6월 16일 (목), 오후 2:23
 */

#ifndef MILLIS_H
#define	MILLIS_H

#include "common.h"

void init_millis();
millis_t millis();
millis_t get_millis(millis_t now, millis_t prev_now);

#endif	/* MILLIS_H */

