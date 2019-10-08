/*
 * signal_handler.c
 *
 *  Created on: Mar 4, 2017
 *      Author: yxie
 */
#include "mydash.h"

pid_t BPTable[1024];

void sig_handler(int sig)
{
	pid_t pid;
	int i;
	for (i = 0; i< 1024; i++){
		if(BPTable[i] != 0){
			pid = waitpid(BPTable[i], NULL, WNOHANG);
			if(pid > 0){
				mydash_job_report(pid, background_job_list);
			}
		}
	}
	return;

}
