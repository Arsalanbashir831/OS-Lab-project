#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

// returns the present working directory
const char *pwd(char *buffer)
{
    return getcwd(buffer, 1024);
}

// list with only directories
void listOfOnlyDirectories(char *path)
{

    DIR *directory;
    struct dirent *entry;
    struct stat st;
    directory = opendir(pwd(path));
    if (directory == NULL)
    {
        printf("Error opening directory.\n");
    }
    while ((entry = readdir(directory)) != NULL)
    {
        if (stat(entry->d_name, &st) < 0)
        {
            perror("stat");
            continue;
        }
        if (S_ISDIR(st.st_mode))
        {
            printf("%s\n", entry->d_name);
        }
    }

    // close the directory... if closedir() fails it will return -1
    if (closedir(directory) == -1)
    {
        // exit with an error message and status if closedir() fails
        printf("Error closing directory.\n");
    }
}

// list with specific path directories

void listWithSpecificPath(char *path)
{

    DIR *directory;
    struct dirent *entry;
    directory = opendir(path);
    if (directory == NULL)
    {
        printf("Error opening directory.\n");
    }
    while ((entry = readdir(directory)) != NULL)
    {

        printf("%s\n", entry->d_name);
    }

    // close the directory... if closedir() fails it will return -1
    if (closedir(directory) == -1)
    {
        // exit with an error message and status if closedir() fails
        printf("Error closing directory.\n");
    }
}

// implementation of the ls commands
void ls(char *path)
{
    DIR *directory;
    struct dirent *entry;
    directory = opendir(pwd(path));
    if (directory == NULL)
    {
        printf("Error opening directory.\n");
    }
    while ((entry = readdir(directory)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    if (closedir(directory) == -1)
    {
        printf("Error closing directory.\n");
    }
}
// implement change directory
const char *cd(char *newPath)
{
    if (chdir(newPath) == -1)
    {
        printf("directory doesnt exist \n");
    }
    return chdir(newPath);
}
// implement the mkdir
void makeDirectory(char *newDirectory)
{
    int retval = _mkdir(newDirectory);
    if (retval == -1)
    {
        // report to the user that an error has occurred
        printf("Make directory failed.\n");
        if (errno == EEXIST)
            printf("Directory already exists.\n");
        else if (errno == ENOENT)
            printf("Path not found.\n");
    }
    else
        printf("Make directory succeeded.\n");
}
// implement the remove directory
void removeDirectory(char *directory)
{
    int retval;
    retval = _rmdir("test");
    if (retval == -1)
    {
        // output a general error message
        printf("Remove directory failed.\n");
        if (errno == ENOENT)
            printf("Path not found.\n");
        else if (errno == ENOTEMPTY)
            printf("Directory not empty.\n");
        else if (errno == EACCES)
            printf("An open handle to the directory exists.\n");
    }
    else
        printf("Remove directory succeeded.\n");
}
// touch cmd implementation
void touch(char *filename)
{
    FILE *fptr;
    fptr = fopen(filename, "w+");
    fclose(fptr);
}
// implement the cat
void cat(char *filename)
{
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (!fptr)
    {
        printf("ERROR");
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        printf("%c", ch);
    }
    fclose(fptr);
}
void grep(){

     FILE *fp;
            char word[50];
            char ch;
            char filename[100];
            char search[100];
            printf("grep ");
            gets(filename);
            gets(search);
            int count = 0;
            int pos[10];
            int pointer = 0;
            int loop;
            fp = fopen(filename, "r");

            do
            {
                ch = fscanf(fp, "%s", word);
                if (strcmp(word, search) == 0)
                {
                    pos[count] = pointer;
                    count++;
                }
                pointer++;
            } while (ch != EOF);

            if (count == 0)
                printf("'%s' not found in %s\n", search, filename);
            else
            {
                printf("Count is %d ", count);
            }
            fclose(fp);
}

int main(int argc, char const *argv[])
{
    printf("Welcome to the Arsalan Shell : \n ");
    printf("\n The cmds implemented are :\n");
    printf("\n 1-ls \n 2- ls -p(list the file/direct of specific path) \n 3- ls -d(list only directories) \n 4-rm \n 5-mkdir \n 6-cd \n 7- touch \n 8- cat \n 9- grep -c \n");
    char input[100];
    while (strcmp(input, "exit") != 0)
    {
        printf("%s : ", pwd(input));
        gets(input);
        if (strcmp(input, "ls") == 0)
        {
            ls(input);
        }
        if (strcmp(input, "ls -p") == 0)
        {
            char path[100];
            gets(path);
            listWithSpecificPath(path);
        }
        if (strcmp(input, "ls -d") == 0)
        {
            listOfOnlyDirectories(pwd(input));
        }
        if (strcmp(input, "cd") == 0)
        {
            printf("cd  ");
            char newPath[100];
            gets(newPath);
            cd(newPath);
        }
        if (strcmp(input, "mkdir") == 0)
        {
            printf("mkdir ");
            char newDirectory[100];
            gets(newDirectory);
            makeDirectory(newDirectory);
        }
        if (strcmp(input, "rm") == 0)
        {
            printf("rm ");
            char rmDirectory[100];
            gets(rmDirectory);
            removeDirectory(rmDirectory);
        }
        if (strcmp(input, "touch") == 0)
        {
            char newFile[100];
            printf("touch  ");
            gets(newFile);
            touch(newFile);
        }
        if (strcmp(input, "cat") == 0)
        {
            char newFile[100];
            printf("cat  ");
            gets(newFile);
            cat(newFile);
        }
        // implementation of grep
        if (strcmp(input, "grep -c") == 0)
        {
           grep();
        }

        printf("\n");
        printf("==============Exit from the shell =========\n");
    }
    return 0;
}
