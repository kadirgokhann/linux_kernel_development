#include <linux/module.h>  // Needed for all kernel modules
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/init.h>    // Needed for the macros

// Function to be called when the module is loaded
static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, World!\n");
    return 0; // 0 indicates successful loading
}

// Function to be called when the module is unloaded
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, World!\n");
}

// Register the functions with the kernel
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kadirgokhann");
MODULE_DESCRIPTION("A Simple Hello World Kernel Module");
