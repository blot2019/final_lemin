// #include "ants.h"
// #include "function_prototypes.h"

// t_stack *queue_nodes_set_parent_mk2(t_stack *target_stack, t_stack *source_stack, t_node *discovered_via, t_node *finish)
// {
//     t_node_stack_item *node;
//     int n;

//     if (!source_stack || source_stack->number_of_items == 0)
//         return (target_stack);
//     n = 0;
//     while (n < source_stack->number_of_items)
//     {
//         node = get_nth_element(source_stack, n);
//         if (node->node->used && (node->node != finish))
//         {
//             n = n + 1;
//             continue ;
//         }
//         if ((node->node->visited == 0) && (node->node->discovered == 0))
//         {
//             target_stack = queue(target_stack, new_node_stack_item(node->node));
//             target_stack->head->node->discovered = 1;
//             target_stack->head->node->discovered_via = discovered_via;
//         }
//         n = n + 1;
//     }
//     return (target_stack);
// }

// void    bfs_visit_mk2(t_node *node, t_stack *node_queue, t_node *finish)
// {
//     if (node->visited)
//         return ;
//     if (node->used)
//         return ;
//     node->visited = 1;
//     node_queue = queue_nodes_set_parent_mk2(node_queue, node->adjacent_nodes, node, finish);
// }

// t_stack *queue_if_not_visited_mk2(t_stack *target_stack, t_stack *source_stack, t_node *finish)
// {
//     t_node_stack_item *node;
//     int n;

//     if (!source_stack || source_stack->number_of_items == 0)
//         return (target_stack);
//     n = 0;
//     while (n < source_stack->number_of_items)
//     {
//         node = get_nth_element(source_stack, n);
//         if (node->node == finish)
//         {
//             while (n)
//             {
//                 pop(target_stack); //unclutter the stack;
//                 n = n - 1;
//             }
//             target_stack = push(target_stack, new_node_stack_item(finish));
//             return (target_stack);
//         }
//         else if (!node->node->used)
//             target_stack = queue(target_stack, new_node_stack_item(node->node));
//         n = n + 1;
//     }
//     return (target_stack);
// }

// static t_stack *set_used(t_stack *stack)
// {
//     int n;
//     t_node_stack_item *current_node_stack_item;

//     if (!stack)
//         return (NULL);
//     n = 0;
//     current_node_stack_item = stack->tail;
//     while (n < stack->number_of_items)
//     {
//         current_node_stack_item->node->used = 1;
//         current_node_stack_item = current_node_stack_item->left;
//         n = n + 1;
//     }
//     return (stack);
// }

// t_stack *backtrack_mk2(t_node *finish, t_node *start)
// {
//     t_stack *path;
//     t_node *current_node;
//     t_node_stack_item *node_stack_item;

//     node_stack_item = new_node_stack_item(finish);
//     path = new_stack(node_stack_item, node_stack_item, 1);
//     current_node = finish->discovered_via;
//     while (current_node != start)
//     {
//         if (!current_node)
//             break ;
//         path = push(path, new_node_stack_item(current_node));
//         current_node = current_node->discovered_via;
//     }
//     if (start != finish)
//         path = push(path, new_node_stack_item(start));
//     return (set_used(path));
// }

// t_stack *bfs(t_node *start, t_node *finish)
// {
//     t_stack *node_item_queue;
//     t_node_stack_item *node_stack_item;
//     t_node *next_node;
//     int path_found;

//     if (start == finish)
//     {
//         node_stack_item = new_node_stack_item(start);
//         return (new_stack(node_stack_item, node_stack_item, 1));
//     }
//     node_item_queue = NULL;
//     start->visited = 1;
//     node_item_queue = queue_if_not_visited_mk2(node_item_queue, start->adjacent_nodes, finish);
//     path_found = 0;
//     while (node_item_queue && node_item_queue->number_of_items)
//     {
//         next_node = node_item_queue->tail->node;
//         if (next_node == finish)
//         {
//             bfs_visit_mk2(next_node, node_item_queue, finish);
//             path_found = 1;
//             break ;
//         }
//         else
//         {
//             bfs_visit_mk2(next_node, node_item_queue, finish);
//             pop(node_item_queue);
//         }
//     }
//     if (path_found)
//         return (backtrack_mk2(finish, start));
//     return (NULL);
// }

