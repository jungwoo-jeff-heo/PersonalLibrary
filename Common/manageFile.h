/**
@file	manageFile.h
@date	2020-03-03
@author	Jungwoo Heo (jungwoo.jeff.heo@gmail.com)
@brief
Common header which includes file managing
@warning
All rights are reserved.
No part of this work covered by the copyright hereon may be
reproduced, stored in a retrieval system, in any form or
by any means, electronic, mechanical, photocopying, recording
or otherwise, without the prior permission of Jungwoo Heo.
*/

#pragma once

#include <ctime>
#include <sys/stat.h>
#include <cstdint>

#ifdef DEBUG
#else
#endif

/*
Usage of Stat
*/
void GetFileStat(const char* i_pstrPath);
void GetFileFStat(const int i_fp);

bool IsDirectory(const char* i_pstrPath);
#ifndef WIN32
void GetFileLStat(const char* i_pstrPath);
#endif

int64_t GetFileSize(const char* i_pstrFileName);

/*
Internal of Stat
*/
void ConvertTime(const time_t* i_pTime, char* o_strTime, const int i_size);
void PrintFileStat(struct stat* i_pstStat);