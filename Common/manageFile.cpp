#include "manageFile.h"

#include <cassert>
#include <sys/types.h>
#include <cstdio>
#include <errno.h>
#include <iostream>

#ifndef WIN32
#include <pwd.h>
#include <grp.h>
#endif

using namespace std;

void GetFileStat(const char* i_pstrPath)
{
	assert(i_pstrPath != nullptr);

	struct stat stStatBuf;
	if (stat(i_pstrPath, &stStatBuf) != 0)
	{
		switch (errno)
		{
		case ENOENT:
			cout << "Cannot find " << i_pstrPath << endl;
			break;
		case EINVAL:
			cout << "Invalid parameter to stat\n";
			break;
		default:
			cout << "Unknown error from stat " << errno << "\n";
			break;
		}
	}
	else
	{
		cout << "Check file stat : " << i_pstrPath << endl;
		PrintFileStat(&stStatBuf);
	}
}

void GetFileFStat(const int i_fp)
{
	struct stat stStatBuf;
	if (fstat(i_fp, &stStatBuf) != 0)
	{
		switch (errno)
		{
		case ENOENT:
			cout << "Cannot find fd : " << i_fp << endl;
			break;
		case EINVAL:
			cout << "Invalid parameter to fstat \n";
			break;
		default:
			cout << "Unknown error from fstat " << errno << "\n";
			break;
		}
	}
	else
	{
		cout << "Check file fd : " << i_fp << endl;
		PrintFileStat(&stStatBuf);
	}
}

#ifndef WIN32
void GetFileLStat(const char* i_pstrPath)
{
	assert(i_pstrPath != nullptr);

	struct stat stStatBuf;
	if (stat(i_pstrPath, &stStatBuf) != 0)
	{
		switch (errno)
		{
		case ENOENT:
			cout << "Cannot find " << i_pstrPath << endl;
			break;
		case EINVAL:
			cout << "Invalid parameter to lstat\n";
			break;
		default:
			cout << "Unknown error from lstat " << errno << "\n";
			break;
		}
	}
	else
	{
		cout << "Check file lstat : " << i_pstrPath << endl;
		PrintFileStat(&stStatBuf);
	}
}
#endif

bool IsDirectory(const char* i_pstrPath)
{
	assert(i_pstrPath != nullptr);

	struct stat stStatBuf;
	bool bRet = false;
	if (stat(i_pstrPath, &stStatBuf) != 0)
	{
		cout << "Fail to check stat " << i_pstrPath << endl;
	}
	else
	{
#ifdef WIN32
		if ((stStatBuf.st_mode & S_IFDIR) != 0)
		{
			bRet = true;
		}
#else
		return S_ISDIR(stStatBuf.st_mode);
#endif
	}
	return bRet;
}

int64_t GetFileSize(const char* i_pstrFileName)
{
	assert(i_pstrFileName != nullptr);
	int64_t size = 0;

#ifndef WIN32
	if (IsDirectory(i_pstrFileName) == true)
	{
		return size;
	}
#endif
	FILE* fp = fopen(i_pstrFileName, "rb");

	do
	{
		if (fp == nullptr)
			return size;

		if (fseek(fp, 0, SEEK_END) != 0)
		{
			break;
		}

		size = ftell(fp);
		if (size == -1)
		{
			size = 0;
			break;
		}
	} while (false);

	fclose(fp);
	return size;
}

void PrintFileStat(struct stat* i_pstStat)
{
	assert(i_pstStat != nullptr);

	cout << "File type:\t\t\t";

	switch (i_pstStat->st_mode & S_IFMT)
	{
#ifdef WIN32
	case _S_IFIFO:
		cout << "FIFO pipe\n";
		break;
#else
	case S_IFBLK:
		cout << "block device\n";
		break;
	case S_IFIFO:
		cout << "FIFO pipe\n";
		break;
	case S_IFLNK:
		cout << "symbolic link\n";
		break;
	case S_IFSOCK:
		cout << "socket\b";
		break;
#endif
	case S_IFCHR:
		cout << "character device\n";
		break;
	case S_IFDIR:
		cout << "directory\n";
		break;
	case S_IFREG:
		cout << "regular file\n";
		break;
	default:
		cout << "Unknown type: " << i_pstStat->st_mode << endl;
		break;
	}

	cout << "device:\t\t\t\t" << static_cast<char>(i_pstStat->st_dev + 'A') << "\n";
	cout << "I-node:\t\t\t\t" << i_pstStat->st_ino << "\n";
	cout.setf(ios::showbase);
	cout << "Mode:\t\t\t\t" << hex << i_pstStat->st_mode << "\n";
	cout.unsetf(ios::showbase);
	cout << "Link count:\t\t\t" << dec << i_pstStat->st_nlink << "\n";
	cout << "Owner:\t\t\t\tUID: " << i_pstStat->st_uid << ", GID: " << i_pstStat->st_gid << "\n";
	cout << "rdev:\t\t\t\t" << static_cast<char>(i_pstStat->st_dev + 'A') << "\n";
	cout << "size:\t\t\t\t" << i_pstStat->st_size << "\n";

#ifndef WIN32
	cout << "blocksize for file I/O:\t\t" << i_pstStat->st_blksize << "\n";
	cout << "blocksize for file I/O:\t\t" << i_pstStat->st_blocks << "\n";

	struct passwd *my_passwd;
	struct group  *my_group;
	my_passwd = getpwuid(i_pstStat->st_uid);
	my_group = getgrgid(i_pstStat->st_gid);
	cout << "Owner:\t\t\t\tOwner: " << my_passwd->pw_name << ", Group: " << my_group->gr_name << "\n";
#endif

	char timebuf[26] = {};

	ConvertTime(&i_pstStat->st_atime, timebuf, sizeof(timebuf));
	//printf("mtime(Last access): %I64d, %s\n", statBuf.st_atime, timebuf);
	cout << "atime(Last access): " << i_pstStat->st_atime << ", " << timebuf;

	ConvertTime(&i_pstStat->st_mtime, timebuf, sizeof(timebuf));
	cout << "mtime(Last modify): " << i_pstStat->st_mtime << ", " << timebuf;

	ConvertTime(&i_pstStat->st_ctime, timebuf, sizeof(timebuf));
	cout << "ctime(Last status change): " << i_pstStat->st_ctime << ", " << timebuf << endl;
}

void ConvertTime(const time_t *i_pTime, char* o_strTime, const int i_size)
{
	assert((o_strTime != nullptr) && (i_pTime != nullptr));

#ifdef WIN32
	errno_t err = ctime_s(o_strTime, i_size, i_pTime);
	if (err)
	{
		cout << "Invalid atime to ctime_s" << *(i_pTime) << "\n";
	}
#else
	ctime_r(i_pTime, o_strTime);
#endif
}