#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef long long ll;

ll max(ll a, ll b)
{
    return a > b ? a : b;
}

ll min(ll a, ll b)
{
    return a < b ? a : b;
}


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


int main(int argc, char **argv)
{
    if (argc != 4)
    {
        perror("Invalid number of Input");
        // printf("%d more input required\n",4-argc);
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

    ll start_char = atoi(argv[2]);
    ll end_char = atoi(argv[3]);
    ll len = end_char - start_char;

    if (fd < 0 || fd2 < 0 || fileLength <= 0 || start_char < 0 || end_char < 0 || start_char > end_char || end_char > fileLength)
    {
        perror("File/Input Error");
        exit(1);
    }

    ll read_bytes = min(max(1000, fileLength / 5),1000*1000*200);

    ll byte_written = 0;

    //******************************************************

    lseek(fd, start_char - min(read_bytes, start_char), SEEK_SET);
    lseek(fd2, 0, SEEK_SET);

    char *buf = (char *)calloc(read_bytes, sizeof(char));

    while (1)
    {
        ll n = read(fd, buf, min(read_bytes, start_char));
        if (n <= 0)
        {
            perror("Number of bytes is less than 0");
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
            perror("Number of bytes is less than equal to 0");
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

    //*************************************************************

    lseek(fd, start_char, SEEK_SET);

    ll read_byte = len + 1;
    char *buff = (char *)calloc(read_byte, sizeof(char));
    ll n = read(fd, buff, read_byte);
    if (n <= 0)
    {
        perror("Number of bytes is less than 0");
        exit(1);
    }

    byte_written += n;
    progress_bar(byte_written, fileLength);

    write(fd2, buff, n);

    //*************************************************************

    read_bytes = max(1000, fileLength / 5);

    lseek(fd, fileLength - min(read_bytes, fileLength - end_char - 1), SEEK_SET);

    char *buf2 = (char *)calloc(read_bytes, sizeof(char));

    while (1)
    {
        ll n = read(fd, buf2, min(read_bytes, fileLength - end_char - 1));

        // reverse the string from last to first
        ll i = 0;
        ll j = n - 1;
        while (i < j)
        {
            char temp = buf2[i];
            buf2[i] = buf2[j];
            buf2[j] = temp;
            i++;
            j--;
        }

        // write reverse string to file
        write(fd2, buf2, n);

        if (lseek(fd, 0, SEEK_CUR) - 2 * read_bytes < end_char)
            break;

        lseek(fd2, 0, SEEK_CUR);
        lseek(fd, -read_bytes * 2, SEEK_CUR);

        byte_written += n;
        progress_bar(byte_written, fileLength);
    }

    if (lseek(fd, -read_bytes, SEEK_CUR) > end_char)
    {
        read_bytes = lseek(fd, 0, SEEK_CUR) - end_char;
        lseek(fd, end_char, SEEK_SET);

        char *buf = (char *)calloc(read_bytes, sizeof(char));

        ll n = read(fd, buf, read_bytes);
        if (n <= 0)
        {
            perror("Number of bytes is less than equal to 0");
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

        // write reverse string to file
        write(fd2, buf, n);

        byte_written += n;
        progress_bar(byte_written, fileLength);
    }

    close(fd);
    close(fd2);

    return 0;
}