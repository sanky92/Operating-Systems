// NOTE- MYDU ONLI WORKS WHEN NO SYMLINKS ARE PRESENT.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>   //stat
#include <sys/types.h>  //getpwid
#include <pwd.h>                //getpwid
#include <grp.h>                //getgrgid
#include <unistd.h>
#include <time.h>
char *fullpath;                 // contains full path
char *sympath;                  // contains symblink path
char *backpath;                 // back up path
int symflag = 0, cflag = 0;

void mode_conv(long int,char * );
void print_ls();
void print_data(struct dirent *dire);
void symlink_check(struct dirent *dire, int );
char type_find(long int );
void time_conv(time_t t, char *time);

int main(int argc, char *argv[])
{
         char *pathname;
         if(argc<2)
        {
            pathname=".";
        }
        else
        {
            pathname = argv[1];
        }
        if (pathname == '\0')
                printf("ERROR NULL PATH\n");

        int len = strlen(pathname);
        fullpath = malloc(1024 * sizeof(char));
        sympath = malloc(1024 * sizeof(char));
        backpath = malloc(1024 * sizeof(char));
        strncpy(fullpath, pathname ,len);
        print_ls();
        return 0;
}

void print_ls()
{
        struct stat statbuf;
        struct dirent *dirp;   //For readdir()
        DIR *dp;
        char *ptr, *sptr;

        if (lstat(fullpath, &statbuf) < 0) /* stat error */
        {
                printf("ERROR FILE WE CAN NOT STAT\n");
        }
        if (S_ISDIR(statbuf.st_mode) == 0) /* not a directory */
        {
        }
        else
        {
             if (symflag == 0)
                {
                        //printf("             %s\n", fullpath);
                        }
                else
                {
                        cflag++;
                        //printf("              %s\n", sympath);
                        int splen;
                        splen = strlen(sympath);
                        sptr = sympath + splen;                         // point to end of fullpath
                        *sptr++ = '/';
                        *sptr = 0;
                }
                int fplen;
                fplen = strlen(fullpath);
                ptr = fullpath + fplen;                         // point to end of fullpath
                *ptr++ = '/';
                *ptr = 0;
                int total=0;
               int blksize=0;
               if((dp=opendir(fullpath))==NULL)
                    printf("Error Cannot read directory: %s\n",fullpath);
                else
                 {   char *try=fullpath;
                     while((dirp = readdir(dp)) != NULL)
                        {
                             if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                                     continue;
                        	strcpy(ptr, dirp->d_name);
                             if (stat(fullpath, &statbuf) < 0) //use stat to deal with symlinks
                             {
                                printf("ERROR FILE/DIR WE CAN NOT STAT\n");
                             }
                             else
                             {
                                 blksize+=statbuf.st_blocks;
                             }}
                      total=blksize/2;
                      if(symflag == 0)
                      {
                         printf("%d           %s\n",total+4,try);
                      }
                     else
                     {
                          printf("%d           %s\n",total+4,try);
                     }
                      
                 }
                 if(closedir(dp) < 0)
                  printf("Cannot close Directory");
                 ptr=fullpath+fplen+1;
                 *(ptr)=0;



                /*if ((dp = opendir(fullpath)) == NULL)           //can't read dir
                        printf("ERROR CAN NOT READ DIRECTORY: %s\n", fullpath);
                else {
                          while ((dirp = readdir(dp)) != NULL)
                        {
                                if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                                        continue;                       // ignore dot and dot-dot
                                strcpy(ptr, dirp->d_name);              // append name after slash to get fullpath
                                print_data(dirp);                               // print all content of file

                        }//WHILE ENDS
                }
                if(closedir(dp) < 0)            //CLOSE DIR
                        printf("CAN NOT CLOSE THE DIRECTORY:%s\n", fullpath);
                ptr = fullpath + fplen +1;      //REDO the fullpath change
                *(ptr) =0;*/
                if ((dp = opendir(fullpath)) == NULL)           //can't read dir
                        printf("ERROR CAN NOT READ DIRECTORY: %s\n", fullpath);
                else
                {
                        //printf("\n");
                         while ((dirp = readdir(dp)) != NULL)
                        {
                                if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                                        continue;                       // ignore dot and dot-dot

                                strcpy(ptr, dirp->d_name); // append name after slash
                                if (symflag == 1) strcpy(sptr, dirp->d_name);
                                symlink_check(dirp, fplen);     //check symlink

                                print_ls();                     //RECURSIVE CALL
                                if (symflag == 0)
                                {
                                        ptr = fullpath + fplen +1;      //REDO the fullpath change
                                        *(ptr) =0;
                                }
                                else {
                                        ptr = fullpath + fplen +1;      //REDO the fullpath change
                                        *(ptr) =0;
                                        if (cflag !=0)
                                                cflag--;
                                        else
                                                strncpy(fullpath, backpath, strlen(backpath));
                                }

                        }//WHILE ENDS
                        symflag = 0;     //DISABLE FLAG

                        if(closedir(dp) < 0)            //CLOSE DIR
                                printf("CAN NOT CLOSE THE DIRECTORY:%s\n", fullpath);
                }//ELSE ENDS
                free(dirp);

        }//IF END
}//FUNCTION END
/*void print_data(struct dirent *dire)
{
        char mode[11];
        int nlink;
        char *usrname;
        char *grpname;
        int size;
        char *time;
        char *name;

        struct stat statbuft;
        struct passwd *passtrt;
        struct group *grp;
        struct tm lt;
         name = dire->d_name;
        if (stat(fullpath, &statbuft) < 0) //use stat to deal with symlinks
        {
                printf("ERROR FILE/DIR WE CAN NOT STAT\n");
        }
        else
        {
                mode_conv(statbuft.st_mode, mode);
                nlink = statbuft.st_nlink;
                size = statbuft.st_size;

                passtrt = getpwuid(statbuft.st_uid);
                usrname = passtrt->pw_name;

                grp = getgrgid(statbuft.st_gid);
                grpname = grp->gr_name;

                time = malloc(100* sizeof(char));
                time_conv(statbuft.st_mtime, time);

                printf("%s %d %s %s %d %s %s\n",mode, nlink, usrname, grpname, size, time, name);
                free(time);
                fflush(stdout);
        }

} */

void symlink_check(struct dirent *dire, int fplen)
{
        struct stat statbuf;
        char *ptr;
        char *cont;

        if (lstat(fullpath, &statbuf) < 0) //for symlink
        {        //continue;
                //printf("ERROR FILE WE CAN NOT STAT\n");
        }
        if (S_ISLNK(statbuf.st_mode) != 0) // SYMLINK
        {
             if (stat(fullpath, &statbuf) < 0)
                {        //continue
                        //printf("ERROR FILE/DIR WE CAN NOT STAT\n");
                }
                else
                {
                    symflag=1;
                    strncpy(sympath, fullpath ,strlen(fullpath));
                                strncpy(backpath, fullpath, fplen+1);
                                ptr = fullpath;
                                if (readlink(fullpath, cont, 1024) == -1);
                                       // printf("ERROR READING CONTENT OF SYMLINK\n");
                                else
                                        strncpy(ptr, cont, strlen(cont)-2);

                             /*   printf("FULLPATH: %s\n",fullpath);
                                printf("BACKPATH: %s\n",backpath);
                                printf("SYMPATH: %s\n",sympath);*/
                        }
                }
        }

