#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm/unistd.h>
#define TASK_RUNNING 0
#define TASK_INTERRUPTIBLE 1
#define TASK_UNINTERRUPTIBLE 2
#define __TASK_STOPPED 4
#define EXIT_ZOMBIE 16

int init_module(void)
{
    struct task_struct *task,*p;
    struct list_head *pos;
    int count=0;
    int cntRunning=0;
    int cntInter=0;
    int cntUninter=0;
    int cntStop=0;
    int cntZombie=0;
    printk("Inserting the module...\n");

    task=&init_task;
    list_for_each(pos,&task->tasks)
    {
        p=list_entry(pos,struct task_struct,tasks);
        count++;
        printk("PNAME = %s ; PID = %ld ; ",p->comm,(long)p->pid);
        if (EXIT_ZOMBIE==p->exit_state) {
            cntZombie++;
            printk("%d|ZOMBIE",p->exit_state);
        }
        else{
            switch (p->state){
                case TASK_RUNNING: cntRunning++;
                    printk("%ld|RUNNING",p->state);break;
                case TASK_INTERRUPTIBLE: cntInter++;
                    printk("%ld|INTERRUPTIBLE",p->state);break;
                case TASK_UNINTERRUPTIBLE: cntUninter++;
                    printk("%ld|UNINTERRUPTIBLE",p->state);break;
                case __TASK_STOPPED: cntStop++;
                    printk("%ld|STOPPED",p->state);break;
                default:printk("%ld|OTHER",p->state);
            }
        }
        printk(" ; ParentNAME = %s\n",p->parent->comm);
    }
    printk("the number of process is:%d\n in which: \n",count);
    printk("  %d in state TASK_RUNNING;\n",cntRunning);
    printk("  %d in state TASK_INTERRUPTIBLE;\n",cntInter);
    printk("  %d in state TASK_UNINTERRUPTIBLE;\n",cntUninter);
    printk("  %d in state __TASK_STOPPED;\n",cntStop);
    printk("  %d in state EXIT_ZOMBIE;\n",cntZombie);
    return 0;
}
void cleanup_module(void)
{
    printk("Leaving the module...\n");
}
MODULE_LICENSE("GPL");
