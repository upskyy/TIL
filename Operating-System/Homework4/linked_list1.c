#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct Node {
	int data;
	struct list_head list;
};

LIST_HEAD(Node_head);

static int list_plus(int data) {
	struct Node *new;
	new = (struct Node *)kmalloc(sizeof(struct Node), GFP_KERNEL);
	new->data = data;
	list_add_tail(&new->list, &Node_head);
	return 0;
}

static void list_print(void) {
	struct Node *p;
	list_for_each_entry(p, &Node_head, list) {
		printk("data (%d)", p->data);
		if ((p->list).next != &Node_head)
			printk("->");
	}
	printk("\n");
}

static int list_init(void) {
	LIST_HEAD(Node_head);
	list_plus(10);
	list_plus(20);
	list_plus(30);
	list_print();

	return 0;
}

static void list_exit(void) {
	printk("Kernel unloaded\n");
}

module_init(list_init);
module_exit(list_exit);

MODULE_LICENSE("GPL");