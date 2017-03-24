#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/time.h>

#define MAX_CPU 128

#define EXIT_REASON_EXCEPTION_NMI       0
#define EXIT_REASON_EXTERNAL_INTERRUPT  1
#define EXIT_REASON_TRIPLE_FAULT        2
#define EXIT_REASON_PENDING_INTERRUPT   7
#define EXIT_REASON_NMI_WINDOW          8
#define EXIT_REASON_TASK_SWITCH         9
#define EXIT_REASON_CPUID               10
#define EXIT_REASON_HLT                 12
#define EXIT_REASON_INVD                13
#define EXIT_REASON_INVLPG              14
#define EXIT_REASON_RDPMC               15
#define EXIT_REASON_RDTSC               16
#define EXIT_REASON_VMCALL              18
#define EXIT_REASON_VMCLEAR             19
#define EXIT_REASON_VMLAUNCH            20
#define EXIT_REASON_VMPTRLD             21
#define EXIT_REASON_VMPTRST             22
#define EXIT_REASON_VMREAD              23
#define EXIT_REASON_VMRESUME            24
#define EXIT_REASON_VMWRITE             25
#define EXIT_REASON_VMOFF               26
#define EXIT_REASON_VMON                27
#define EXIT_REASON_CR_ACCESS           28
#define EXIT_REASON_DR_ACCESS           29
#define EXIT_REASON_IO_INSTRUCTION      30
#define EXIT_REASON_MSR_READ            31
#define EXIT_REASON_MSR_WRITE           32
#define EXIT_REASON_INVALID_STATE       33
#define EXIT_REASON_MSR_LOAD_FAIL       34
#define EXIT_REASON_MWAIT_INSTRUCTION   36
#define EXIT_REASON_MONITOR_TRAP_FLAG   37
#define EXIT_REASON_MONITOR_INSTRUCTION 39
#define EXIT_REASON_PAUSE_INSTRUCTION   40
#define EXIT_REASON_MCE_DURING_VMENTRY  41
#define EXIT_REASON_TPR_BELOW_THRESHOLD 43
#define EXIT_REASON_APIC_ACCESS         44
#define EXIT_REASON_EOI_INDUCED         45
#define EXIT_REASON_EPT_VIOLATION       48
#define EXIT_REASON_EPT_MISCONFIG       49
#define EXIT_REASON_INVEPT              50
#define EXIT_REASON_RDTSCP              51
#define EXIT_REASON_PREEMPTION_TIMER    52
#define EXIT_REASON_INVVPID             53
#define EXIT_REASON_WBINVD              54
#define EXIT_REASON_XSETBV              55
#define EXIT_REASON_APIC_WRITE          56
#define EXIT_REASON_INVPCID             58
#define EXIT_REASON_PML_FULL            62
#define EXIT_REASON_XSAVES              63
#define EXIT_REASON_XRSTORS             64
#define EXIT_REASON_PCOMMIT             65
#define EXIT_REASON_MAX									66

#define EVENT_MAX                       3

extern unsigned int vmx_exit_counter[MAX_CPU][EXIT_REASON_MAX];
extern unsigned int vmx_event[MAX_CPU][EVENT_MAX];
extern struct timespec vmx_exit_start_time;
unsigned int vmx_exits[EXIT_REASON_MAX];
int total_cpu;
int total_num_exits = 51;

int init_module(void);
void cleanup_module(void);

unsigned int get_total_exits_per_id(int exit_id);
unsigned int get_total_events_per_cpu_id(int cpu_id);
unsigned int get_total_exits_per_cpu_id(int cpu_id);

void print_statistics(void);
void print_exit_statistics(void);
void print_events_per_cpu(void);
void print_exits_per_cpu_per_second(void);

int init_module(void)
{
  //printk("init_module");
  print_statistics();
  return 0;
}

void print_statistics(void)
{
//  printk("vmx_exit_start_time.tv_sec: %ld\n",vmx_exit_start_time.tv_sec);

  // print individual events
  printk("\n*************************************\n");
  printk("CMPE283 bonus assignment\n");
  printk("*************************************\n");

  // print individual events
  printk("\n*************************************\n");
  printk("1. Total number of exits of each type\n");
  print_exit_statistics();
  printk("*************************************\n");

  printk("\n*************************************\n");
  printk("2. Total number of event per CPU\n");
  //printk("Number of CPU: %d\n", total_cpu);
  print_events_per_cpu();
  printk("*************************************\n");

  printk("\n*************************************\n");
  printk("3. Average number of exits per second, per CPU \n");
  print_exits_per_cpu_per_second();
  printk("*************************************\n");

}