// void    reset_graph(t_node **nodes)
// {
//     int n;

//     n = 0;
//     while (nodes[n] != NULL)
//     {
//         nodes[n]->used = 0;
//         nodes[n]->visited = 0;
//         nodes[n]->discovered = 0;
//         nodes[n]->discovered_via = NULL;
//         n = n + 1;
//     }
// }

// t_stack **get_greedy_paths(t_colony *colony)
// {
//     t_stack **paths;
//     int n;

//     reset_graph(colony->nodes);
//     paths = mallokill(sizeof(struct s_stack) * (colony->number_of_paths + 1));
//     n = 0;
//     while (n < colony->number_of_paths)
//     {
//         paths[n] = bfs(colony->start, colony->finish);
//         wipe_graph(colony->nodes);
//         n = n + 1;
//     }
//     paths[n] = NULL;
//     return (paths);
// }

// static int check_if_node_on_any_path(t_stack **paths, t_node_stack_item *node_stack_item)
// {
//     int n;

//     n = 0;
//     while (paths[n])
//     {
//         if (paths[n]->head->right->node == node_stack_item->node)
//             return (1);
//         n = n + 1;
//     }
//     return (0);
// }

// static int mark_all_used_trminal_nodes(t_colony *colony, int unmark)
// {
//     int n;
//     int nodes_marked;
//     t_node_stack_item *current_node_stack_item;

//     n = 0;
//     nodes_marked = 0;
//     if (unmark)
//     {
//         while (n < colony->finish->adjacent_nodes->number_of_items)
//         {
//         current_node_stack_item = get_nth_element(colony->finish->adjacent_nodes, n);
//         current_node_stack_item->node->used = 0;
//         n = n + 1;
//         }
//         return (0);
//     }
//     while (n < colony->finish->adjacent_nodes->number_of_items)
//     {
//         current_node_stack_item = get_nth_element(colony->finish->adjacent_nodes, n);
//         if (check_if_node_on_any_path(colony->paths, current_node_stack_item))
//         {
//             current_node_stack_item->node->used = 1;
//             nodes_marked = nodes_marked + 1;
//         }
//         n = n + 1;
//     }
//     return (nodes_marked);
// }

// static int min(int a, int b)
// {
//     return ((a < b) ? a : b);
// }

// t_stack **get_alternative_paths(t_colony *colony) //should work for n >= 2;
// {
//     t_stack **paths;
//     int n;
//     int number_of_paths;
//     int nodes_marked;
//     t_node_stack_item *current_node;

//     t_stack *current_path; //debug;

//     reset_graph(colony->nodes);
//     number_of_paths = min(colony->start->adjacent_nodes->number_of_items, colony->finish->adjacent_nodes->number_of_items);
//     paths = mallokill(sizeof(struct s_stack) * (number_of_paths + 1));
//     n = 0;
    
//     nodes_marked = mark_all_used_trminal_nodes(colony, 0);
//     while (n < number_of_paths - nodes_marked) //create new paths;
//     {
//         current_path = bfs(colony->start, colony->finish);
//         paths[n] = current_path;
//         n = n + 1;
//         wipe_graph(colony->nodes);
//     }
//     mark_all_used_trminal_nodes(colony, 1);
//     while (n < number_of_paths)
//     {
//         current_path = bfs(colony->start, colony->finish);
//         paths[n] = current_path;
//         n = n + 1;
//         wipe_graph(colony->nodes);
//     }
//     paths[n] = NULL;
//     return (paths);
// }