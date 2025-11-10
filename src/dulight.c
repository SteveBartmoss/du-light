#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

long getDirSize(const char *path) {
  DIR *dir;
  struct dirent *entry;
  struct stat info;
  long total_size = 0;
  char fullpath[1024;

  dir = opendir(path);

  if (!dir) return 0;

  while((entry = readdir(dir)) != NULL){
    if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,".."))
      continue;

    snprintf(fullpath, sizeof(fullpath), "%s%s", path, entry->d_name);

    if(stat(fullpath, &info) == 0){
      if(S_ISDIR(info.st_mode)){
        total_size += getDirSize(fullpath);
      } else {
        total_size += info.st_size;
      }
    }
    
  }

  closedir(dir);
  return total_size;
}

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("Uso: %s <directorio>\n", argv[0]);
    return 1;
  }

  long total = getDirSize(argv[1]);
  printf("Tamanio tota de %s: %.2f MB\n", argv[1], (double)total / (1024*1024));
  return 0;
  
}
