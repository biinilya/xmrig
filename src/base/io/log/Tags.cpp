/* XMRig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "base/io/log/Tags.h"
#include "base/io/log/Log.h"


const char *uvloop::Tags::config()
{
    static const char *tag = CYAN_BG_BOLD(WHITE_BOLD_S " config  ");

    return tag;
}


const char *uvloop::Tags::network()
{
    static const char *tag = BLUE_BG_BOLD(WHITE_BOLD_S " net     ");

    return tag;
}


const char* uvloop::Tags::origin()
{
    static const char* tag = YELLOW_BG_BOLD(WHITE_BOLD_S " origin  ");

    return tag;
}


const char *uvloop::Tags::signal()
{
    static const char *tag = YELLOW_BG_BOLD(WHITE_BOLD_S " signal  ");

    return tag;
}


#ifdef XMRIG_MINER_PROJECT
const char *uvloop::Tags::cpu()
{
    static const char *tag = CYAN_BG_BOLD(WHITE_BOLD_S " cpu     ");

    return tag;
}


const char *uvloop::Tags::miner()
{
    static const char *tag = MAGENTA_BG_BOLD(WHITE_BOLD_S " miner   ");

    return tag;
}


#ifdef XMRIG_ALGO_RANDOMX
const char *uvloop::Tags::randomx()
{
    static const char *tag = BLUE_BG(WHITE_BOLD_S " randomx ") " ";

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_BENCHMARK
const char *uvloop::Tags::bench()
{
    static const char *tag = GREEN_BG_BOLD(WHITE_BOLD_S " bench   ");

    return tag;
}
#endif
#endif


#ifdef XMRIG_PROXY_PROJECT
const char *uvloop::Tags::proxy()
{
    static const char *tag = MAGENTA_BG_BOLD(WHITE_BOLD_S " proxy   ");

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_CUDA
const char *uvloop::Tags::nvidia()
{
    static const char *tag = GREEN_BG_BOLD(WHITE_BOLD_S " nvidia  ");

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_OPENCL
const char *uvloop::Tags::opencl()
{
    static const char *tag = MAGENTA_BG_BOLD(WHITE_BOLD_S " opencl  ");

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_MO_BENCHMARK
const char *uvloop::Tags::benchmark()
{
    static const char *tag = BRIGHT_BLACK_BG(CYAN_BOLD_S " benchmk ");

    return tag;
}
#endif

#ifdef XMRIG_FEATURE_PROFILING
const char* uvloop::Tags::profiler()
{
    static const char* tag = CYAN_BG_BOLD(WHITE_BOLD_S " profile ");

    return tag;
}
#endif
