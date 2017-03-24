# Linux-Kernel-development
Kernel module for system monitoring by augmenting the KVM. Implemented statistics gathering functionality in Kernel to characterise virtual machines.

## How do you obtain the statistics implemented?
1. Apply the git diff patch (cmpe283.diff) to kvm folder using "git apply cmpe283.diff"
2. Build and install the kernel
3. Build the kernel module in the module folder present in <kernel_source>/arch/x86/kvm path 4. Run the get_statistics.sh script from <kernel_source>/arch/x86/kvm/module
5. View the statistics by dmesg

## Steps used to complete the assignment:
1. Open terminal on Ubuntu 16.04 machine and do all update and upgrades * sudo apt-get update
* sudo apt-get upgrade
2. Clone kernel source code from the following link:
* git clone git://kernel.ubuntu.com/ubuntu/ubuntu-xenial.git 3. Build the environment:
* sudo apt-get build-dep linux-image-$(uname -r)
4. Make appropriate changes to vmx.c and vmx.h files
5. Make changes in /etc/default/grub, and set a long enough timeout to ensure that you have time to access the new kernel during boot
> sudo edit /etc/default/grub
I used these settings:
GRUB_DEFAULT=0 #GRUB_HIDDEN_TIMEOUT=0 GRUB_HIDDEN_TIMEOUT_QUIET=true GRUB_TIMEOUT=20
> sudo update-grub 6. Building the kernel
Change your working directory to the root of the kernel source tree and then type the following commands:
* fakeroot debian/rules clean
* fakeroot debian/rules binary-headers binary-generic binary-perarch
After build is successful we see *.deb in previous directory (on doing cd ..)
7. Testing the new kernel
Install the package set with dpkg -i and then reboot:
* sudo dpkg -i *.deb
* sudo reboot
8. In the GRUB select the newly created Kernel
9. Build the kernel module
10. The module folder contains the following files:
* get_statistics.c * get_statistics.sh * Makefile
11. Run the following commands to build our helper module: * make
12. Install Virtual Machine Manager in host OS.
13. Install DSL inside the VM using iso image.
14. Once the Guest VM is running, go back to directory module and run statistics.sh 15. View the statistics by dmesg
