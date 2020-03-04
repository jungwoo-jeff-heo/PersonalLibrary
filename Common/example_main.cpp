#include "manageFile.h"
#include <fcntl.h>
#include <iostream>

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main()
{
	/*Stat*/
	GetFileStat(".");
	GetFileStat("manageFile.h");
	GetFileStat("manageFile.ha");

	int fd = -1;
#ifdef WIN32
	_sopen_s(&fd, "a.out", _O_CREAT | _O_WRONLY | _O_TRUNC, SH_DENYNO, _S_IREAD | _S_IWRITE);
	if(fd != -1)
		GetFileFStat(fd);
	_close(fd);
#else
	GetFileLStat("manageFile.h");

	fd = open("a.out", O_CREAT | O_RDONLY, 0777);
	if (fd != -1)
		GetFileFStat(fd);
	close(fd);
#endif

	/**/
	cout << ". size : " << GetFileSize(".") << "\n";
	cout << "manageFile.h size : " << GetFileSize("manageFile.h") << "\n";
	cout << "manageFile.ha size : " << GetFileSize("manageFile.ha") << "\n";
	return 0;
}