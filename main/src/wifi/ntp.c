#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include "lwip/apps/sntp.h"

void set_ntp_time(const char *posix_tz, int server_cnt, ...)
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
	va_list ap;
	va_start(ap, server_cnt);
	if (server_cnt > SNTP_MAX_SERVERS)         // sntp_setservername最多支持 SNTP_MAX_SERVERS 个地址
		server_cnt = SNTP_MAX_SERVERS;         // 超过三个的地址会被抛弃
	for (int i = 0; i < server_cnt; ++i)
		sntp_setservername(i, va_arg(ap, const char*));
	va_end(ap);
	sntp_init();
	setenv("TZ", posix_tz, 1);
	tzset();
	while (time(NULL) < 1580000000);	// 阻塞，直到时间同步
		//yield();
	sntp_stop();
}

void ntp_init()
{
    set_ntp_time("UTC-8", 3, "ntp1.aliyun.com", "ntp2.aliyun.com", "ntp3.aliyun.com");
}
