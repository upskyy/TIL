#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<linux/init.h>
static struct timer_list my_timer;
void my_timer_callback(struct timer_list *timer)
{
	printk(KERN_NOTICE "%s called (%ld)\n", __func__, jiffies);
}
static int __init timer_module_init(void)
{
	int ret;
	printk(KERN_NOTICE "%s : Timer module loaded!!!\n", __func__);

	setup_timer(&my_timer, my_timer_callback, 0);
	printk(KERN_NOTICE "%s : Setup timer to fire in 1000ms (%ld)\n", __func__, jiffies);
	ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));

	if (ret) printk(KERN_NOTICE "Error in mod_timer\n");
	return 0;
}
static void __exit timer_module_exit(void)
{
	int ret;
	ret = del_timer(&my_timer);
	if (ret) printk(KERN_NOTICE "The timer is still in use.\n");
	printk(KERN_NOTICE "%s : Timer module unloaded!!!\n"), __func__);
}
MODULE_LICENSE("GPL");
module_init(timer_module_init);
module_exit(timer_module_exit);
