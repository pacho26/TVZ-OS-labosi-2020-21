#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Moj modul");
MODULE_AUTHOR("Patrik Slovic");

size_t t1;

int moj_init(void){
    printk(KERN_INFO "UCITAVANJE:\nJiffies = %lu\nJiffies/HZ = %lu\n", jiffies, jiffies/HZ);
    t1 = jiffies/HZ;
    return 0;
}

void moj_exit(void){
    printk(KERN_INFO "UKLANJANJE:\nJiffies = %lu\nJiffies/HZ = %lu\n", jiffies, jiffies/HZ);
    int razlika_vremena = jiffies/HZ - t1;
    printk(KERN_INFO "Proteklo vrijeme: %d sekundi\n", razlika_vremena);
}

module_init(moj_init);
module_exit(moj_exit);