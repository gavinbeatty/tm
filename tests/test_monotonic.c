/**
tm Copyright 2010, 2011 Gavin Beatty <gavinbeatty@gmail.com>.
All rights reserved.

New BSD License

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of the tm project owners nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <tm/tm.h>

#include <errno.h>

#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct tm_timespec_t tspec;
    double fst = -1.0;
    double snd = -2.0;
    if (-1 == tm_monotonic(&tspec)) {
        fprintf(stderr, "tm_monotonic 1st failed: %s\n", strerror(errno));
        return 1;
    }
    fst = tm_timespec_to_double(&tspec);
    printf("1st: %.10g\n", fst);

    if (-1 == tm_monotonic(&tspec)) {
        fprintf(stderr, "tm_monotonic 2nd failed: %s\n", strerror(errno));
        return 1;
    }
    snd = tm_timespec_to_double(&tspec);
    printf("2nd: %.10g\n", snd);

    return snd >= fst;
}

