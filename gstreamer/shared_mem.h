#ifndef SHAREDMEM_H
#define SHAREDMEM_H


#include <sys/ipc.h>
#include <sys/shm.h>


# define PROJECT_ID 100 // use whatever you used in sender process
# define SHM_ID_DEFAULT -1 // default value of shm id

char * sharedMemInit(const char * filename, size_t memSizeBytes, int* shmIdOut) {
    // generate unique key
    key_t key = ftok(filename,PROJECT_ID);
  
    // init shared memory
    int shmid = shmget(key,memSizeBytes,0666); // we hardcode permissions
    *shmIdOut = shmid;

    // shmat to attach to shared memory
    char *pStart = (char*) shmat(shmid,(void*)0,0);

    return pStart;  
}

// TODO: We may not need it 
// void sharedMemoryRead(char * dest, char * src, size_t size) {

// 	memcpy(dest, src, size); 
// }


void sharedMemDetach(char * pStart) {
    shmdt(pStart);
}


#endif /* SHAREDMEM_H */
