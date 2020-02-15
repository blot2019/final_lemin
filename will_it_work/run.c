#include "ants.h"
#include "function_prototypes.h"
#include "lemin.h"

static void	initialize_stuff(t_colony *colony)
{
	colony->ants = spawn_all_ants(colony->start, colony->number_of_ants);
	colony->current_flow = get_flow_paths(colony, 0);
	// colony->current_flow = new_path_list(new_path(naive_bfs(colony->start, colony->finish, 0)));
	if (!colony->current_flow)
	{
		write(1, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(1);
	}
	initialize_the_flow_netowrk(colony, colony->current_flow);
	unplug_all_paths(colony->current_flow);
	colony->optimal_flow = copy_flow(colony->current_flow);
	saturate_and_distribute(colony, colony->optimal_flow, 1);
	colony->min_running_time = estimate_running_time_mk2(colony->optimal_flow);
	colony->current_running_time = colony->min_running_time;
	colony->m_prime = colony->m;
}

static void	get_solution_in_the_first_approximation(t_colony *colony)
{
	while (1)
    {
        reset_everything(colony);
        colony->residual_path =
		new_path(naive_bfs(colony->start, colony->finish, 2));
        wipe_graph(colony->nodes);
        if (!colony->residual_path)
			break ;
        superimpose(colony, colony->residual_path, 0);
		destroy_path_list(&colony->current_flow, 0);
        colony->current_flow = get_flow_paths(colony, 1);
        unplug_all_paths(colony->current_flow);
		//
		reset_paths(colony->current_flow);
		saturate_and_distribute(colony, colony->current_flow, 1);
		//
        colony->current_running_time =
		estimate_running_time_mk2(colony->current_flow);
        if (colony->current_running_time < colony->min_running_time)
			set_minimum(colony);
		else if (colony->current_running_time > colony->min_running_time)
		{
			destroy_path(&colony->residual_path);
			break ;
		}
        destroy_path(&colony->residual_path);
    }
}

static void	refine_solution_via_pivots(t_colony *colony)
{
	while (1)
    {
        reset_everything(colony);
		block_pivots(colony->active_pivots, 1);
        colony->residual_path =
		new_path(naive_bfs(colony->start, colony->finish, 2));
        wipe_graph(colony->nodes);
        if (!colony->residual_path)
			break ;
		plug_all_paths(colony->current_flow);
		compute_distance_superimpose(colony);
		unplug_all_paths(colony->current_flow);
		destroy_path_list(&colony->current_flow, 0);
        colony->current_flow = get_flow_paths(colony, 1);
        unplug_all_paths(colony->current_flow);
		//
		reset_paths(colony->current_flow);
		saturate_and_distribute(colony, colony->current_flow, 1);
		//
        colony->current_running_time =
		estimate_running_time_mk2(colony->current_flow);
        if (colony->current_running_time < colony->min_running_time)
			set_minimum(colony);
        destroy_path(&colony->residual_path);
    }
}

/*
check if the input implementation is still retarded;
what about move description length?
go through the assignment and the check list;

bus error on several arguments on stdin ?
reads stdin when ./lem-in [nonexistant file];
investigate extremely low move counts;

SEGFAULT:
./lem-in maps/invalid/empty_line_no_end_defined
./lem-in maps/invalid/empty_line_no_tube_to_end 

get_flow_paths() now has a cut-off for long paths; this is risky, run some tests;
test the pivot placing strategies;
play around with path initialization; 
superimpose_mk2() does not remove edges;
*/

int			main(int arg_count, char **arg_values)
{
	t_lemin		lemin;
	t_colony	*colony;

	if (!lets_read(&lemin, feel_map_file(arg_count, arg_values, &lemin)))
	{
		if (lemin.initial_text)
			free_for_all(&lemin);
		return (err_out());
	}
	print_initial_text(lemin.initial_text);
	colony = get_colony(lemin);
	initialize_stuff(colony);
	reset_paths(colony->optimal_flow);
    get_solution_in_the_first_approximation(colony);
	reset_flow_network(colony);
	initialize_the_flow_netowrk(colony, colony->optimal_flow);
	destroy_path_list(&colony->current_flow, 0);
	colony->current_flow = copy_flow(colony->optimal_flow);
	refine_solution_via_pivots(colony);
	//
	reset_paths(colony->optimal_flow);
	saturate_and_distribute(colony, colony->optimal_flow, 0);
	//
	block_pivots(colony->active_pivots, 0);
	block_pivots(colony->pivot_nodes, 0);
	go_forth(colony);
	if (lemin.print_path)
		display_all_paths(colony->optimal_flow);
	return (collect_garbage(lemin, colony));
}
