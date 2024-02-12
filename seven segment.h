/*
 * seven_segment.h
 *
 * Created: 10/20/2018 10:31:18 PM
 *  Author: Dell
 */ 

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_
void seven_seg_vinit(unsigned char port_name);
void seven_seg_write(unsigned char portname,unsigned char number);
#endif /* SEVEN SEGMENT_H_ */