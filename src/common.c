#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "common.h"
#include "monitor.h"

//The purpose of this file is to contain functions that shouldn't really be in stdlib.c but don't necessarily have a purpose anywhere else.

extern void call_cpuid(struct cpuid* cpuid); //this is located in helpers.S

uint32_t check_acpi(){ //this checks if ACPI is supported
  struct cpuid cpuid;
  monitor_put('\n');
  call_cpuid(&cpuid);
  return cpuid.edx & CPUID_FEAT_EDX_ACPI;

}
