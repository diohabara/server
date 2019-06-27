/* Copyright (c) 2019, MariaDB Corporation.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#include <my_global.h>
#include <my_cpu.h>

#ifdef HAVE_PAUSE_INSTRUCTION
/** How many times to invoke PAUSE in a loop */
unsigned my_cpu_relax_multiplier = 200;

# include <stdint.h>

# ifdef _MSC_VER
#  include <intrin.h>
# else
#  include <x86intrin.h>
# endif

#define PAUSE4  MY_RELAX_CPU(); MY_RELAX_CPU(); MY_RELAX_CPU(); MY_RELAX_CPU()
#define PAUSE16 PAUSE4; PAUSE4; PAUSE4; PAUSE4

/**
  Initialize my_cpu_relax_multiplier.

  Determine the duration of a PAUSE instruction by running an
  unrolled loop of 16 PAUSE instructions twice, and taking the
  faster of the two runs. In this way, even if the execution is
  interrupted by the operating system, it should be extremely
  unlikely that both loops get interrupted.

  On the Intel Skylake microarchitecture, the PAUSE instruction takes
  around 140 clock cycles, while on earlier microarchitectures it could
  be 10 clock cycles or less. Scale the PAUSE loop counter accordingly.

  On a pre-Skylake Intel Xeon CPU E5-2630 v4 @ 2.20GHz running an AMD64
  executable, the numbers would be between 172 and 220 when all the code
  is inlined as follows:

  rdtsc,mov,shl,or, 16*pause,
  rdtsc,mov,shl,or, 16*pause,
  rdtsc.

  That would yield 11 to 14 cycles per PAUSE instruction even if we
  (wrongly) ignore the overhead of the other instructions.

  On a Skylake mobile processor Intel Core i7-6500U CPU @ 2.50GHz, the
  numbers would range from 1896 to 2410 (or 1976 if taking the minimum
  of two runs), yielding 118 to 151 (or 123) cycles per PAUSE instruction.

  Let us define a threshold at roughly 30 cycles per PAUSE instruction,
  and use a shorter delay if the PAUSE instruction takes longer than
  that. In some AMD processors, the PAUSE instruction could take 40 or
  50 cycles. Let us use a shorter delay multiplier for them as well.

  The 1/10 scaling factor (200/20) was derived experimentally by
  Mikhail Sinyavin from Intel.
*/
void my_cpu_init(void)
{
  uint64_t t0, t1, t2;
  t0= __rdtsc();
  PAUSE16;
  t1= __rdtsc();
  PAUSE16;
  t2= __rdtsc();
  if (t2 - t1 > 30 * 16 && t1 - t0 > 30 * 16)
    my_cpu_relax_multiplier= 20;
}
#endif
