#include "common.h"

#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

int main()
{
	// �����ڴ�Ľṹ��
	struct ShmEntry *entry;

	// 1. ���빲���ڴ�
	int shmid = shmget((key_t)1111, sizeof(struct ShmEntry), 0666 | IPC_CREAT);
	if (shmid == -1) {
		std::cout << "Create share memory error!" << std::endl;
		return -1;
	}

	// 2. ���ӵ���ǰ���̿ռ�/ʹ�ù����ڴ�
	entry = (ShmEntry*)shmat(shmid, 0, 0);
	entry->can_read = 0;
	while (true) {
		if (entry->can_read == 1) {
			std::cout << "Received message: " << entry->msg << std::endl;
			entry->can_read = 0;
		}
		else {
			std::cout << "Entry can not read. Sleep 1s." << std::endl;
			sleep(1);
		}
	}
	// 3. ������̿ռ�
	shmdt(entry);

	// 4. ɾ�������ڴ� 
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