void print_exits_per_cpu_per_second(void)
{
  unsigned int c=0;
  struct timespec current_time;

  printk("Number of types of exits: %d\n", total_num_exits);
  for(c = 0; c < total_cpu; c++)
  {
    int time_s = 0;
    getnstimeofday(&current_time);
    time_s = current_time.tv_sec - vmx_exit_start_time.tv_sec;
    printk("Total exits per CPU[%d] per second : %d\n", c, get_total_exits_per_cpu_id(c)/time_s);
  }

  for(c = 0; c < total_cpu; c++)
  {
    int time_s = 0;
    getnstimeofday(&current_time);
    time_s = current_time.tv_sec - vmx_exit_start_time.tv_sec;
    printk("Avg exits per CPU[%d] per second : %d\n", c, get_total_exits_per_cpu_id(c)/(time_s*total_num_exits));
  }
}

void print_events_per_cpu(void)
{
  unsigned int c=0;
  for(c = 0; c < total_cpu; c++)
  {
    printk("Events per CPU[%d] : %d\n", c, get_total_events_per_cpu_id(c));
  }
}

void print_exit_statistics(void)
{
  vmx_exits[EXIT_REASON_EXCEPTION_NMI] = get_total_exits_per_id(EXIT_REASON_EXCEPTION_NMI);
  printk("EXIT_REASON_EXCEPTION_NMI: %d\n", vmx_exits[EXIT_REASON_EXCEPTION_NMI]);

  vmx_exits[EXIT_REASON_EXTERNAL_INTERRUPT] = get_total_exits_per_id(EXIT_REASON_EXTERNAL_INTERRUPT);
  printk("EXIT_REASON_EXTERNAL_INTERRUPT: %d\n", vmx_exits[EXIT_REASON_EXTERNAL_INTERRUPT]);

  vmx_exits[EXIT_REASON_TRIPLE_FAULT] = get_total_exits_per_id(EXIT_REASON_TRIPLE_FAULT);
  printk("EXIT_REASON_TRIPLE_FAULT: %d\n", vmx_exits[EXIT_REASON_TRIPLE_FAULT]);

  vmx_exits[EXIT_REASON_PENDING_INTERRUPT] = get_total_exits_per_id(EXIT_REASON_PENDING_INTERRUPT);
  printk("EXIT_REASON_PENDING_INTERRUPT: %d\n", vmx_exits[EXIT_REASON_PENDING_INTERRUPT]);

  vmx_exits[EXIT_REASON_NMI_WINDOW] = get_total_exits_per_id(EXIT_REASON_NMI_WINDOW);
  printk("EXIT_REASON_NMI_WINDOW: %d\n", vmx_exits[EXIT_REASON_NMI_WINDOW]);

  vmx_exits[EXIT_REASON_TASK_SWITCH] = get_total_exits_per_id(EXIT_REASON_TASK_SWITCH);
  printk("EXIT_REASON_TASK_SWITCH: %d\n", vmx_exits[EXIT_REASON_TASK_SWITCH]);

  vmx_exits[EXIT_REASON_CPUID] = get_total_exits_per_id(EXIT_REASON_CPUID);
  printk("EXIT_REASON_CPUID: %d\n", vmx_exits[EXIT_REASON_CPUID]);

  vmx_exits[EXIT_REASON_HLT] = get_total_exits_per_id(EXIT_REASON_HLT);
  printk("EXIT_REASON_HLT: %d\n", vmx_exits[EXIT_REASON_HLT]);

  vmx_exits[EXIT_REASON_INVD ] = get_total_exits_per_id(EXIT_REASON_INVD );
  printk("EXIT_REASON_INVD : %d\n", vmx_exits[EXIT_REASON_INVD ]);

  vmx_exits[EXIT_REASON_INVLPG  ] = get_total_exits_per_id(EXIT_REASON_INVLPG  );
  printk("EXIT_REASON_INVLPG  : %d\n", vmx_exits[EXIT_REASON_INVLPG  ]);

  vmx_exits[EXIT_REASON_RDPMC ] = get_total_exits_per_id(EXIT_REASON_RDPMC );
  printk("EXIT_REASON_RDPMC : %d\n", vmx_exits[EXIT_REASON_RDPMC ]);

  vmx_exits[EXIT_REASON_RDTSC ] = get_total_exits_per_id(EXIT_REASON_RDTSC );
  printk("EXIT_REASON_RDTSC : %d\n", vmx_exits[EXIT_REASON_RDTSC ]);

  vmx_exits[EXIT_REASON_VMCALL] = get_total_exits_per_id(EXIT_REASON_VMCALL);
  printk("EXIT_REASON_VMCALL: %d\n", vmx_exits[EXIT_REASON_VMCALL]);

  vmx_exits[EXIT_REASON_VMCLEAR] = get_total_exits_per_id(EXIT_REASON_VMCLEAR);
  printk("EXIT_REASON_VMCLEAR: %d\n", vmx_exits[EXIT_REASON_VMCLEAR]);

  vmx_exits[EXIT_REASON_VMLAUNCH] = get_total_exits_per_id(EXIT_REASON_VMLAUNCH);
  printk("EXIT_REASON_VMLAUNCH: %d\n", vmx_exits[EXIT_REASON_VMLAUNCH]);

  vmx_exits[EXIT_REASON_VMPTRLD] = get_total_exits_per_id(EXIT_REASON_VMPTRLD);
  printk("EXIT_REASON_VMPTRLD: %d\n", vmx_exits[EXIT_REASON_VMPTRLD]);

  vmx_exits[EXIT_REASON_VMPTRST] = get_total_exits_per_id(EXIT_REASON_VMPTRST);
  printk("EXIT_REASON_VMPTRST: %d\n", vmx_exits[EXIT_REASON_VMPTRST]);

  vmx_exits[EXIT_REASON_VMREAD] = get_total_exits_per_id(EXIT_REASON_VMREAD);
  printk("EXIT_REASON_VMREAD: %d\n", vmx_exits[EXIT_REASON_VMREAD]);

  vmx_exits[EXIT_REASON_VMRESUME] = get_total_exits_per_id(EXIT_REASON_VMRESUME);
  printk("EXIT_REASON_VMRESUME: %d\n", vmx_exits[EXIT_REASON_VMRESUME]);

  vmx_exits[EXIT_REASON_VMWRITE] = get_total_exits_per_id(EXIT_REASON_VMWRITE);
  printk("EXIT_REASON_VMWRITE: %d\n", vmx_exits[EXIT_REASON_VMWRITE]);

  vmx_exits[EXIT_REASON_VMOFF] = get_total_exits_per_id(EXIT_REASON_VMOFF);
  printk("EXIT_REASON_VMOFF: %d\n", vmx_exits[EXIT_REASON_VMOFF]);

  vmx_exits[EXIT_REASON_VMON] = get_total_exits_per_id(EXIT_REASON_VMON);
  printk("EXIT_REASON_VMON: %d\n", vmx_exits[EXIT_REASON_VMON]);

  vmx_exits[EXIT_REASON_CR_ACCESS] = get_total_exits_per_id(EXIT_REASON_CR_ACCESS);
  printk("EXIT_REASON_CR_ACCESS: %d\n", vmx_exits[EXIT_REASON_CR_ACCESS]);

  vmx_exits[EXIT_REASON_DR_ACCESS] = get_total_exits_per_id(EXIT_REASON_DR_ACCESS);
  printk("EXIT_REASON_DR_ACCESS: %d\n", vmx_exits[EXIT_REASON_DR_ACCESS]);

  vmx_exits[EXIT_REASON_IO_INSTRUCTION] = get_total_exits_per_id(EXIT_REASON_IO_INSTRUCTION);
  printk("EXIT_REASON_IO_INSTRUCTION: %d\n", vmx_exits[EXIT_REASON_IO_INSTRUCTION]);

  vmx_exits[EXIT_REASON_MSR_READ] = get_total_exits_per_id(EXIT_REASON_MSR_READ);
  printk("EXIT_REASON_MSR_READ: %d\n", vmx_exits[EXIT_REASON_MSR_READ]);

  vmx_exits[EXIT_REASON_MSR_WRITE] = get_total_exits_per_id(EXIT_REASON_MSR_WRITE);
  printk("EXIT_REASON_MSR_WRITE: %d\n", vmx_exits[EXIT_REASON_MSR_WRITE]);

  vmx_exits[EXIT_REASON_INVALID_STATE] = get_total_exits_per_id(EXIT_REASON_INVALID_STATE);
  printk("EXIT_REASON_INVALID_STATE: %d\n", vmx_exits[EXIT_REASON_INVALID_STATE]);

  vmx_exits[EXIT_REASON_MSR_LOAD_FAIL] = get_total_exits_per_id(EXIT_REASON_MSR_LOAD_FAIL);
  printk("EXIT_REASON_MSR_LOAD_FAIL: %d\n", vmx_exits[EXIT_REASON_MSR_LOAD_FAIL]);

  vmx_exits[EXIT_REASON_MWAIT_INSTRUCTION] = get_total_exits_per_id(EXIT_REASON_MWAIT_INSTRUCTION);
  printk("EXIT_REASON_MWAIT_INSTRUCTION: %d\n", vmx_exits[EXIT_REASON_MWAIT_INSTRUCTION]);

  vmx_exits[EXIT_REASON_MONITOR_TRAP_FLAG] = get_total_exits_per_id(EXIT_REASON_MONITOR_TRAP_FLAG);
  printk("EXIT_REASON_MONITOR_TRAP_FLAG: %d\n", vmx_exits[EXIT_REASON_MONITOR_TRAP_FLAG]);

  vmx_exits[EXIT_REASON_MONITOR_INSTRUCTION] = get_total_exits_per_id(EXIT_REASON_MONITOR_INSTRUCTION);
  printk("EXIT_REASON_MONITOR_INSTRUCTION: %d\n", vmx_exits[EXIT_REASON_MONITOR_INSTRUCTION]);

  vmx_exits[EXIT_REASON_PAUSE_INSTRUCTION] = get_total_exits_per_id(EXIT_REASON_PAUSE_INSTRUCTION);
  printk("EXIT_REASON_PAUSE_INSTRUCTION: %d\n", vmx_exits[EXIT_REASON_PAUSE_INSTRUCTION]);

  vmx_exits[EXIT_REASON_MCE_DURING_VMENTRY] = get_total_exits_per_id(EXIT_REASON_MCE_DURING_VMENTRY);
  printk("EXIT_REASON_MCE_DURING_VMENTRY: %d\n", vmx_exits[EXIT_REASON_MCE_DURING_VMENTRY]);

  vmx_exits[EXIT_REASON_TPR_BELOW_THRESHOLD] = get_total_exits_per_id(EXIT_REASON_TPR_BELOW_THRESHOLD);
  printk("EXIT_REASON_TPR_BELOW_THRESHOLD: %d\n", vmx_exits[EXIT_REASON_TPR_BELOW_THRESHOLD]);

  vmx_exits[EXIT_REASON_APIC_ACCESS ] = get_total_exits_per_id(EXIT_REASON_APIC_ACCESS );
  printk("EXIT_REASON_APIC_ACCESS : %d\n", vmx_exits[EXIT_REASON_APIC_ACCESS ]);

  vmx_exits[EXIT_REASON_EOI_INDUCED] = get_total_exits_per_id(EXIT_REASON_EOI_INDUCED);
  printk("EXIT_REASON_EOI_INDUCED: %d\n", vmx_exits[EXIT_REASON_EOI_INDUCED]);

  vmx_exits[EXIT_REASON_EPT_VIOLATION] = get_total_exits_per_id(EXIT_REASON_EPT_VIOLATION);
  printk("EXIT_REASON_EPT_VIOLATION: %d\n", vmx_exits[EXIT_REASON_EPT_VIOLATION]);

  vmx_exits[EXIT_REASON_EPT_MISCONFIG] = get_total_exits_per_id(EXIT_REASON_EPT_MISCONFIG);
  printk("EXIT_REASON_EPT_MISCONFIG: %d\n", vmx_exits[EXIT_REASON_EPT_MISCONFIG]);

  vmx_exits[EXIT_REASON_INVEPT] = get_total_exits_per_id(EXIT_REASON_INVEPT);
  printk("EXIT_REASON_INVEPT: %d\n", vmx_exits[EXIT_REASON_INVEPT]);

  vmx_exits[EXIT_REASON_RDTSCP] = get_total_exits_per_id(EXIT_REASON_RDTSCP);
  printk("EXIT_REASON_RDTSCP: %d\n", vmx_exits[EXIT_REASON_RDTSCP]);

  vmx_exits[EXIT_REASON_PREEMPTION_TIMER] = get_total_exits_per_id(EXIT_REASON_PREEMPTION_TIMER);
  printk("EXIT_REASON_PREEMPTION_TIMER: %d\n", vmx_exits[EXIT_REASON_PREEMPTION_TIMER]);

  vmx_exits[EXIT_REASON_INVVPID] = get_total_exits_per_id(EXIT_REASON_INVVPID);
  printk("EXIT_REASON_INVVPID: %d\n", vmx_exits[EXIT_REASON_INVVPID]);

  vmx_exits[EXIT_REASON_WBINVD] = get_total_exits_per_id(EXIT_REASON_WBINVD);
  printk("EXIT_REASON_WBINVD: %d\n", vmx_exits[EXIT_REASON_WBINVD]);

  vmx_exits[EXIT_REASON_XSETBV] = get_total_exits_per_id(EXIT_REASON_XSETBV);
  printk("EXIT_REASON_XSETBV: %d\n", vmx_exits[EXIT_REASON_XSETBV]);

  vmx_exits[EXIT_REASON_APIC_WRITE] = get_total_exits_per_id(EXIT_REASON_APIC_WRITE);
  printk("EXIT_REASON_APIC_WRITE: %d\n", vmx_exits[EXIT_REASON_APIC_WRITE]);

  vmx_exits[EXIT_REASON_INVPCID] = get_total_exits_per_id(EXIT_REASON_INVPCID);
  printk("EXIT_REASON_INVPCID: %d\n", vmx_exits[EXIT_REASON_INVPCID]);

  vmx_exits[EXIT_REASON_PML_FULL] = get_total_exits_per_id(EXIT_REASON_PML_FULL);
  printk("EXIT_REASON_PML_FULL: %d\n", vmx_exits[EXIT_REASON_PML_FULL]);

  vmx_exits[EXIT_REASON_XSAVES] = get_total_exits_per_id(EXIT_REASON_XSAVES);
  printk("EXIT_REASON_XSAVES: %d\n", vmx_exits[EXIT_REASON_XSAVES]);

  vmx_exits[EXIT_REASON_XRSTORS] = get_total_exits_per_id(EXIT_REASON_XRSTORS);
  printk("EXIT_REASON_XRSTORS: %d\n", vmx_exits[EXIT_REASON_XRSTORS]);

  vmx_exits[EXIT_REASON_PCOMMIT] = get_total_exits_per_id(EXIT_REASON_PCOMMIT);
  printk("EXIT_REASON_PCOMMIT: %d\n", vmx_exits[EXIT_REASON_PCOMMIT]);
}

unsigned int get_total_exits_per_id(int exit_id)
{
  unsigned int total = 0, c = 0, tmp_total_cpu = 0;
  for (c = 0; c < MAX_CPU; c++)
  {
    //printk("%d\n", vmx_exit_counter[c][event_id]);
    total += vmx_exit_counter[c][exit_id];
    if(vmx_exit_counter[c][exit_id] > 0)
    {
      tmp_total_cpu += 1;
    }
  }

  if(tmp_total_cpu > total_cpu)
  {
    total_cpu = tmp_total_cpu;
  }

  return total;
}

unsigned int get_total_events_per_cpu_id(int cpu_id)
{
  unsigned int total = 0, e = 0;
  for (e = 0; e < EVENT_MAX; e++)
  {
    total += vmx_event[cpu_id][e];
  }

  return total;
}

unsigned int get_total_exits_per_cpu_id(int cpu_id)
{
  unsigned int total = 0, e = 0;
  for (e = 0; e < EXIT_REASON_MAX; e++)
  {
    total += vmx_exit_counter[cpu_id][e];
  }

  return total;
}

void cleanup_module(void)
{
  //printk(KERN_ALERT "cleanup_module");
}

MODULE_LICENSE("GPL");
