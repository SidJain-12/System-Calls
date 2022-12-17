#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef long long ll;
void progress_bar(ll written, ll total)
{
    char array[4];
    array[0] = '\b';
    array[3] = '\r';

    array[1] = ((written * 100) / total) / 10 + '0';
    array[2] = ((written * 100) / total) % 10 + '0';
    write(1," Progress: ",strlen(" Progress: "));
    write(1, array, 4);
}

ll max(ll a, ll b)
{
    return a > b ? a : b;
}

ll min(ll a, ll b)
{
    return a < b ? a : b;
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        perror("Invalid Inputs given\n");
        // printf("%d more input required\n",2-argc);
        exit(1);
    }
    ll fd = open(argv[1], O_RDONLY);
    mkdir("Assignment", 0700);
    char str[100] = "Assignment/1_";

    char *filename = strrchr(argv[1], '/');
    if (!filename)
    {
        filename = argv[1];
    }
    else
    {
        filename++;
    }

    ll fd2 = open(strcat(str, filename), O_CREAT | O_WRONLY | O_TRUNC, 0644);
    off_t fileLength = lseek(fd, 0, SEEK_END);

    if (fd < 0 || fd2 < 0 || fileLength <= 0)
    {
        perror("File descriptor error\n");
        exit(1);
    } // open error

    ll read_bytes = min(max(1000, fileLength / 5),1000*1000*200);

    lseek(fd, fileLength - min(read_bytes, fileLength), SEEK_SET);
    lseek(fd2, 0, SEEK_SET);

    char *buf = (char *)calloc(read_bytes, sizeof(char));
    ll byte_written = 0;

    while (1)
    {
        ll n = read(fd, buf, min(read_bytes, fileLength));
        if (n <= 0)
        {
            perror("Read bytes are less than 0");
            exit(1);
        }

        // reverse the string from last to first
        ll i = 0;
        ll j = n - 1;
        while (i < j)
        {
            char temp = buf[i];
            buf[i] = buf[j];
            buf[j] = temp;
            i++;
            j--;
        }

        // write reverse string to file
        write(fd2, buf, n);


        if (lseek(fd, 0, SEEK_CUR) - 2 * read_bytes < 0)
            break;

        lseek(fd2, 0, SEEK_CUR);
        lseek(fd, -read_bytes * 2, SEEK_CUR);

        byte_written += n;
        progress_bar(byte_written, fileLength);
    }

    if (lseek(fd, -read_bytes, SEEK_CUR) > 0)
    {
        read_bytes = lseek(fd, 0, SEEK_CUR);
        lseek(fd, 0, SEEK_SET);

        char *buf = (char *)calloc(read_bytes, sizeof(char));

        ll n = read(fd, buf, read_bytes);
        if (n <= 0)
        {
            perror("Read bytes are less than equal to 0");
            exit(1);
        }
        // reverse the string from last to first
        ll i = 0;
        ll j = strlen(buf) - 1;

        while (i < j)
        {
            char temp = buf[i];
            buf[i] = buf[j];
            buf[j] = temp;
            i++;
            j--;
        }

        byte_written += n;
        progress_bar(byte_written, fileLength);

        // write reverse string to file
        write(fd2, buf, n);
    }

    close(fd);
    close(fd2);

    return 0;
}