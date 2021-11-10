#include "node.h"

// make a new node with the given type and the value which is an entry in the symbol table
node *node_make(node_type type, node_type_class type_class, long value) {
	node *n = malloc(sizeof(node));
	n->type = type;
	n->type_class = type_class;
	n->value = value;
	return n;
}

// make a new node array
node_array *node_array_make() {
	node_array *arr = malloc(sizeof(node_array));
	arr->node_array = malloc(sizeof(node) * NODE_ARRAY_INIT_SIZE);
	arr->used = 0;
	arr->size = NODE_ARRAY_INIT_SIZE;
	return arr;
}

node_type_class node_array_get_node_type_class(node_array *arr, long position) {
	return arr->node_array[position].type_class;
}

// add a new entry to the node array
void node_array_add(node_array *arr, node_type type, node_type_class type_class, long value) {
	if (arr->used == arr->size) {
		arr->node_array = realloc(arr->node_array, arr->size * 2 * sizeof(node));
		arr->size = arr->size * 2;
	}
	arr->node_array[arr->used].type = type;
	arr->node_array[arr->used].type_class = type_class;
	arr->node_array[arr->used].value = value;
	arr->used += 1;
}

// get the node type of a node
node_type node_array_get_node_type(node_array *arr, long position) {
	return (arr->node_array[position]).type;
}

// get a pointer to the node of an array
node *node_array_get_node(node_array *arr, long position) {
	return &(arr->node_array[position]);
}

long *node_array_get_val(node_array *arr, long position) {
	return &(arr->node_array[position].value);
}