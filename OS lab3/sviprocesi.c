#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Svi procesi");
MODULE_AUTHOR("Patrik Slovic");

int sviprocesi_init(void){
    struct task_struct* task_list;
    size_t brojac_procesa = 0;
    for_each_process(task_list){
        printk(KERN_INFO "%s (PID: %ld, PPID: %ld, Stanje: %ld)\n", task_list->comm, (long)task_list->pid,
               (long)task_list->real_parent->pid, task_list->state);
        brojac_procesa++;
    }
    printk(KERN_INFO "Ukupan broj procesa: %d\n", brojac_procesa);
    return 0;
}

void sviprocesi_exit(void){

}

module_init(sviprocesi_init);
module_exit(sviprocesi_exit);