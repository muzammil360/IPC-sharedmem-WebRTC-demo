#ifndef SHAREDMEM_H
#define SHAREDMEM_H


#include <sys/ipc.h>
#include <sys/shm.h>


# define PROJECT_ID 100 // use differently in another project 
# define SHM_ID_DEFAULT -1 // default value of shm id

char * sharedMemInit(const char * filename, size_t memSizeBytes, int* shmIdOut) {
    // generate unique key
    key_t key = ftok(filename,PROJECT_ID);
  
    // init shared memory
    int shmid = shmget(key,memSizeBytes,0666|IPC_CREAT); // we hardcode permissions
  	*shmIdOut = shmid;

    // shmat to attach to shared memory
    char *pStart = (char*) shmat(shmid,(void*)0,0);

    return pStart;	
}

void sharedMemoryWrite(void * dest, void * src, size_t size) {

	memcpy(dest, src, size); 
}

void sharedMemDetach(char * pStart) {
	   shmdt(pStart);
}

void sharedMemFree(int shmid) {

    shmctl(shmid,IPC_RMID,NULL);
}

void sharedMemCleanup(char * pStart, int shmid) {
	sharedMemDetach(pStart);
    sharedMemFree(shmid);
}



#endif /* SHAREDMEM_H */
