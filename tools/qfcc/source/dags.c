/*
	dags.c

	DAG representation of basic blocks

	Copyright (C) 2012 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2012/05/08

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#include <stdlib.h>
#include <ctype.h>

#include "qfalloca.h"

#include "QF/alloc.h"
#include "QF/dstring.h"
#include "QF/mathlib.h"
#include "QF/set.h"

#include "dags.h"
#include "diagnostic.h"
#include "flow.h"
#include "function.h"
#include "qfcc.h"
#include "statements.h"
#include "strpool.h"
#include "symtab.h"
#include "type.h"
#include "value.h"

static daglabel_t *free_labels;
static dagnode_t *free_nodes;
static dag_t *free_dags;

static daglabel_t *daglabel_chain;

static void
flush_daglabels (void)
{
	while (daglabel_chain) {
		operand_t  *op;

		if ((op = daglabel_chain->op)) {
			if (op->op_type == op_def)
				op->o.def->daglabel = 0;
			else if (op->op_type == op_temp)
				op->o.tempop.daglabel = 0;
			else if (op->op_type == op_value)
				op->o.value->daglabel = 0;
			else if (op->op_type == op_label)
				op->o.label->daglabel = 0;
			else
				internal_error (0, "unexpected operand type");
		}
		daglabel_chain = daglabel_chain->daglabel_chain;
	}
}

static dag_t *
new_dag (void)
{
	dag_t      *dag;
	ALLOC (256, dag_t, dags, dag);
	return dag;
}

static daglabel_t *
new_label (dag_t *dag)
{
	daglabel_t *label;
	ALLOC (256, daglabel_t, labels, label);
	label->daglabel_chain = daglabel_chain;
	daglabel_chain = label;
	label->number = dag->num_labels;
	dag->labels[dag->num_labels++] = label;
	return label;
}

static dagnode_t *
new_node (dag_t *dag)
{
	dagnode_t *node;
	ALLOC (256, dagnode_t, nodes, node);
	node->parents = set_new ();
	node->edges = set_new ();
	node->identifiers = set_new ();
	node->number = dag->num_nodes;
	set_add (dag->roots, node->number);	// nodes start out as root nodes
	dag->nodes[dag->num_nodes++] = node;
	return node;
}

const char *
daglabel_string (daglabel_t *label)
{
	static dstring_t *str;
	if ((label->opcode && label->op) || (!label->opcode && !label->op))
		return "bad label";
	if (label->opcode)
		return label->opcode;
	if (!str)
		str = dstring_new ();
	// operand_string might use quote_string, which returns a pointer to
	// a static variable.
	dstring_copystr (str, operand_string (label->op));
	return quote_string (str->str);
}

static daglabel_t *
opcode_label (dag_t *dag, const char *opcode, expr_t *expr)
{
	daglabel_t *label;

	label = new_label (dag);
	label->opcode = opcode;
	label->expr = expr;
	return label;
}

static daglabel_t *
operand_label (dag_t *dag, operand_t *op)
{
	def_t      *def = 0;
	ex_value_t *val = 0;
	daglabel_t *label;

	if (!op)
		return 0;

	if (op->op_type == op_temp) {
		while (op->o.tempop.alias)
			op = op->o.tempop.alias;
		if (op->o.tempop.daglabel)
			return op->o.tempop.daglabel;
		label = new_label (dag);
		label->op = op;
		op->o.tempop.daglabel = label;
	} else if (op->op_type == op_def) {
		def = op->o.def;
		if (def->daglabel)
			return def->daglabel;
		label = new_label (dag);
		label->op = op;
		def->daglabel = label;
	} else if (op->op_type == op_value) {
		val = op->o.value;
		if (val->daglabel)
			return val->daglabel;
		label = new_label (dag);
		label->op = op;
		val->daglabel = label;
	} else if (op->op_type == op_label) {
		if (op->o.label->daglabel)
			return op->o.label->daglabel;
		label = new_label (dag);
		label->op = op;
		op->o.label->daglabel = label;
	} else {
		internal_error (0, "unexpected operand type: %d", op->op_type);
	}
	return label;
}

static dagnode_t *
leaf_node (dag_t *dag, operand_t *op, expr_t *expr)
{
	daglabel_t *label;
	dagnode_t  *node;

	if (!op)
		return 0;
	node = new_node (dag);
	node->tl = op->type;
	label = operand_label (dag, op);
	label->dagnode = node;
	label->expr = expr;
	node->label = label;
	return node;
}

static dagnode_t *
dag_node (operand_t *op)
{
	def_t      *def;
	dagnode_t  *node = 0;

	if (!op)
		return 0;
	if (op->op_type == op_def) {
		def = op->o.def;
		if (def->daglabel)
			node = def->daglabel->dagnode;
	} else if (op->op_type == op_temp) {
		while (op->o.tempop.alias)
			op = op->o.tempop.alias;
		if (op->o.tempop.daglabel)
			node = op->o.tempop.daglabel->dagnode;
	} else if (op->op_type == op_value) {
		if (op->o.value->daglabel)
			node = op->o.value->daglabel->dagnode;
	} else if (op->op_type == op_label) {
		if (op->o.label->daglabel)
			node = op->o.label->daglabel->dagnode;
	}
	if (node && node->killed)
		node = 0;
	return node;
}

static void
dag_make_children (dag_t *dag, statement_t *s, operand_t *operands[4],
				   dagnode_t *children[3])
{
	int         i;

	flow_analyze_statement (s, 0, 0, 0, operands);
	for (i = 0; i < 3; i++) {
		if (!(children[i] = dag_node (operands[i + 1])))
			children[i] = leaf_node (dag, operands[i + 1], s->expr);
	}
}

static int
dagnode_deref_match (const dagnode_t *n, const daglabel_t *op,
				     dagnode_t *children[3])
{
	int         i;

	for (i = 0; i < 2; i++) {
		if (n->children[i] != children[i + 1])
			return 0;
	}
	return 1;
}

static int
dagnode_match (const dagnode_t *n, const daglabel_t *op,
			   dagnode_t *children[3])
{
	int         i;

	if (n->killed)
		return 0;
	if (!strcmp (op->opcode, ".")
		&& n->label->opcode && !strcmp (n->label->opcode, ".="))
		return dagnode_deref_match (n, op, children);
	if (n->label->opcode != op->opcode)
		return 0;
	for (i = 0; i < 3; i++) {
		if (n->children[i] != children[i])
			return 0;
	}
	return 1;
}

static dagnode_t *
dagnode_search (dag_t *dag, daglabel_t *op, dagnode_t *children[3])
{
	int         i;

	for (i = 0; i < dag->num_nodes; i++)
		if (dagnode_match (dag->nodes[i], op, children))
			return dag->nodes[i];
	return 0;
}

static void
dagnode_add_children (dag_t *dag, dagnode_t *n, operand_t *operands[4],
					  dagnode_t *children[3])
{
	int         i;

	for (i = 0; i < 3; i++) {
		dagnode_t  *child = children[i];
		if ((n->children[i] = child)) {
			n->types[i] = operands[i + 1]->type;
			set_remove (dag->roots, child->number);
			set_add (child->parents, n->number);
		}
	}
}

static int
dagnode_set_edges_visit (def_t *def, void *_node)
{
	dagnode_t  *node = (dagnode_t *) _node;
	daglabel_t *label;

	label = def->daglabel;
	if (label && label->dagnode) {
		set_add (node->edges, label->dagnode->number);
		label->live = 1;
	}
	return 0;
}

static int
dag_find_node (def_t *def, void *_daglabel)
{
	daglabel_t **daglabel = (daglabel_t **) _daglabel;
	if (def->daglabel && def->daglabel->dagnode) {
		*daglabel = def->daglabel;
		return def->daglabel->dagnode->number + 1;	// ensure never 0
	}
	return 0;
}

static void
dagnode_set_edges (dag_t *dag, dagnode_t *n)
{
	int         i;

	for (i = 0; i < 3; i++) {
		dagnode_t  *child = n->children[i];
		if (child && n != child)
			set_add (n->edges, child->number);
	}
	if (n->type == st_flow)
		return;
	for (i = 0; i < 3; i++) {
		dagnode_t  *child = n->children[i];
		if (child) {
			if (child->label->op) {
				dagnode_t  *node = child->label->dagnode;
				operand_t  *op = child->label->op;
				if (node != child && node != n)
					set_add (node->edges, n->number);
				if (op->op_type == op_value
					&& op->o.value->type == ev_pointer
					&& op->o.value->v.pointer.def)
					def_visit_all (op->o.value->v.pointer.def, 1,
								   dagnode_set_edges_visit, n);
				if (op->op_type == op_def
					&& (op->o.def->alias || op->o.def->alias_defs))
					def_visit_all (op->o.def, 1, dagnode_set_edges_visit, n);
			}
			if (n != child)
				set_add (n->edges, child->number);
		}
	}
	if (n->type == st_func) {
		const char *num_params = 0;
		int         first_param = 0;
		flowvar_t **flowvars = dag->flownode->graph->func->vars;

		if (!strncmp (n->label->opcode, "<RCALL", 6)) {
			num_params = n->label->opcode + 6;
			first_param = 2;
		} else if (!strncmp (n->label->opcode, "<CALL", 5)) {
			num_params = n->label->opcode + 5;
		} else if (!strcmp (n->label->opcode, "<RETURN>")) {
			daglabel_t *label = n->children[0]->label;
			if (!label->op) {
				set_iter_t *lab_i;
				for (lab_i = set_first (n->children[0]->identifiers); lab_i;
					 lab_i = set_next (lab_i)) {
					label = dag->labels[lab_i->element];
				}
			}
			label->live = 1;
		}
		if (num_params && isdigit (*num_params)) {
			for (i = first_param; i < *num_params - '0'; i++) {
				flowvar_t  *var = flowvars[i + 1];
				def_t      *param_def = var->op->o.def;
				daglabel_t *daglabel;
				int         param_node;

				// FIXME hopefully only the one alias :P
				param_node = def_visit_all (param_def, 0, dag_find_node,
											&daglabel);
				if (!param_node) {
					bug (0, ".param_%d not set for %s", i, n->label->opcode);
					continue;
				}
				daglabel->live = 1;
				set_add (n->edges, param_node - 1);
			}
		}
	}
}

static int
op_is_identifier (operand_t *op)
{
	if (op->op_type == op_label)
		return 0;
	if (op->op_type == op_value)
		return 0;
	if (op->op_type == op_temp)
		return 1;
	if (op->op_type != op_def)
		return 0;
	return 1;
}

static int
dag_kill_aliases_visit (def_t *def, void *_l)
{
	daglabel_t *l = (daglabel_t *) _l;
	dagnode_t  *node = l->dagnode;;
	daglabel_t *label;

	if (def == l->op->o.def)
		return 0;
	label = def->daglabel;
	if (label && label->dagnode) {
		set_add (node->edges, label->dagnode->number);
		set_remove (node->edges, node->number);
		label->dagnode->killed = 1;
	}
	return 0;
}

static void
dag_kill_aliases (daglabel_t *l)
{
	operand_t  *op = l->op;

	if (op->op_type == op_temp) {
	} else if (op->op_type == op_def) {
		if (op->o.def->alias || op->o.def->alias_defs)
			def_visit_all (op->o.def, 1, dag_kill_aliases_visit, l);
	} else {
		internal_error (0, "rvalue assignment?");
	}
}

static int
dag_live_aliases (def_t *def, void *_d)
{

	if (def != _d && def->daglabel)
		def->daglabel->live = 1;
	return 0;
}

static void
dagnode_attach_label (dagnode_t *n, daglabel_t *l)
{
	if (!l->op)
		internal_error (0, "attempt to attach operator label to dagnode "
						"identifiers");
	if (!op_is_identifier (l->op))
		internal_error (0, "attempt to attach non-identifer label to dagnode "
						"identifiers");
	if (l->dagnode) {
		dagnode_t  *node = l->dagnode;
		set_union (n->edges, node->parents);
		set_remove (n->edges, n->number);
		set_remove (node->identifiers, l->number);
	}
	l->live = 0;	// remove live forcing on assignment
	l->dagnode = n;
	set_add (n->identifiers, l->number);
	dag_kill_aliases (l);
	if (n->label->op) {
		// FIXME temps
		// FIXME it would be better to propogate the aliasing
		if (n->label->op->op_type == op_def
			&& (n->label->op->o.def->alias
				|| n->label->op->o.def->alias_defs))
			def_visit_all (n->label->op->o.def, 1, dag_live_aliases,
						   n->label->op->o.def);
	}
}

static int
dag_alias_live (def_t *def, void *_live_vars)
{
	set_t      *live_vars = (set_t *) _live_vars;
	if (!def->flowvar)
		return 0;
	return set_is_member (live_vars, def->flowvar->number);
}

static void
dag_remove_dead_vars (dag_t *dag, set_t *live_vars)
{
	int         i;

	for (i = 0; i < dag->num_labels; i++) {
		daglabel_t *l = dag->labels[i];
		flowvar_t  *var;

		if (!l->op || !l->dagnode)
			continue;
		if (l->live)		// label forced live (probably via an alias)
			continue;
		var = flow_get_var (l->op);
		if (!var)
			continue;
		if (set_is_member (dag->flownode->global_vars, var->number))
			continue;
		if (l->op->op_type == op_def
			&& def_visit_all (l->op->o.def, 1, dag_alias_live, live_vars))
			continue;
		if (!set_is_member (live_vars, var->number))
			set_remove (l->dagnode->identifiers, l->number);
	}
}

static void
dag_sort_visit (dag_t *dag, set_t *visited, int node_index, int *topo)
{
	set_iter_t *node_iter;
	dagnode_t  *node;

	if (set_is_member (visited, node_index))
		return;
	set_add (visited, node_index);
	node = dag->nodes[node_index];
	for (node_iter = set_first (node->edges); node_iter;
		 node_iter = set_next (node_iter))
		dag_sort_visit (dag, visited, node_iter->element, topo);
	node->topo = *topo;
	dag->topo[(*topo)++] = node_index;
}

static void
dag_sort_nodes (dag_t *dag)
{
	set_iter_t *root_iter;
	set_t      *visited = set_new ();
	int         topo = 0;
	int        *tmp_topo;

	if (dag->topo)
		free (dag->topo);
	dag->topo = alloca (dag->num_nodes * sizeof (int));
	for (root_iter = set_first (dag->roots); root_iter;
		 root_iter = set_next (root_iter))
		dag_sort_visit (dag, visited, root_iter->element, &topo);
	set_delete (visited);
	tmp_topo = malloc (topo * sizeof (int));
	memcpy (tmp_topo, dag->topo, topo * sizeof (int));
	dag->topo = tmp_topo;
	dag->num_topo = topo;
}

static void
dag_make_var_live (set_t *live_vars, operand_t *op)
{
	flowvar_t  *var = 0;

	if (op)
		var = flow_get_var (op);
	if (var)
		set_add (live_vars, var->number);
}

static void
dag_kill_nodes (dag_t *dag, dagnode_t *n)
{
	int         i;
	dagnode_t  *node;

	for (i = 0; i < dag->num_nodes; i++) {
		node = dag->nodes[i];
		if (node == n->children[1])	{
			// assume the pointer does not point to itself. This should be
			// reasonable because without casting, only a void pointer can
			// point to itself (the required type is recursive).
			continue;
		}
		if (node->label->op && !op_is_identifier (node->label->op)) {
			// While constants in the Quake VM can be changed via a pointer,
			// doing so would cause much more fun than a simple
			// mis-optimization would, so consider them safe from pointer
			// operations.
			continue;
		}
		node->killed = 1;
	}
	n->killed = 0;
}

dag_t *
dag_create (flownode_t *flownode)
{
	dag_t      *dag;
	sblock_t   *block = flownode->sblock;
	statement_t *s;
	dagnode_t **nodes;
	daglabel_t **labels;
	int         num_statements = 0;
	set_t      *live_vars = set_new ();

	flush_daglabels ();

	// count the number of statements so the number of nodes and labels can be
	// guessed
	for (s = block->statements; s; s = s->next)
		num_statements++;

	set_assign (live_vars, flownode->live_vars.out);

	dag = new_dag ();
	dag->flownode = flownode;
	// at most 4 per statement
	dag->nodes = alloca (num_statements * 4 * sizeof (dagnode_t));
	// at most 4 per statement, + return + params
	dag->labels = alloca (num_statements * (4 + 1 + 8) * sizeof (daglabel_t));
	dag->roots = set_new ();

	for (s = block->statements; s; s = s->next) {
		operand_t  *operands[4];
		dagnode_t  *n = 0, *children[3] = {0, 0, 0};
		daglabel_t *op, *lx;
		int         i;

		dag_make_children (dag, s, operands, children);
		if (s->type == st_flow)
			for (i = 0; i < 3; i++)
				if (children[i])
					dag_make_var_live (live_vars, operands[i]);
		op = opcode_label (dag, s->opcode, s->expr);
		n = children[0];
		if (s->type != st_assign
			&& !(n = dagnode_search (dag, op, children))) {
			n = new_node (dag);
			n->type = s->type;
			n->label = op;
			dagnode_add_children (dag, n, operands, children);
			dagnode_set_edges (dag, n);
		}
		lx = operand_label (dag, operands[0]);
		if (lx && lx->dagnode != n) {
			lx->expr = s->expr;
			dagnode_attach_label (n, lx);
		}
		if (n->type == st_ptrassign)
			dag_kill_nodes (dag, n);
	}

	nodes = malloc (dag->num_nodes * sizeof (dagnode_t *));
	memcpy (nodes, dag->nodes, dag->num_nodes * sizeof (dagnode_t *));
	dag->nodes = nodes;
	labels = malloc (dag->num_labels * sizeof (daglabel_t *));
	memcpy (labels, dag->labels, dag->num_labels * sizeof (daglabel_t *));
	dag->labels = labels;

	dag_remove_dead_vars (dag, live_vars);
	dag_sort_nodes (dag);
	set_delete (live_vars);
	return dag;
}

static statement_t *
build_statement (const char *opcode, operand_t **operands, expr_t *expr)
{
	int         i;
	operand_t  *op;
	statement_t *st = new_statement (st_none, opcode, expr);

	for (i = 0; i < 3; i++) {
		if ((op = operands[i])) {
			while (op->op_type == op_alias)
				op = op->o.alias;
			if (op->op_type == op_temp) {
				while (op->o.tempop.alias)
					op = op->o.tempop.alias;
				op->o.tempop.users++;
			}
		}
	}
	st->opa = operands[0];
	st->opb = operands[1];
	st->opc = operands[2];
	return st;
}
#if 0
static void
dag_calc_node_costs (dagnode_t *dagnode)
{
	int         i;

	for (i = 0; i < 3; i++)
		if (dagnode->children[i])
			dag_calc_node_costs (dagnode->children[i]);

	// if dagnode->a is null, then this is a leaf (as b and c are guaranted to
	// be null)
	if (!dagnode->children[0]) {
		// Because qc vm statements don't mix source and destination operands,
		// leaves never need temporary variables.
		dagnode->cost = 0;
	} else {
		int         different = 0;

		// a non-leaf is guaranteed to have a valid first child
		dagnode->cost = dagnode->children[0]->cost;
		for (i = 1; i < 3; i++) {
			if (dagnode->children[i]
				&& dagnode->children[i]->cost != dagnode->cost) {
				dagnode->cost = max (dagnode->cost,
									 dagnode->children[i]->cost);
				different = 1;
			}
		}
		if (!different)
			dagnode->cost += 1;
	}
}
#endif
static operand_t *
fix_op_type (operand_t *op, etype_t type)
{
	if (op && op->op_type != op_label && op->type != type)
		op = alias_operand (type, op);
	return op;
}

static operand_t *
make_operand (dag_t *dag, sblock_t *block, const dagnode_t *dagnode, int index)
{
	operand_t  *op;

	op = dagnode->children[index]->value;
	op = fix_op_type (op, dagnode->types[index]);
	return op;
}

static operand_t *
generate_moves (dag_t *dag, sblock_t *block, dagnode_t *dagnode)
{
	set_iter_t *var_iter;
	daglabel_t  *var;
	operand_t   *operands[3] = {0, 0, 0};
	statement_t *st;
	operand_t   *dst;

	operands[0] = make_operand (dag, block, dagnode, 0);
	operands[1] = make_operand (dag, block, dagnode, 1);
	dst = operands[0];
	for (var_iter = set_first (dagnode->identifiers); var_iter;
		 var_iter = set_next (var_iter)) {
		var = dag->labels[var_iter->element];
		operands[2] = var->op;
		dst = operands[2];
		st = build_statement ("<MOVE>", operands, var->expr);
		sblock_add_statement (block, st);
	}
	return dst;
}

static operand_t *
generate_moveps (dag_t *dag, sblock_t *block, dagnode_t *dagnode)
{
	set_iter_t *var_iter;
	daglabel_t  *var;
	operand_t   *operands[3] = {0, 0, 0};
	statement_t *st;
	operand_t   *dst = 0;

	operands[0] = make_operand (dag, block, dagnode, 0);
	operands[1] = make_operand (dag, block, dagnode, 1);
	for (var_iter = set_first (dagnode->identifiers); var_iter;
		 var_iter = set_next (var_iter)) {
		var = dag->labels[var_iter->element];
		dst = var->op;
		operands[2] = value_operand (new_pointer_val (0, 0, dst->o.def));
		st = build_statement ("<MOVEP>", operands, var->expr);
		sblock_add_statement (block, st);
	}
	return dst;
}

static operand_t *
generate_assignments (dag_t *dag, sblock_t *block, operand_t *src,
					  set_iter_t *var_iter, etype_t type)
{
	statement_t *st;
	operand_t   *dst = 0;
	operand_t   *operands[3] = {0, 0, 0};
	daglabel_t  *var;

	operands[0] = fix_op_type (src, type);
	for ( ; var_iter; var_iter = set_next (var_iter)) {
		var = dag->labels[var_iter->element];
		operands[1] = fix_op_type (var->op, type);
		if (!dst)
			dst = operands[1];

		st = build_statement ("=", operands, var->expr);
		sblock_add_statement (block, st);
	}
	return dst;
}

static void
dag_gencode (dag_t *dag, sblock_t *block, dagnode_t *dagnode)
{
	operand_t  *operands[3] = {0, 0, 0};
	operand_t  *dst = 0;
	statement_t *st;
	set_iter_t *var_iter;
	int         i;
	etype_t     type;

	switch (dagnode->type) {
		case st_none:
			if (!dagnode->label->op)
				internal_error (0, "non-leaf label in leaf node");
			dst = dagnode->label->op;
			if ((var_iter = set_first (dagnode->identifiers))) {
				type = dst->type;
				dst = generate_assignments (dag, block, dst, var_iter, type);
			}
			break;
		case st_expr:
			operands[0] = make_operand (dag, block, dagnode, 0);
			if (dagnode->children[1])
				operands[1] = make_operand (dag, block, dagnode, 1);
			type = low_level_type (get_type (dagnode->label->expr));
			if (!(var_iter = set_first (dagnode->identifiers))) {
				operands[2] = temp_operand (get_type (dagnode->label->expr));
			} else {
				daglabel_t *var = dag->labels[var_iter->element];

				operands[2] = fix_op_type (var->op, type);
				var_iter = set_next (var_iter);
			}
			dst = operands[2];
			st = build_statement (dagnode->label->opcode, operands,
								  dagnode->label->expr);
			sblock_add_statement (block, st);
			generate_assignments (dag, block, operands[2], var_iter, type);
			break;
		case st_assign:
			internal_error (0, "unexpected assignment node");
		case st_ptrassign:
			operands[0] = make_operand (dag, block, dagnode, 0);
			operands[1] = make_operand (dag, block, dagnode, 1);
			if (dagnode->children[2])
				operands[2] = make_operand (dag, block, dagnode, 2);
			st = build_statement (dagnode->label->opcode, operands,
								  dagnode->label->expr);
			sblock_add_statement (block, st);
			// the source location is suitable for use in other nodes
			dst = operands[0];
			break;
		case st_move:
			if (!strcmp (dagnode->label->opcode, "<MOVE>")) {
				dst = generate_moves (dag, block, dagnode);
				break;
			}
			if (!strcmp (dagnode->label->opcode, "<MOVEP>")
				&& !dagnode->children[2]) {
				dst = generate_moveps (dag, block, dagnode);
				break;
			}
			//fall through
		case st_state:
		case st_func:
			for (i = 0; i < 3; i++)
				if (dagnode->children[i])
					operands[i] = make_operand (dag, block, dagnode, i);
			st = build_statement (dagnode->label->opcode, operands,
								  dagnode->label->expr);
			sblock_add_statement (block, st);
			break;
		case st_flow:
			operands[0] = make_operand (dag, block, dagnode, 0);
			if (dagnode->children[1])
				operands[1] = make_operand (dag, block, dagnode, 1);
			st = build_statement (dagnode->label->opcode, operands,
								  dagnode->label->expr);
			sblock_add_statement (block, st);
			break;
	}
	dagnode->value = dst;
}

void
dag_remove_dead_nodes (dag_t *dag)
{
	int         added_root;
	set_iter_t *root_i, *child_i;
	dagnode_t  *node, *child;

	do {
		added_root = 0;
		for (root_i = set_first (dag->roots); root_i;
			 root_i = set_next (root_i)) {
			node = dag->nodes[root_i->element];
			// only st_none (leaf nodes), st_expr and st_move can become
			// dead nodes (no live vars attached).
			if (node->type != st_none && node->type != st_expr
				&& node->type != st_move)
				continue;
			if (!set_is_empty (node->identifiers))
				continue;
			// MOVEP with a variable destination pointer is never dead
			if (node->type == st_move && node->children[2])
				continue;
			set_remove (dag->roots, node->number);
			for (child_i = set_first (node->edges); child_i;
				 child_i = set_next (child_i)) {
				child = dag->nodes[child_i->element];
				if (!set_is_member (child->parents, node->number))
					continue;	// not really a child (dependency edge)
				set_remove (child->parents, node->number);
				if (set_is_empty (child->parents)) {
					set_add (dag->roots, child->number);
					added_root = 1;
				}
			}
		}
	} while (added_root);
	dag_sort_nodes (dag);
}

void
dag_generate (dag_t *dag, sblock_t *block)
{
	int         i;

	for (i = 0; i < dag->num_topo; i++)
		dag_gencode (dag, block, dag->nodes[dag->topo[i]]);
}
