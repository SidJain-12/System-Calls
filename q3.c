#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

typedef long long ll;

ll max(ll a, ll b)
{
    return a > b ? a : b;
}

ll min(ll a, ll b)
{
    return a < b ? a : b;
}


void print_file_details(char *str, char *filename, ll permission, ll index)
{
    write(1, str, strlen(str));
    if (index == 1)
    {
        write(1, "newfile", strlen("newfile"));
    }
    else if (index == 2)
    {
        write(1, "oldfile", strlen("oldfile"));
    }
    else
    {
        write(1, "directory", strlen("directory"));
    }
    write(1, permission ? ": Yes\n" : ": No\n", 6);
}

void write_perm(char *filename, ll index)
{
    ll fd = open(filename, O_RDONLY);
    struct stat st;
    if (stat(filename, &st) < 0)
        st.st_mode = 0;

    print_file_details("User has read permission on ", filename, st.st_mode & S_IRUSR, index);
    print_file_details("User has write permission on ", filename, st.st_mode & S_IWUSR, index);
    print_file_details("User has execute permission on ", filename, st.st_mode & S_IXUSR, index);
    print_file_details("Group has read permission on ", filename, st.st_mode & S_IRGRP, index);
    print_file_details("Group has write permission on ", filename, st.st_mode & S_IWGRP, index);
    print_file_details("Group has execute permission on ", filename, st.st_mode & S_IXGRP, index);
    print_file_details("Other has read permission on ", filename, st.st_mode & S_IROTH, index);
    print_file_details("Other has write permission on ", filename, st.st_mode & S_IWOTH, index);
    print_file_details("Other has execute permission on ", filename, st.st_mode & S_IXOTH, index);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        perror("Invalid Input");
        exit(1);
    }

    // Check if the directory exists

    struct stat de;
    if (stat(argv[3], &de) == -1)
    {
        write(1, "Directory is created: No\n", strlen("Directory is created: No\n"));
    }
    else if (S_ISDIR(de.st_mode))
    {
        write(1, "Directory is created: Yes\n", strlen("Directory is created: Yes\n"));
    }
    else
    {
        write(1, "Directory is created: No\n", strlen("Directory is created: No\n"));
    }

    // check if file is reversed

    ll ans = 1;

    ll fd = open(argv[1], O_RDONLY);
    ll fd2 = open(argv[2], O_RDONLY);

    off_t fileLength = lseek(fd, 0, SEEK_END);

    ll read_bytes = max(1000, fileLength / 5);

    lseek(fd, fileLength - min(read_bytes, fileLength), SEEK_SET);
    lseek(fd2, 0, SEEK_SET);

    char *buf = (char *)calloc(read_bytes, sizeof(char));
    char *buf2 = (char *)calloc(read_bytes, sizeof(char));

    while (1)
    {
        ll n = read(fd, buf, min(read_bytes, fileLength));
        ll m = read(fd2, buf2, min(read_bytes, fileLength));

        if (n < 0 || m < 0){
            perror("File descriptor error\n");
            exit(1);
        }
            

        // reverse the string from last to first
        ll i = 0;
        while (i < n && i < m)
        {
            if (buf[i] == buf2[m - i - 1])
            {
                i++;
            }
            else
            {
                ans = 0;
                break;
            }
        }

        if (lseek(fd, 0, SEEK_CUR) - 2 * read_bytes < 0)
            break;

        lseek(fd, -read_bytes * 2, SEEK_CUR);
    }

    if (lseek(fd, -read_bytes, SEEK_CUR) > 0)
    {
        read_bytes = lseek(fd, 0, SEEK_CUR);
        lseek(fd, 0, SEEK_SET);

        char *buf = (char *)calloc(read_bytes, sizeof(char));
        char *buf2 = (char *)calloc(read_bytes, sizeof(char));

        ll n = read(fd, buf, read_bytes);
        ll m = read(fd2, buf2, read_bytes);

        if (n < 0 || m < 0){
            perror("File descriptor error\n");
            exit(1);
        }
            
        // reverse the string from last to first
        ll i = 0;

        while (i < n && i < m)
        {
            if (buf[i] == buf2[m - i - 1])
            {
                i++;
            
            }
            else
            {
                ans = 0;
                break;
            }
        }
    }

    write(1, "Whether file contents are reversed in newfile: ", strlen("Whether file contents are reversed in newfile: "));
    write(1, ans == 1 ? "Yes\n" : "No\n", 4);

    // check for new file, oldfile, directory

    write_perm(argv[1], 1);
    write_perm(argv[2], 2);
    write_perm(argv[3], 3);

    return 0;
}