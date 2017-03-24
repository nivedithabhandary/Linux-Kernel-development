# Linux-Kernel-development
Kernel module for system monitoring by augmenting the KVM. Implemented statistics gathering functionality in Kernel to characterise virtual machines.

## How do you obtain the statistics implemented?
1. Apply the git diff patch (cmpe283.diff) to kvm folder using "git apply cmpe283.diff"
2. Build and install the kernel
3. Build the kernel module in the module folder present in <kernel_source>/arch/x86/kvm path 4. Run the get_statistics.sh script from <kernel_source>/arch/x86/kvm/module
5. View the statistics by dmesg
