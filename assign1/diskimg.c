#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "diskimg.h"

int diskimg_open(char *pathname, int readOnly) {
  return open(pathname, readOnly ? O_RDONLY : O_RDWR);
}

int diskimg_getsize(int fd) {
  return lseek(fd, 0, SEEK_END);
}

int diskimg_readsector(int fd, int sectorNum,  void *buf) { // read a diskimg_sector_size data
  if (lseek(fd, sectorNum * DISKIMG_SECTOR_SIZE, SEEK_SET) == (off_t) -1) return -1;  //lseek : fd, offset, where(head here) 重新定位文件读写的位移
  return read(fd, buf, DISKIMG_SECTOR_SIZE); // success: number ; fail : -1
}

int diskimg_writesector(int fd, int sectorNum,  void *buf) {
  if (lseek(fd, sectorNum * DISKIMG_SECTOR_SIZE, SEEK_SET) == (off_t) -1) {
    return -1;
  }

  return write(fd, buf, DISKIMG_SECTOR_SIZE);
}

int diskimg_close(int fd) {
  return close(fd);
}
