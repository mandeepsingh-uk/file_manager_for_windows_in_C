#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<stdbool.h>
#include "engine.h"

int list_files(const char *path)
{
    DIR *directory;
    struct dirent *entry;
    struct stat filestatus;
    directory= opendir(path);
    char full_path[1024];

    if(directory==NULL)
    {
        printf("wrong paath has been entred");
        closedir(directory);
        return 1;
    }
    
    while((entry=readdir(directory))!=0)
    {
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
        {
            continue;
        }

        snprintf(full_path,sizeof(full_path),"%s/%s",path,entry->d_name);

        if(stat(full_path,&filestatus)==0)
        {
            if(S_ISDIR(filestatus.st_mode))
            {
                printf("FOLDER: %s ,size: %lld \n",entry->d_name,(full_size(full_path)/((long long)1024)));
            }
            else
            {
                printf("FILE: %s ,size:%lld \n",entry->d_name,((long long)filestatus.st_size)/((long long)1024));
            }
        }
    }
    closedir(directory);
    return 0;
}
long long full_size(const char *path){
    DIR *directory;
    struct dirent *entry;
    struct stat filestatus;
    char full_path[1024];
    directory=opendir(path);
    int total_length=0;

    while((entry=readdir(directory))!=0)
    {
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
        {
            continue;
        }
        snprintf(full_path,sizeof(full_path),"%s/%s",path,entry->d_name);
        if(stat(full_path,&filestatus)==0)
        {
            if(S_ISDIR(filestatus.st_mode))
            {
                total_length+=full_size(full_path);
            }
            else
            {
                total_length+=filestatus.st_size;
            }
        }
    }
    closedir(directory);
    return total_length;
}
