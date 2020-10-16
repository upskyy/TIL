#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct Node{
	int data;
	struct list_head list;
};

LIST_HEAD(Node_head);

static int list_insert(int data){
	struct Node *new;
	new = (struct Node *)kmalloc(sizeof(struct Node), GFP_KERNEL);
	new->data = data;
	list_add_tail(&new->list, &Node_head);
	return 0;
}

static void list_all_delete(void){
	struct Node *p, *q;
	list_for_each_entry_safe(p, q, &Node_head, list){
		list_del(&p->list);
		kfree(p);
	}
}

static void list_little_delete(void){
	struct Node *p, *q;
	list_for_each_entry_safe(p, q, &Node_head, list){
		if ((p->data == 10) || (p->data == 25)) {
			list_del(&p->list);
			kfree(p);
		}
	}
}

static void list_print(void){
	struct Node *p;
	list_for_each_entry(p, &Node_head, list){
		printk("data (%d)", p->data);
		if ((p->list).next != &Node_head)
			printk("->");
	}
	printk("\n");
}

static int list_init(void) {
	LIST_HEAD(Node_head);
	printk("*** Insert ***\n");
	list_insert(5);
	list_insert(10);
	list_insert(15);
	list_insert(20);
	list_insert(25);
	list_insert(30);
	list_insert(35);
	list_print();

	printk("*** Slightly Delete(10,25) ***\n");
	list_little_delete();
	list_print();

	printk("*** All Delete ***\n");
	list_all_delete();
	list_print();

	return 0;
}

static void list_exit(void) {
	printk("Kernel unloaded\n");
}

module_init(list_init);
module_exit(list_exit);

MODULE_LICENSE("GPL");