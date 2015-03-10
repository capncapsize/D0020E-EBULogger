/*
 * analyser.h
 *
 *  Created on: Jan 26, 2015
 *      Author: machine
 */

#ifndef ANALYSER_H_
#define ANALYSER_H_


struct datagram{
	int byte_count;
	char databuff;
	struct datagram next;
};


#endif /* ANALYSER_H_ */
