#include "stack.h"
#include <linux/slab.h>

stack_entry_t* create_stack_entry(void *data)
{
    stack_entry_t* ptr = kmalloc(sizeof(struct stack_entry), GFP_KERNEL);
    if (!ptr) {
        /* handle error ... */
        return NULL;
    }
    ptr->data = data;
    INIT_LIST_HEAD(&(ptr->lh));    
    return ptr;
}

void delete_stack_entry(stack_entry_t *entry)
{
    kfree(entry);
}

void stack_push(struct list_head *stack, stack_entry_t *entry)
{
    list_add(&(entry->lh), stack);
}

stack_entry_t* stack_pop(struct list_head *stack)
{
    struct list_head *next;
    stack_entry_t *ptr;
    if (stack_empty(stack)) {
        return NULL;
    }
    // why is it works?
    // stack_entry_t *ptr = list_entry(stack->next, struct stack_entry_t, lh);
    next = stack->next;
    ptr = container_of(next, stack_entry_t, lh);
    list_del_init(next);
    return ptr;
}
