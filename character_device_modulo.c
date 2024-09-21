#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> // for copy_to_user
#include <linux/cdev.h>    // for character devices

#define DEVICE_NAME "simple_char_dev"

static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char __user *buffer, size_t len, loff_t *offset)
{
    const char *message = "Hello from kernel space!\n";
    size_t message_len = strlen(message);

    if (copy_to_user(buffer, message, message_len)) {
        return -EFAULT;
    }

    return message_len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
};

static int major_num;
static struct cdev my_cdev;

static int __init char_dev_init(void)
{
    major_num = register_chrdev(0, DEVICE_NAME, &fops);

    if (major_num < 0) {
        printk(KERN_ALERT "Failed to register char device\n");
        return major_num;
    }

    printk(KERN_INFO "Registered char device with major number %d\n", major_num);
    return 0;
}

static void __exit char_dev_exit(void)
{
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Char device unregistered\n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Simple Character Device Driver");
