#include "node.h"

node *node_make(node_type type, long value) {
	node *n = malloc(sizeof(node));
	n->type = type;
	n->value = value;
	return n;
}

node_array *node_array_make() {
	node_array *arr = malloc(sizeof(node_array));
	arr->node_array = malloc(sizeof(node) * NODE_ARRAY_INIT_SIZE);
	arr->used = 0;
	arr->size = NODE_ARRAY_INIT_SIZE;
	return arr;
}

void node_array_add(node_array *arr, node_type type, long value) {
	if (arr->used == arr->size) {
		arr->node_array = realloc(arr->node_array, arr->size * 2 * sizeof(node));
		arr->size *= 2;
	}
	arr->node_array[arr->used].type = type;
	arr->node_array[arr->used].value = value;
	arr->used += 1;
}

node_type node_array_get_node_type(node_array *arr, long position) {
	return (arr->node_array[position]).type;
}

node *node_array_get_node(node_array *arr, long position) {
	return &(arr->node_array[position]);
}
